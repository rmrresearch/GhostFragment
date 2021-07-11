.. _gmbe_proof:

*****************
Deriving the GMBE
*****************

.. |m| replace:: :math:`m`
.. |E| replace:: :math:`E` 

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

- |I|, |J|, |K| index fragments/monomers, *i.e* the subsystems the user divided
  the total system into,
- there are |m| fragments,  
- |IJ|, |IK|, |JK|, |IJK|, *etc.* index nmers (unions of :math:`n` fragments),
- The total energy of the system is |E|   

The Basic Form
===============

We start by showing that the general form of the GMBE is:

.. math::

    \newcommand{\etot}{E} 
    \newcommand{\e}[1]{\mathcal{E}_{#1}}
    \newcommand{\Den}[2]{\Delta\mathcal{E}^{(#1)}_{#2}}
    
    E = \sum_{n=1}^{m} \sum_{i=1}^{{_m}C_n}\Den{n}{i}

Here:

- :math:`n` indexes the family of nmers (*i.e.*, it runs over monomers, 
  dimers. trimers, *etc.*), 
- :math:`i` indexes the nmers in the family, 
- There are |m| choose :math:`n` nmers; this quantity is denoted 
  :math:`{_m}C_2`,
- the :math:`\Delta\mathcal{E}^{(n)}_{i}` are intersection-corrected |n|-body
  interactions.

At this point we only define the :math:`m`-body intersection-corrected 
interaction, which is defined as:

.. math::

   \Den{m}{1} = E - \sum_{n=1}^{m-1} \sum_{i=1}^{{_m}C_n}\Den{n}{i}   

(the 1 is because there's only one of them, the entire system).

.. admonition:: Proof of Exact Equality
   :class: dropdown, note

   Separating off the last term of the GMBE we have:

   .. math:: 
      E =\Den{m}{1} + \sum_{n=1}^{m-1} \sum_{i=1}^{{_m}C_n}\Den{n}{i} 

   Inserting the defition of the :math:`m`-body intersection-corrected 
   interaction gives:
   
   .. math::
      E =& \left(E - \sum_{n=1}^{m-1} \sum_{i=1}^{{_m}C_n}\Den{n}{i}\right) + 
          \sum_{n=1}^{m-1} \sum_{i=1}^{{_m}C_n}\Den{n}{i}\\
        =&E
    
   proving that this form is exact for any definition of the :math:`n<m`-body
   intersection-corrected interactions.
      
We choose to define the :math:`n<m`-body intersection-corrected interactions as:

.. math::
   \newcommand{\Sni}[2]{\mathbb{S}^{(#1)}_{#2}}
   \newcommand{\En}[2]{E^{(#1)}_{#2}}

   \Den{n}{i} = \en{n}{i}


.. admonition:: Motivating the Form of the Intersection-corrected Interactions
   :class: dropdown, note
   
   The form of the :math:`n<m`-body intersection-corrected interactions comes
   from wanting to make contact with tne normal MBE while properly accounting
   for intersections. We illustrate this by explicitly working out the lowest
   order scenarios.
   
   The one fragment case is trivial, the GMBE is simply:

   .. math::
      \newcommand{\EI}{E_I}
      
      E = \EI = \e{I}

   where the intersection-corrected interaction of the fragment is simply its
   energy.   
  
   The first non-trivial case is for two fragments. For two fragments we can do 
   both a one- and two-body expansion. We are in particular interested in the
   one-body expansion as it is the only one which involves terms :math:`n<m`.
   Using the  inclusion-exclusion principle to avoid overcounting, the one-body 
   approximation to the energy is:

   .. math::

      \newcommand{\EJ}{E_J}
      \newcommand{\EIcJ}{E_{I\cap J}}
   
      E \approx \EI + \EJ - \EIcJ

   We now define the following intersection-corrected "energies" (it is 
   customary to drop the :math:`\Delta` on one-body terms):

   .. math::
      \e{I} =& \EI\\
      \e{J} =& \EJ - \EIcJ

   The decision to include the intersection in :math:`\mathcal{E}_{J}` has been
   made to preserve the definition of :math:`\mathcal{E}_I` that came from the 
   one-body approximation. With these definition the one-body approximation 
   becomes:
   
   .. math::
      E \approx \e{I} + \e{J}

   In terms of these intersection corrected energies the full GMBE is:
   
   .. math::
      \newcommand{\De}[1]{\Delta\e{#1}}

      E = \e{I} + \e{J} + \De{IJ}

   where using the defintion of the :math:`m`-body intersection-corrected 
   interaction we have:

   .. math::
      \De{IJ} = E_{IJ} - \e{i} - \e{J}

   For three fragments both the one and two-body approximations involve 
   :math:`n<m`-body intersection-corrected interactions. For the one-body
   approximation, according to the inclusion-exclusion principle we have:

   .. math::
      \newcommand{\EK}{E_K}
      \newcommand{\EIcK}{E_{I\cap K}}
      \newcommand{\EJcK}{E_{J\cap K}}
      \newcommand{\EIcJcK}{E_{I\cap J\cap K}}

      E \approx \EI + \EJ + \EK - \EIcJ - \EIcK - \EJcK + \EIcJcK

   Defining intersection-corrected energies:

   .. math::         
      \e{I} =& \EI\\
      \e{J} =& \EJ - \EIcJ\\
      \e{K} =& \EK - \EIcK - \EJcK + \EIcJcK

   Where again the decision for how to partition terms stems from maintaining
   the same definitions of :math:`\mathcal{E}_I` and :math:`\mathcal{E}_J`. 
   With these defiitions the one-body approximation becomes:

   .. math::
      E \approx \e{I} + \e{J} + \e{K}

   For the two-body approximation to the energy we have:
    
   .. math::
      \newcommand{\Eik}{E_{IK}}
      \newcommand{\Ejk}{E_{JK}}
      \newcommand{\Eijcik}{E_{IJ\cap IK}}
      \newcommand{\Eijcjk}{E_{IJ\cap JK}}
      \newcommand{\Eikcjk}{E_{IK\cap JK}}
      \newcommand{\Eijcikcjk}{E_{IJ\cap IK\cap JK}}

      \etot \approx E_{IJ} + \Eik + \Ejk - \Eijcik - \Eijcjk - \Eikcjk + 
                    \Eijcikcjk

   If we want to write the "three-fragment,two-body" approximation in terms of 
   the "three-fragment,one-body approximation" we can add and subtract the 
   one-body approximation:
                    
   .. math::
      E \approx& E_{IJ} + \Eik + \Ejk - \Eijcik - \Eijcjk - \Eikcjk + 
                 \Eijcikcjk +\\
               &\left(\e{I} + \e{J} + \e{K}\right) - 
                \left(\e{I} + \e{j} + \e{K}\right)
               
   We now defining intersection-corrected two-body interaction energies:

   .. math::
               
      \De{IJ} =& E_{IJ} - \e{I} - \e{J}\\
      \De{IK} =& \Eik - \Eijcik - \e{K}\\
      \De{JK} =& \Ejk - \Eijcjk - \Eikcjk + \Eijcikcjk

   whose definitions partition terms to preserve the definition of 
   :math:`\Delta\mathcal{E}_{IJ}` already established, and so that 
   :math:`\mathcal{E}_K` is given to the term :math:`K` first appears in. With
   these definitions the two-body approximation becomes:
  
   .. math::
      E \approx \e{I} + \e{J} + \e{K} + \De{IJ} + \De{IK} + \De{JK}
      
   The total GMBE for three fragments, using the definitions of intersection-
   corrected interactions is then:

   .. math::
      E = \e{I} + \e{J} + \e{K} + \De{IJ} + \De{IK} + \De{JK} + \De{IJK}

   with the :math:`m`-body interaction given by:
   
   .. math::
      \De{IJK} = E_{IJK} - \e{I} - \e{J} - \e{K}  - \De{IJ} - \De{IK} - \De{JK}

   At this point the pattern is becoming clear. A given :math:`n`-body 
   intersection-corrected interaction has three pieces: the energy of the nmer,
   a piece from subtracting out lower order interactions, and a piece from the
   inclusion-exclusion principle. The term :math:`\Delta\mathcal{E}_{IK}` has
   all three pieces: :math:`E_{IK}` is the energy of the nmer, 
   :math:`\mathcal{E}_K` is the piece that comes from lower order interactions,
   and :math:`E_{IJ\cap IK}` comes from the inclusion-exclusion principle. 

The motivation suggests that this defintion of intersection-corrected
interactions results in a GMBE that is overcounting-free, even when truncated at
an order :math:`n<m`, and that the sum of all :math:`n`-body 
intersection-corrected interactions is the total of all :math:`n`-body 
interactions in the system (while we have partitioned this quantity into 
contributions from specific nmers this partitioning is not unique). The formal
proof follows.
   
.. admonition:: Proof
   :class: dropdown, note  

   We start with the approximate :math:`n`-body energy as given by the 
   inclusion-exclusion principle:

   .. math::
      \newcommand{\nmer}[2]{F^{(#1)}_{#2}}
      \newcommand{\mCn}[1]{{_m}C_{#1}}
      E \approx \sum_{i=1}^{\mCn{n}}E_{\nmer{n}{i}} - 
                \sum_{j>i}E_{\nmer{n}{i}\cap\nmer{n}{j}} + \cdots + 
                (-1)^{\mCn{n} - 1}
                  E_{\nmer{n}{1}\cap\nmer{n}{2}\cap\cdots\nmer{n}{\mCn{n}}}

   Next we partition these terms into intersection-corrected nmer energies
   according to:
   
   .. math::
      \e{\nmer{n}{i}} = E_{\nmer{n}{i}} - 
                        \sum_{j=1}^{i}E_{\nmer{n}{j}\cap\nmer{n}{i}} + \cdots + 
                        (-1)^{i - 1}
                          E_{\nmer{n}{1}\cap\nmer{n}{2}\cap\cdots\nmer{n}{i}}
   
   This results in:

   .. math::
      E \approx \sum_{i=1}^{\mCn{n}}\e{\nmer{n}{i}}
      
   To write the :math:`n`-body approximation in terms of the :math:`(n-1)`-body 
   approximation we add and subtract the :math:`(n-1)`-body approximation. The
   sum of the :math:`n`-body intersection-corrected interactions is then the
   difference between the :math:`n` and :math:`(n-1)`-body approximations:

   .. math:;
      \sum_{i=1}^{\mCn{n}}\Den{n}{i} = \sum_{i=1}^{\mCn{n}}\e{\nmer{n}{i}} - 
                                       \sum_{j=1}^{\mCn{n-1}}\e{\nmer{n-1}{j}}

    

   Each monomer appears in :math:`m-1` dimers, we partition the monomers such
   that monomer :math:`j` appears with the dimer it first contributes to. This
   is somewhat complicated to express mathematically, but if 
   :math:`s^{(1,2)}_{i}` is the set of all monomers found in dimer i then
   the monomers we want to pair with dimer i, :math:`S^{(1,2}_{i}`, are given 
   by:

   .. math::
      S^{(1,2)}_i = s^{(1,2)}_i\setminus
                    \left(\bigcup_{j=1}^{i-1}s^{(1,2)}_j\right)

   Using :math:`S` we can define:
   
   .. math::
      \De{\nmer{2}{i}} = \e{\nmer{2}{i}} - 
                         \sum_{\nmer{1}{j} \in S^{(1,2)}_{i}} \e{\nmer{1}{j}}

   and the two-body approximation becomes:
   
   .. math::
      E \approx \sum_{i=1}^{\mCn{1}}\e{\nmer{1}{i}} + 
                \sum_{i=1}^{\mCn{2}}\De{\nmer{2}{i}}

   Generalizing the intersection-corrected interaction is:
   
   .. math::
      \De{\nmer{n}{i}} = \e{\nmer{n}{i}} - 
                         \sum_{l=1}^{n-1}
                         \sum_{\nmer{l}{j} \in S^{(l,n)}_{i}} \De{\nmer{l}{j}}

   If we make the connection that:
   
   .. math::
      \De{\nmer{1}{j}} = \e{\nmer{1}{j}}

   We see that our two-body intersection-corrected interactions are of this 
   general form, proving the base case for induction. We now assume that we have 
   proved that 