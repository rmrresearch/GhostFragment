#############################
GhostFragment Design Overview
#############################

The purpose of this page is to provide a quick, high-level overview of the 
design of GhostFragment and to point the interested reader to where they
may find more details.

**********************
What is GhostFragment?
**********************

GhostFragment is a software package designed to facilitate developing and
running fragment-based methods. It is now known that to use fragment-based
methods to accurately approximate traditional methods one must also account
for basis-set superposition error. GhostFragment also includes functionality to
correct for basis-set superposition error.

*****************************
Why do we need GhostFragment?
*****************************

There is no one-stop shop for fragment-based methods. Various electronic
structure packages have implementations of one or a few methods, but no
package readily provides acccess to a large number of methods. GhostFragment
seeks to change this while also facilitating rapid-prototyping of new methods.

****************************
GhostFragment Considerations
****************************

There are a number of considerations that went into the design of
GhostFragment, this section only summarizes the high-level, project-drivining
considerations. The design discussions for each component track the
component-level considerations.

Performance
   Fragment-based methods are meant to be an approximation to traditional
   electronic structure methods. Most traditional methods have highly-performant
   implementations. To be useful, fragment-based methods should improve the
   applicability of traditional methods. This can only be done if the 
   implementations of the fragment-based methods are accurate and also
   performant.

Accuracy
   Brought up in the performance consideration, general applicability of
   fragment-based methods requires the resulting approximation to be accurate.

***********************
Design of GhostFragment
***********************

Architecture Overview
=====================

Link to full discussion: :ref:`gf_architecture`.

.. _fig_gf_arch:

.. figure:: assets/overview.png
   :align: center

   GhostFragment is comprised of three components: the fragmenter, the engine,
   and the computer. See text for more details.

:numref:`fig_gf_arch` shows the high-level architecture of GhostFragment. The
unifying theme of all fragment-methods is that they strive to approximate one
large computation via a series of smaller computations. How one goes from the
inputs (the colliquial "molecule" and "basis set") of the large computation, 
to the inputs of each smaller computation is handled by the "Fragmenter"
component. Once we know the inputs for the smaller computations the "Engine"
is used to run the smaller computations. Finally, once we have the results
from each of each smaller computation we can assemble the target property for
the larger system.

