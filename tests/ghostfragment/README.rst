###################
tests/ghostfragment
###################

This directory's structure is meant to mirror ``src/ghostfragment``. Unit tests
are located in their mirrored positions (*e.g.*, the module defined in
``src/ghostfragment/single_atom.cpp`` is unit tested in
``tests/ghostfragment/single_atom.cpp``). Aside from that, a couple of notes:

- We use Catch2 for unit testing
- ``tests/ghostfragment/testing`` contains unit testing infrastructure. In most
  cases these are functions for generating inputs needed by modules and
  functions defined in GhostFragment.
- ``main.cpp`` is the ``main`` routine used to create the ``test_ghostfragment``
  executable.
