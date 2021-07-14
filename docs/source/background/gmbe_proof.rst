.. _gmbe_proof:

*****************
Deriving the GMBE
*****************

.. |m| replace:: :math:`m`
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
.. |EJ| replace:: :math:`E_{J}`
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

For a single fragment the GMBE is trivial:

.. math::
   \newcommand{\En}[1]{E^{\left(#1\right)}}
   \newcommand{\nmer}[2]{F^{\left(#1\right)}_{#2}}
   \newcommand{\mi}{\nmer{1}{I}}

   E = \En{1} = E_{\mi}

Two fragments
-------------

For two fragments we have a one-body approximation to the GMBE as well as the
two-body GMBE.

One-body
^^^^^^^^

.. math::
   \newcommand{\mj}{\nmer{1}{J}}
   \newcommand{\Iicj}{\nmer{1}{I\cap J}}

   E \approx \En{1} = E_{\mi} + E_{\mj} - E_{\Iicj}

Two-body
^^^^^^^^

.. math::
   \newcommand{\mij}{\nmer{1}{IJ}}

   E = \En{2} = E_{\mij}

The two body interaction of fragments I with J is given by:

.. math::
   \newcommand{\De}[2]{\Delta\mathcal{E}^{\left(#1\right)}_{#2}}
   \newcommand{\Deij}{\De{1}{IJ}}

   \Deij \equiv \En{2}-\En{1} = E_{\mij} - E_{\mi} - E_{\mj} + E_{\Iicj}

Thus we can rewrite the two-body GMBE as:

.. math::
   E = \En{1} + \Deij

Three fragments
---------------

One-body
^^^^^^^^

.. math::
   \newcommand{\mk}{\nmer{1}{K}}
   \newcommand{\Iick}{\nmer{1}{I\cap K}}
   \newcommand{\Ijck}{\nmer{1}{J\cap K}}
   \newcommand{\Iicjck}{\nmer{1}{I\cap J\cap K}}

   E \approx \En{1} = E_{\mi} + E_{\mj} + E_{\mk} -
                      E_{\Iicj} - E_{\Iick} - E_{\Ijck} + E_{\Iicjck}

Two-body
^^^^^^^^

.. math::
   \newcommand{\mik}{\nmer{1}{IK}}
   \newcommand{\mjk}{\nmer{1}{JK}}
   \newcommand{\Iijcik}{\nmer{1}{IJ\cap IK}}
   \newcommand{\Iijcjk}{\nmer{1}{IJ\cap JK}}
   \newcommand{\Iikcjk}{\nmer{1}{IK\cap JK}}
   \newcommand{\Iijcikcjk}{\nmer{1}{IJ\cap IK\cap JK}}

   E\approx \En{2} = E_{\mij} + E_{\mik} + E_{\mjk} -
                     E_{\Iijcik} - E_{\Iijcjk} - E_{\Iikcjk} + E_{\Iijcikcjk}

The sum of the two-body interactions are given by the difference between the
two-body and one-body approximation:

.. math::
   \newcommand{\Iijck}{\nmer{1}{I\left(J\cap K\right)}}
   \newcommand{\Ijick}{\nmer{1}{J\left(I\cap K\right)}}
   \newcommand{\Ikicj}{\nmer{1}{K\left(I\cap J\right)}}
   \newcommand{\Iicjickjck}{\nmer{1}{\left(I\cap J\right)\left(I\cap K\right)\left(J\cap K\right)}}

   \En{2} -\En{1} =& E_{\mij} + E_{\mik} + E_{\mjk} -
                     E_{\Iijcik} - E_{\Iijcjk} - E_{\Iikcjk} + E_{\Iijcikcjk} -
                    \left( E_{\mi} + E_{\mj} + E_{\mk} -
                      E_{\Iicj} - E_{\Iick} - E_{\Ijck} + E_{\Iicjck}\right)\\
                  =& \left(E_{\mij} -E_{\mi} - E_{\mj} + E_{\Iicj}\right) +
                     \left(E_{\mik} -E_{\mi} - E_{\mk} + E_{\Iick}\right) +
                     \left(E_{\mjk} -E_{\mj} - E_{\mk} + E_{\Ijck}\right)
                     + E_{\mi} + E_{\mj} + E_{\mk} -
                    E_{\Iijcik} - E_{\Iijcjk} - E_{\Iikcjk} + E_{\Iijcikcjk} -
                    E_{\Iicjck}\\
                  =& \left(E_{\mij} -E_{\mi} - E_{\mj} + E_{\Iicj}\right) +
                     \left(E_{\mik} -E_{\mi} - E_{\mk} + E_{\Iick}\right) +
                     \left(E_{\mjk} -E_{\mj} - E_{\mk} + E_{\Ijck}\right) -
                     \left(E_{\Iijck} - E_{\mi} - E_{\Ijck} + E_{\Iicjck} \right) -
                     \left(E_{\Ijick} - E_{\mj} - E_{\Iick} + E_{\Iicjck}\right) -
                     \left(E_{\Ikicj} - E_{\mk} - E_{\Iicj} + E_{\Iicjck}\right) +
                     \left(E_{\Iicjickjck} - E_{\Iicj} - E_{\Iick} - E_{Ijck} +
                      2E_{\Iicjck}
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
