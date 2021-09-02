#################################
Fragment Molecular Orbital Method
#################################

The fragment molecular orbital (FMO) method is arguably one of the most 
established methods in the field of fragment-based methods.

Origins
=======

The FMO method arguably got its start as the pair interaction molecular orbital
method :cite:t:`Kitaura199a`. In the original paper, for a system split into
:math:`N` disjoint fragments, the Hamiltonian for the :math:`I`-th fragment is 
written as:

.. math::
   \widehat{H}_I = \widehat{H}_I^0 + \sum_{J=1; J\neq I}^N\widehat{V}_{IJ}

where :math:`\widehat{H}_I^0` is the Hamiltonian of the :math:`I`-th fragment 
and :math:`\widehat{V}_{IJ}` is the interaction of :math:`I` with :math:`J`. 
:math:`\widehat{V}_{IJ}` is given by density embedding (TODO: link)


Summary

Name | Fragments | Embedding         | Caps
---- | --------- | ----------------- | ----
PIMO | Cluster   | One-body density  | N/A   

