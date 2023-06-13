#include <ghostfragment/molecular_graph.hpp>

namespace ghostfragment {
namespace detail_ {

struct MolecularGraphPIMPL {
    using parent_type = MolecularGraph;

    using partitioned_mol_type = parent_type::partitioned_mol_type;

    using connectivity_type = parent_type::connectivity_type;

    MolecularGraphPIMPL(partitioned_mol_type ns, connectivity_type es) :
      m_nodes(std::move(ns)), m_edges(std::move(es)) {}

    bool operator==(const MolecularGraphPIMPL& rhs) const noexcept {
        return std::tie(m_nodes, m_edges) == std::tie(rhs.m_nodes, rhs.m_edges);
    }

    partitioned_mol_type m_nodes;

    connectivity_type m_edges;
};

namespace {

template<typename... Args>
auto make_pimpl(Args&&... args) {
    return std::make_unique<MolecularGraphPIMPL>(std::forward<Args>(args)...);
}

} // namespace

} // namespace detail_

//------------------------------------------------------------------------------
//                          CTors, Assignment, and DTors
//------------------------------------------------------------------------------

MolecularGraph::MolecularGraph() noexcept = default;

MolecularGraph::MolecularGraph(partitioned_mol_type nodes,
                               connectivity_type edges) :
  m_pimpl_(detail_::make_pimpl(std::move(nodes), std::move(edges))) {}

MolecularGraph::MolecularGraph(const MolecularGraph& other) :
  m_pimpl_(other.m_pimpl_ ? detail_::make_pimpl(*other.m_pimpl_) : nullptr) {}

MolecularGraph::MolecularGraph(MolecularGraph&& other) noexcept = default;

MolecularGraph& MolecularGraph::operator=(const MolecularGraph& rhs) {
    if(this == &rhs) return *this;
    return *this = std::move(MolecularGraph(rhs));
}

MolecularGraph& MolecularGraph::operator=(MolecularGraph&& rhs) noexcept =
  default;

MolecularGraph::~MolecularGraph() noexcept = default;

//------------------------------------------------------------------------------
//                             Accessors
//------------------------------------------------------------------------------

MolecularGraph::const_molecule_reference MolecularGraph::molecule() const {
    assert_pimpl_();
    return m_pimpl_->m_nodes.supersystem();
}

MolecularGraph::size_type MolecularGraph::nnodes() const noexcept {
    if(m_pimpl_) return m_pimpl_->m_nodes.size();
    return 0;
}

MolecularGraph::size_type MolecularGraph::nedges() const noexcept {
    if(m_pimpl_) return m_pimpl_->m_edges.bonds().size();
    return 0;
}

MolecularGraph::edge_list MolecularGraph::edges() const noexcept {
    if(m_pimpl_) return m_pimpl_->m_edges.bonds();
    return edge_list{};
}

MolecularGraph::const_node_reference MolecularGraph::node(size_type i) const {
    if(i < nnodes() && m_pimpl_) return m_pimpl_->m_nodes.at(i);
    throw std::out_of_range(
      std::to_string(i) + " is not in the range [0, nnodes) where nnodes == " +
      std::to_string(nnodes()));
}

//------------------------------------------------------------------------------
//                               Utilities
//------------------------------------------------------------------------------

bool MolecularGraph::operator==(const MolecularGraph& rhs) const noexcept {
    if(m_pimpl_ && rhs.m_pimpl_)
        return *m_pimpl_ == *rhs.m_pimpl_;
    else if(!m_pimpl_ && !rhs.m_pimpl_)
        return true;
    return false; // One has a PIMPL other doesn't
}

void MolecularGraph::print(std::ostream& os) const {
    if(!m_pimpl_) return;
    for(const auto& nuke_i : m_pimpl_->m_nodes) os << nuke_i << std::endl;
    os << m_pimpl_->m_edges;
}

//------------------------------------------------------------------------------
//                           Protected/Private Members
//------------------------------------------------------------------------------

void MolecularGraph::assert_pimpl_() const {
    if(m_pimpl_) return;

    throw std::runtime_error("Instance does not have a PIMPL. Was it default "
                             "constructed or moved from?");
}

} // namespace ghostfragment
