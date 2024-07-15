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

######################################################
Electorstatically-Embedded Many-Body Expansion (EE-MB)
######################################################

.. |q_a| replace:: :ref:`ee_mb_a`
.. |q_b| replace:: :ref:`ee_mb_b`
.. |q_s| replace:: :ref:`screened_charge_model`
.. |com| replace:: :ref:`com_screening`

The EE-MB method was proposed by :cite:t:`Dahlke2006`. Its initial formulation
amounted to applying a MBE to molecular culsters and using one of two embedding
methods, |q_a| and |q_b|. The resulting fragment-based methods were termed 
EE-MB-A and EE-MB-B. This initial study was largely dedicated to
understanding how these two embedding methods work on small water clusters (up
to a pentamer). Notably errors in the absolute energy only weakly depended on 
the charge scheme used (Mulliken, TIP3P, and CM4 were considered), and whether
|q_a| or |q_b| was used.

The next development in the EE-MB method was the development of a multi-level
formulation :cite:`Dahlke2007a`. Dubbed EE-MB-CE, this new method separately
applies a MBE to the SCF and correlation energies. In practice, however EE-MB-CE
was always run with the full SCF energy, thus it was only the correlation energy
which is truncated. Also proposed was |com|. Calculations looked at reproducing
superystem MP2 energies.

In 2011, :cite:t:`Tempkin_2011` introduced the next version of EE-MB, sEE-MB (s
stands for screened). Instead of traditional point charges, sEE-MB uses charges
defined by the |q_s| embedding scheme. |q_s| accounts for charge penetration
(when atoms are close the charge densities overlap and the electrons actually
see more of the nuclear charge). The sEE-MB method was applied to water clusters
where for a given MBE truncation order sEE-MB better replicated the supersystem
energy than EE-MB-B.

:cite:t:`Qi2013` presented the next incarnations of EE-MB termed EE-MB-NE and 
EE-MB-HE, where NE means nonlocal energy and HE means higher-level energy. 
Conceptually EE-MB-NE is the same as EE-MB-CE except that instead of performing 
a supersystem SCF calculation, one instead runs a local DFT calculation. 
EE-MB-HE is the name they give to the concept of running a multi-level 
calculation such that the lowest level is a supersystem calculation. Hence 
EE-MB-CE and EE-MB-NE are two specific cases of EE-MB-HE (specifically when the
lowest level is SCF or a local DFT respectively).


*******
Summary
*******

It seems fair to say that the unifying theme of the various flavors of EE-MB is
the use of non-iterative point charges. Unlike many of the other fragment based
methods EE-MB has almost always been used to refer to a single flavor 
(EE-MB-B) and care has been taken to distinguish among the other flavors. 

+--------------------+-------------+---------------+------------+--------------+
| Name               | Fragments   | Embedding     | Caps       | Screening    |
+====================+=============+===============+============+==============+
| EE-MB-A            | N/A         | |q_a|         | N/A        | N/A          |
+--------------------+-------------+---------------+------------+--------------+
| EE-MB-B            | N/A         | |q_b|         | N/A        | N/A          |
+----------+---------+-------------+---------------+------------+--------------+
|          | Layer 1 | Supersystem SCF                                         |
| EE-MB-CE +---------+-------------+---------------+------------+--------------+
|          | Layer 2 | N/A         | |q_b|         | N/A        | |com|        |
+----------+---------+-------------+---------------+------------+--------------+
| sEE-MB             | N/A         | |q_s|         | N/A        | N/A          |
+----------+---------+-------------+---------------+------------+--------------+
|          | Layer 1 | Supersystem local DFT                                   |
| EE-MB-NE +---------+-------------+---------------+------------+--------------+
|          | Layer 2 | N/A         | |q_b|         | N/A        | |com|        |
+----------+---------+-------------+---------------+------------+--------------+
|          | Layer 1 | Low-level supersystem                                   |
| EE-MB-HE +---------+-------------+---------------+------------+--------------+
|          | Layer 2 | N/A         | |q_b|         | N/A        | N/A          |
+----------+---------+-------------+---------------+------------+--------------+

*******************
Other EE-MB Results
*******************

:cite:t:`Dahlke2008a` considered the applicability of (presumably) EE-MB-B for
performing molecular dynamics calculations on water clusters. The specific study
focused on how accurately EE-MB-B replicated the supersystem gradients for a
water cluster containing 64 water molecules. All calculations were done with
DFT.

:cite:t:`Dahlke2008` considered how well EE-MB-CE could be used to reproduce
supersystem energies computed with CCSD, CCSD(T), and higher-order Moller-
Plesset perturbation theory. The study focused on water hexamer isomers.

:cite:t:`Sorkin2008` applies (presumably) EE-MB-B to water clusters containing a
NH3 molecule. The main point was to study how well EE-MB can replicate the
absolute and relative energetics of the corresponding supersystem calculations.
Also considered were several methods for computing the point charges.

:cite:t:`Leverentz2009` revisits the discussion of EE-MB-A vs. EE-MB-B for mixed
water, sulfuric acid, and ammonia clusters using DFT. The study notably
considers a lot of different ways to compute the charges, but ultimately
concludes the final results are pretty insensitive to the charge details.

:cite:t:`Hua2010a` applied EE-MB-B to Zn coordination compounds. The study 
specifically notes that having each ligand be one fragment, and the Zn be 
another led to unacceptale errors. Instead one fragment is Zn and the two 
closest ligands, and the remaining ligands are their own fragments. With such a
fragmentation scheme EE-MB-B was able to accurately reproduce supersystem
ligand disassociation energies.

:cite:t:`Kurbanov2011` again considered EE-MB-B applications to Zn coordination
compounds. This study considers how to fragment the compleexes in a more 
systematic manner. The main finding of this study is a series of guidelines for
fragmenting coordination compounds. These guidelines are not a fragmentation 
method, since they don't tell you how to fragment the system; rather the 
guidelines tell you how you can't fragment the system. By adhereing to the
aforementioned guidelines, EE-MB-B was again demonstrated to be able to predict
ligand dissassociation energies.

:cite:t:`Leverentz_2012` uses EE-MB-B to reproduce supersystem partial charges,
intermolecular charge transfer, and dipole moments of molecular clusters. Of
note they were only able to obtain qualitative agreement with supersystem 
results for intermolecular charge transfer.

:cite:t:`Kurbanov_2013` applied EE-MB-B and EE-MB-CE to Zn and Cd coordination
compounds. The study proposes a fragmentation method for Zn and Cd compounds 
that amounts to pairing the metal with the two ligands with the strongest 
Coulomb interaction (as deterimined by the maximum absolute point-charge-point-
charge interaction). Also of interest is a discussion pertaining to how to
classify the various EE-MB methods. Of particular note is the claim that there
is an ambiguity in trying to distinguish between intersecting and disjoint
methods.

:cite:t:`Friedrich_2014` applied EE-MB-B to water clusters with 26 monomers. The
goal of the study was to replicate CCSD(T)/CBS results computed using the 
incremental method. Overall the EE-MB-B results match the incremental method
results quite well.

*************
EE-MB Reviews
*************

:cite:t:`Wang2014a` reviewed the various flavors of EE-MB as well as the EE-MTA
method. This review also introduces the anchor points reactive potential method
which generates a semi-analytical potential energy surface by partitioning the
internal coordinates of the system. They then suggest that such a method should
also be considered a fragment-based method because it fragments the 
internal coordinates. 