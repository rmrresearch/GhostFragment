.. _gf_input_driver_design:

######################################
Designing GhostFragment's Input Driver
######################################

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
   driver.

.. _gf_input_driver_pt:

Supersystem property type
   :ref:`gf_design_overview` mentioned that the module implementing the 
   fragment-based method should satisfy the same property type as the module
   it is approximating. If the input driver is to be the first contact with the
   user's input, we can skip a pre-processing step by having the input driver's
   API be a subset of the target property type's inputs.