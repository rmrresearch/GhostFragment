/*
 * Copyright 2024 GhostFragment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ghostfragment/nuclear_graph.hpp>

namespace ghostfragment {
namespace detail_ {

class NuclearGraphPIMPL {
public:
    using parent_type = NuclearGraph;

    using fragmented_nuclei = parent_type::fragmented_nuclei;

    using connectivity_type = parent_type::connectivity_type;

    NuclearGraphPIMPL(fragmented_nuclei ns, connectivity_type es) :
      m_nodes(std::move(ns)), m_edges(std::move(es)) {}

    bool operator==(const NuclearGraphPIMPL& rhs) const noexcept {
        return std::tie(m_nodes, m_edges) == std::tie(rhs.m_nodes, rhs.m_edges);
    }

    fragmented_nuclei m_nodes;

    connectivity_type m_edges;
};

namespace {

template<typename... Args>
auto make_pimpl(Args&&... args) {
    return std::make_unique<NuclearGraphPIMPL>(std::forward<Args>(args)...);
}

} // namespace

} // namespace detail_

//------------------------------------------------------------------------------
//                          CTors, Assignment, and DTors
//------------------------------------------------------------------------------

NuclearGraph::NuclearGraph() noexcept = default;

NuclearGraph::NuclearGraph(fragmented_nuclei nodes, connectivity_type edges) :
  m_pimpl_(detail_::make_pimpl(std::move(nodes), std::move(edges))) {}

NuclearGraph::NuclearGraph(const NuclearGraph& other) :
  m_pimpl_(other.m_pimpl_ ? detail_::make_pimpl(*other.m_pimpl_) : nullptr) {}

NuclearGraph::NuclearGraph(NuclearGraph&& other) noexcept = default;

NuclearGraph& NuclearGraph::operator=(const NuclearGraph& rhs) {
    if(this != &rhs) NuclearGraph(rhs).swap(*this);
    return *this;
}

NuclearGraph& NuclearGraph::operator=(NuclearGraph&& rhs) noexcept = default;

NuclearGraph::~NuclearGraph() noexcept = default;

//------------------------------------------------------------------------------
//                             Accessors
//------------------------------------------------------------------------------

NuclearGraph::const_nuclei_reference NuclearGraph::nuclei() const {
    assert_pimpl_();
    return m_pimpl_->m_nodes.supersystem();
}

NuclearGraph::size_type NuclearGraph::nodes_size() const noexcept {
    if(m_pimpl_) return m_pimpl_->m_nodes.size();
    return 0;
}

NuclearGraph::size_type NuclearGraph::edges_size() const noexcept {
    if(m_pimpl_) return m_pimpl_->m_edges.bonds().size();
    return 0;
}

NuclearGraph::edge_list NuclearGraph::edges() const noexcept {
    if(m_pimpl_) return m_pimpl_->m_edges.bonds();
    return edge_list{};
}

NuclearGraph::const_node_reference NuclearGraph::node(size_type i) const {
    if(i < nodes_size() && m_pimpl_) return m_pimpl_->m_nodes.at(i);
    throw std::out_of_range(
      std::to_string(i) + " is not in the range [0, nnodes) where nnodes == " +
      std::to_string(nodes_size()));
}

//------------------------------------------------------------------------------
//                               Utilities
//------------------------------------------------------------------------------

void NuclearGraph::swap(NuclearGraph& other) noexcept {
    m_pimpl_.swap(other.m_pimpl_);
}

bool NuclearGraph::operator==(const NuclearGraph& rhs) const noexcept {
    if(m_pimpl_ && rhs.m_pimpl_)
        return *m_pimpl_ == *rhs.m_pimpl_;
    else if(!m_pimpl_ && !rhs.m_pimpl_)
        return true;
    return false; // One has a PIMPL other doesn't
}

void NuclearGraph::print(std::ostream& os) const {
    if(!m_pimpl_) return;
    for(const auto& nuke_i : m_pimpl_->m_nodes) os << nuke_i << std::endl;
    os << m_pimpl_->m_edges;
}

//------------------------------------------------------------------------------
//                           Protected/Private Members
//------------------------------------------------------------------------------

void NuclearGraph::assert_pimpl_() const {
    if(m_pimpl_) return;

    throw std::runtime_error("Instance does not have a PIMPL. Was it default "
                             "constructed or moved from?");
}

} // namespace ghostfragment
