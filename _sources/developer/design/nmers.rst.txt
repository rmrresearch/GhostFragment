.. _gf_nmer_driver_design:

#########################
Designing the NMer Driver
#########################

.. |n| replace:: :math:`n`

*******************
What is an |n|-mer?
*******************

If we think of each fragment as a set of atoms, then an |n|-mer, simply put
is the set of atoms which results from taking the union of |n| fragments. The
driver is responsible for wrapping the process of going from an input
``ChemicalSystem`` to the final set of ``FragmentedNuclei``.


************************
Why do we need |n|-mers?
************************

Fragments usually consist of spatially local atoms. Simply summing the energies
of the fragments would neglect the many-body interactions and would be a poor
approximation. To better approximate the energy we need to account for the
significant many-body interactions. One way to do this is through the so-called
supermolecular method, namely to compute the |n|-body interaction of |n|
fragments one takes the union of the |n| fragments, computes the energy, and
then subtracts out the energies of the fragments, the two-body interactions,
the three-body interactions, ..., and the :math:`(n-1)`-body interactions.
Thus we need |n|-mers to compute |n|-body interactions via the supermolecular
method.

*************************
NMerDriver Considerations
*************************

.. _nd_frags:

Fragments.
   The entire concept of an |n|-mer is predicated on the existence of the
   fragments. Depending on the application of the |n|-mers, we may need to
   record which fragments formed the |n|-mer. 


.. _nd_screening:

Screening.
   If we always wanted to iterate over the entire set of |n|-mers we could
   use a generator (or something similar) to create the |n|-mers as needed,
   *i.e.*, there would be no need to store the fragments. In practice, the
   reason we need the NMers class is because we only want to store the
   |n|-mers which passed screening. Screening based on energy (or distance)
   requires us to have capped |n|-mers.

.. _nd_output:

FragmentedNuclei output
   While the fragments are screened as ``ChemicalSystem`` objects, it is
   actually the ``Nuclei`` of the ``ChemicalSystem`` objects which are combined
   to form the |n|-mers, not the ``Molecule`` objects. Thus the output should 
   be another ``FragmentedNuclei`` object.

   - Trying to take unions of molecules also requires us to take unions of
     the electrons too. In practice, the number of electrons in an |n|-mer is
     also just dictated by the identity of the nuclei in the |n|-mer.
   - Assigning charges/multiplicity from the fragments is actually more
     difficult than assinging them from the overall ``ChemicalSystem``. In
     the former one must determine how to combine the charges and multiplicities
     of the fragments, whereas the latter amounts to assinging the charge,
     unpaired electrons to atoms in the overall system.
   - It is also worth noting that if we tried to take unions of capped fragments
     we would have to determine if the atom the cap is replacing also appears
     in the fragment. This is just easier to do by reassigning caps after
     establishing the |n|-mers.

     - The set of caps needed for the |n|-mers is a subset of those needed
       for the fragments.

*****************
NMerDriver Design
*****************

.. _fig_gf_nmer_driver:

.. figure:: assets/nmer_driver.png
   :align: center

   The architecture of the nmer driver component. 