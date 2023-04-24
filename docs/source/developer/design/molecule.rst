######################################
Designing the FragmentedMolecule Class
######################################

.. |n| replace:: :math:`n`

******************************
What is a fragmented molecule?
******************************

In computational chemistry parlance, a molecule is the set of atoms we are
running a computation on. Sometimes we need to describe a "piece of a 
molecule." These pieces are fragments, and when we decompose a molecules into
a set of fragments, we say that the set forms a fragmented molecule if each
atom in the original molecule appears in at least one of the fragments. 

************************************
Why do we need fragmented molecules?
************************************

In computational chemistry there are a number of methods which require breaking
the molecule up into two or more pieces. While at some point many of these
methods will rely on the fact that the fragments are themselves perfectly good
molecules, most times the algorithm will also need to use the fact that the
fragments are pieces of a larger system. In turn, we need a way to represent
the fragments, while not forgetting the molecule the fragments come from.

***************************************
FragmentedMolecule Class Considerations
***************************************

.. _fs_molecule:

Molecule class.
   Chemist defines the ``Molecule`` class. A set of fragments should function
   like a series of views of the ``Molecule`` class. 

.. _fs_type_dispatch:

Type dispatch.   
   Modules recieving ``Molecule`` objects as input do not need to worry about
   fragments, whereas modules recieving ``FragmentedMolecule`` objects do need
   to worry about the fact that there is (in general) a set of fragments.
    
.. _fs_charge_mult:

Charge and multiplicity.
   The total charge and multiplicity of the original molecule must somehow be
   assigned to the fragments. In both cases, this is usually done by having
   the user assign the charge, or unpaired electrons, to one or more atoms.

.. _fs_non_disjoint:

Non-disjoint.
   While many initial fragment-based techniques relied on disjoint fragments,
   more modern techniques relax this requirement. The ``FragmentedMolecule``
   class needs to be able to handle multiple fragments, even if those fragments
   are non-disjoint.

Ignored Considerations
======================

.. |phi_set| replace:: :math:`\left\lbrace\phi_i\right\rbrace`

AO Basis Set.
   It is almost always assumed that if |phi_set| is the atomic basis set
   for atom :math:`i` in the :ref:`supersystem`, then |phi_set| is also the
   atomic basis set for atom :math:`i` in each fragment. In other words, the
   molecular basis set is fragmented in the same way as the :ref:`supersystem`.
   Thus if we know how to generate |phi_set| for any given atom, it is trivial
   to assemble the molecular basis set for a given fragment. This is one reason
   why we do not worry about storing the AO basis set in the 
   ``FragmentedMolecule`` class. Another reason is to parallel the un-fragmented
   hierarchy where ``Molecule`` and ``AOBasisSet`` are separate classes.

.. _fs_caps:

Caps.

   Full design discussion: :ref:`designing_the_caps_class`.

   When a large covalent molecule is fragmented, covalent bonds will usually be
   broken. There are several sub-considerations here:
   
   - For methods which go on to create |n|-mers, we want to take unions of
     uncapped fragments (if you take unions of capped fragments, you can end
     up with the cap and the atom it replaces in the same |n|-mer).
   - Computing overlaps is much more difficult for reasons similar to the first
     point, *i.e.*, if one fragment has a cap and another has the atom the cap
     replaces, then those fragments actually overlap.
   - If we ignore the caps at this stage, then the resulting fragments will be 
     radicals if used directly from the ``FragmentedMolecule`` class. 

   The first two points suggest it's better to treat the caps as a separate
   concern. The :ref:`fs_charge_mult` consideration suggests that since the
   user will need to set the charge/multiplicity for each fragment (usually by
   specifying the charged atom(s), or the atom(s) with unpaired electrons), the
   fact that the fragments in the ``FragmentedMolecule`` class  will be 
   radicals, is somewhat material since it doesn't actually factor in to
   assingning the charge/multiplicity.

Fields.
   While we ultimately want to fragment the chemical system, which includes
   the external fields, we want our fragmented chemical system class to
   parallel the non-fragmented versions. Since the chemical system contains
   a molecule, we want the fragmented chemical system to contain a fragmented
   molecule. The point is that fragmenting the fields is handled elsewhere. 