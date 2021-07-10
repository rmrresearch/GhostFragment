#include "../modules.hpp"
#include "ghostfragment/property_types/property_types.hpp"

namespace ghostfragment {

const auto mod_desc = R"(

)";

MODULE_CTOR(MBE) {
    description(mod_desc);
    satisfies_property_type<pt::energy>();

    add_submodule<pt::fragmented_mol>("Fragment generator");
    add_submodule<pt::ao_space>("AO Space assigner");
}

MODULE_RUN(MBE) {
    using ao_space_type;
    using frag_type;
    using ao_space_vec   = std::vector<ao_space_type>;
    using fragmented_aos = libchemist::FamilyOfSets<ao_space_vec>;
    using nmer_aos       = libchemist::FamilyOfSets<fragmented_aos>;

    const auto& [mol] = pt::energy::unwrap_inputs(inputs);

    const auto& [frags] = submods.run_as<pt::fragmented_mol>(mol);

    auto& ao_mod = submods.at("AO Space assigner");

    ao_space_vec aos;
    for(const auto& frag : frags) {
        const auto& [aos_i] = ao_mod.run_as<pt::ao_space>(frag2mol(frag));
        aos.push_back(aos_i);
    }

    const auto& [nmers] = submods.run_as<pt::nmer_maker>(frags);

    for(const auto& nmer_i : nmers) {
        // Union of basis sets
        // Make molecule
        // run
    }
}

} // namespace ghostfragment