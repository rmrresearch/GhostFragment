#################
Density Embedding
#################

.. |I| replace:: :math:`I`
.. |J| replace:: :math:`J`

For fragment-based methods, density embedding was introduced in the context of 
the Pair-Interaction Molecular Orbital Method :cite:t:`Kitaura1999a`. In density
embedding, :math:`\widehat{V}_{IJ}` is the potential fragment |I| feels because 
of the electron density and nuclei of fragment |J|. Mathematically this is:

.. math::
   \widehat{V}_{IJ} = \sum_{i=1}^{n_I}\left[
                     \int dr \frac{\rho_J(r)}{|r-r_i|} -
                     \sum_{A}^{N_A}\frac{Z_A}{|r_i-r_A|}\right]

where :math:`i` runs over the :math:`n_I` electrons in fragment |I|, 
:math:`A` runs over the :math:`N_A` nuclei in fragment |J|, and
:math:`\rho_J(r)` is the electron density of fragment |J| evaluated at 
:math:`r`.
