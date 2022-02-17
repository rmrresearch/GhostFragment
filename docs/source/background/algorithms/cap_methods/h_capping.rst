#########
H Capping
#########

.. |X| replace:: :math:`X`
.. |Y| replace:: :math:`Y`
.. |F| replace:: :math:`F`

******************
Simple Replacement
******************

The simplest possible capping scheme. When a bond between an atom |X| and an
atom |Y| is severed such that |X| is in the fragment |F|, but |Y| is not. This 
capping scheme adds a hydrogen atom to |F| at the location of |Y|.

*****************
Standard Distance
*****************

This capping scheme is a slight variation on :ref:`simple replacement`. Given a 
bond  between an atom |X| and an atom |Y| which has been severed such that |X| 
is in the fragment |F|, but |Y| is not, this capping scheme adds a hydrogen atom
to |F| such that the |X|-H bond length corresponds to the length of a "typical 
|X|-H bond". In general the location of the cap will NOT be the location of |Y|.


In the context of MTA this capping scheme is first described by
:cite:t:`Babu2003`. A more detailed description is given later by 
:cite:t:`Rahalkar2011`. To our knowledge, the exact values of thes tandard bond 
length is not given.

*****************
Weighted Distance
*****************

.. |XY| replace:: :math:`X-Y`
.. |c|  replace:: :math:`c`

As part of the SMF method :cite:t:`Deev2005` introduced a capping method. Say
we are breaking a bond |XY| and that |X| is in the fragment, then a hydrogen
atom is placed at the point :math:`\mathbf{r}_H` given by:

.. math::

   \mathbf{r}_H = \mathbf{r}_X + c\left(\mathbf{r}_Y - \mathbf{r}_X\right),

where :math:`\mathbf{r}_X` is the position of |X|, :math:`\mathbf{r}_Y` is the
position of |Y|, and |c| is the ratio of a normal :math:`X-H` bond to a normal
|XY| bond. 