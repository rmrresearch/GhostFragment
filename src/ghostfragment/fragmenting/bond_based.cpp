#include "fragmenting.hpp"
#include <ghostfragment/property_types/property_types.hpp>
#include <simde/simde.hpp>

namespace ghostfragment::fragmenting {

// This function takes a MolecularGraph, a node and a parameter nbonds and returns
// all nuclei that are within nbonds bonds of the given node. Uses a stack nodeStack
// to perform a depth-first search, where the elements of nodeStack are pairs
// containing the indices of nodes and their distance from the root node. The function
// loops over the stack, adding the nodes with distance <= nbonds to a set.

<<<<<<< HEAD
std::set<size_t> frag_nodes(const ghostfragment::MolecularGraph graph,
std::size_t root_node, std::size_t nbonds) {
   const auto& bonds = graph.edges();
   std::set<std::size_t> visited;
   std::stack<std::pair<std::size_t, std::size_t>> nodeStack;

   nodeStack.push(std::make_pair(root_node, 0));

   while (!nodeStack.empty()) {
       std::size_t currentNode = nodeStack.top().first;
       std::size_t currentDistance = nodeStack.top().second;
       nodeStack.pop();

       if (visited.count(currentNode) > 0) {
           continue;  // Skip if node has already been counted
       }

       visited.insert(currentNode);

       if (currentDistance >= nbonds) {
=======
std::set<size_t> frag_nodes(const ghostfragment::MolecularGraph graph, std::size_t root_node, std::size_t nbonds) {
   const auto& bonds = graph.edges();
   std::unordered_map<std::size_t, std::size_t> distance;
   std::stack<std::pair<std::size_t, std::size_t>> node_stack;

   node_stack.push(std::make_pair(root_node, 0));
   distance[root_node] = 0;

   while (!node_stack.empty()) {
       std::size_t current_node = node_stack.top().first;
       std::size_t current_distance = node_stack.top().second;
       node_stack.pop();

       if (current_distance >= nbonds) {
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f
           continue;  // Skip if node is beyond distance nbonds
       }

       for (auto bond : bonds) {
<<<<<<< HEAD
           if(bond[0] == currentNode) {  // If first index is current node
               if (visited.count(bond[1]) == 0) {  // If bonded node is new
                   nodeStack.push(std::make_pair(bond[1], currentDistance + 1));
               }
           }

           if(bond[1] == currentNode) {  // If second index is current node
               if (visited.count(bond[0]) == 0) {  // If bonded node is new
                   nodeStack.push(std::make_pair(bond[0], currentDistance + 1));
=======
           if (bond[0] == current_node) {  // If first index is current node
               std::size_t next_node = bond[1];
               if (distance.count(next_node) == 0 || distance[next_node] > current_distance + 1) {
                   distance[next_node] = current_distance + 1;
                   node_stack.push(std::make_pair(next_node, current_distance + 1));
               }
           }

           if (bond[1] == current_node) {  // If second index is current node
               std::size_t next_node = bond[0];
               if (distance.count(next_node) == 0 || distance[next_node] > current_distance + 1) {
                   distance[next_node] = current_distance + 1;
                   node_stack.push(std::make_pair(next_node, current_distance + 1));
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f
               }
           }
       }
   }

   // Convert nodes (which could consist of multiple nuclei) to their constituent nuclei
<<<<<<< HEAD
   std::set<std::size_t> nuclei; 
   for(std::size_t i : visited) {
        for(std::size_t j : graph.node(i)) {
            if(nuclei.count(j) == 0) {
=======
   std::set<std::size_t> nuclei;
   for (const auto& entry : distance) {
        std::size_t node = entry.first;
        for (std::size_t j : graph.node(node)) {
            if (nuclei.count(j) == 0) {
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f
                nuclei.insert(j);
            }
        }
   }
<<<<<<< HEAD
   return(nuclei);
=======
   return nuclei;
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f
}

// This function takes a MolecularGraph and a parameter nbonds, and loops
// over all nodes in MolecularGraph, calling frag_nodes for each. If the set
// of indices is novel, then it is added to a vector of sets to be returned.

std::vector<std::set<std::size_t>> graph_to_frags(const ghostfragment::MolecularGraph graph,
std::size_t nbonds) {
   std::vector<std::set<std::size_t>> indices;  // vector of sets of indices denoting fragments
   std::set<std::size_t> current_frag;
<<<<<<< HEAD
   std::size_t duplicates = 0;
=======
   std::size_t supersets = 0;
   std::size_t subsets = 0;
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f

   for(std::size_t i = 0; i < graph.nnodes(); ++i) {

       current_frag = frag_nodes(graph, i, nbonds);
<<<<<<< HEAD

       for(std::size_t j = 0; j < indices.size(); ++j) {
           if(indices[j] == current_frag) {
               duplicates ++;
           }
       }

       if(duplicates == 0) {
           indices.push_back(current_frag);
       }

       duplicates = 0;
=======
       std::size_t j = 0;
       while(j < indices.size()) {
           if(std::includes(indices[j].begin(), indices[j].end(), current_frag.begin(), current_frag.end())) {
               supersets ++;
           }
           if(std::includes(current_frag.begin(), current_frag.end(), indices[j].begin(), indices[j].end())) {
               indices.erase(indices.begin()+j);
               j --;
               subsets ++;
           }
           j ++;
       }

       if(supersets == 0) {
           indices.push_back(current_frag);
       } else if(subsets > 0) {
           indices.push_back(current_frag);
       }

       supersets = 0;
       subsets = 0;
>>>>>>> f063bb6c46436fa7237f5de120bffa099b777b9f
   }
   return(indices);
}

const auto mod_desc = R"(
Bond-Based Fragmenter
-------------------

This module takes as input a MolecularGraph representation of the molecular system
and an integer parameter nbonds, and outputs a FragmentedNuclei object. The fragments
are generated by looping over the nodes in MolecularGraph and assembling all nodes a
distance of nbonds or less away from the node in question into a fragment. Each distinct
fragment will be output exactly once (i.e. no repeats).
)";

using my_pt     = ghostfragment::pt::MolecularGraphToFragments;
using graph_pt  = ghostfragment::pt::MolecularGraph;

MODULE_CTOR(BondBased) {
    description(mod_desc);
    satisfies_property_type<my_pt>();

    add_input<std::size_t>("nbonds")
    .set_description("bond width of fragment")
    .set_default(std::size_t(0));
}

MODULE_RUN(BondBased) {
   using result_type   = pt::MolecularGraphToFragmentsTraits::fragment_type;
   using subset_type   = typename result_type::value_type;
   using input_type    = pt::MolecularGraphToFragmentsTraits::graph_type;
   using molecule_type = typename input_type::molecule_type;

   const auto& [graph] = my_pt::unwrap_inputs(inputs);
   const auto& nbonds = inputs.at("nbonds").value<std::size_t>();

    if(graph.nnodes() == 0) { // Handles trivial mol edge-case
        auto rv = results();
        return my_pt::wrap_results(rv, result_type{molecule_type{}});
    }

   result_type frags(graph.molecule()); // Will be the fragments

   const auto& indices = graph_to_frags(graph, nbonds);

   for(std::size_t i = 0; i < indices.size(); ++i) {
       frags.add_fragment(indices[i].begin(), indices[i].end());
   }

   auto rv = results();
   return my_pt::wrap_results(rv, frags);
}

} // namespace ghostfragment::partitioned