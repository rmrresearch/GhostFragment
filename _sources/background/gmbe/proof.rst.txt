.. |m| replace:: :math:`m`
.. |n| replace:: :math:`n`
.. |l| replace:: :math:`\ell`
.. |I| replace:: :math:`I`
.. |k| replace:: :math:`k`

##########
GMBE Proof
##########

The Induction Hypothesis
========================

Based on the motivation in (TODO: add section) we hypothesize that the GMBE for 
a system fragmented into |m| fragments can be written in a form designed to
mimic a corresponding MBE via:

.. math::
   \newcommand{\e}[1]{\mathcal{E}_{#1}}
   \newcommand{\De}[1]{\Delta\e{#1}} 
   \newcommand{\mCk}[2]{_{#1}C_{#2}}
   \newcommand{\kmers}[1]{\mathbb{F}^{\left(m, #1\right)}}
   \newcommand{\kmeri}[2]{F^{\left(#1\right)}_{#2}}
   \newcommand{\ei}{\e{I}}
   \newcommand{\Deij}{\De{IJ}}
   \newcommand{\mCn}{\mCk{m}{n}}
   \newcommand{\nmers}{\kmers{n}}
   \newcommand{\nmeri}{\kmeri{n}{I}}
   
   E =& \sum_{I=1}^{m} \ei + \sum_{I=1}^{m-1}\sum_{J=I+1}^{m} \Deij + \cdots +
       \De{IJK\cdots m}\\
     =& \sum_{\kmeri{1}{K}\in\kmers{1}} \e{\kmeri{1}{K}} + 
        \sum_{n=2}^{m}\sum_{\nmeri\in\nmers}^{\mCn} \De{\nmeri}

Here the intersection-corrected energy of the |I|-th |n|-mer are defined by:

.. math::
    \newcommand{\nmersuptoi}{\mathbb{F}^{\left(m,n\right)}[1:I-1]}
    \newcommand{\powersetk}[2]{\mathbb{P}^{\left(#1\right)}\left(#2\right)}
    \newcommand{\setint}[1]{\left(\bigcap {#1}\right)}
    \newcommand{\nmerj}{\kmeri{n}{J}}
    
    \e{\nmeri} =& E_{\nmeri} - 
                  \sum_{\nmerj\in\nmersuptoi} E_{\nmerj\cap\nmeri} + 
                  \sum_{x\in\powersetk{2}{\nmersuptoi}}
                  E_{\setint{x}\cap\nmeri} - \cdots +\\ 
                & (-1) ^{I-1} E_{\setint{\nmersuptoi}\cap\nmeri}\\
               =& E_{\nmeri} - 
                  \sum_{k=1}^{I-1}\sum_{x\in\powersetk{k}{\nmersuptoi}}
                    (-1) ^ k E_{\left(\bigcap x\right)\cap \nmeri}         

The notation is complex, but the idea is simple. The |I|-th |n|-mer's
intersection-corrected enegy is obtaind by subtracting from the |I|-th |n|-mer's
energy (the :math:`k=0` term) the components of the energy which appeared in any
of the previous :math:`I-1` |n|-mers (these corrections are the :math:`k=1` 
terms); however, for components which appear in three or more of the previous 
|n|-mers we have now removed them too many times and need to add them back in 
(the :math:`k=2` terms). This process repeats until we have addresed the 
intersection of all |I| |n|-mers. If it helps you can think of this as the
set-equivalent of Gram-Schmidt orthogonalization. 

Akin to the MBE we obtain |n|-body interactions by removing |k|-body 
interactions (|k| less than |n|). The caveat here is that intersection-corrected
eneriges have already done some of this for us and we need to be careful not to 
remove lower-order interactions too many times. To that end we define the set:

.. math::
   \newcommand{\psetp}[2]{\mathbb{P}'^{\left(#1\right)}\left(#2\right)}


   \psetp{k}{\nmeri} = \powersetk{k}{\nmeri}\setminus
                       \left(\bigcup_{J=1}^{I-1}\psetp{k}{\nmerj}\right)

which is the set of |k|-mers that can be formed from the monomers comprising the
|I|-th |n|-mer, but can not be formed from any of the previously considered 
|n|-mers. In terms of this set, the intersection-corrected interactions are:

.. math::
   \De{\nmeri} = \e{\nmeri} - 
                 \sum_{k=2}^{n-1}\sum_{\kmeri{k}{J}\in\psetp{k}{\nmeri}} 
                  \De{\kmeri{k}{J}} - \sum_{\kmeri{1}{K}\in\psetp{1}{\nmeri}} 
                  \e{\kmeri{1}{K}}

Proof Of Exactness
==================

We now proceed to show that this form of the GMBE is exact. To that end consider
the GMBE for |m| fragments:

.. math::
   E = \sum_{I=1}^{m} \ei + 
         \sum_{n=2}^{m}\sum_{\nmeri\in\nmers}^{\mCn} \De{\nmeri}
         
We expand the :math:`n=m` interaction:

.. math::
   \De{\kmeri{m}{1}} = \e{\kmeri{m}{1}} - 
                       \sum_{n=2}^{m-1}\sum_{\nmeri\in\psetp{k}{\kmeri{m}{1}}}
                         \De{\nmeri} - 
                       \sum_{\kmeri{1}{K}\in\psetp{1}{\kmeri{m}{1}}} 
                         \e{\kmeri{1}{K}}

Here the notation :math:`F^{\left(m\right)}_{0}` is meant to make explicit that 
there is only one |m|-mer, the entire system. Consequently, for a given |k| 
(including :math:`k=1`) we have:

.. math::
    \psetp{k}{\kmeri{m}{1}} = \powersetk{k}{\kmeri{m}{1}} = \kmers{k}

which is to say that since there are no previous |m|-mers the primed powerset
reduces to the normal powerset, which in turn reduces to the set of |k|-mers
because the |m|-mer is the entire system. With this realization:   

.. math::
    \De{\kmeri{m}{1}} = \e{\kmeri{m}{1}} - 
                        \sum_{n=2}^{m-1}\sum_{\nmeri\in\nmers}
                          \De{\nmeri} - 
                        \sum_{\kmeri{1}{K}\in\nmers} 
                          \e{\kmeri{1}{K}}

and:

.. math::
    E =& \sum_{\kmeri{1}{K}\in\kmers{1}} \e{\kmeri{1}{K}} + 
         \sum_{n=2}^{m-1}\sum_{\nmeri\in\nmers}^{\mCn} \De{\nmeri} +
         \e{\kmeri{m}{1}} - 
         \sum_{n=2}^{m-1}\sum_{\nmeri\in\nmers} \De{\nmeri} - 
         \sum_{\kmeri{1}{K}\in\kmers{1}} \e{\kmeri{1}{K}}\\
       =& \e{\kmeri{m}{1}}\\
       =& E_{\kmeri{m}{1}}
       
which with the last line follows from the definition of the 
intersection-corrected |m|-mer energy. Basically this proof shows that, like the
normal MBE, the GMBE is just a very creative way of adding zero.

Exactness of the Intersection-Corrected Energies
================================================

The exactness proof only relies on the fact that:

.. math::
   E = \e{\kmeri{m}{1}} = E_{\kmeri{m}{1}}
   
and:

.. math::
    \De{\kmeri{m}{1}} = \e{\kmeri{m}{1}} - 
    \sum_{n=2}^{m-1}\sum_{\nmeri\in\nmers}
      \De{\nmeri} - 
    \sum_{\kmeri{1}{K}\in\nmers} 
      \e{\kmeri{1}{K}}

The defitions of the intersection-corrected energies and interactions of orders
:math:`k\neq m` are immaterial in the exactness proof. Here we show that our
intersection-corrected energies are defined such that the |n|-body approximation
to the energy of the supersystem is given by:

.. math::
   E^{(m,n)} = \sum_{\nmeri}\e{\nmeri} 

   
The base case
-------------

For a system comprsied of a single |n|-mer we have:

.. math::
   E^{(1,n)} = E_{\kmeri{n}{1}}

For arbitrary |n|, it is always true that for the :math:`I=1`-th |n|-mer:

   .. math::
      \sum_{k=1}^{I-1}\sum_{\kmeri{k}{J}\in\powersetk{k}{\nmersuptoi}}
        (-1)^k E_{\left(\bigcap \kmeri{k}{J}\right)\cap \nmeri} = 0

Hence:

.. math::
    E^{(1,n)} =& E_{\kmeri{n}{1}} + 
                \sum_{k=1}^{I-1}\sum_{\kmeri{k}{J}\in\powersetk{k}{\nmersuptoi}}
                (-1)^k E_{\left(\bigcap \kmeri{k}{J}\right)\cap \nmeri}\\
              =& \e{\kmeri{n}{1}}  
 
Proving that the proposed intersection-corrected energy formula does not
under/overcount a system comprised of a single |n|-mer. In the next section we
use induction to prove that this is true for an arbitrary number of |n|-mers.

Proof By Induction
------------------

.. |Fl| replace:: :math:`\mathbb{F}^{\left(m,n\right)}[1:\ell]`
.. |Fl1| replace:: :math:`\mathbb{F}^{\left(m,n\right)}[1:\ell-1]`

We now assume that for :math:`\ell - 1` |n|-mers the following is true:

.. math::
   E^{(\ell - 1,n)} = \sum_{I=1}^{\ell - 1}\e{\kmeri{n}{I}}

It is perhaps a somewhat esoteric point, but the above equation simply states 
that :math:`E^{(\ell - 1, n)}` is the under-/over-counting free approximation 
to the system's energy resulting from using :math:`\ell - 1` |n|-mers. It is
not clamining that this is a good approximation to the system's energy, nor does
it have to be for our current purposes. For example, and simplicity, let |m| be 
2, |l| be 2, and |n|  be 1. In this example, unless the first fragment 
is actually the  entire system, :math:`E^{(\ell - 1, n)}` will be missing 
energies of entire atoms  (specifically the atoms that appear in the second 
fragment, but not the first),  making it a very poor approximation to the 
system's energy. In practice, the only |l| we care about is when |l| equals
"|m| choose |n|"; this proof shows that the route we take to get to "|m| choose
|n|" is under-/over-counting free.

Esoteric point aside, we proceed by creating the ordered set |Fl| by appending 
the |l|-th |n|-mer onto to the ordered set |Fl1|. The approximate energy is 
then given by IEP. We choose to write the IEP as the sum of the :math:`\ell-1` 
approximate energy (which is intersection corrected by assumption) plus the 
energy of the |l|-th |n|-mer, corrected for the intersections of the |l|-th 
|n|-mer with the proceeding :math:`\ell-1` fragments:

.. math::
   E^{(\ell, n)} =& E^{(\ell - 1, n)} + E_{\kmeri{n}{\ell}} - 
                 \sum_{I=1}^{\ell-1} E_{\kmeri{n}{I}\cap\kmeri{n}{\ell}} +
                 \sum_{I=1}^{\ell-2}\sum_{J=I+1}^{\ell-1} 
                   E_{\kmeri{n}{I}\cap\kmeri{n}{J}\cap\kmeri{n}{\ell}} - 
                 \cdots\\
              =& E^{(\ell-1, n)} + E_{\kmeri{n}{\ell}} -  
                 \sum_{k=1}^{\ell-1}
                 \sum_{\kmeri{k}{I}\in
                       \powersetk{k}{\mathbb{F}^{\left(m,n\right)}[1:\ell - 1]}}
                    (-1)^k 
                    E_{\left(\bigcap \kmeri{k}{I}\right)\cap\kmeri{n}{\ell}}\\
              =& E^{(\ell-1, n)} + \e{\kmeri{n}{\ell}}\\              
              =& \sum_{I=1}^{\ell}\e{\kmeri{n}{I}}

Proving it for |l| |n|-mers. 

Exactness of the Many-Body Interactions
=======================================

The next step in the proof is to show that the when the GMBE is truncated at an
|n| not equal to |m| (we already showed |n| equal to |m|) the 
intersection-corrected many-body interactions also do not over-/under-count 
interactions. Truncated at order |n| the GMBE reads:

.. math::
   E^{(m,n)} =  \sum_{\kmeri{1}{I}\in\kmers{1}} \e{\kmeri{1}{I}} + 
   \sum_{\ell=2}^{n}\sum_{\kmeri{\ell}{J}\in\kmers{\ell}}^{\mCk{m}{\ell}} 
     \De{\kmeri{\ell}{J}}

Expanding the the |n|-body intersection-corrected interaction:

.. math::
   E^{(m, n)} =& 
     \sum_{\kmeri{1}{I}\in\kmers{1}} \e{\kmeri{1}{I}} + 
     \sum_{\ell=2}^{n-1}
       \sum_{\kmeri{\ell}{J}\in\kmers{\ell}}^{\mCk{m}{\ell}} 
          \De{\kmeri{\ell}{J}} + \\
     & \sum_{\kmeri{n}{J}\in\kmers{n}}^{\mCn}
        \left[
          \e{\kmeri{n}{J}} - 
          \sum_{\ell=2}^{n-1}
          \sum_{\kmeri{\ell}{K}\in\psetp{\ell}{\kmeri{n}{J}}} 
            \De{\kmeri{\ell}{K}} - 
          \sum_{\kmeri{1}{\ell}\in\psetp{1}{\kmeri{n}{J}}}
          \e{\kmeri{1}{\ell}}       
        \right]

Assuming every fragment shows up in at least one |n|-mer, we have:

.. math::
   \sum_{\kmeri{n}{J}\in\kmers{n}}^{\mCn}
   \sum_{\ell=2}^{n-1}
   \sum_{\kmeri{\ell}{K}\in\psetp{\ell}{\kmeri{n}{J}}} 
     \De{\kmeri{\ell}{K}} =
   \sum_{\ell=2}^{n-1}
   \sum_{\kmeri{\ell}{K}\in\kmers{\ell}}^{\mCk{m}{\ell}} \De{\kmeri{\ell}{K}}

Similarly:

.. math::
   \sum_{\kmeri{n}{J}\in\kmers{n}}^{\mCn}
   \sum_{\kmeri{1}{\ell}\in\psetp{1}{\kmeri{n}{J}}}
     \e{\kmeri{1}{\ell}}  =
   \sum_{\kmeri{1}{\ell}\in\kmers{1}}\e{\kmeri{1}{\ell}}  

and we have:

.. math::
   E^{(m, n)} = \sum_{\kmeri{n}{J}\in\kmers{n}}^{\mCn} \e{\kmeri{n}{J}}

which is just the IEP for |n|-mers.   