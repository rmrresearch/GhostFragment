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

from set_base import SetBase
class Union(SetBase):
    """ Class representing a set which has been formed by taking the symbolic
        union of one or more objects.
    """
    def print_type(self):
        rv = "Union("
        for x in self.terms:
            rv += x.print_type() + ","
        return rv + ")"

    def is_union(self):
        return True

    def is_proper_subset(self, rhs):
        """ Determines if the current Union instance is a proper subset of `rhs`

        Unions can only be proper subsets of other unions. An index is
        essentially a single element union; since we don't have any empty sets,
        it is not possible for a Union instance to contain less elements than
        an index. Similar logic applies to intersections containing one index.
        If an intersection contains more than one index, it is necessarilly a
        proper subset of anything containing any of the indices in the
        intersection.
        """
        if rhs.is_union():
            # rhs must contain more elements
            if len(rhs) <= len(self):
                return False

            # Every element in this union must be in rhs
            for x in self.terms:
                if rhs.count(x) == 0:
                    return False
            return True

        # Getting here means we have an index or an intersection
        return False


    def clean_up(self):
        new_terms = [x.clean_up() for x in self.terms]
        final_terms = []
        nterms = len(new_terms)
        for i in range(nterms):
            termi = self.terms[i]
            is_good = True
            for j in range(nterms):
                if i == j:
                    continue
                termj = self.terms[j]
                if termi.is_proper_subset(termj):
                    is_good = False
                    break
            if is_good:
                final_terms.append(termi)
        if len(final_terms) == 1:
            return final_terms[0]
        return Union(*final_terms)

    def associate(self):
        new_terms = []
        for i in range(len(self.terms)):
            new_term = self.terms[i].associate()
            if new_term.is_union():
                for x in new_term:
                    new_terms.append(x)
            else:
                new_terms.append(new_term)
        return Union(*new_terms)

    def distribute(self):
        new_me = self.associate()
        new_terms = []
        for x in new_me.terms:
            new_terms.append(x.distribute())
        return Union(*new_terms).associate()


    def __lt__(self, rhs):
        if rhs.is_index(): 
            return False
        elif rhs.is_intersection():
            return True
        else:
            if len(self.terms) < len(rhs.terms):
                return True
            return self.terms < rhs.terms

    def __str__(self):
        sym = "U"

        rv = ""
        for i in range(len(self.terms)):
            x_str = str(self.terms[i])

            if self.terms[i].is_intersection():
               x_str = "(" + x_str + ")"

            if i == 0:
                rv = x_str
                continue

            rv += sym + x_str
        return rv

    def __eq__(self, rhs):
        if type(rhs) == Union:
            if len(rhs.terms) != len(self.terms):
                return False

            # Order doesn't matter
            for x in self.terms:
                if rhs.count(x) == 0:
                    return False
            return True
        return False
