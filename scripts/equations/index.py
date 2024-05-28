# Copyright 2024 GhostFragment
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


class Index:

    def __init__(self, value):
        self.value = value

    def print_type(self):
        return "Index"

    def clean_up(self):
        return self

    def is_union(self):
        return False

    def is_intersection(self):
        return False

    def is_index(self):
        return True

    def is_proper_subset(self, rhs):
        """Returns whether or not this Index instance is a proper subset of
           `rhs`.

        Indices are the smallest indivisible elements in our class hierarchy.
        This means they can not be proper subsets of other Indices or
        intersections (an intersection which contains an Index is either equal
        to that index or is a subset of that index). They can be subsets of
        unions, however.

        :param rhs: The object we are comparing to.
        :type rhs: Index, Union, or Intersection
        :return: True if `rhs` is a Union, which contains this index and at
                 least one other element. False otherwise.
        :rtype: boolean
        """
        if rhs.is_union():
            if rhs.count(self) == 0:
                return False
            elif len(rhs) > 1:
                return True
        return False

    def is_proper_superset(self, rhs):
        """Returns whether or not this Index instance is a proper superset of
           `rhs`.

        *N.B.* in our class hierarchy, an Index is an indvisible unit. Thus it
        it is never a proper superset of anything, other than the empty set
        (which we never encounter). Hence this function always returns False.

        :param rhs: The object we are comparing to.
        :type rhs: Index, Union, or Intersection
        :return: False because an index is never a superset of anything
        :rtype: boolean
        """
        return False

    def associate(self):
        return self

    def distribute(self):
        return self

    def __lt__(self, rhs):
        if rhs.is_index():
            return self.value < rhs.value
        return True

    def __len__(self):
        return 1

    def __repr__(self):
        return str(self)

    def __str__(self):
        return str(self.value)

    def __eq__(self, rhs):
        if type(rhs) == Index:
            return self.value == rhs.value
        return False
