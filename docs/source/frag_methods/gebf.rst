#############################################
Generalized Energy Based Fragmentation (GEBF)
#############################################

.. |zeta| ..replace:: :math:`\zeta`
.. |g| replace:: :math:t:`g`
.. |Fg| replace:: :math:t:`F_g`


With the original GEBF fragmentation method, :cite:t:`Li2007` presented a
fragmentation method. Using our terminology, this method is to:

#. Define pseudoatoms

   - In the orignal presentation no general criteria was specified; however, it
     is assumed that for molecular clusters pseudoatoms are individual 
     molecules.

#. For each pseudoatom, define a fragment which is the pseudoatom and all
   pseudoatoms close to it.

   - The original method uses two criteria for "close", one for covalent systems
     and one for molecular clusters.
   - For covalent systems two pseudoatoms are close if they are bonded either
     covalentally or with a hydrogen bond
   - For clusters pseudoatoms within some distance |zeta| are considered close
     (default is 3 Angstroms)

#. Cap fragments

   - Original method specified with hydrogen atoms.

#. Remove fragments which are subsets of other fragments

#. Determine intersections

Of note an algorithm for assigning multiplicities to intersections was also
presented namely:

- Assume largest fragment contains :math:`n` pseudoatoms.
- Look for a set of :math:`n-1` pseudoatoms which appears in more than one
  fragment. The multiplicity of this intersection is :math:`1-k`, where :math`k`
  is the number of fragments it appears in.
- Repeat the previous step for sets of :math`n-2, n-3, \ldots, 1` pseudoatoms 

The presented fragmentation method contained an additional step meant to include
some two-body interactions, namely dimers were considered if the distance
between them is less than a threshold. The description presented implies that
the fragments should be disjoint.