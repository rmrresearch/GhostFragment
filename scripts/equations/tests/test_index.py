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

import unittest
import sys
import os

sys.path.insert(0, os.path.join(os.getcwd(), ".."))

from union import Union
from intersection import Intersection
from index import Index


class IndexTest(unittest.TestCase):

    def setUp(self):
        self.i = Index("I")
        self.j = Index("J")

    def test_clean_up(self):
        self.assertEqual(self.i.clean_up(), Index("I"))
        self.assertEqual(self.j.clean_up(), Index("J"))

    def test_is_union(self):
        self.assertFalse(self.i.is_union())
        self.assertFalse(self.j.is_union())

    def test_is_intersection(self):
        self.assertFalse(self.i.is_intersection())
        self.assertFalse(self.j.is_intersection())

    def test_is_index(self):
        self.assertTrue(self.i.is_index())
        self.assertTrue(self.j.is_index())

    def test_is_proper_subset(self):
        self.assertFalse(self.i.is_proper_subset(Index("I")))
        self.assertFalse(self.i.is_proper_subset(self.j))
        self.assertFalse(self.i.is_proper_subset(Union(self.i)))
        self.assertTrue(self.i.is_proper_subset(Union(self.i, self.j)))
        self.assertFalse(self.i.is_proper_subset(Intersection(self.i)))
        self.assertFalse(self.i.is_proper_subset(Intersection(self.i, self.j)))


if __name__ == "__main__":
    unittest.main()
