.. _ecmfcc:

#####################
Energy-Corrected MFCC
#####################

EC-MFCC was introduced by :cite:t:`Li_2005` as a follow-up to the :ref:`DCLC`
fragment-based method. EC-MFCC differs from DCLC in that it also inclues 
two-body, and higher, interactions among the pseudoatoms (our terminology; the 
original manuscript refers to them as fragments). At the one-body level EC-MFCC
is the same as DCLC. Since it uses essentially two fragmentation methods, from
our perspective, EC-MFCC is a multi-layer fragment-based method. The first layer
is a traditional MBE using pseudoatoms as fragments  and the 
:ref:`DCLC_capping_method`. The second layer is the DCLC calculation. Hence the 
energy for the two-body EC-MFCC method is given by:

.. math::

   E \approx& \left(\sum_{I} E_I +\sum_{I<J}\Delta E_{IJ}\right) +
       \left(E^{DCLC} - \sum_{I}E_I\right)\\
     \approx& E^{DCLC} + \sum_{I<J}\Delta E_{IJ}

where summation indices are pseudoatoms and :math:`E^{DCLC}` is the energy of
the fragments computed using a 1-body GMBE (fragments/pseudoatoms again
adhereing to our terminology).