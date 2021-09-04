###############################
Generalized Many-Body Expansion
###############################

Motivation
==========

.. todo::

   Explain why we want to go beyond the MBE. 

Equations
=========

.. |n| replace:: :math:`n`
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

For a system broken into |n|, possibly intersecting, fragments the GMBE provides 
a many-body decomposition of the total energy, |E|:

.. math::
   
   \newcommand{\etot}{E} 
   \newcommand{\e}[1]{\mathcal{E}_{#1}}
   \newcommand{\De}[1]{\Delta\e{#1}}
   \newcommand{\eI}{\e{I}}
   \newcommand{\DeIJ}{\De{IJ}}
   
   E = \sum_{I}^n \ei + \sum_{IJ}^{{_n}C_2} \DeIJ + \cdots + 
       \Delta\mathcal{E}_{IJ\cdots N}

where:

- |I|, |J|, |K| index fragments/monomers, 
- |IJ| is the dimer formed by taking the union of monomers |I| and |J|, 
- the ellipses ellide terms involving trimers, tetramers, and so on up to the 
  :math:`(n-1)`-mers, and 
- :math:`IJ\cdots N` is the one |n|-mer, *i.e.* the entire system. 
 
The energies and intersections appearing in the expansion are 
"intersection-corrected", meaning they in general contain additional terms 
beyond their normal MBE-counterparts to avoid over/under correcting 
intersections. The intersection-corrected energies are given in terms of the
non-

We use the convention that |EI|, |EJ|, |EK|, *etc.* are the energies of the 
fragments and |EIJ|, |EIK|, |EJK|, |EIJK|, *etc* are the energies of the 
nmers

The proof of these equations is somewhat involved and is presented on another
page :ref:`gmbe_proof`.

      

Three-Body Equation
^^^^^^^^^^^^^^^^^^^

The three-body equation is:

.. math::
 
   \newcommand{\eijk}{E_{IJK}}
   
   \etot = \eijk

Adding and subtracting the three-fragment, two-body expansion:

.. math::
   
   \etot \approx \eijk + \left(\eI + \ej + \ek + \De{IJ} + \De{IK} + 
                 \De{JK}\right) - \left(\eI + \ej + \ek + \De{IJ} + \De{IK} + 
                 \De{JK}\right)

Defining:

.. math::
   
   \newcommand{\Deijk}{\Delta E_{IJK}}
   
   \Deijk = \eijk - \left(\eI + \ej + \ek + \De{IJ} + \De{IK} + 
            \De{JK}\right)

The three-body energy equation becomes:

.. math::

   \etot \approx \eI + \ej + \ek + \De{IJ} + \De{IK} + \De{JK}



It is worth noting that if we relabel dimer |IJ| with a single letter index |L|, 
dimer |IK| as |M|, and |JK| as |N|, the two-body approximation looks like the
one-body approximation:

.. math::
   
    \newcommand{\El}{E_L}
    \newcommand{\Em}{E_M}
    \newcommand{\En}{E_N}
    \newcommand{\Ek}{E_K}
    \newcommand{\Elcm}{E_{L\cap M}}
    \newcommand{\Elcn}{E_{L\cap N}}
    \newcommand{\Emcn}{E_{M\cap N}}
    \newcommand{\Elcmcn}{E_{L\cap M\cap N}}
    
    \etot \approx \El + \Em + \En - \Elcm - \Elcn - \Emcn + \Elcmcn

which was the idea used in the original GMBE paper to derive equations.



Noting that intersection distributes over union we have:

.. math::
      
      \newcommand{\Eijck}{E_{I\cup(J\cap K)}}
   
      \Eijcik =& E_{(I\cap IK) \cup (J\cap IK)}\\
              =& E_{I \cup (J\cap IK)}\\
              =& E_{I \cup (J\cap I) \cup (J\cap K)}\\
              =& \Eijck
      
   Similar manipulations afford:
      
   .. math::
   
      \newcommand{\Ejick}{E_{J\cup(I\cap K)}}
      \newcommand{\Ekicj}{E_{K\cup(I\cap J)}}
   
      \Eijcjk =& \Ejick \\ 
      \Eikcjk =& \Ekicj 
      
   For the triple intersection we get:
      
   .. math::
      
      \newcommand{\tripleint}{E_{(I\cap J)\cup (I\cap K)\cup (J\cap K)}}
   
       \Eijcikcjk =& E_{(IJ \cap IK)\cap JK}\\
                  =& E_{[I\cup (J\cap K)]\cap JK}\\
                  =& E_{(I\cap JK)\cup[(J\cap K)\cap JK)]}\\
                  =& \tripleint