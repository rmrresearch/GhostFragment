
.. _designing_the_caps_class:

########################
Designing the Caps Class
########################

**************
What are caps?
**************

********************
Why do we need caps?
********************

If we want to apply fragment-based methods to large covalently-bonded systems
then we will necessarily have to break covalent bonds. Since we will not want
to treat the resulting fragments as radicals, we will also need to cap the
fragments. As discussed in :ref:`fs_caps`, the decision has been made to store
the caps separately from the ``FragmentedMolecule``, hence not only do we need
to represent the caps, we need a new class to do it.

*******************
Caps considerations
*******************

.. _cc_new_atoms:

New atoms.
   Caps typically are placed in locations in space where no supersystem atom
   resides (they usually are not placed directly where the atom they replace
   resided). This means that the caps will have to be treated as new atoms
   since they are not actuall present in the target supersystem.

.. _cc_asymmetry:

Asymmetry.
   Given a severed bond A-B and caps C and D, C-B, and A-D will in general lead
   to different caps in the sense that C will not necessarily reside at the
   same spot as D. 

.. _cc_bond_memory:

Bond memory.
   It is important for a cap to remember what atom it replaced and what atom
   it is bonded to.

.. _cc_multiple_caps:

Multiple caps.
   It is possible that when forming a fragment we break more than one bond to
   the same atom. In other words, it may be that fragmenting results in an
   atom needing more than one cap.
