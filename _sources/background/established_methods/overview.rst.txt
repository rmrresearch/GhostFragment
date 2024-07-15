.. Copyright 2024 GhostFragment
..
.. Licensed under the Apache License, Version 2.0 (the "License");
.. you may not use this file except in compliance with the License.
.. You may obtain a copy of the License at
..
.. http://www.apache.org/licenses/LICENSE-2.0
..
.. Unless required by applicable law or agreed to in writing, software
.. distributed under the License is distributed on an "AS IS" BASIS,
.. WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
.. See the License for the specific language governing permissions and
.. limitations under the License.

##############################################
Overview of Established Fragment Based Methods
##############################################

TODO: Proper overview instead of bullet points

- Many fragment-based methods started in relative isolation
- Each group called their method something different
- Even when similarities emerge, typically the gropu maintains the method's name
- Tendency to talk about methods as if they're black box methods
  
  - e.g., much in the way that one would say "we ran B3LYP" groups will say
    they "ran ``<insert fragmentation method here>``" with little to few 
    details.

- Unlike established quantum chemistry methods, fragment based methods tend to
  be much more sensitive to the specifics.
- Our argument is that each method can be decomposed into a few key algorithms
- Specifying the algorithms is akin to specifying a method.
- Upon enumating the algorithms we can propose new method names which are more
  in the spirit of black box methods (although the utility of such names over
  just specifying the algorithm pieces is debatable).