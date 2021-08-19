.. |m| replace:: :math:`m`
.. |n| replace:: :math:`n`
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

Proof that Intersection-Corrected Energies Do Not Double Count
==============================================================

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

For a single fragment we have:

.. math::
   E^{(1,1)} = E_{\kmeri{1}{1}}

For arbitrary |n| (inlcuding :math:`n=1`), it is always true that for the 
:math:`I=1`-th |n|-mer:

   .. math::
      \sum_{k=1}^{I-1}\sum_{x\in\powersetk{k}{\nmersuptoi}}
        (-1)^k E_{\left(\bigcap x\right)\cap \nmeri} = 0

Hence:

.. math::
    E^{(1,1)} =& E_{\kmeri{1}{1}} + 
                \sum_{k=1}^{I-1}\sum_{x\in\powersetk{k}{\nmersuptoi}}
                (-1)^k E_{\left(\bigcap x\right)\cap \nmeri}\\
              =& \e{\kmeri{1}{1}}  
 
Proving it for the base case.

Proof By Induction
------------------

.. |Fm| replace:: :math:`\mathbb{F}^{\left(m\right)}`
.. |Fm1| replace:: :math:`\mathbb{F}^{\left(m-1\right)}`

We now assume that for :math:`m-1` fragments the following is true:

.. math::
   E^{(m-1,1)} = \sum_{I=1}^{m-1}\e{\kmeri{1}{I}}
   
and create the ordered set |Fm| by appending the |m|-th fragment to the ordered 
set |Fm1|. The approximate one-body energy is then given by IEP. We choose to
write the IEP as the sum of the
:math:`m-1` approximate energy (which is intersection corrected by assumption)
plus the energy of the |m|-th fragment, corrected for the intersections of the
|m|-th fragment with the proceeding :math:`m-1` fragments:

.. math::
   E^{(m, 1)} =& E^{(m-1, 1)} + E_{\kmeri{1}{m}} - 
                 \sum_{I=1}^{m-1} E_{\kmeri{1}{I}\cap\kmeri{1}{m}} +
                 \sum_{I=1}^{m-2}\sum_{J=I+1}^{m-1} 
                   E_{\kmeri{1}{I}\cap\kmeri{1}{J}\cap\kmeri{1}{m}} - \cdots\\
              =& E^{(m-1, 1)} + E_{\kmeri{1}{m}} -  
                 \sum_{k=1}^{m-1}\sum_{\kmeri{k}{I}\in\mathbb{F}^{(m-1, k)}}
                    (-1)^k E_{\left(\bigcap \kmeri{k}{I}\right)\cap\kmeri{1}{m}}         

Using:

.. math::
   \mathbb{F}^{\left(m-1, k\right)} = 
    \powersetk{k}{\mathbb{F}^{\left(m,1\right)}[1:m-1]}

we have:

.. math::
    E^{(m, 1)}=& E^{(m-1, 1)} + E_{\kmeri{1}{m}} -  
                 \sum_{k=1}^{m-1}\sum_{\kmeri{k}{I}\in
                    \powersetk{k}{\mathbb{F}^{\left(m,1\right)}[1:m-1]}}
                    (-1)^k E_{\left(\bigcap \kmeri{k}{I}\right)\cap\kmeri{1}{m}}\\
               =& E^{(m-1, 1)} + \e{\kmeri{1}{m}}\\
               = \sum_{I=1}^{m}\e{\kmeri{1}{I}}

Proving it for :math:`m` fragments.

Subject to the caveat that equality with :math:`E^{(m,n)}` is only achieved when
the summation runs over all |m| choose |n| intersection-corrected energies, the
above proof can be replicated with minor modifications to also prove this 
for arbitrary |n|. In other words the definition of the intersection-corrected
energies are simply a partitioning of the IEP, and work regardless of |n| or 
|m|.
