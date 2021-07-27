.. _gmbe_proof:

*****************
Deriving the GMBE
*****************

.. |m| replace:: :math:`m`
.. |n| replace:: :math:`n`
.. |E| replace:: :math:`E`

.. |monomer_i| replace:: :math:`F^{(1)}_{i}`
.. |dimer_i| replace:: :math:`F^{(2)}_{I}`
.. |nmer_i| replace:: :math:`F^{(2)}_{j}`
.. |m_int| replace:: :math:`\Delta\mathcal{E}_{F^{(m)}_1}`


.. |I| replace:: :math:`I`
.. |J| replace:: :math:`J`
.. |K| replace:: :math:`K`
.. |L| replace:: :math:`L`
.. |M| replace:: :math:`M`
.. |N| replace:: :math:`N`
.. |IJ| replace:: :math:`IJ`
.. |IK| replace:: :math:`IK`
.. |JK| replace:: :math:`JK`
.. |IJK| replace:: :math:`IJK`

.. |EI| replace:: :math:`E_{I}`
.. |eI| replace:: :math:`\mathcal{E}_{I}`
.. |EJ| replace:: :math:`E_{J}`
.. |eJ| replace:: :math:`\mathcal{E}_{J}`
.. |EK| replace:: :math:`E_{K}`
.. |EIJ| replace:: :math:`E_{IJ}`
.. |EIK| replace:: :math:`E_{IK}`
.. |EJK| replace:: :math:`E_{JK}`
.. |EIJK| replace:: :math:`E_{IJK}`
.. |EI_J| replace:: :math:`E_{I\cap J}`

This page derives the GMBE. Following the main GMBE page, we adopt the notation:

- |E| is the energy of the system
- |m| is the total number of monomers we divided our system into
- |monomer_i| is the :math:`i`-th monomer,
- |dimer_i| is the :math:`i`-th dimer, (*i.e.*, the union of two monomers)
- |nmer_i| is the :math:`i`-th nmer (generalization of monomer, dimer, etc. to
  the union of :math:`n` monomers)
- :math:`{_m}C_n` is the binomial coefficient "|m| choose :math:`n`",
  *i.e.*, the number of nmers that can be formed from |m| monomers.

Motivating the Induction Hypothesis
===================================

To motivate the induction hypothesis we explicitly write out the first several
scenarios.

One fragment
------------

.. |Enm| replace:: :math:`E^{\left(n\right)}_m`
.. |DEIJ| replace:: :math:`\Delta E_{IJ}`

For a single fragment, |I|, the GMBE is trivial:

