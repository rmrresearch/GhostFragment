#include "drivers.hpp"
#include <ghostfragment/property_types/property_types.hpp>
#include <simde/energy/ao_energy.hpp>

namespace ghostfragment::drivers {

using my_pt         = simde::AOEnergy;
using frag_sys_pt   = pt::FragmentedSystem;
using nmer_sys_pt   = pt::NMerSystem;
using expression_pt = pt::Expression;

namespace {

const auto mod_desc = R"(
Fragment-Based Method Driver
----------------------------

)";
}

MODULE_CTOR(FragmentBasedMethod) {
    satisfies_property_type<my_pt>();
    description(mod_desc);

    add_submodule<frag_sys_pt>("Fragment Maker");
    add_submodule<nmer_sys_pt>("N-Mer Maker");
    add_submodule<expression_pt>("Expression generator");
    add_submodule<my_pt>("energy method");

    unsigned int m(1);
    add_input<unsigned int>("GMBE truncation order").set_default(m);
}

MODULE_RUN(FragmentBasedMethod) {
    // Step 0: Unpack input
    const auto& [aos, sys] = my_pt::unwrap_inputs(inputs);
    const auto n = inputs.at("GMBE truncation order").value<unsigned int>();

    // Stp 1: Create those fragments
    auto& frag_mod      = submods.at("Fragment Maker");
    const auto& [frags] = frag_mod.run_as<frag_sys_pt>(sys, aos.basis_set());

    // Step 2: Create those n-mers
    auto& nmer_mod      = submods.at("N-Mer Maker");
    const auto& [nmers] = nmer_mod.run_as<nmer_sys_pt>(frags, n);

    // Step 3: Create an expression
    auto& expr_mod     = submods.at("Expression generator");
    const auto& [expr] = expr_mod.run_as<expression_pt>(nmers);

    // Step 4: Run those terms

    // Get MPI conditions
    auto& rt  = get_runtime();
    auto size = rt.size();
    auto me   = rt.my_resource_set().mpi_rank();

    // Work out batch sizes
    auto extra      = expr.size() % size; // Remainder?
    auto batch_size = (expr.size() - extra) / size;
    auto my_begin   = me * batch_size;
    auto my_end     = my_begin + batch_size + (me == size - 1 ? extra : 0);
    std::cout << me << " " << my_begin << " " << my_end << std::endl;

    double e      = 0.0;
    auto& egy_mod = submods.at("energy method");
    for(std::size_t term_index = my_begin; term_index < my_end; ++term_index) {
        const auto& term_i = expr.at(term_index);
        const auto sys_i   = term_i.chemical_system();
        const chemist::orbital_space::AOSpace aos_i(term_i.ao_basis_set());
        const auto c_i        = term_i.coefficient();
        const auto [e_term_i] = egy_mod.run_as<my_pt>(aos_i, sys_i);
        e += c_i * e_term_i;
    }

    auto egys = rt.gather(e);
    e         = std::accumulate(egys.begin(), egys.end(), 0.0);
    auto rv   = results();
    return my_pt::wrap_results(rv, e);
}

} // namespace ghostfragment::drivers
