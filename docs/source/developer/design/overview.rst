.. _gf_design_overview:

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
running fragment-based methods.

*****************************
Why do we need GhostFragment?
*****************************

There is no one-stop shop for fragment-based methods. Various electronic
structure packages have implementations of one or a few methods, but no
package readily provides acccess to a large number of methods. GhostFragment
seeks to change this while also facilitating rapid-prototyping of new methods.

.. _gf_considerations:

****************************
GhostFragment Considerations
****************************

.. _gf_perfomance:

Performance
   Fragment-based methods are meant to be an approximation to traditional
   electronic structure methods. Most traditional methods have highly-performant
   implementations. To be useful, fragment-based methods should improve the
   applicability of traditional methods. This can only be done if the 
   implementations of the fragment-based methods are accurate and also
   performant.

.. _gf_accuracy:

Accuracy
   Brought up in the performance consideration, general applicability of
   fragment-based methods requires the resulting approximation to be accurate.
   We are specifically referring to having the fragment-based method faithfully
   replicate the traditional method it is approximating. The accuracy of the
   traditional method (compared to say experiment or the time-independent
   Schrodinger equation) is beyond our scope.

   - As a corrollary we note that it is now known that basis-set superposition
     error plays a role in the convergence of most fragment-based methods. Thus
     to implement accurate fragment-based methods we need to be able to correct
     for BSSE. 

.. _gf_generality:

Generality
   We want GhostFragment to be able to house as many fragment-based methods as
   possible. This requires having an overall architecture which is as applicable
   as possible.

   - A corollary is that we want to be able to interface with other electronic
     structure packages as well.

.. _gf_multi_layer:

Multi-layer
   A promising variation on a traditional fragment-based method is to treat
   part of the chemical system with one level of theory, and the rest with
   another (in theory this can easily be extended to more than two levels,
   but in practice is often limited to two). GhostFragment should be designed
   in a nestable fashion to support recursive invocations such as those
   necessary for a multi-layer approach.

.. _gf_supersystem_pt:

Supersystem property type
   The user actually cares about some property of the supersystem. The 
   fragment-based method should be a module which can be used as a drop-in
   replacement for the traditional calculation. For example, if we want to
   approximate calling a module satisfying the ``Energy`` property type with
   a fragment-based method, the module implementing the fragment-based method 
   should also satisfy the ``Energy`` property type.

***********************
Design of GhostFragment
***********************

The :ref:`gf_perfomance` and :ref:`gf_generality` considerations have led us to
implement GhostFragment as an NWChemEx plugin. More specifically, NWChemEx's
PluginPlay framework is designed to faciliate writing software which can easily
be customized and extended. This in turn makes it easier to modularize the
pieces of GhostFragment which are responsible for the major algorithms like:
fragmenting, capping, embedding, and screening. 

Generally speaking, we expect the algorithms which live in GhostFragment to be 
substantially cheaper than the electronic structure methods we will run on
each sub-calculation. Thus, our main performance consideration is expected to
be effeciently parallelizing the sub-computations, while also maximizing the
re-use of common information among sub-compuations (*e.g.*, common guesses
for the SCF). We assume that the electronic structure method we are calling is
peformant already.

The remaining considerations from :ref:`gf_considerations` fall under the
architecture of GhostFragment.

.. _fig_gf_arch:

.. figure:: assets/overview.png
   :align: center
   
   GhostFragment is comprised of two components: an input driver, and an
   engine.

:numref:`fig_gf_arch` shows the high-level architecture of GhostFragment. The
unifying theme of all fragment-methods is that they strive to approximate one
large computation via a series of smaller computations. How one maps the 
target system to sub-computations is handled by the "input driver"
component. Once we know the inputs for the smaller computations the "Engine"
is used to run the smaller computations. Given the results of the smaller
computations, GhostFragment can then approximate the property of interest for 
the larger system. While not shown explicitly the input to GhostFragment being
a chemical system and the result being an energy, is consistent with a module
satisfying the ``Energy`` property type, consistent with 
:ref:`gf_supersystem_pt`. Similar top-level designs could be made for any
property type taking a chemical system.

The "input driver" is discussed in more detail at :ref:`gf_input_driver_design`.
The "input driver" controls the creation of the inputs to the engine. The 
accuracy of a fragment-based method (relative to the method it is approximating)
is determined primarily by those inputs. Hence addressing the 
:ref:`gf_accuracy` consideration falls to the input driver. The final high-level
consideration, :ref:`gf_multi_layer`, can easily be addressed by nesting calls
to GhostFragment. In terms of architecture, the :ref:`gf_multi_layer`
consideration means GhostFragment needs to be written in a manner which is
ammenable to being nested. This is somewhat trivially satisfiable by making
GhostFragment's top-level a PluginPlay module, and by then relying on the fact
that PluginPlay modules can be nested.