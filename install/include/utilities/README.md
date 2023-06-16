<!--
  ~ Copyright 2022 NWChemEx-Project
  ~
  ~ Licensed under the Apache License, Version 2.0 (the "License");
  ~ you may not use this file except in compliance with the License.
  ~ You may obtain a copy of the License at
  ~
  ~ http://www.apache.org/licenses/LICENSE-2.0
  ~
  ~ Unless required by applicable law or agreed to in writing, software
  ~ distributed under the License is distributed on an "AS IS" BASIS,
  ~ WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ~ See the License for the specific language governing permissions and
  ~ limitations under the License.
-->

Utilities Source Root
=======================

The current directory is the root of the Utilities source tree.  The source
itself is separated into four subtypes for the moment:

- Containers These are classes that implement various non-standard container 
types.
- IterTools  These are classes that aid in condensing multiple loops or 
complicated looping patterns into a single, simple foreach loop.
- Mathematician This directory contains things an omnipotent mathematician 
would know (and isn't in the STL or handled by TAMM).  This includes things 
like factorials, binomial coefficients, *etc.*
- TypeTraits These are various template structures meant to facilitate 
meta-template programming. 
