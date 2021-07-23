.. _gmbe_proof:

*****************
Deriving the GMBE
*****************

.. |m| replace:: :math:`m`
.. |n| replace:: :math:`n`
.. |E| replace:: :math:`E`

.. |monomer_i| replace:: :math:`F^{(1)}_{i}`
.. |dimer_i| replace:: :math:`F^{(2)}_{j}`
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
corrected two-body energy and an intersection-corrected two-body interaction, |DeIJ|:

.. math::
   \newcommand{\De}[1]{\Delta\mathcal{E}_{#1}}
   \newcommand{\Deij}{\De{IJ}}

   \eij \equiv& \Eij\\
   \Deij \equiv& \DEij

and the final two-body, two-fragment GMBE is:

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
   \En{2}{3}-\En{1}{3} =& \Eij + \Eik + \Ejk -
                         \Eijcik - \Eijcjk - \Eikcjk + \Eijcikcjk -
                         \left(\ei + \ej + \ek\right)
                       =& \En{2}{2}  + \Eik + \Ejk -
                         \Eijcik - \Eijcjk - \Eikcjk + \Eijcikcjk - \ek

At this point it is tempting to try to define intersection-corrected dimer
energies according to:

.. math::
   \newcommand{\eij}{\e{IJ}}
   \newcommand{\eik}{\e{IK}}
   \newcommand{\ejk}{\e{JK}}

   \eik \equiv& \Eik - \Eijcik\\
   \ejk \equiv& \Ejk - \Eijcjk - \Eikcjk + \Eijcikcjk

if we do this we get:

.. math::
   \En{2}{3} =& \En{1}{3}  + \En{2}{2} + \eik + \ejk - \ek\\
             =& -\En{1}{3} + \En{2}{2} + \Deik + \ Dejk + \ei + \ej + \ek

The appearance of the intersection-corrected monomer energies is at first
unexpected; however, note that for disjoint fragments:

.. math::
   \eij - \ei - \ej =& \Eij - \Ei - \Ej
   \eik - \ei - \ej =& \Eik - \Ei - \Ei -\Ek\\
   \ejk - \ej - \ek =& \Ejk - \Ej - \Ek - \Ej - \Ek

and we see that the definitions of our intersection-corrected dimer energies
leads to two-body interactions which have subtracted out the energy of each
monomer one too many times. We instead propose the following
intersection-corrected interactions:

.. math::

   \Deij =& \Eij - \ei - \ej\\
   \Deik =& \Eik - \Eijcik - \ek\\
   \Dejk =& \Ejk - \Eijcjk - \Eikcjk + \Eijcikcjk

which for disjoint fragments reduce to:

.. math::
   \Eij - \ei - \ej =& \Eij - \Ei - \Ej
   \Eik - \ei - \ej =& \Eik - \Ei - \Ek\\
   \Ejk - \ej - \ek =& \Ejk - \Ej - \Ek

with these defitions we get:

.. math::
   \En{2}{3} =& \En{1}{3} + \En{2}{2} + \Deik + \ Dejk\\
             =& \ei + \ej + \ek + \Deij + \Deik + \Dejk

Three-body
^^^^^^^^^^

For three fragments we again obtain a trivial equation for the GMBE:

.. math::
   \newcommand{\Eijk}{E_{IJK}}

   E = \Emn{3}{3} = \Eijk

defining the three-body interaction as:

.. math::
   \newcommand{\Deijk}{\De{IJK}}

   \Deijk = \Eijk - \left(\ei + \ej + \ek + \Deij + \Deik + \Dejk\right)

we can write:
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

   \Emn{1}{4} = \Ei + \Ej + \Ek + \El
                - \Eicj - \Eick - \Eicl - \Ejck - \Ejcl - \Ekcl +
                \Eicjck + \Eicjcl + \Eickcl + \Ejckcl - \Eicjckcl

In terms of the one-body, three-fragment approximation:

.. math::
   \Emn{1}{4} = \Emn{1}{3} + \El - \Eicl - \Ejcl - \Ekcl +
                \Eicjcl + \Eickcl + \Ejckcl - \Eicjckcl

Defining:

.. math::
   \el = \El - \Eicl - \Ejcl - \Ekcl + \Eicjcl + \Eickcl + \Ejckcl - \Eicjckcl

We get:

.. math::
  \Emn{1}{4} = \Emn{1}{3} + \el = \ei + \ej + \ek + \el

Two-body
^^^^^^^^

Following the IECP


.. math::
   \newcommand{\Iijck}{\nmer{1}{I\left(J\cap K\right)}}
   \newcommand{\Ijick}{\nmer{1}{J\left(I\cap K\right)}}
   \newcommand{\Ikicj}{\nmer{1}{K\left(I\cap J\right)}}
   \newcommand{\Iicjickjck}{\nmer{1}{\left(I\cap J\right)\left(I\cap K\right)\left(J\cap K\right)}}
   \newcommand{\Deik}{\De{1}{IK}}
   \newcommand{\Dejk}{\De{1}{JK}}
   \newcommand{\Deijck}{\De{1}{I\left(J\cap K\right)}}
   \newcommand{\Dejick}{\De{1}{J\left(I\cap K\right)}}
   \newcommand{\Dekicj}{\De{1}{K\left(I\cap J\right)}}
   \newcommand{\Deicjickjck}{\De{1}{\left(I\cap J\right)\left(I\cap K\right)\left(J\cap K\right)}}

   \En{2} -\En{1} =& E_{\mij} + E_{\mik} + E_{\mjk} -
                     E_{\Iijcik} - E_{\Iijcjk} - E_{\Iikcjk} +
                     E_{\Iijcikcjk} -\\
                     &\left( E_{\mi} + E_{\mj} + E_{\mk} -
                             E_{\Iicj} - E_{\Iick} - E_{\Ijck} +
                             E_{\Iicjck}\right)\\
                  =& \left(E_{\mij} -E_{\mi} - E_{\mj} + E_{\Iicj}\right) +
                     \left(E_{\mik} -E_{\mi} - E_{\mk} + E_{\Iick}\right) + \\
                   & \left(E_{\mjk} -E_{\mj} - E_{\mk} + E_{\Ijck}\right) +
                     E_{\mi} + E_{\mj} + E_{\mk} - E_{\Iijcik} - E_{\Iijcjk} -\\
                   & E_{\Iikcjk} + E_{\Iijcikcjk} - E_{\Iicjck}\\
                  =& \Deij + \Deik + \Dejk  -
                     \left(E_{\Iijck} - E_{\mi} - E_{\Ijck} + E_{\Iicjck}\right) -\\
                   & \left(E_{\Ijick} - E_{\mj} - E_{\Iick} + E_{\Iicjck}\right) -
                     \left(E_{\Ikicj} - E_{\mk} - E_{\Iicj} + E_{\Iicjck}\right) + \\
                   & \left(E_{\Iicjickjck} - E_{\Iicj} - E_{\Iick} - E_{\Ijck} +
                      2E_{\Iicjck}\right)\\
                  =& \Deij + \Deik + \Dejk  - \Deijck - \Dejick - \Dekicj +
                     \Deicjickjck

The form of the two-body interactions are perhaps unexpected; however, the
interpretation is straightforward. An intersection-corrected two-body
interaction like :math:`\Delta\mathcal{E}_{F^{(1)}_{IJ}}` only corrects for the
intersections of the monomers in the two-body interaction it doesn't correct for
the overcounting in the sum of two-body interactions. For example, since |I|
appears in both :math:`\Delta\mathcal{E}_{F^{(1)}_{IJ}}` and
:math:`\Delta\mathcal{E}_{F^{(1)}_{IK}}`, the interaction of |I| with
:math:`J\cap K` is counted twice. Similar analysis gives rise to the other two
monomer-intersection interactions. The last term arises from the fact that our
subtraction took out the interaction of the three intersections one too many
times.

Three-body
^^^^^^^^^^

The three-body energy is given by:

.. math::
   \newcommand{\mijk}{\nmer{1}{IJK}}

   E = \En{3} = E_{\mijk}

Defining a three-body interaction:

.. math::
   \newcommand{\Deijk}{\De{1}{IJK}}

   \Deijk = E_{\mijk} - \left(\Deij + \Deik + \Dejk  - \Deijck - \Dejick -
            \Dekicj + \Deicjickjck\right) - \left(E_{\mi} + E_{\mj} + E_{\mk} -
                      E_{\Iicj} - E_{\Iick} - E_{\Ijck} + E_{\Iicjck}
            \right)

The total energy can be written as:

.. math::
   E = \En{1} + \left(\Deij + \Deik + \Dejk  - \Deijck - \Dejick -
            \Dekicj + \Deicjickjck\right) + \Deijk

Four fragments
--------------

Two-body
^^^^^^^^

E_{\mi}



The Basic Form
===============

We start by showing that the |E| can be expressed exactly in the form of the
GMBE:

.. math::


   \newcommand{\mCn}[2]{{_{#1}}C_{#2}}
   \newcommand{\e}[1]{\mathcal{E}_{#1}}
   \newcommand{\De}[1]{\Delta\mathcal{E}_{#1}}

    E = \sum_{i=1}^{n}\e{\nmer{1}{i}} +
         \sum_{i=1}^{\mCn{m}{2}}\De{\nmer{2}{i}} +
         \cdots + \De{\nmer{m}{1}}

if we define |m_int| in terms of the :math:`l<m`-body intersection-corrected
interactions as:

.. math::

   \De{\nmer{m}{1}} =
     E - \sum_{l=1}^{m-1} \sum_{i=1}^{\mCn{m}{l}}\De{\nmer{l}{i}}

Here :math:`\mathcal{E}_{F^{(1)}_i}` is the intersection-corrected energy of
|monomer_i| and the various :math:`\Delta\mathcal{E}_{F^{(n)}_i}`` are the
intersection-corrected |n|-body interactions arising from nmer :math:`i`. It is
easily proved that equality holds for any definition of the :math:`l<m`-body
intersection-corrected interactions.

.. admonition:: Proof of Exact Equality
   :class: dropdown, note

   Separating off the last term of the GMBE we have:

   .. math::
      E = \De{\nmer{m}{1}} +
            \sum_{l=1}^{m-1} \sum_{i=1}^{\mCn{m}{l}}\De{\nmer{l}{i}}

   Inserting the defition of |m_int|:

   .. math::
      E =& \left(E -
             \sum_{l=1}^{m-1} \sum_{i=1}^{\mCn{m}{l}}\De{\nmer{l}{i}}
           \right) +
           \sum_{l=1}^{m-1} \sum_{i=1}^{\mCn{m}{l}}\De{\nmer{n}{i}}\\
        =&E

   proving that this form is exact for any definition of the :math:`l<m`-body
   intersection-corrected interactions.

We now choose to define the intersection-corrected nmer energy as:

.. math::
   \e{\nmer{n}{i}}
     \equiv E_{\nmer{n}{i}} -
            \sum_{j=1}^{i-1}E_{\nmer{n}{j}\cap\nmer{n}{i}} +
            \cdots +
            \left(-1\right)^{i-1}
             E_{\nmer{n}{2}\cap\nmer{n}{2}\cap\cdots\cap\nmer{n}{i}}

Here Roman "E"s (as opposed to caligraphy "E"s) denote energies of nmers, and
intersections of nmers, which have **not** been corrected for over-/under-
counting.

.. admonition:: Motivating the Form of the Intersection-Corrected NMer Energy
   :class: dropdown, note

   If we truncate the GMBE at order 1 we get:

   .. math::
      \newcommand{\E}[1]{E^{(#1)}}
      \E{1} = \sum_{i=1}^{m}\e{\nmer{1}{i}}

   By analogy to the normal MBE we would like :math:`E^{(1)}` to be a one-body
   approximation to the energy of the system. The
   inclusion-exclusion principle (IEP) tells us:

   .. math::
      \E{1} = \sum_{i=1}^{m}E_{\nmer{1}{i}} -
              \sum_{i=1}^{m}\sum_{j=1}^{i-1}E_{\nmer{1}{j}\cap\nmer{1}{i}} +
              \cdots +
              \left(-1\right)^{m-1}
                E_{\nmer{1}{1}\cap\nmer{1}{2}\cap\cdots\cap\nmer{1}{m}}

   The form of this equation suggests (and we adopt) the intersection-corrected
   energy definition:

   .. math::
      \e{\nmer{1}{i}}
        \equiv E_{\nmer{1}{i}} -
               \sum_{j=1}^{i-1}E_{\nmer{1}{j}\cap\nmer{1}{i}} +
               \cdots +
               \left(-1\right)^{i-1}
                 E_{\nmer{1}{1}\cap\nmer{1}{2}\cap\cdots\cap\nmer{1}{i}}

   With this partioning of the energies, the first three intersection-corrected
   energies look like:

   .. math::
      \e{\nmer{1}{1}} =& E_{\nmer{1}{1}}\\
      \e{\nmer{1}{2}} =& E_{\nmer{1}{2}} - E_{\nmer{1}{1}\cap\nmer{1}{2}}\\
      \e{\nmer{1}{3}} =& E_{\nmer{1}{3}} - E_{\nmer{1}{1}\cap\nmer{1}{3}} -
                         E_{\nmer{1}{2}\cap\nmer{1}{3}} +
                         E_{\nmer{1}{1}\cap\nmer{1}{2}\cap\nmer{1}{3}}

   that is the intersection-corrected energies work analogous to Gram-Schmidt
   orthogonalization, namely for each new monomer we apply the IEP to it and the
   monomers that came before it.

   Applying the IEP to the set of dimers, we get the two-body approximation to
   the energy:

   .. math::
      \E{2} = \sum_{i=1}^{\mCn{m}{2}}E_{\nmer{2}{i}} -
              \sum_{i=1}^{\mCn{m}{2}}\sum_{j=1}^{i-1}
                E_{\nmer{2}{j}\cap\nmer{2}{i}} +
              \cdots +
              \left(-1\right)^{\mCn{m}{n}-1}
                E_{\nmer{2}{1}\cap\nmer{2}{2}\cap\cdots\cap\nmer{2}{\mCn{m}{2}}}

   and we define the intersection-corrected dimer energies:

   .. math::
      \e{\nmer{2}{i}}
        \equiv E_{\nmer{2}{i}} -
               \sum_{j=1}^{i-1}E_{\nmer{2}{j}\cap\nmer{2}{i}} +
               \cdots +
               \left(-1\right)^{i-1}
                E_{\nmer{1}{2}\cap\nmer{2}{2}\cap\cdots\cap\nmer{2}{i}}

   The generalization from dimers to nmers is now apparant.


This definition is such that the |n|-body approximation to the system's energy,
:math:`E^{(n)}` is given by:

.. math::
   \E{n} = \sum_{i=1}^{\mCn{m}{n}}\e{\nmer{n}{i}}

.. admonition:: Proof
   :class: dropdown, note

   Inserting the definition of the intersection-corrected nmer energy gives:

   .. math::
     \E{n} = \sum_{i=1}^{\mCn{m}{n}}E_{\nmer{n}{i}} -
             \sum_{i=1}^{\mCn{m}{n}}\sum_{j=1}^{i-1}
               E_{\nmer{n}{j}\cap\nmer{n}{i}} +
             \cdots +
             \sum_{i=1}^{\mCn{m}{n}}\left(-1\right)^{i-1}
               E_{\nmer{n}{2}\cap\nmer{n}{2}\cap\cdots\cap\nmer{n}{i}}

   This is simply the IEP.


We choose to define the :math:`n<m`-body intersection-corrected interactions as:

.. math::
   \newcommand{\Sni}[2]{\mathbb{S}^{(#1)}_{#2}}
   \newcommand{\En}[2]{E^{(#1)}_{#2}}

   \Den{n}{i} = \en{n}{i}


.. admonition:: Motivating the Form of the Intersection-corrected Interactions
   :class: dropdown, note

   The sum of all of the two-body interactions in the system is the difference
   between the two-body approximation to the energy and one-body approximation:

   .. math::
      \sum_{i=1}^{\mCn{m}{2}}\De{\nmer{2}{i}}
        =& \E{2} - \E{1}\\
        =& \sum_{i=1}^{\mCn{m}{2}}\e{\nmer{2}{i}} -
           \sum_{j=1}^{m}\e{\nmer{1}{j}}

   Each of the monomers appears in |m|-1 dimers. We choose to partition them so
   that monomer :math:`j` appears with the first dimer that contains it.
   Unfortunately our notation obscures which monomers contribute to a dimer. If
   we further assume that the dimers are ordered lexicographically, that is:

   .. math::
      \nmer{2}{1} =& \nmer{1}{1}\cup\nmer{1}{2}\\
      \nmer{2}{2} =& \nmer{1}{1}\cup\nmer{1}{3}\\
      \cdots      =& \cdots\\
      \nmer{2}{m-1} = & \nmer{1}{1}\cup\nmer{1}{m}\\
      \nmer{2}{m} = & \nmer{1}{2}\cup\nmer{1}{3}\\
      \cdots =& \cdots\\
      \nmer{2}{\mCn{m}{2}} =& \nmer{1}{m-1}\nmer{1}{m}

   then for the first intersection-corrected two-body interactions we get:

   .. math::
      \De{\nmer{2}{1}} = \e{\nmer{2}{1}} - \e{\nmer{1}{1}} - \e{\nmer{1}{2}}

   for the next |m|- 2 intersection corrected two-body interactions we get:

   .. math::
      \begin{align*}
      \De{\nmer{2}{i}} = \e{\nmer{2}{i}} - \e{\nmer{1}{i+1}} && (1 < i < m)
      \end{align*}

   and the remaining two-body interactions are given by:

   .. math::
      \begin{align*}
      \De{\nmer{2}{j}} = \e{\nmer{2}{j}} && (j >= m)
      \end{align*}

   Writing out the first intersection-corrected two-body interaction:

   .. math::

      \De{\nmer{2}{1}} =& E_{\nmer{1}{1}\cup\nmer{1}{2}} -
                          \e{\nmer{1}{1}} - \e{\nmer{1}{2}}\\
                       =& E_{\nmer{1}{1}\cup\nmer{1}{2}} -
                          E_{\nmer{1}{1}} - E_{\nmer{1}{2}} +
                          E_{\nmer{1}{1}\cap\nmer{1}{2}}

   The second:

   .. math::
      \De{\nmer{2}{2}} =&
        E_{\nmer{1}{1}\cup\nmer{1}{3}} -
        E_{\nmer{1}{1}\cup\left(\nmer{1}{2}\cap\nmer{1}{3}\right)} -
        \e{\nmer{1}{3}}\\
      =& E_{\nmer{1}{1}\cup\nmer{1}{3}} -
         E_{\nmer{1}{1}\cup\left(\nmer{1}{2}\cap\nmer{1}{3}\right)} -
         \left(E_{\nmer{1}{3}} -
               E_{\nmer{1}{1}\cap\nmer{1}{3}} -
               E_{\nmer{1}{2}\cap\nmer{1}{3}} +
               E_{\nmer{1}{1}\cap\nmer{1}{2}\cap\nmer{1}{3}}
         \right)\\
      =& \left(E_{\nmer{1}{1}\cup\nmer{1}{3}} -
               E_{\nmer{1}{1}} - E_{\nmer{1}{3}} +
               E_{\nmer{1}{1}\cap\nmer{1}{3}}\right) -
         \left[E_{\nmer{1}{1}\cup\left(\nmer{1}{2}\cap\nmer{1}{3}\right)} -
               E_{\nmer{1}{1}} - E_{\nmer{1}{2}\cap\nmer{1}{3}} +
               E_{\nmer{1}{1}\cap\nmer{1}{2}\cap\nmer{1}{3}}\right]

   where we used:

   .. math::
      \nmer{1}{1}\cup\left(\nmer{1}{2}\cap\nmer{1}{3}\right) =
      \left(\nmer{1}{1}\cup\nmer{1}{2}\right)\cap
      \left(\nmer{1}{1}\cup\nmer{1}{3}\right)

   This looks like the 1-3 interaction less the interaction of 1 with the
   intersection of 2 and 3. The third:

   .. math::
      \De{\nmer{2}{3}}
      =& E_{\nmer{1}{1}\cup\nmer{1}{4}} -
         E_{\nmer{1}{1}\cup\left(\nmer{1}{2}\cap\nmer{1}{4}\right)} -
         E_{\nmer{1}{1}\cup\left(\nmer{1}{3}\cap\nmer{1}{4}\right)} +
         E_{\nmer{1}{1}\cup
            \left(\nmer{1}{2}\cap\nmer{1}{3}\cap\nmer{1}{4}\right)} -
        \e{\nmer{1}{4}}\\
      =&  E_{\nmer{1}{1}\cup\nmer{1}{4}} -
         E_{\nmer{1}{1}\cup\left(\nmer{1}{2}\cap\nmer{1}{4}\right)} -
         E_{\nmer{1}{1}\cup\left(\nmer{1}{3}\cap\nmer{1}{4}\right)} +
         E_{\nmer{1}{1}\cup
            \left(\nmer{1}{2}\cap\nmer{1}{3}\cap\nmer{1}{4}\right)} -
        \left(E_{\nmer{1}{4}} - E_{\nmer{1}{1}\cap\nmer{1}{4}} -
              E_{\nmer{1}{2}\cap\nmer{1}{4}} - E_{\nmer{1}{3}\cap\nmer{1}{4}} +
              E_{\nmer{1}{1}\cap\nmer{1}{2}\cap\nmer{1}{4}} +
              E_{\nmer{1}{1}\cap\nmer{1}{3}\cap\nmer{1}{4}} +
              E_{\nmer{1}{2}\cap\nmer{1}{3}\cap\nmer{1}{4}} -
              E_{\nmer{1}{1}\cap\nmer{1}{2}\cap\nmer{1}{3}\cap\nmer{1}{4}}
        \right)\\
      =&\left(E_{\nmer{1}{1}\cup\nmer{1}{4}} -
              E_{\nmer{1}{1}} - E_{\nmer{1}{4}} +
              E_{\nmer{1}{1}\cap\nmer{1}{4}} \right) -
         \left(E_{\nmer{1}{1}\cup\left(\nmer{1}{2}\cap\nmer{1}{4}\right)} -
               E_{\nmer{1}{1}} - E_{\nmer{1}{2}\cap\nmer{1}{4}} +
               E_{\nmer{1}{1}\cap\nmer{1}{2}\cap{1}{4}}\right) -
         \left(E_{\nmer{1}{1}\cup\left(\nmer{1}{3}\cap\nmer{1}{4}\right)} -
               E_{\nmer{1}{1}} - E_{\nmer{1}{3}\cap\nmer{1}{4}} +
               E_{\nmer{1}{1}\cap\nmer{1}{3}\cap{1}{4}}\right) +
         \left(E_{\nmer{1}{1}\cup
                   \left(\nmer{1}{2}\cap\nmer{1}{3}\cap\nmer{1}{4}\right)} -
               E_{\nmer{1}{1}} - E_{\nmer{1}{2}\cap\nmer{1}{3}\cap{1}{4}} +
               E_{\nmer{1}{1}\cap\nmer{1}{2}\cap\nmer{1}{3}\cap\nmer{1}{4}}
         \right)

   This looks like the 1-4 interaction less the interaction of 1 with the
   intersection of 2 and 4, less the interaction of 1 with intersection 3 and 4,
   plus the interaction of 1 with the intersection of 2, 3, and 4.
