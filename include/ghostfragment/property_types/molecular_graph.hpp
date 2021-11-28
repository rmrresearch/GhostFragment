#pragma once
#include "ghostfragment/molecular_graph.hpp"
#include "ghostfragment/types.hpp"

namespace ghostfragment::pt {

struct MolecularGraphTraits {
    using input_type  = type::fragmented_molecule;
    using result_type = ghostfragment::MolecularGraph;
};

/** @brief Property type for forming a molecular graph
 *
 *  There are a number of use cases in computational chemistry which lead to the
 *  molecular system being thought of as a mathematical graph. Modules which
 *  satisfy this property type are responsible for taking a fragmented molecule
 *  (fragments define the nodes of the graph) and creating a molecular graph
 *  from it (essentially the module must assign connectivity to the nodes).
 */
DECLARE_PROPERTY_TYPE(MolecularGraph);

PROPERTY_TYPE_INPUTS(MolecularGraph) {
    using input_type = MolecularGraphTraits::input_type;

    return pluginplay::declare_input().add_field<input_type>("Pseudoatoms");
}

PROPERTY_TYPE_RESULTS(MolecularGraph) {
    using result_type = MolecularGraphTraits::result_type;

    return pluginplay::declare_result().add_field<result_type>("Graph");
}

} // namespace ghostfragment::pt