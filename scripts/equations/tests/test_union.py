import unittest
import sys
import os
sys.path.insert(0, os.path.join(os.getcwd(), ".."))

from union import Union

class Intersection:
    def __init__(self, lhs, rhs = None):
        self.terms = [lhs]
        if rhs and lhs != rhs:
            self.terms.append(rhs)

    def print(self, sym):
        if len(self.terms) == 1:
            return str(self.terms[0])
        return str(self.terms[0]) + sym + str(self.terms[1])

    def __str__(self):
        return self.print("^")

class UnionTest(unittest.TestCase):
    def setUp(self):
        self.i = Union("I")
        self.j = Union("J")
        self.k = Union("K")
        self.l = Union("L")
        self.ij = Union(self.i, self.j)
        self.ijk = Union(self.i, Union(self.j, self.k))
        self.icj_k = Union(Intersection(self.i, self.j), self.k)
        self.ijkl = Union(Union(self.ij, self.k), self.l)
        self.icj_kl = Union(Union(Intersection(self.i, self.j), self.k), self.l)

    def test_is_simple(self):
        self.assertTrue(self.i.is_simple())
        self.assertTrue(self.j.is_simple())
        self.assertTrue(self.k.is_simple())
        self.assertTrue(self.l.is_simple())
        self.assertTrue(self.ij.is_simple())
        self.assertTrue(self.ijk.is_simple())
        self.assertFalse(self.icj_k.is_simple())
        self.assertTrue(self.ijkl.is_simple())
        self.assertFalse(self.icj_kl.is_simple())


    def test_str(self):
        self.assertEqual(str(self.i), "I")
        self.assertEqual(str(self.j), "J")
        self.assertEqual(str(self.k), "K")
        self.assertEqual(str(self.l), "L")
        self.assertEqual(str(self.ij), "IJ")
        self.assertEqual(str(self.ijk), "IJK")
        self.assertEqual(str(self.icj_k), "(I^J)U(K)")
        self.assertEqual(str(self.ijkl), "IJKL")
        self.assertEqual(str(self.icj_kl), "((I^J)U(K))U(L)")


if __name__ == "__main__":
    unittest.main()
