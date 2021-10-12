#########################################
Terminology Used Throughout GhostFragment
#########################################

.. |n| replace:: :math`n`

There are a lot of existing fragment-based methods. Many of these methods have
coined their own terms for similar concepts. In order to provide a unified
description of these methods we have settled on the following terminology.

fragment
   The inputs to the MBE and GMBE. Fragments are sets of pseudoatoms.

pseudoatom
   In fragmenting the supersystem there are some most fundamental units, *i.e.*
   units which themselves are never fragmented. In the most extreme limit these
   fundamental units are the individual atoms; however, in most fragmentation
   algorithms the fundamental units involve several atoms. For example, in
   fragmenting a molecular cluster a popular and obvious choice is to take the
   molecules as the fundamental units. Regardless of their composition, the most
   fundamental units of the fragmentation algorithm are termed "pseudoatoms."

supersystem
   This is the system whose properties are actually of interest. Its properties
   are computed by fragmenting it into subsystems.