.. math::
   \newcommand{\Enm}[2]{E^{\left(#1\right)}_{#2}}
   \newcommand{\Ei}{E_{I}}

   E = \Enm{1}{1} = \Ei

Here, |E| is the energy of the entire system, |Enm| is the |n|-body
approximation to the energy of the entire system when the system is comprised of
|m| fragments, and |EI| is the energy of |I|. To make contact with the
forthcoming equations we define the intersection-corrected energy of |I|, |eI|,
as:

.. math::
   \newcommand{\e}[1]{\mathcal{E}_{#1}}
   \newcommand{\ei}{\e{I}}

   \ei \equiv \Ei

Two fragments
-------------

For two fragments we have a one-body approximation to the GMBE as well as the
two-body GMBE.

One-body
^^^^^^^^

From the IEP we have:

.. math::
   \newcommand{\Ej}{E_{J}}
   \newcommand{\Eicj}{E_{I\cap J}}

   E \approx \Enm{1}{2} = \Ei + \Ej - \Eicj

Writing this in terms of the one-body, one-fragment approxmation:

.. math::
   \Enm{1}{2} = \Enm{1}{1} + \Ej - \Eicj

Defining |eJ| as:

.. math::
   \newcommand{\ej}{\e{J}}

   \ej \equiv \Ej - \Eicj

this becomes:

.. math::
   \Enm{1}{2} = \Enm{1}{1} + \ej = \ei + \ej

Two-body
^^^^^^^^

For two fragments, the dimer is the entire system and we trivially have:

.. math::
   \newcommand{\Eij}{E_{IJ}}

   E = \Enm{2}{2} = \Eij

The two body interaction of fragments I with J, |DEIJ|, is given by the
difference in energy between the two-body and one-body approximations:

.. math::
   \newcommand{\DE}[1]{\Delta E_{#1}}
   \newcommand{\DEij}{\DE{IJ}}

   \DEij \equiv \Enm{2}{2}-\Enm{1}{2} = \Eij - \ei - \ej

Using |DEIJ|, we can rewrite the two-body GMBE as:

.. math::
   E = \Enm{1}{2} + \DEij = \ei + \ej + \DEij

Again to make-contact with the forthcoming equations we define an intersection-
corrected two-body interaction, |DeIJ|:

.. math::
   \newcommand{\De}[1]{\Delta\mathcal{E}_{#1}}
   \newcommand{\Deij}{\De{IJ}}

   \Deij \equiv \DEij

with which the final two-body, two-fragment GMBE is:

.. math::
   E = \ei + \ej + \Deij

Three fragments
---------------

For three fragments we now have one, two, and three-body approximations.

One-body
^^^^^^^^

From the IEP we have:

.. math::
   \newcommand{\Ek}{E_{K}}
   \newcommand{\Eick}{E_{I\cap K}}
   \newcommand{\Ejck}{E_{J\cap K}}
   \newcommand{\Eicjck}{E_{I\cap J\cap K}}

   E \approx \Enm{1}{3} = \Ei + \Ej + \Ek - \Eicj - \Eick - \Ejck + \Eicjck

In terms of the one-body, two-fragment approximation this becomes:

.. math::
   \Enm{1}{3} = \Enm{1}{2} + \Ek - \Eick - \Ejck + \Eicjck

Defining:

.. math::
   \newcommand{\ek}{\e{K}}

   \ek \equiv \Ek - \Eick - \Ejck + \Eicjck


yields:

.. math::
   \Enm{1}{3} = \Enm{1}{2} + \ek = \ei + \ej + \ek

Two-body
^^^^^^^^

Using the IEP we get:

.. math::
   \newcommand{\Eik}{E_{IK}}
   \newcommand{\Ejk}{E_{JK}}
   \newcommand{\Eijcik}{E_{IJ\cap IK}}
   \newcommand{\Eijcjk}{E_{IJ\cap JK}}
   \newcommand{\Eikcjk}{E_{IK\cap JK}}
   \newcommand{\Eijcikcjk}{E_{IJ\cap IK\cap JK}}

   E\approx \Enm{2}{3} = \Eij + \Eik + \Ejk -
                         \Eijcik - \Eijcjk - \Eikcjk + \Eijcikcjk

The sum of the two-body interactions are given by the difference between the
two-body and one-body approximations:

.. math::
   \Enm{2}{3}-\Enm{1}{3} =& \Eij + \Eik + \Ejk -
                         \Eijcik - \Eijcjk - \Eikcjk + \Eijcikcjk -
                         \left(\ei + \ej + \ek\right)\\
                         =& \Enm{2}{2}  + \Eik + \Ejk -
                         \Eijcik - \Eijcjk - \Eikcjk + \Eijcikcjk - \ek

At this point we define intersection-corrected dimer energies according to:

.. math::
   \newcommand{\eij}{\e{IJ}}
   \newcommand{\eik}{\e{IK}}
   \newcommand{\ejk}{\e{JK}}

   \eik \equiv& \Eik - \Eijcik\\
   \ejk \equiv& \Ejk - \Eijcjk - \Eikcjk + \Eijcikcjk

if we do this and try to write the two-body interactions in the "usual way" we
get:

.. math::
   \Enm{2}{3} =& \Enm{1}{3} + \Enm{2}{2} + \eik + \ejk - \ek\\
              =& \Enm{1}{3} + \Enm{2}{2} + \left(\eik - \ei - \ek\right) +
                 \left(\ejk - \ej -\ek\right) + \ei + \ej + \ek

The appearance of the intersection-corrected monomer energies is at first
unexpected; however, note that for disjoint fragments:

.. math::
   \eij - \ei - \ej =& \Eij - \Ei - \Ej\\
   \eik - \ei - \ek =& \left(\Eik - \Ei\right) - \Ei -\Ek\\
   \ejk - \ej - \ek =& \left(\Ejk - \Ej - \Ek\right) - \Ej - \Ek

That is to say, the intersection-corrected dimer energies already remove the
energies of the previously seen monomers(i.e., with our ordering IJ is first, so
when we consider IK, the intersection-correction removes the energy of I,
similarly for JK, the intersection-correction removes the energies of J and K).
We instead propose the following intersection-corrected interactions:

.. math::
   \newcommand{\Deik}{\De{IK}}
   \newcommand{\Dejk}{\De{JK}}

   \Deij =& \eij - \ei - \ej\\
   \Deik =& \eik - \ek\\
   \Dejk =& \ejk

which for disjoint fragments reduce to the usual two-body interactions. With
these defitions we get:

.. math::
   \Enm{2}{3} =& \Enm{1}{3} + \Enm{2}{2} + \Deik + \ Dejk\\
             =& \ei + \ej + \ek + \Deij + \Deik + \Dejk

Three-body
^^^^^^^^^^

For three fragments we again obtain a trivial equation for the GMBE:

.. math::
   \newcommand{\Eijk}{E_{IJK}}

   E = \Enm{3}{3} = \Eijk

defining the three-body interaction as the difference in the three-body
approximation and the two-body approximation we get:

.. math::
   \newcommand{\Deijk}{\De{IJK}}

   \Deijk \equiv \Enm{3}{3} - \Enm{2}{3} =
              \Eijk - \left(\ei + \ej + \ek + \Deij + \Deik + \Dejk\right)

with which we can write the full GMBE as:

.. math::
   E = \ei + \ej + \ek + \Deij + \Deik + \Dejk + \Deijk

Four Fragments
--------------

One-body
^^^^^^^^

Following the IEP we have:

.. math::
   \newcommand{\El}{E_L}
   \newcommand{\Eicl}{E_{I\cap L}}
   \newcommand{\Ejcl}{E_{J\cap L}}
   \newcommand{\Ekcl}{E_{K\cap L}}
   \newcommand{\Eicjcl}{E_{I\cap J\cap L}}
   \newcommand{\Eickcl}{E_{I\cap K\cap L}}
   \newcommand{\Ejckcl}{E_{J\cap K\cap L}}
   \newcommand{\Eicjckcl}{E_{I\cap J\cap K\cap L}}
   \newcommand{\el}{\e{L}}

   \Enm{1}{4} =& \Ei + \Ej + \Ek + \El-\\
               & \Eicj - \Eick - \Eicl - \Ejck - \Ejcl - \Ekcl +\\
               & \Eicjck + \Eicjcl + \Eickcl + \Ejckcl - \Eicjckcl

In terms of the one-body, three-fragment approximation:

.. math::
   \Enm{1}{4} = \Enm{1}{3} + \El - \Eicl - \Ejcl - \Ekcl +
                \Eicjcl + \Eickcl + \Ejckcl - \Eicjckcl

Defining:

.. math::
   \el = \El - \Eicl - \Ejcl - \Ekcl + \Eicjcl + \Eickcl + \Ejckcl - \Eicjckcl

We get:

.. math::
  \Enm{1}{4} = \Enm{1}{3} + \el = \ei + \ej + \ek + \el

Two-body
^^^^^^^^

We now have six dimers, so the IEP for two-body approximation has 63 terms. We
jump right to the intersection-corrected dimer energies:

.. math::
   \newcommand{\Eil}{E_{IL}}
   \newcommand{\Ejl}{E_{JL}}
   \newcommand{\Ekl}{E_{KL}}
   \newcommand{\eil}{\e{IL}}
   \newcommand{\ejl}{\e{JL}}
   \newcommand{\ekl}{\e{KL}}
   \newcommand{\Eijcil}{E_{IJ\cap IL}}
   \newcommand{\Eikcil}{E_{IK\cap IL}}
   \newcommand{\Ejkcil}{E_{JK\cap IL}}
   \newcommand{\Eijcikcil}{E_{IJ\cap IK\cap IL}}
   \newcommand{\Eijcjkcil}{E_{IJ\cap JK\cap IL}}
   \newcommand{\Eikcjkcil}{E_{IK\cap JK\cap IL}}
   \newcommand{\Eijcikcjkcil}{E_{IJ\cap IK\cap JK\cap IL}}
   \newcommand{\Eijcjl}{E_{IJ\cap JL}}
   \newcommand{\Eikcjl}{E_{IK\cap JL}}
   \newcommand{\Ejkcjl}{E_{JK\cap JL}}
   \newcommand{\Eilcjl}{E_{IL\cap JL}}
   \newcommand{\Eijcikcjl}{E_{IJ\cap IK\cap JL}}
   \newcommand{\Eijcjkcjl}{E_{IJ\cap JK\cap JL}}
   \newcommand{\Eijcilcjl}{E_{IJ\cap IL\cap JL}}
   \newcommand{\Eikcjkcjl}{E_{IK\cap JK\cap JL}}
   \newcommand{\Eikcilcjl}{E_{IK\cap IL\cap JL}}
   \newcommand{\Ejkcilcjl}{E_{JK\cap IL\cap JL}}
   \newcommand{\Eijcikcjkcjl}{E_{IJ\cap IK\cap JK\cap JL}}
   \newcommand{\Eijcikcjkcil}{E_{IJ\cap IK\cap IL\cap JL}}
   \newcommand{\Eijcjkcilcjl}{E_{IJ\cap JK\cap IL\cap JL}}
   \newcommand{\Eikcijcilcjl}{E_{IK\cap IJ\cap IL\cap JL}}
   \newcommand{\Eijcikcjkcilcjl}{E_{IJ\cap IK\cap JK\cap IL\cap JL}}
   \newcommand{\Eijckl}{E_{IJ\cap KL}}
   \newcommand{\Eikckl}{E_{IK\cap KL}}
   \newcommand{\Ejkckl}{E_{JK\cap KL}}
   \newcommand{\Eilckl}{E_{IL\cap KL}}
   \newcommand{\Ejlckl}{E_{JL\cap KL}}
   \newcommand{\Eijcikckl}{E_{IJ\cap IK\cap KL}}
   \newcommand{\Eijcjkckl}{E_{IJ\cap JK\cap KL}}
   \newcommand{\Eijcilckl}{E_{IJ\cap IL\cap KL}}
   \newcommand{\Eijcjlckl}{E_{IJ\cap JL\cap KL}}
   \newcommand{\Eikcjkckl}{E_{IK\cap JK\cap KL}}
   \newcommand{\Eikcilckl}{E_{IK\cap IL\cap KL}}
   \newcommand{\Eikcjlckl}{E_{IK\cap JL\cap KL}}
   \newcommand{\Ejkcilckl}{E_{JK\cap IL\cap KL}}
   \newcommand{\Ejkcjlckl}{E_{JK\cap JL\cap KL}}
   \newcommand{\Eilcjlckl}{E_{IL\cap JL\cap KL}}
   \newcommand{\Eijcikcjkckl}{E_{IJ\cap IK\cap JK\cap KL}}
   \newcommand{\Eijcikcilckl}{E_{IJ\cap IK\cap IL\cap KL}}
   \newcommand{\Eijcikcjlckl}{E_{IJ\cap IK\cap JL\cap KL}}
   \newcommand{\Eijcjkcilckl}{E_{IJ\cap JK\cap IL\cap KL}}
   \newcommand{\Eijcjkcjlckl}{E_{IJ\cap JK\cap IL\cap KL}}
   \newcommand{\Eijcilcjlckl}{E_{IJ\cap IL\cap JL\cap KL}}
   \newcommand{\Eikcjkcilckl}{E_{IK\cap JK\cap IL\cap KL}}
   \newcommand{\Eikcjkcjlckl}{E_{IK\cap JK\cap JL\cap KL}}
   \newcommand{\Eikcilcjlckl}{E_{IK\cap IL\cap JL\cap KL}}
   \newcommand{\Ejkcilcjlckl}{E_{JK\cap IL\cap JL\cap KL}}
   \newcommand{\Eijcikcjkcilckl}{E_{IJ\cap IK\cap JK\cap IL\cap KL}}
   \newcommand{\Eijcikcjkcjlckl}{E_{IJ\cap IK\cap JK\cap JL\cap KL}}
   \newcommand{\Eijcikcilcjlckl}{E_{IJ\cap IK\cap IL\cap JL\cap KL}}
   \newcommand{\Eijcjkcilcjlckl}{E_{IJ\cap JK\cap IL\cap JL\cap KL}}
   \newcommand{\Eikcjkcilcjlckl}{E_{IK\cap JK\cap IL\cap JL\cap KL}}
   \newcommand{\Eijcikcjkcilcjlckl}{E_{IJ\cap IK\cap JK\cap IL\cap JL\cap KL}}

   \eij =& \Eij\\
   \eik =& \Eik - \Eijcik\\
   \ejk =& \Ejk -
           \Eijcjk - \Eikcjk +
           \Eijcikcjk\\
   \eil =& \Eil -
           \Eijcil - \Eikcil - \Ejkcil +
           \Eijcikcil + \Eijcjkcil + \Eikcjkcil-\\
         &  \Eijcikcjkcil\\
   \ejl =& \Ejl -
           \Eijcjl - \Eikcjl - \Ejkcjl - \Eilcjl +
           \Eijcikcjl + \Eijcjkcjl + \Eijcilcjl +\\
         &   \Eikcjkcjl + \Eikcilcjl + \Ejkcilcjl -
           \Eijcikcjkcjl - \Eijcikcjkcjl - \Eijcjkcilcjl -\\
         &   \Eikcijcilcjl +
           \Eijcikcjkcilcjl\\
   \ekl =& \Ekl -
           \Eijckl - \Eikckl - \Ejkckl - \Eilckl - \Ejlckl +
           \Eijcikckl + \Eijcjkckl + \\
         &   \Eijcilckl + \Eijcjlckl + \Eikcjkckl + \Eikcilckl + \Eikcjlckl +
             \Ejkcilckl + \\
         &   \Ejkcjlckl+ \Eilcjlckl -
           \Eijcikcjkckl - \Eijcikcilckl - \Eijcikcjlckl - \\
         &   \Eijcjkcilckl -\Eijcjkcjlckl - \Eijcilcjlckl -
             \Eikcjkcilckl - \Eikcjkcjlckl - \\
         &   \Eikcilcjlckl - \Ejkcilcjlckl +
           \Eijcikcjkcilckl + \Eijcikcjkcjlckl + \\
         &   \Eijcikcilcjlckl + \Eijcjkcilcjlckl + \Eikcjkcilcjlckl -
           \Eijcikcjkcilcjlckl

From which we define the intersection-corrected two-body interactions:

.. math::
   \newcommand{\Deil}{\De{IL}}
   \newcommand{\Dejl}{\De{JL}}
   \newcommand{\Dekl}{\De{KL}}

   \Deij =& \eij - \ei -\ej\\
   \Deik =& \eik - \ek\\
   \Deil =& \eil - \el\\
   \Dejk =& \ejk\\
   \Dejl =& \ejl\\
   \Dekl =& \ekl

If the monomers are disjoint we get:

.. math::


   \Deij =& \left(\Eij\right) - \Ei - \Ej\\
   \Deik =& \left(\Eik - \Ei\right) - \Ek\\
   \Deil =& \left(\Eil - \Ei - \Ei + \Ei\right) - \El\\
   \Dejk =& \left(\Ejk - \Ej - \Ek\right)\\
   \Dejl =& \left(\Ejl - \Ej - \Ej - \El + \Ej\right)\\
   \Dekl =& \left(\Ekl - \Ek - \Ek - \El - \El + \Ek + \El\right)


where we use parenthesis to show which terms arise from the
intersection-corrected dimer energy as opposed to which terms arise from
subtracting out the one-body approximation.

Three-Body
^^^^^^^^^^

There are four possible trimers, so compared to the two-body case the equation
is far simpler.

.. math::
   \newcommand{\Eijl}{E_{IJL}}
   \newcommand{\Eikl}{E_{IKL}}
   \newcommand{\Ejkl}{E_{JKL}}
   \newcommand{\Eijkcijl}{E_{IJK\cap IJL}}
   \newcommand{\Eijkcikl}{E_{IJK\cap IKL}}
   \newcommand{\Eijlcikl}{E_{IJL\cap IKL}}
   \newcommand{\Eijkcjkl}{E_{IJK\cap JKL}}
   \newcommand{\Eijlcjkl}{E_{IJL\cap JKL}}
   \newcommand{\Eiklcjkl}{E_{IKL\cap JKL}}
   \newcommand{\Eijkcijlcikl}{E_{IJK\cap IJL\cap IKL}}
   \newcommand{\Eijkcijlcjkl}{E_{IJK\cap IJL\cap JKL}}
   \newcommand{\Eijkciklcjkl}{E_{IJK\cap IKL\cap JKL}}
   \newcommand{\Eijlciklcjkl}{E_{IJL\cap IKL\cap JKL}}
   \newcommand{\Eijkcijlciklcjkl}{E_{IJK\cap IJL\cap IKL\cap JKL}}

   \Enm{3}{4} =& \Eijk + \Eijl + \Eikl + \Ejkl -
                 \Eijkcijl - \Eijkcikl - \Eijkcjkl - \Eijlcikl - \\
               &   \Eijlcjkl - \Eiklcjkl +
                 \Eijkcijlcikl + \Eijkcijlcjkl + \Eijkciklcjkl + \\
               &   \Eijlciklcjkl -
                 \Eijkcijlciklcjkl

Defining intersection-corrected trimer energies:

.. math::
   \newcommand{\eijk}{\e{IJK}}
   \newcommand{\eikl}{\e{IKL}}
   \newcommand{\ejkl}{\e{JKL}}
   \newcommand{\eijl}{\e{IJL}}

   \eijk =& \Eijk\\
   \eijl =& \Eijl - \Eijkcijl\\
   \eikl =& \Eikl - \Eijkcikl - \Eijlcikl + \Eijkcijlcikl\\
   \ejkl =& \Ejkl - \Eijkcjkl - \Eijlcjkl - \Eiklcjkl + \Eijkcijlcjkl +
              \Eijkciklcjkl + \\
          & \Eijlciklcjkl - \Eijkcijlciklcjkl

.. math::
   \newcommand{\Deijl}{\De{IJL}}
   \newcommand{\Deikl}{\De{IKL}}
   \newcommand{\Dejkl}{\De{JKL}}

   \Deijk =& \eijk - \Deij - \Deik - \Dejk - \ei - \ej -\ek\\
   \Deijl =& \eijl - \Deil - \Dejl - \el\\
   \Deikl =& \eikl - \Dekl\\
   \Dejkl =& \ejkl

For disjoint-fragments:

.. math::
   \Deijk =& \left[\Eijk\right] -
             \left(\Eij - \Ei -\Ej\right) -
             \left(\Eik - \Ei -\Ek\right) -
             \left(\Ejk - \Ej -\Ek\right) - \Ei - \Ej - \Ek\\
          =& \Eijk - \Eij - \Eik - \Ejk + \Ei + \Ej + \Ek\\
   \Deijl =& \left[\Eijl - \Eij\right] -
             \left(\Eil - \Ei - \El\right) -
             \left(\Ejl - \Ej - \El\right) - \El\\
          =& \Eijl - \Eij - \Eil - \Ejl + \Ei + \Ej + \El\\
   \Deikl =& \left[\Eikl - \Eik - \Eil + \Ei\right] -
              \left(\Ekl - \Ek - \El\right) \\
          =& \Eikl - \Eik - \Eil - \Ekl + \Ei + \Ek + \El\\
   \Dejkl =& \left[\Ejkl - \Ejk - \Ejl - \Ekl + \Ej + \Ek + \El\right]

where we have used square-brackets to show which terms came form the
intersection-corrected trimer energies and parenthesis to show which come from
the intersection-corrected dimer energies. These are the usual (cleaned-up)
three-body expressions.

Four-Body
^^^^^^^^^

.. math::
   \newcommand{\Eijkl}{E_{IJKL}}

   E = \Enm{4}{4} = \E_{IJKL}

Defining the four-body interaction:

.. math::
   \newcommand{\Deijkl}{\De{IJKL}}

   \Deijkl = E_{IJKL} - \Deijk - \Deijl - \Deikl - \Dejkl -
             \Deij - \Deik - \Deil - \Dejk - \Dejl - \Dek -
             \ei - \ej - \ek - \el

we arrive at the GMBE for four fragments:

.. math::
   E = \ei + \ej + \ek + \el + \Deij + \Deik + \Deil + \Dejk + \Dejl + \Dekl +
       \Deijk + \Deijl + \Deikl + \Dejkl + \Deijkl

Notation
========



The Induction Hypothesis
========================
