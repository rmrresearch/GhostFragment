.. _efa_mfcc:

###########################################
Electrostatic Field Adapted MFCC (EFA-MFCC)
###########################################

.. |dclc_frag| replace:: :ref:`DCLC fragmentation<DCLC_fragmentation_method>`
.. |dclc_cap| replace:: :ref:`DCLC_capping_method`
.. |mfcc_embed| replace:: :ref:`ec_mfcc_charges`
 
In an effort to extend the DCLC and EC-MFCC methods to charged systems, 
:cite:t:`Jiang2006` introduced the electrostatic field-adapted MFCC (EFA-MFCC)
method. EFA-MFCC is DCLC with electrostatic embedding via |mfcc_embed| (N.B. 
aside from details on how the fragments are formed, the manuscript is actually a
bit sparse on the details of the EFA-MFCC method and this is our best guess as
to how the EFA-MFCC method waas implemented).  
 
+-------------------+-------------+---------------+------------+---------------+
| Name              | Fragments   | Embedding     | Caps       | Screening     |
+===================+=============+===============+============+===============+
| EFA-MFCC          | |dclc_frag| | |mfcc_embed|  | |dclc_cap| | N/A           |
+-------------------+----------------------------------------------------------+