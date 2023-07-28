###############################
How to Add a New Capping Method
###############################

************************************
Where do I Put a New Capping Method?
************************************

C++
===

C++ capping methods live in ``src/ghostfragment/capping``. Each capping method
should be implemented as a module (TODO: link to PluginPlay module). The name
of the module should reflect the algorithm in the module. For example the 
``SingleAtom`` module uses a single atom to cap all bonds. It is common C++
practice to name the source file based on the algorithm within it. So, the
``SingleAtom`` module lives in ``src/ghostfragment/capping/single_atom.cpp``.

****************************************
How do I Implement a New Capping Method?
****************************************

C++
===

1. Once you know the name for module, add a corresponding ``DECLARE_MODULE`` 
   statement to ``src/ghostfragment/capping/capping.hpp``
2. Update ``load_modules`` in ``src/ghostfragment/capping/capping.hpp`` so that
   it loads your module.
3. If applicable, modify ``set_defaults`` in ``src/ghostfragment/capping.hpp``
   so that it sets the default submodules for your new module.
4. In ``src/ghostfragment/capping/name_of_your_module.cpp`` create a new module
   satisfying the property type ``Capped<T>``.
