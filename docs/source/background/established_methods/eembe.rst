######################################################
Electorstatically-Embedded Many-Body Expansion (EE-MB)
######################################################

.. |q_a| replace:: :ref:`ee_mb_a`
.. |q_b| replace:: :ref:`ee_mb_b`
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