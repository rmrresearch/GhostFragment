#pragma once
#include <chemist/chemical_system/chemical_system.hpp>
#include <ghostfragment/molecular_graph.hpp>

namespace ghostfragment {

struct MolecularGraphTraits {
    using input_type  = chemist::ChemicalSystem;
    using result_type = ghostfragment::MolecularGraph;
};

/** @brief Property type for forming a molecular graph
 *
 *  There are a number of use cases in computational chemistry which lead to the
 *  molecular system being thought of as a mathematical graph. Modules which
 *  satisfy this property type are responsible for taking a Molecule and
 *  creating a molecular graph from it (essentially the module must break the
 *  Molecule into nodes and assign connectivity to the nodes).
 */
DECLARE_PROPERTY_TYPE(MolecularGraph);

PROPERTY_TYPE_INPUTS(MolecularGraph) {
    using chemical_system_type = typename MolecularGraphTraits::input_type;
    using input_type = chemist::ChemicalSystemView<const chemical_system_type>;

    return pluginplay::declare_input().add_field<input_type>("Chemical System");
}

PROPERTY_TYPE_RESULTS(MolecularGraph) {
    using result_type = MolecularGraphTraits::result_type;

    return pluginplay::declare_result().add_field<result_type>("Graph");
}

} // namespace ghostfragment
