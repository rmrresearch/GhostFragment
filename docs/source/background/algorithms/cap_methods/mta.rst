###########
MTA Capping
###########

.. |X| replace:: :math:`X`
.. |Y| replace:: :math:`Y`
.. |F| replace:: :math:`F`

.. note::

   While we have called this the MTA capping scheme it is one of the most 
   straightforward capping schemes and likely was in use prior to MTA.

In the context of MTA this capping scheme is first described by
:cite:t:`Babu2003`. A more detailed description is given later by 
:cite:t:`Rahalkar2011`. 

This capping scheme is a slight variation on ref:`h capping`. Given a bond 
between an atom |X| and an atom |Y| which has been severed such that |X| is in 
the fragment |F|, but |Y| is not, this capping scheme adds a hydrogen atom to 
|F| such that the |X|-H bond length corresponds to the length of a "typical 
|X|-H bond". In general the location of the cap will NOT be the location of |Y|.
In the context of MTA, the exact value of this standard bond length is not
given.

