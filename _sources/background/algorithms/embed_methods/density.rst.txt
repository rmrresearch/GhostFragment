.. Copyright 2024 GhostFragment
..
.. Licensed under the Apache License, Version 2.0 (the "License");
.. you may not use this file except in compliance with the License.
.. You may obtain a copy of the License at
..
.. http://www.apache.org/licenses/LICENSE-2.0
..
.. Unless required by applicable law or agreed to in writing, software
.. distributed under the License is distributed on an "AS IS" BASIS,
.. WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
.. See the License for the specific language governing permissions and
.. limitations under the License.

.. _density_embedding:

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
:math:`r`. Since the Hamiltoniann for each fragment depends on the densities of
the remaining fragments, the densities must be solved for iteratively.

For embedding higher-order :math:`n`-mers, one typically uses the converged
fragment densities and does not iterate using the :math:`n`-mer Hamiltonians.

.. _fmo02_embedding:

***************
FMO02 Embedding
***************

The FMO02 embedding method :cite:t:`Nakano2002`: introduces two approximations
into traditional density embedding based on the separation between |I| and |J|. 
For moderately separated |I| and |J|:

.. math::

   V^{IJ}_{\mu\nu} = \sum_{\lambda\in J}
                     \left(\mathbf{P}^{J}\mathbf{S}\right)_{\lambda\lambda}
                     \left(\mu\nu \middle| \lambda\lambda\right)

for :math:`\mu,\nu\in I`. The quantity 
:math:`\left(\mathbf{P}^{J}\mathbf{S}\right)_{\lambda\lambda}` is the Mulliken
population of orbital :math:`\lambda`. \For distant |I| and |J|:                  

.. math::

   V^{IJ}_{\mu\nu} \approx \sum_{A\in J}
                    \Braket{\mu | \frac{Q_A}{\mid r_i - r_A\mid} | \nu}
               

where :math:`A` indexes atoms, and :math:`Q_A` is the Mulliken charge of atom
:math:`A` (the sum of the Mulliken populations on atom :math:`A`).