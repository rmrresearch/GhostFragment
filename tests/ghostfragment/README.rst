###################
tests/ghostfragment
###################

This directory's structure is meant to mirror ``src/ghostfragment``. Unit tests
are located in their mirrored positions (*e.g.*, the module defined in
``src/ghostfragment/single_atom.cpp`` is unit tested in
``tests/ghostfragment/single_atom.cpp``). To facilitate unit testing
``tests/ghostfragment/testing`` contains a series of functions which will
generate inputs commonly needed by many of the unit tests (*e.g.*, molecules,
basis sets, fragments).
