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

class SetBase:
    def __init__(self, *args):
        self.terms = []
        # This makes sure we only add unique elements
        for x in args:
            is_good = True
            for y in self.terms:
                if x == y:
                    is_good = False
                    break
            if is_good:
                self.terms.append(x)
        self.terms.sort()

    def count(self, elem):
        # This exploits that only unique elements are stored
        for x in self.terms:
            if x == elem:
                return 1
        return 0

    def is_union(self):
        return False

    def is_intersection(self):
        return False

    def is_index(self):
        return False

    def __len__(self):
        return len(self.terms)

    def __repr__(self):
        return str(self)

    def __getitem__(self, idx):
        return self.terms[idx]
