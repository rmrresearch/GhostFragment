#########
H Capping
#########

.. |X| replace:: :math:`X`
.. |Y| replace:: :math:`Y`
.. |F| replace:: :math:`F`

.. _simple_replacement:

******************
Simple Replacement
******************

The simplest possible capping scheme. When a bond between an atom |X| and an
atom |Y| is severed such that |X| is in the fragment |F|, but |Y| is not. This 
capping scheme adds a hydrogen atom to |F| at the location of |Y|.

.. _standard_distance_capping:

*****************
Standard Distance
*****************

This capping scheme is a slight variation on :ref:`simple_replacement`. Given a 
bond  between an atom |X| and an atom |Y| which has been severed such that |X| 
is in the fragment |F|, but |Y| is not, this capping scheme adds a hydrogen atom
to |F| such that the |X|-H bond length corresponds to the length of a "typical 
|X|-H bond". In general the location of the cap will NOT be the location of |Y|.


In the context of MTA this capping scheme is first described by
:cite:t:`Babu2003`. A more detailed description is given later by 
:cite:t:`Rahalkar2011`. To our knowledge, the exact values of the standard bond 
length is not given.

.. _DCLC_capping_method:

*******************
DCLC Capping Method
*******************

:cite:t:`Li2004` introduced a capping method which is a slight variation on the
:ref:`standard_distance_capping` method. If we are breaking an |X|-|Y| bond,
the |X|-H bond distance is set to the average of any existing |X|-H bonds (e.g.,
if we are capping a carbon which is part of a CH2 group, you average the two
existing C-H bonds). If there are no other |X|-H bonds the DCLC capping method
falls back to :ref:`standard_distance_capping`.

One of the somewhat unique features of DCLC is that it allows for severing
non-standard bonds (e.g. multiple bonds, or bonds on charged species). To
accomplish this, DCLC actually includes two more steps beyond placing the
original H caps. First, one adds or removes additional hydrogens to |X| in order
to satisfy the valency of |X| (adding is needed when severing a multiple bond,
whereas removing is needed when |X| is positively charged). Second, a 
constrained geometry optimization is performed (only the caps can move) to 
obtain the final positions. N.B. the geometry optimizaton is only performed if
the origninal |X|-H capping was insufficient.

:cite:t:`Li2004` provided the standard distances of 1.07, 1.00, and 0.96 
:math:`\AA` for C-H, N-H, and O-H bonds respectively.

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