##################################################
Molecular Fractionation with Conjugate Caps (MFCC)
##################################################

Introduced in 2003 MFCC :cite:`Zhang2003` focused on fragment-based 
calculations of proteins. Using our terminology, the original method treated
individual amino acids as groups, and capped the alpha carbon of the peptide 
bond with NH2 caps and the nitrogen atom with a -RCH2 group (R being the side
chain of the amino acid the cap is replacing). The resulting fragments intersect
with fragments they are bonded to. MFCC pairs the intersections together as a
molecule (instead of treating the intersections individually). Initial small 
basis SCF and DFT (with the B3LYP functional) results focused on water-peptide 
interactions and were shown to be in excellent agreement with supersystem 
results.

In a follow up study :cite:t:`Zhang2003b` considered how the cap choice and
cutting location affected the error by looking at the potential energy surface
for the interaction of a water molecule with a five amino acid peptide. 
Calculations were at the SCF and B3LYP level of theory, with small basis sets 
(3-21G, 3-21+G, 3-21G*, and 6-31G). Results indicated that cutting the bond
between the alpha-carbon and the carbonyl carbon, was better than cutting the
peptide bond (depending on the particular potential energy surface point, could
be more than 1 kcal/mol difference). Cap size was found to have a smaller effect
on the error (about 0.5 kcal/mol). 

******************
Other MFCC Results
******************

:cite:t:`Zhang2003a` applied MFCC to a streptavidin-biotin system, which is a 
121 amino-acid protein. Results are computed using the HF/3-21G model chemistry
and compared to the AMBER force field. Relatively large energetic discrepancies
between the two are noted.