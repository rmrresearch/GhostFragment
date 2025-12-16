.. Copyright 2024 GhostFragment
..
.. Licensed under the Apache License, Version 2.0 (the "License");
.. you may not use this file except in compliance with the License.
.. You may obtain a copy of the License at
..
.. http://www.apache.org/licenses/LICENSE-2.0
..
.. Unless required by applicable law or agreed to in writing, software
.. distributed under the License is distributed on an "AS IS" BASIS,
.. WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
.. See the License for the specific language governing permissions and
.. limitations under the License.

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

Fragment-based methods offer a promising mechanism for extending electronic
structure calculations to larger systems. The "trick" behind fragment-based
methods is that they break the large, intractable, calculation into a series of 
smaller, more tractable, calculations. Furthermore, these smaller calculations
are independent and can easily be run in parallel.

GhostFragment will provide:

- Algorithms for fragmenting chemical systems.
- Algorithms for capping fragments (i.e., treating broken bonds).
- Algorithms for embedding fragments in an approximate representation of the
  rest of the system (e.g., point charges, frozen densities, etc.).
- Algorithms for screening/approximating calculations with small contributions.
- Drivers for creating the calculations needed for a variety of fragment-based
  methods.
- Drivers for running the calculations.
- Drivers for assembling the results.  

Unlike other options GhostFragment will:

- Be modular, algorithms can be swapped out easily (even at runtime).
- Decoupled from any specific electronic structure package.
  - Admittedly the reusable infrastructure GhostFragment is built on is the
    same software stack as NWChemEx, but GhostFragment is not tied to NWChemEx.
- Be extensible, new algorithms and methods can be rapidly prototyped.

*****************************
Why do we need GhostFragment?
*****************************

Since fragment-based methods are naturally implemented by scripting over
existing electronic structure packages, many developers maintain bespoke 
software solutions for their methods. Unfortunately, many of these solutions
do not integrate well into other software systems. Similarly, various electronic
structure packages provide implementations of some fragment-based methods, but 
do so by coupling the method to the rest of the electronic structure package.
Again, this makes it difficult to integrate the fragment-based method into other
software systems.

At present, the space of open-source, modular fragment-based libraries is quite
limited. GhostFragment aims to fill this gap.

.. _gf_considerations:

****************************
GhostFragment Considerations
****************************

The software design of GhostFragment is driven by a few key considerations:

.. _gf_modularity:

Modularity
==========

**Consideration**: Fragment-based methods are made up of a variety of 
algorithms. For example, one algorithm is responsible for fragmenting the 
system, another for capping broken bonds, another for embedding the fragments, 
and so on. Different fragment-based methods differ in which algorithms they use 
for each step. To facilitate rapid prototyping of new fragment-based methods, 
GhostFragment should be modular such that different algorithms can be swapped 
out easily.

**Solution**: The "Modularity" consideration has led us to implement 
GhostFragment as an plugin compatible with the 
`PluginPlay framework <https://nwchemex.github.io/PluginPlay/>`__. PluginPlay 
is designed to facilitate writing modular scientific software. In particular,
PluginPlay makes it easy to modify the control flow of the program, even at
runtime, thereby allowing the caller to inject additional functionality. The
core components of a fragment-based method are implemented as PluginPlay
modules and assembled at runtime via the usual PluginPlay mechanisms.

.. _gf_generality:

Generality
==========

**Consideration**: Fragment-based methods are often thought of as "going over
top of" traditional electronic structure methods. In other words, the fragment-
based method drives calls to the traditional method. Given that traditional
electronic structure methods are implemented in a variety of software packages,
we want to avoid coupling GhostFragment to any specific electronic structure
package. This will make GhostFragment easier to adopt by other potential users.

**Solution**: The "Generality" consideration is also partially addressed by
PluginPlay. Plugins in PluginPlay do not explicitly couple to module 
implementations. Instead they rely on calls to interfaces (called property types
in PluginPlay). Any module that satisfies the interface can be used at such
callback points. In other words, software already compatible with PluginPlay
will interoperate with GhostFragment. Other software, may require wrappers to
satisfy the PluginPlay interfaces, but these wrappers should be relatively
easy to write.

.. _gf_perfomance:

Performance
===========

**Consideration**: Fragment-based methods are meant to be an approximation to 
traditional electronic structure methods. To be useful, fragment-based methods 
should improve the applicability of traditional methods, e.g., enable 
quicker simulations and/or larger simulations. This means that the fragment-
based method should be as performant (or ideally more performant) than the 
traditional method. For fragment-based methods, this requires worrying about:

- Minimizing data transformations.
- Parallelization of independent fragment calculations.
- Avoiding unnecessary calculations (such as those describing negligible
  interactions).
- Reuse of common intermediates when possible.

**Solution**: The "Performance" consideration is partially addressed by relying 
on C++ and its accompanying ecosystem of high-performance software. C++ is also
the language of choice for many electronic structure packages, thereby making
data transformations (potentially) easier. The remaining performance
considerations must be addressed at an algorithmic level. However, the
decision to use PluginPlay again helps here. For example, it is straightforward
to "wrap" a module which determines fragments with one that removes fragments
leading to negligible interactions. Additional notes:

- Chemist is used for modeling the chemical system (and will eventually be
  used to model partitioning operators).

.. _gf_accuracy:

Accuracy
========

**Consideration**: Speeding up electronic structure calculations via fragment-
based methods is only useful if the results faithfully replicate the supersystem
results. The accuracy of the supersystem method (compared to say experiment or
full solution of the time-independent Schrodinger equation) is beyond our scope.
Here we note a few general results:

- It is now known that basis-set superposition error plays a role in the 
  convergence :cite:t:`Ouyang2014` of most fragment-based methods. Thus to 
  implement accurate fragment-based methods we need to be able to correct for 
  BSSE.
- Overlapping fragments (whether by intention, or by taking unions of fragments)
  tend to improve accuracy. 
- Multi-level methods (where different fragments are treated at different levels
  of theory) can improve accuracy while reducing cost by allowing the more
  expensive method to only be applied to the fragments that need it.

**Solution**: The "Accuracy" consideration is primarily addressed by the
architecture of GhostFragment. In particular, our driver is designed to itself
be modular. This makes it easy to quickly write different drivers, e.g., write
one driver that implements a BSSE-corrected method, one that implements a
multi-level method, and so on. The architecture of GhostFragment also assumes
overlapping fragments from the beginning. The architecture of GhostFragment is
discussed in more detail at :ref:`gf_architecture`.

.. _gf_supersystem_pt:

Supersystem-Based Interface
===========================

**Consideration**: In most cases the fragments are simply a means to an end, 
i.e., the goal is to compute the properties of the supersystem. GhostFragment 
will integrate more seamlessly into existing software if its interface conforms 
to this convention. In other words, high-level interfaces should be designed to
take/return supersystem properties, not fragment properties. Having a unified,
supersystem-based interface also makes it easier to nest calls to GhostFragment,
such as is needed for multi-layer fragment-based methods.

**Solution**: The "Supersystem-Based Interface" consideration is addressed by
using Chemist's "Fragment" sub-library internally and exposing interfaces that
rely on ``ChemicalSystem`` and ``AOBasisSet`` objects.
