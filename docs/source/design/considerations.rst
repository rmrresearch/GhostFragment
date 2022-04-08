#####################
Design Considerations
#####################

.. |n| replace:: :math:`n`
.. |m| replace:: :math:`m`

When designing GhostFragment we have noted the following pertaining to the field
of fragment-based methods:

#. There are a plethora of fragment-based methods
#. These method typically only differ in a handful of ways: how the fragments
   are formed, how |n|-mers are screened, how severed bonds are dealt with, and
   how neglected interactions are approximated.
#. Other

******************************
Fragment Method Considerations
******************************

#. Most methods differ in how they form fragments.
#. Forming fragments is more than grouping atoms, it also requires the ability 
   to assign AOs, and electrons to the fragments and intersections of fragments
#. Most fragment methods start by preliminarily forming pseudoatoms, i.e.,
   disjoint groups of atoms that are never separated.
#. The actual atoms themselves can always be used as a trivial set of 
   pseudoatoms
#. For disjoint fragments, the fragments themselves can be considered 
   pseudoatoms
#. Mapping of AOs and number of electrons needs to be done from pseudoatoms to
   work with intersecting fragments


******************************
N-Mer Formation Considerations
******************************

#. In practice it's the set of overlap-corrected |n|-mers that are used to
   approximate the property.
#. Generally speaking, a set of |n|-mers can be considered a set of overlapping
   fragments ("generally" caveat is required because it's possible, but not
   common, for the |n|-mers to be disjoint).
#. |n|-mers are usually treated differently enough (e.g. are screened, basis of
   MBE and BSSE equations) that they warrant specialized treatment relative to
   fragments.
#. The set of |n|-mers created by simply taking unions of non-disjoint fragments
   can contain |n|-mers which are proper subsets of other |n|-mers
#. GhostFragment treats |m|-mers (|m| < |n|) as intersections, the exception
   is when an |m|-mer is not a proper subset of any |n|-mer (possible when
   screening). In such a case, neglecting the |m|-mer can lead to neglecting
   interactions (and even atoms).
#. Forming |n|-mers, and their intersections, also requires us to assign
   electrons and AOs (can use the fragment assignments)

*****************************
Capping Method Considerations
*****************************

#. It is necessary to cap not only fragments, but |n|-mers, and intersections.
#. Caps (more specifically the atoms replaced by the caps) need to be considered 
   when forming intersections. For example, consider a system A-B which gets 
   fragmented A-H, H-B. Summing A-H and H-B double counts the severed bond. We 
   can approximately account for this double counting by: (A-H) + (H-B) - (H-H).


******************************
Energy Equation Considerations
******************************

#. Most equations pertaining to fragment-based method have redundancy to them,
   e.g. :math:`\sum_I E_I + \sum_{I<J} \Delta E_{IJ}` has the :math:`E_I` terms
   appear multiple times (explicitly in the sum over monomers and implicitly in
   the two-body interactions).
#. The user may actually care about the value of some intermediate quantity,
   e.g., in a conventional MBE the user may want to know the two-body
   interactions. Hence computing the equations in the least redundant format is
   not always desired.
#. The coefficients on a term depend on how the equation is written.
