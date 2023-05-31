#pragma once
#include <ghostfragment/type/type.hpp>
#include <simde/simde.hpp>

namespace ghostfragment {
namespace detail_ {

/// Class which actually contains the MolecularGraph's state
class MolecularGraphPIMPL;

} // namespace detail_

/** @brief Provides a few of a molecular system as a graph in the mathematical
 *         sense.
 *
 *  For many computational chemistry applications it is useful to think of the
 *  molecular system as a graph where the atoms (or possibly connected sets of
 *  atoms; think a methyl group for example) are viewed as nodes and the edges
 *  are typicaly taken to be covalent bonds (some applications may also consider
 *  other types of bonds, notably hydrogen-bonds, as edges).
 *
 *  This class assumes that the atoms in the molecular system have been
 *  partitioned in some manner (notably "partitioned" requires that the sets of
 *  atoms are disjoint) and that the connectiivty of those partitions has been
 *  defined. In this case, the partitions are the nodes and the connectivity
 *  defines the edges.
 *
 */
class MolecularGraph {
public:
    /// Type used to input the partitioned molecular system
    using partitioned_mol_type = type::fragmented_molecule;

    /// Type used to model the Molecule
    using molecule_type = partitioned_mol_type::superset_type;

    /// Read-only reference to the Molecule
    using const_molecule_reference = const molecule_type&;

    /// Type of a node in the graph
    using node_type = partitioned_mol_type::value_type;

    /// Type of a read-only reference to a node in the graph
    using const_node_reference = const node_type&;

    /// Type used to input the connectivity
    using connectivity_type = simde::type::connectivity_table;

    /// Type used for edges of the graph
    using edge_type = connectivity_type::pair_type;

    /// Type used for a list of edges
    using edge_list = connectivity_type::bond_list_type;

    /// Type used for indexing and offsets
    using size_type = std::size_t;

    /** @brief Creates an empty MolecularGraph instance with no PIMPL.
     *
     *  Default instances behave like a graph with 0 nodes and 0 edges. At the
     *  moment the only way to give a defaulted instance state is to assign to
     *  it.
     *
     *  @throw None No throw guarantee.
     */
    MolecularGraph() noexcept;

    /** @brief Creates a MolecularGraph with the specified state.
     *
     *  This ctor assumes you have already partitioned a molecular system into
     *  subsets and established the connectivity of those subsets.
     *
     *  @param[in] nodes The partitioned molecular system, which will serve as
     *                   the nodes for the graph.
     *  @param[in] edges The connectivity information of the molecular system,
     *                   which defines the edges of the system.
     *
     */
    MolecularGraph(partitioned_mol_type nodes, connectivity_type edges);

    /** @brief Makes a deep copy of another instance.
     *
     *  @param[in] other The instance we are copying.
     *
     *  @throw std::bad_alloc if there is a problem copying @p other 's state.
     *                        Strong throw guarantee.
     */
    MolecularGraph(const MolecularGraph& other);

    /** @brief Creates a new instance by taking ownership of another instance's
     *         state.
     *
     *  @param[in,out] other The instance whose state is being taken. After this
     *                       operation @p other will behave as an empty graph.
     *
     *  @throw None No throw guarantee.
     */
    MolecularGraph(MolecularGraph&& other) noexcept;

    /** @brief Overwrites this instance's state with a deep copy of @p rhs's
     *         state.
     *
     *  @param[in] rhs The instance whose state is being copied.
     *
     *  @return The current instance after overwriting its state.
     *
     *  @throw std::bad_alloc if there is a problem copying @p rhs's state.
     *                        Strong throw guarantee.
     */
    MolecularGraph& operator=(const MolecularGraph& rhs);

    /** @brief Overwrite's this instance's state by taking ownership of another
     *         instance's state.
     *
     *  @param[in,out] rhs The instance whose state is being taken. After this
     *                       operation @p rhs will behave as an empty graph.
     *
     *  @return The current instance, after taking @p rhs 's state.
     *
     *  @throw None No throw guarantee.
     */
    MolecularGraph& operator=(MolecularGraph&& rhs) noexcept;

