# Build the Documentation for GhostFragment

This directory contains the source files for GhostFragment's documentation. 
The documentation has two parts: the C++ API documentation, and reST-based
narrative documentation (design, tutorials, etc.). The documentation hosted
on GitHub ([link](https://rmrresearch.github.io/GhostFragment/)) combines the
two pieces into a single cohesive document. The joining of the two pieces
is actually the responsibility of the GitHub action which deploys the
documentation.

When you are writing documentation it is often helpful to build the
documentation locally so that you can visualize your changes. Locally, the
two pieces of the documentation are build separately, so follow the
instructions for the piece you want to build.

## Build C++ API

Building the C++ API documentation is managed by CMake. In the root
directory run:

```.sh
cmake -H. -Bbuild -DBUILD_DOCS=TRUE -DONLY_BUILD_DOCS=TRUE
cmake --build build --target ghostfragment_cxx_api
```

This will create a directory `build/html` in the root directory which contains 
`index.html` (among a number of other files). Direct your webbrowser at
`index.html` to view the C++ API documentation.

## Build reST-Based Documentation

The reST-Based documentation relies on Sphinx. We strongly recommend you use
a virtual Python environment to install the dependencies for the reST-based
documentation (including Sphinx). To create, and activate, a virtual 
environment named `venv` run the following:

```.sh
python3 -m venv venv
source venv/bin/activate
```

This will create a directory `venv/` in your current directory which will be
used to install the dependencies for the documentation. To install the
dependencies run (in this directory):

```.sh
pip install -r requirements.txt
```

Once the dependencies are installed you can build the actual documentation by
running (again in this directory):

```.sh
make html
```

which will create a directory `build/docs/html` in your current directory. To
view the documentation simply direct your webbrowser to 
`build/docs/html/index.html`