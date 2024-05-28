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


class IntersectionTest(unittest.TestCase):
    def setUp(self):
        i, j, k, l = Index("I"), Index("J"), Index("K"), Index("L")
        self.icj = Intersection(i, j)
        self.icjck = Intersection(self.icj, k)
        self.icjckcl = Intersection(self.icj, Intersection(k, l))
        self.icjk = Intersection(i, Union(j, k))

    def test_is_union(self):
        self.assertFalse(self.icj.is_union())
        self.assertFalse(self.icjck.is_union())
        self.assertFalse(self.icjckcl.is_union())
        self.assertFalse(self.icjk.is_union())
    
    def test_is_intersection(self):
        self.assertTrue(self.icj.is_intersection())
        self.assertTrue(self.icjck.is_intersection())
        self.assertTrue(self.icjckcl.is_intersection())
        self.assertTrue(self.icjk.is_intersection())

    def test_is_index(self):
        self.assertFalse(self.icj.is_index())
        self.assertFalse(self.icjck.is_index())
        self.assertFalse(self.icjckcl.is_index())
        self.assertFalse(self.icjk.is_index())

    def test_associate(self):      
        i, j, k, l = Index("I"), Index("J"), Index("K"), Index("L")

        corr = Intersection(i, j)
        self.assertEqual(self.icj.associate(), corr)
        
        corr = Intersection(i, j, k)
        self.assertEqual(self.icjck.associate(), corr)

        corr = Intersection(i, j, k, l)
        self.assertEqual(self.icjckcl.associate(), corr)

        ijkl_2 = Intersection(i, Intersection(j, Intersection(k, l)))
        self.assertEqual(ijkl_2.associate(), Intersection(i, j, k, l))

        jk = Union(j, k)
        corr = Intersection(i, jk)
        self.assertEqual(self.icjk.associate(), corr)

        i_jck_jk = Intersection(i, jk, Intersection(j, k))
        self.assertEqual(i_jck_jk.associate(), Intersection(i, jk, j, k))

    def test_distribute(self):
        i, j, k, l = Index("I"), Index("J"), Index("K"), Index("L")

        corr = Intersection(i, j)
        self.assertEqual(self.icj.distribute(), corr)
        
        corr = Intersection(i, j, k)
        self.assertEqual(self.icjck.distribute(), corr)

        corr = Intersection(i, j, k, l)
        self.assertEqual(self.icjckcl.distribute(), corr)

        ijkl_2 = Intersection(i, Intersection(j, Intersection(k, l)))
        self.assertEqual(ijkl_2.distribute(), Intersection(i, j, k, l))

        jk = Union(j, k)
        corr = Union(Intersection(i, j), Intersection(i, k))
        self.assertEqual(self.icjk.distribute(), corr)

        i_jck_jk = Intersection(i, jk, Intersection(j, k))
        corr = Union(Intersection(i, j, j, k), Intersection(i, k, j, k))
        self.assertEqual(i_jck_jk.distribute(), corr)

        ijcikcjk = Intersection(Union(i, j), Union(i, k), Union(j, k))
        corr = Union(Intersection(i, i, j), Intersection(i, i, k), 
                     Intersection(i, k, j), Intersection(i, k, k),
                     Intersection(j, i, j), Intersection(j, i, k), 
                     Intersection(j, k, j), Intersection(j, k, k))
        self.assertEqual(ijcikcjk.distribute(), corr)


    def test_equal(self):
        i, j, k, l = Index("I"), Index("J"), Index("K"), Index("L")
        self.assertEqual(self.icj, Intersection(i, j))
        self.assertNotEqual(self.icj, Intersection(j, i))
        self.assertNotEqual(self.icj, Union(i, j))
        self.assertNotEqual(self.icj, Intersection(i, j, k))

    def test_str(self):
        self.assertEqual(str(self.icj), "I^J")
        self.assertEqual(str(self.icjck), "I^J^K")
        self.assertEqual(str(self.icjckcl), "I^J^K^L")
        self.assertEqual(str(self.icjk), "I^(JUK)")


if __name__ == "__main__":
    unittest.main()