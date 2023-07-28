.. _MFCC:

##################################################
Molecular Fractionation with Conjugate Caps (MFCC)
##################################################

.. |mfcc_f| replace:: :ref:`mfcc_frag_method`
.. |h_cap|  replace:: :ref:`simple_replacement`

Introduced in 2003, MFCC :cite:`Zhang2003` focused on fragment-based 
calculations of proteins. The original MFCC method uses the |mfcc_f| and the
|h_cap| capping method (or at least we assume it does since the manuscript only
mentions adding hydrogen atoms). 
The resulting fragments intersect with the fragments they are bonded to. Instead 
of directly using the IEP, MFCC corrects for intersections by combining the 
intersections into molecules (for each non-terminal amino acid, the left and
right intersections are combined into a molecule). Initial small basis SCF and 
DFT (with the B3LYP functional) results focused on water-peptide interactions 
and were shown to be in excellent agreement with supersystem results.

.. todo::
   
   The next two paragraphs do not seem to be consistent with our terminology.

In a follow up study :cite:t:`Zhang2003b` considered how the cap choice and
cutting location affected the error by looking at the potential energy surface
for the interaction of a water molecule with a five amino acid peptide. 
Calculations were at the SCF and B3LYP level of theory, with small basis sets 
(3-21G, 3-21+G, 3-21G*, and 6-31G). Results indicated that cutting the bond
between the alpha-carbon and the carbonyl carbon, was better than cutting the
peptide bond (depending on the particular potential energy surface point, could
be more than 1 kcal/mol difference). Cap size was found to have a smaller effect
on the error (about 0.5 kcal/mol). 

The next development came when :cite:t:`Chen2004` applied MFCC to proteins 
containing disulfide bonds. In addition to severing the alpha carbon-carbonyl
carbon bonds, the sulfide bonds were also severed. They considered two capping 
strategies for the severed sulfide bonds: hydrogen atoms, or methyls. The latter
was found to afford better results. Sample calculations were at the SCF, B3LYP, 
and MP2 levels of theory paired with several small basis sets (at most 6-31G). 

+-------------------+-------------+---------------+------------+---------------+
| Name              | Fragments   | Embedding     | Caps       | Screening     |
+===================+=============+===============+============+===============+
| MFCC              | |mfcc_f|    | N/A           | |h_cap|    | N/A           |
+-------------------+-------------+---------------+------------+---------------+

******************
Other MFCC Results
******************

:cite:t:`Zhang2003a` applied MFCC to a streptavidin-biotin system, which is a 
121 amino-acid protein. Results are computed using the HF/3-21G model chemistry
and compared to the AMBER force field. Relatively large energetic discrepancies
between the two are noted.