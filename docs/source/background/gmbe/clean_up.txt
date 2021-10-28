
For a three fragment system, truncating the GMBE at dimers we have:

.. math::
   \newcommand{\enm}[2]{E^{\left(#1, #2\right)}}
 
   \enm{3}{2}  = E_{IJ} + E_{IK} + E_{JK} - E_{(IJ)\cap(IK)} - E_{(IJ)\cap(JK)} 
                 - E_{(I\cup K)\cap(J\cup K)} 
                 + E_{(I\cup J)\cap(I\cup K)\cap(J\cup K)}

Using the properties of union and intersections we can clean up the imers to:

.. math::

    E^{(3,2)} = E_{IJ} + E_{IK} + E_{JK} -
                E_{I\cup(J\cap K)} - E_{J\cup (I\cap K)} - E_{K\cup (I\cap J) +
                E_{(I\cap J)\cup (I\cap K)\cup(J\cap K)}


In terms of intersection-corrected dimer energies this becomes:

.. math::
   \newcommand{\E}[1]{\mathcal{E}_{#1}}
   
   \E{IJ} =& E_{IJ}\\
   \E{IK} =& E_{IK} - E_{I\cup(J\cap K)}\\
   \E{JK} =& E_{JK} - E_{J\cup(I\cap K)} - E_{K\cup(I\cap J)} 
             + E_{(I\cap J)\cup (I\cap K)\cup(J\cap K)}

If we add a fourth fragment:

.. math::
   \E{IL} =& E_{IL} -E_{(I)U(J^L)} - E_{(I)U(K^L)} 
             + E_{(I)U(J^K^L)}
             + E_{(I^J)U(I^K)U(J^L)} 
             + E_{(I^J)U(I^K)U(K^L)} 
             - E_{(I^J)U(I^K)U(J^K^L)}
             - E_{(I^J)U(I^K)U(J^L)U(K^L)}\\ 
   \E{JL} =& E_{JL} -E_{(J)U(I^L)} - E_{(J)U(K^L)} - E_{LU(I^J)} 
             + E_{(J)U(I^K^L)} 

             - E_{(I^J)U(K^L)} 

             + E_{(I^J)U(I^L)U(J^K)}
             + E_{(I^J)U(I^L)U(J^L)}
             + E_{(I^J)U(I^L)U(K^L)} 
             + E_{(I^J)U(J^K)U(K^L)} 
             + E_{(I^J)U(J^L)U(K^L)}

             - E_{(I^J)U(I^L)U(J^K^L)} 
             - E_{(I^J)U(J^K)U(I^K^L)} 
             - E_{(I^J)U(J^L)U(I^K^L)} 

             + E_{(I^J)U(I^K^L)U(J^K^L)}

             - E_{(I^J)U(I^L)U(J^K)U(K^L)}\\
   \E{KL} =& E_{KL} - E_{(K)U(I^L)} - E_{(K)U(J^L)} - E_{LU(I^K)} - E_{LU(J^K)}
             
             + E_{(K)U(I^J^L)} + E_{LU(I^J^K)} 
             
             - E_{(I^K)U(J^L)} 
             - E_{(I^L)U(J^K)} 

             + E_{(I^K)U(I^L)U(J^K)} 
             + E_{(I^K)U(J^K)U(J^L)} 
             + E_{(I^K)U(I^L)U(J^L)} 
             + E_{(I^L)U(J^K)U(J^L)} 
             + E_{(I^K)U(I^L)U(K^L)} 
             + E_{(I^L)U(J^K)U(K^L)} 
             + E_{(I^K)U(J^L)U(K^L)} 
             + E_{(J^K)U(J^L)U(K^L)} 

             - E_{(I^K)U(J^K)U(I^J^L)} 
             - E_{(I^K)U(I^L)U(J^K^L)} 
             - E_{(J^K)U(J^L)U(I^K^L)} 
             - E_{(I^L)U(J^L)U(I^J^K)} 
             - E_{(I^K)U(K^L)U(I^J^L)} 
             - E_{(J^K)U(K^L)U(I^J^L)} 
             - E_{(I^L)U(K^L)U(I^J^K)} 
             - E_{(J^L)U(K^L)U(I^J^K)}

             + E_{(I^J^L)U(I^K)U(J^K^L)} 
             + E_{(J^K)U(I^J^L)U(I^K^L)} 
             + E_{(I^L)U(I^J^K)U(J^K^L)} 
             + E_{(J^L)U(I^J^K)U(I^K^L)} 
             + E_{(K^L)U(I^J^K)U(I^J^L)} 

             - E_{(I^K)U(I^L)U(J^K)U(J^L)}

             - E_{(I^J^K)U(I^J^L)U(I^K^L)U(J^K^L)}



which shows that for each dimer XY we get:

- the dimer
- terms like X\cup (I\cap Y) and Y\cup (I\cap X)
  - you get a X\cup(I\cap Y) term for every I less than Y (skipping X)
  - you get a Y\cup(I\cap X) term for every I less than X (skipping Y)
- terms like X\cup (I\cap J\cap Y) and Y\cup (I\cap J\cap X)
  - you get a X\cup(I\cap J\cap Y) term for every I and J less than Y 
    (skipping X)
  - you get a Y\cup(I\cap J\cap X) term for every I and J less than X 
    (skipping Y)
- etc. up to X\cup(I\cap J\cap ...\cap N-2 \cap Y)
- dimers of idimers like (I\cap X)\cup(J\cap Y) and (I\cap Y)\cup(J\cap X)
  - (I\cap X)\cup(J\cap Y) for every IJ where J < Y
  - (I\cap Y)\cup(J\cap X) for every IJ where J < X
- dimers of an idimer and an itrimer etc.   
- trimer of idimers 
- trimer of two idimers and one itrimer
- trimer of one idimer and two itrimers

pairwise intersections of dimers IX and IY generate: 
- I\cup (X\cap Y) and 
pairwise intersections of dimers IJ and XY generate:
- (I^X)(I^Y)(X^J)(Y^J)
three-way intersections of dimers IX, IY, IZ
- I\cup (X\cap Y\cap Z)
three-way intersection of dimers IX, IY, WZ
- (I^X)U(I^Y)U(W^Z)
three-way intersection of dimers IJ, KL, XY

It bears mentioning that the "less than" criteria is specifically tied to our
particular ordering scheme, *i.e.*, if you choose a different ordering scheme
you're going to have different criteria.