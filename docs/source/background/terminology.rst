#########################################
Terminology Used Throughout GhostFragment
#########################################

.. |n| replace:: :math`n`

There are a lot of existing fragment-based methods. Many of these methods have
coined their own terms for similar concepts. In order to provide a unified
description of these methods we have settled on the following terminology.

dimer
   A subsystem made by taking the union of two monomers

fragment
   The inputs to the MBE and GMBE. Fragments are sets of pseudoatoms.

monomer
   Same as fragment, but preferred when subsystems are being distinguished by
   numerical prefix. *i.e.*, we use monomer, and not fragment, when we are also
   talking about dimers, trimers, *etc.*  

n-mer
   The generalization of monomer, dimer, *etc.* to the union of |n| fragments.

pseudoatom
   In fragmenting the supersystem there are some "most fundamental" units, 
   *i.e.* units which themselves are never fragmented. In the most extreme limit 
   these fundamental units are the individual atoms; however, in most 
   fragmentation algorithms the fundamental units involve several atoms. For 
   example, in fragmenting a molecular cluster a popular and obvious choice is 
   to take the molecules as the fundamental units. Regardless of their 
   composition, the most fundamental units of the fragmentation algorithm are 
   termed "pseudoatoms."

supersystem
   This is the system whose properties are actually of interest. Its properties
   are computed by fragmenting it into subsystems.

************************
Graph Theory Terminology
************************

Particularly when describing fragmentation algorithms we often treat the
supersystem as a mathematical graph. 

edge
   These are the connections between two nodes in the graph. They will usually
   correspond to covalent bonds, but exactly what defines an edge is usually
   left up to the user.
degree
   This is the number of edges a node has. 
leaf
   This is a node with degree 1.
node
   In the context of a molecular graph nodes are typically pseudoatoms.