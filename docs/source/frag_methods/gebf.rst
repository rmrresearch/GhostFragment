#############################################
Generalized Energy Based Fragmentation (GEBF)
#############################################

.. |zeta| ..replace:: :math:`\zeta`
.. |g| replace:: :math:t:`g`
.. |Fg| replace:: :math:t:`F_g`

1. Create groups
2. Determine bonds between groups
3. For group |g|, fragment |Fg| is |g| plus all groups bonded to |g|
4. Cap |Fg|
5. Embed |Fg| in point charges



.. note::
 
   In the original presentation what we call groups are called "fragments". What
   we call fragments are called "primitivie subsystems". And what we call
   intersections are called "derived subsystems".

*********************
Original Presentation
*********************

This section presents the GEBF fragmentation method as it was originally
described in :cite:t:`Li2007`.

The first step is still to create groups (they are called fragments in the 
original presentation). Li *et al.* specified that for molecular 

1. Create groups
   - For molecualr clusters 
2. Cap each fragment from 1 with surrounding fragments(called primitive subsystems)
   - Fragments are considered bonded if there is a covalent or hydrogen bond
     between them
   - For clusters all molecules within some distance |zeta| are considered part
     of a primitive subsystem (default is 3 Angstroms)
3. Add hydrogens to severed bonds
4. Remove primitive subsystems which are subsets of other subsystems
5. Create derivative subsystems.
   - Assume largest primitive subsystem contains n fragments
   - Look for sets of n-1 fragments which appear in more than one primitive
     subsystem. The coefficient of such a system is (1-k) where k is the number
     of systems it appears in.
   - Repeat for sets of n-2, n-3, ..., 1 fragments which appear in more than one
     primative subsystem
6. Add in some dimers based on distance

