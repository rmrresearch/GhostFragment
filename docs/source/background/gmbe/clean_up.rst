
For a three fragment system, truncating the GMBE at dimers we have:

.. math::
    E^{(3,2)} = E_{IJ} + E_{IK} + E_{JK} - E_{(IJ)\cap(IK)} - E_{(IJ)\cap(JK)} -
    E_{(I\cup K)\cap(J\cup K)} + E_{(I\cup J)\cap(I\cup K)\cap(J\cup K)}

Using the properties of union and intersections we can clean this up to:

.. math::

    E^{(3,2)} = E_{IJ} + E_{IK} + E_{JK} -
                E_{I\cup(J\cap K)} - E_{J\cup (I\cap K)} - E_{K\cup (I\cap J) +
                E_{(I\cap J)\cup (I\cap K)\cup(J\cap K)}

For a four fragment system, trucnating the GMBE at dimers we get:

.. math::
   E^{(4,2)} = E_{IJ} + E_{IK} + E_{IL} + E_{JK} + E_{JL} + E_{KL}
               - E_{IU(J^K)} - E_{IU(J^L)} - E_{IU(K^L)}
               - E_{JU(I^K)} - E_{JU(I^L)} - E_{JU(K^L)}
               - E_{KU(I^J)} - E_{KU(I^L)} - E_{KU(J^L)}
               - E_{LU(I^J)} - E_{LU(I^K)} - E_{LU(J^K)}

               + E_{IU(J^K^L)} + E_{JU(I^K^L)} + E_{KU(I^J^L)} + E_{LU(I^J^K)}

               -E_{(I^J)U(K^L)} - E_{(I^K)U(J^L)} - E_{(I^L)U(J^K)}

               + E_{(I^J)U(I^K)U(J^K)} + E_{(I^J)U(I^K)U(J^L)} + E_{(I^J)U(I^K)U(K^L)} 
               + E_{(I^J)U(I^L)U(J^K)} + E_{(I^J)U(I^L)U(J^L)} + E_{(I^J)U(I^L)U(K^L)} 
               + E_{(I^J)U(J^K)U(K^L)} 
               + E_{(I^J)U(J^L)U(K^L)}                
               + E_{(I^K)U(I^L)U(J^K)} + E_{(I^K)U(I^L)U(J^L)} + E_{(I^K)U(I^L)U(K^L)}
               + E_{(I^K)U(J^K)U(J^L)} 
               + E_{(I^K)U(J^L)U(K^L)}
               + E_{(I^L)U(J^K)U(J^L)} + E_{(I^L)U(J^K)U(K^L)} 
               + E_{(J^K)U(J^L)U(K^L)}


               - E_{(I^J)U(I^K)U(J^K^L)}
               - E_{(I^J)U(I^L)U(J^K^L)}
               - E_{(I^J)U(J^K)U(I^K^L)}
               - E_{(I^J)U(J^L)U(I^K^L)}
               - E_{(I^K)U(I^L)U(J^K^L)}
               - E_{(I^K)U(J^K)U(I^J^L)}
               - E_{(I^K)U(K^L)U(I^J^L)} 
               - E_{(I^L)U(J^L)U(I^J^K)}
               - E_{(I^L)U(K^L)U(I^J^K)} 
               - E_{(J^K)U(J^L)U(I^K^L)}
               - E_{(J^K)U(K^L)U(I^J^L)} 
               - E_{(J^L)U(K^L)U(I^J^K)}

               + 1.0E_{(I^J)U(I^K^L)U(J^K^L)} 
               + 1.0E_{(I^K)U(I^J^L)U(J^K^L)} 
               + 1.0E_{(I^L)U(I^J^K)U(J^K^L)} 
               + 1.0E_{(J^K)U(I^J^L)U(I^K^L)}
               + 1.0E_{(J^L)U(I^J^K)U(I^K^L)}
               + 1.0E_{(K^L)U(I^J^K)U(I^J^L)}

               -1.0E_{(I^J)U(I^K)U(J^L)U(K^L)}
               -1.0E_{(I^J)U(I^L)U(J^K)U(K^L)}
               -1.0E_{(I^K)U(I^L)U(J^K)U(J^L)}

               - 1.0E_{(I^J^K)U(I^J^L)U(I^K^L)U(J^K^L)}


.. math::
   \sum_{I = 1}^{N-1}\sum_{J = I + 1}^N E_{IJ} -
   \sum_{I = 1}^N\sum_{J< K} E_{I\cup (J\cap K)} +
   \sum_{I = 1}^N\sum_{J<K<L} E_{I\cup (J\cap K\cap L)}