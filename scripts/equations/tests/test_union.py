import unittest
import sys
import os
sys.path.insert(0, os.path.join(os.getcwd(), ".."))

from union import Union
from intersection import Intersection
from index import Index


class UnionTest(unittest.TestCase):
    def setUp(self):
        i, j, k, l = Index("I"), Index("J"), Index("K"), Index("L")
        self.ij = Union(i, j)
        self.ijk = Union(self.ij, k)
        self.ijkl = Union(self.ij, Union(k, l))
        self.i_jck = Union(i, Intersection(j, k))

    def test_is_union(self):
        self.assertTrue(self.ij.is_union())
        self.assertTrue(self.ijk.is_union())
        self.assertTrue(self.ijkl.is_union())
        self.assertTrue(self.i_jck.is_union())
    
    def test_is_intersection(self):
        self.assertFalse(self.ij.is_intersection())
        self.assertFalse(self.ijk.is_intersection())
        self.assertFalse(self.ijkl.is_intersection())
        self.assertFalse(self.i_jck.is_intersection())

    def test_is_index(self):
        self.assertFalse(self.ij.is_index())
        self.assertFalse(self.ijk.is_index())
        self.assertFalse(self.ijkl.is_index())
        self.assertFalse(self.i_jck.is_index())

    def test_associate(self):      
        i, j, k, l = Index("I"), Index("J"), Index("K"), Index("L")

        corr = Union(i, j)
        self.assertEqual(self.ij.associate(), corr)
        
        corr = Union(i, j, k)
        self.assertEqual(self.ijk.associate(), corr)

        corr = Union(i, j, k, l)
        self.assertEqual(self.ijkl.associate(), corr)

        ijkl_2 = Union(i, Union(j, Union(k, l)))
        self.assertEqual(ijkl_2.associate(), Union(i, j, k, l))

        jck = Intersection(j, k)
        corr = Union(i, jck)
        self.assertEqual(self.i_jck.associate(), corr)

        i_jck_jk = Union(i, jck, Union(j, k))
        self.assertEqual(i_jck_jk.associate(), Union(i, jck, j, k))


    def test_distribute(self):
        i, j, k, l = Index("I"), Index("J"), Index("K"), Index("L")

        corr = Union(i, j)
        self.assertEqual(self.ij.distribute(), corr)
        
        corr = Union(i, j, k)
        self.assertEqual(self.ijk.distribute(), corr)

        corr = Union(i, j, k, l)
        self.assertEqual(self.ijkl.distribute(), corr)

        ijkl_2 = Union(i, Union(j, Union(k, l)))
        self.assertEqual(ijkl_2.distribute(), Union(i, j, k, l))

        jck = Intersection(j, k)
        corr = Union(i, jck)
        self.assertEqual(self.i_jck.distribute(), corr)

        i_jck_jk = Union(i, jck, Union(j, k))
        self.assertEqual(i_jck_jk.distribute(), Union(i, jck, j, k))

        i_jkcl = Union(i, Intersection(Union(j, k), l))
        corr = Union(i, Intersection(j, l), Intersection(k, l))
        self.assertEqual(i_jkcl.distribute(), corr)


    def test_equal(self):
        i, j, k, l = Index("I"), Index("J"), Index("K"), Index("L")
        self.assertEqual(self.ij, Union(i, j))
        self.assertNotEqual(self.ij, Union(j, i))
        self.assertNotEqual(self.ij, Intersection(i, j))
        self.assertNotEqual(self.ij, Union(i, j, k))

    def test_str(self):
        self.assertEqual(str(self.ij), "IUJ")
        self.assertEqual(str(self.ijk), "IUJUK")
        self.assertEqual(str(self.ijkl), "IUJUKUL")
        self.assertEqual(str(self.i_jck), "IU(J^K)")


if __name__ == "__main__":
    unittest.main()
