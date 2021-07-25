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

We now have six dimers, so the two-body approximation has 63 terms and explicity
enumerating them all is too cumbersome. Instead we assume that the dimers are
ordered in some manner and we define |dimer_i| as the |I|-th dimer. With this
notation we have:

.. math::
   \newcommand{\nmer}[2]{F^{\left(#1\right)}_{#2}}
   \newcommand{\di}{\nmer{2}{I}}
   \newcommand{\dj}{\nmer{2}{J}}
   \newcommand{\dk}{\nmer{2}{K}}
   \newcommand{\dl}{\nmer{2}{L}}
   \newcommand{\dm}{\nmer{2}{M}}
   \newcommand{\dn}{\nmer{2}{N}}
   
   \Enm{2}{4} =& \sum_{I=1}^{6} E_{\di} - 
                 \sum_{I=2}^{6}\sum_{J=1}^{I-1}E_{\dj\cap\di} +
                 \sum_{I=3}^{6}\sum_{J=1}^{I-2}\sum_{K=J+1}^{I-1}
                   E_{\dj\cap\dk\cap\di} -\\
               &  \sum_{I=4}^{6}\sum_{J=1}^{I-3}\sum_{K=J+1}^{I-2}
                   \sum_{L=K+1}^{I-1} E_{\dj\cap\dk\cap\dl\cap\di} +\\
                &\sum_{I=5}^{6}\sum_{J=1}^{I-4}\sum_{K=J+1}^{I-3}
                 \sum_{L=J+1}^{I-2}\sum_{M=L+1}^{I-1} 
                 E_{\dj\cap\dk\cap\dl\cap\dm\cap\di} -\\
               & \sum_{I=6}^{6}\sum_{J=1}^{I-5}\sum_{K=J+1}^{I-4}
                 \sum_{L=J+1}^{I-3}\sum_{M=L+1}^{I-2}\sum_{N=M+1}^{I-1}
                 E_{\dj\cap\dk\cap\dl\cap\dm\cap\dn\cap\di}

where the summations have been manipulated so that the dimers in the 
intersections are indexed lexicographically, the indices are driven by |I|, and 
|I| is always the largest index (this facilitates defining the 
intersection-corrected dimer energies). This is still a cumbersome notation. 
The spirit of what is going on here is that for an intersection involving 
|dimer_i| and |n| other dimers, we are iterating over all combinations of |n| 
dimers that can be formed from the :math:`I-1` dimers proceeding |I|. Let 
:math:`\mathbb{F}^{(n, m)}` be the ordered set of |n|-mers which can be made 
from |m| monomers; furthermore let :math:`\mathbb{F}^{(n,m)}_{I}` be the subset
of :math:`\mathbb{F}^{(n, m)}` consisting of the first |I|, |n|-mers. Next we
define :math:`\mathbb{P}^{(k)}\left(\mathbb{X}\right)` to be the set of 
:math:`k`-element combinations which can be formed from the set 
:math:`\mathbb{X}`. Finally we define a quantity 
:math:`X\left(\mathbb{a}\right)` which is the intersection of each element in a 
set :math:`\mathbb{a}` according to:

.. math::

   X\left(\mathbb{a}\right) = \bigcap_{b\in \mathbb{a}} b

Then the two-body energy can be written much more compactly as:

.. math::
   \newcommand{\nmerset}[3]{\mathbb{F}^{\left(#1, #2\right)}_{#3}}
   \newcommand{\powerset}[2]{\mathbb{P}^{\left(#1\right)}\left({#2}\right)}

   \Enm{2}{4} = \sum_{I=1}^{6}\left[\sum_{n=0}^5\left(-1\right)^{n}
                \sum_{p\in\powerset{n}{\nmerset{2}{4}{I-1}}}
                  E_{X\left(p\right)\cap\di}\right]

where the quantity in square brackets defines the intersection-corrected dimer
energy.                  