    /// Default, no-throw dtor
    ~MolecularGraph() noexcept;

    /** @brief Returns a read-only reference to the molecular system this graph
     *         models.
     *
     *  The MolecularGraph class ultimately models a molecular system as a
     *  mathematical graph. This function can be used to retrieve the molecular
     *  system this graph describes.
     *
     *  @return The molecular system the present graph describes.
     *
     *  @throw std::runtime_error if the instance does not contain a PIMPL.
     *                            Strong throw guarantee.
     */
    const_molecule_reference molecule() const;

    /** @brief Returns the number of nodes in the graph.
     *
     *  Each MolecularGraph is a representation of a molecular system. In this
     *  representation the atoms in the molecular system are partitioned into
     *  disjoint sets (either as one atom per set, or with multiple atoms in
     *  the same set). Regardless of how the atoms are partitioned, the sets
     *  resulting from the partitioning are the nodes of the graph. This
     *  function returns the number of nodes in the graph.
     *
     *  @return The number of nodes in the graph.
     *
     *  @throw None No throw guarantee.
     */
    size_type nnodes() const noexcept;

    /** @brief Returns the number of edges in the graph.
     *
     *  Each MolecularGraph is a representation of a molecular system. In this
     *  representation the atoms in the molecular system are partitioned into
     *  disjoint sets (either as one atom per set, or with multiple atoms in
     *  the same set). Regardless of how the atoms are partitioned, the sets
     *  resulting from the partitioning are the nodes of the graph. If an atom
     *  in one node is bonded to an atom in another node, then an edge exists
     *  between those nodes. This function returns the number of edges between
     *  nodes. It should be noted that this does NOT include in the count any
     *  bonds which are inside a node (this distinction is only relevant when a
     *  node contains multiple atoms).
     *
     *  @return The number of edges.
     *
     *  @throw None No throw guarantee.
     */
    size_type nedges() const noexcept;

    /** @brief Returns a list of the edges in the graph.
     *
     *  @return A random-access container filled with edges. Edges in the
     *          container are modeled as pairs of indices, where the indices
     *          map to nodes.
     *
     *  @throw None No throw guarantee.
     */
    edge_list edges() const noexcept;

    /** @brief Returns the requested node of the graph.
     *
     *  @param[in] i The index of the node.
     *
     *  @throw std::out_of_range if @p i is not in the range [0, nnodes()).
     *                           Strong throw guarantee.
     */
    const_node_reference node(size_type i) const;

    /** @brief Determines if this instance is equivalent to @p rhs.
     *
     *  Two MolecularGraph instances are equal if they partition the same
     *  molecular system in the same way, and if the same partitions are
     *  connected to each other.
     *
     *  @param[in] rhs The instance we are comparing to.
     *
     *  @return True if this instance is equivalent to @p rhs and false
     *          otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator==(const MolecularGraph& rhs) const noexcept;

    void print(std::ostream& os) const;

private:
    /// Throws if there is no PIMPL
    void assert_pimpl_() const;

    /// Type of the class holding the state
    using pimpl_type = detail_::MolecularGraphPIMPL;

    /// Type of a modifiable pointer to the state
    using pimpl_ptr = std::unique_ptr<pimpl_type>;

    /// The class's actual state.
    pimpl_ptr m_pimpl_;
};

inline std::ostream& operator<<(std::ostream& os, const MolecularGraph& g) {
    g.print(os);
    return os;
}

/** @brief Determines if two MolecularGraph instances are different.
 *
 *  @relates MolecularGraph
 *
 *  Two MolecularGraph instances are different if they do not compare equal. See
 *  MolecularGraph::operator== for the definition of equality.
 *
 *  @returns false if @p lhs and @p rhs are equal and true otherwise.
 *
 *  @throw None No throw guarantee.
 */
inline bool operator!=(const MolecularGraph& lhs, const MolecularGraph& rhs) {
    return !(lhs == rhs);
}

} // namespace ghostfragment
