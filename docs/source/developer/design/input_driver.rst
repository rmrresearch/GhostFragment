.. _gf_input_driver_design:

######################################
Designing GhostFragment's Input Driver
######################################

.. |n| replace:: :math:`n``

*************************
What is the Input Driver?
*************************

:ref:`gf_design_overview` separated GhostFragment into two components: the 
input driver and the engine. The input driver is tasked with going from the
system we actually care about to the inputs needed to approximate that system.


***************************
Input Driver Considerations
***************************

.. _gf_input_driver_accuracy:

Accuracy
   :ref:`gf_design_overview` delegated the accuracy consideration to the input
   driver. At this level accuracy primarily entails:

   - Ensuring that the final set of sub-systems contains all important 
     interactions, *i.e.*, all important |n|-mers are present.
   - Being able to correct for BSSE.

.. _gf_input_driver_pt:

Supersystem property type
   :ref:`gf_design_overview` mentioned that the module implementing the 
   fragment-based method should satisfy the same property type as the module
   it is approximating. If the input driver is to be the first contact with the
   user's input, we can skip a pre-processing step by having the input driver's
   API be a subset of the target property type's inputs.

.. _gf_overlap:

Overlap
   We assume that the sub-systems we are working with are non-disjoint. We also
   note that many BSSE methods need to track which sub-systems contributed to 
   an overlap in order to work out what the basis set should be for that 
   overlap. Thus the process of working out overlaps must be tied to the
   exact approximation being made.

*******************
Input Driver Design
*******************

.. _fig_gf_input_driver:

.. figure:: assets/input_driver.png
   :align: center

   The architecture of the input driver component. 

:numref:`fig_gf_input_driver` shows the high-level design of the input driver.
Following from consideration :ref:`gf_input_driver_pt` the inputs to the driver
match those of the module it's meant to be approximating (here it's assumed to
be ``AOEnergy``, but a similar idea holds for gradients or frequencies). Inside
the input driver we decompose the process of preparing the sub-calculation 
inputs into two steps: the "Fragmented System Driver" prepares the chemical 
systems for the sub-calculations and the "Interaction Driver" uses those 
chemical systems to form the entire set of sub-calculations.

A full discussion of the "Fragmented System Driver" is derferred to 
:ref:`gf_fragmented_system_driver_design`. For now we note, the Fragmented
System Driver is responsible for taking an input ``ChemicalSystem`` and
producing the final set of sub-systems to use. These sub-systems are returned
as a ``FragmentedMoleculeSystem`` object and do NOT include the overlaps (as
dictated by consideration :ref:`gf_overlap`). Forming of |n|-mers will
happen in the fragmented system driver and thus satisfying consideration
:ref:`gf_input_driver_accuracy` will be partially addressed here.

The exact contents of the "Interaction Driver" will depend on the approximation
being used. If the user wants the traditional (G)MBE, the input will be the
set of n-mers which survived the screening process and the module will be
responsible for working out the overlaps (including their weights), capping the
overlaps, and assigning AOs to each |n|-mer and overlap. If the user instead
wants a BSSE-corrected interaction, then assigning the AOs becomes more 
complicated. A full discussion of the Interaction driver is beyond our current
scope.