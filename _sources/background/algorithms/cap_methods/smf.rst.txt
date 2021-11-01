#################################################
Systematic Molecular Fragmentation Capping Method
#################################################

.. |X| replace:: :math:`X`
.. |Y| replace:: :math:`Y`
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