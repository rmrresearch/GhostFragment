#########################################
Terminology Used Throughout GhostFragment
#########################################

.. |n| replace:: :math`n`

There are a lot of existing fragment-based methods. Many of these methods have
coined their own terms for similar concepts. In order to provide a unified
description of these methods we have settled on the following terminology.

.. _capping:

capping
   When fragmenting one usually tries to split the system across non-covalent
   interactions; however, if one is to divide a large covalently bonded system
   into fragments it becomes necessary to "break" covalent bonds (a covalent
   bond is said to be broken when only one of the atoms involved in the bond 
   appear in a fragment). When a fragment contains a broken bond, running the
   computation as is will usually result in an unphysical electronic state
   (the fragment will have a different spin state than the overall system).
   Capping methods ensure the fragment has the same spin state as the parent
   system (usually by adding a hydrogen atom).

.. _dimer:

dimer(s)
   A subsystem made by taking the union of two monomers

.. _fragment:

fragment(x)
   The inputs to the MBE and GMBE. Fragments are sets of pseudoatoms.

.. _monomer:

monomer(s)
   Same as fragment, but preferred when subsystems are being distinguished by
   numerical prefix. *i.e.*, we use monomer, and not fragment, when we are also
   talking about dimers, trimers, *etc.*  

multi-layer
   Refers to when the final fragment-based method is put together in an ONIOM-
   like manner. The layers can be different theories, different fragmentations, 
   etc. 

.. _nmer:

n-mer(s)
   The generalization of monomer, dimer, *etc.* to the union of |n| fragments.

.. _pseudoatom:

pseudoatom(s)
   In fragmenting the supersystem there are some "most fundamental" units, 
   *i.e.* units which themselves are never fragmented. In the most extreme limit 
   these fundamental units are the individual atoms; however, in most 
   fragmentation algorithms the fundamental units involve several atoms. For 
   example, in fragmenting a molecular cluster a popular and obvious choice is 
   to take the molecules as the fundamental units. Regardless of their 
   composition, the most fundamental units of the fragmentation algorithm are 
   termed "pseudoatoms."

.. _supersystem:

supersystem
   This is the system whose properties are actually of interest. Its properties
   are computed by fragmenting it into subsystems.

************************
Graph Theory Terminology
************************

Particularly when describing fragmentation algorithms we often treat the
supersystem as a mathematical graph. 

.. _edge:

edge
   These are the connections between two nodes in the graph. They will usually
   correspond to covalent bonds, but exactly what defines an edge is usually
   left up to the user.

.. _degree:

degree
   This is the number of edges a node has. 

.. _leaf:

leaf
   This is a node with degree 1.

.. _node:

node
   In the context of a molecular graph nodes are typically pseudoatoms.