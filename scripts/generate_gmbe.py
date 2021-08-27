from itertools import combinations
from typing import Set



class Union(SetTheoryBase):
    def flatten(self):
        rv = []
        for termi in self.terms:
            if type(termi) == Union:
                for x in termi.flatten():
                    rv.append(x)
            else:
                rv.append(termi)

        temp = ""
        for x in rv:
            if type(x) != str:
                return rv
            else:
                temp += x

        return [temp]

    def clean_up(self):
        if len(self.terms) <2:
            return self

        if type(self.terms[0]) == str and type(self.terms[1]) == str:
            return Union(self.terms[0] + self.terms[1])
        elif type(self.terms[0]) == str or type(self.terms) == str:
            return self

        if self.terms[0].indices().issubset(self.terms[1].indices()):
            return self.terms[0]
        if self.terms[1].indices().issubset(self.terms[0].indices()):
            return self.terms[1]
        return self


    def __str__(self):
        flat_terms = self.flatten()

        if len(flat_terms) == 1:
            return str(flat_terms[0])


        rv = "\\left(" + str(flat_terms[0])
        for x in flat_terms[1:]:
            rv += "\\cup " + str(x)
        rv += "\\right)"
        return rv

class Intersection(SetTheoryBase):
    def flatten(self):
        rv = []
        for termi in self.terms:
            if type(termi) == Intersection:
                for x in termi.flatten():
                    rv.append(x)
            else:
                rv.append(termi)
        return rv

    def clean_up(self):
        if len(self.terms) < 2:
            return self

        if type(self.terms[0]) == Union and len(self.terms[0].terms) == 2:
            new_lhs = Intersection(self.terms[0].terms[0], self.terms[1]).clean_up()
            new_rhs = Intersection(self.terms[0].terms[1], self.terms[1]).clean_up()
            return Union(new_lhs, new_rhs).clean_up()
        if type(self.terms[1]) == Union and len(self.terms[1].terms) == 2:
            new_lhs = Intersection(self.terms[0], self.terms[1].terms[0]).clean_up()
            new_rhs = Intersection(self.terms[0], self.terms[1].terms[1]).clean_up()
            return Union(new_lhs, new_rhs).clean_up()
        return self

    def __str__(self):
        flat_terms = self.flatten()

        if len(flat_terms) == 1:
            return str(flat_terms[0])


        rv = "\\left(" + str(flat_terms[0])
        for x in flat_terms[1:]:
            rv += "\\cap " + str(x)
        rv += "\\right)"
        return rv

class Term:
    def __init__(self, sign, value):
        self.sign = sign
        self.value = value

    def clean_up(self):
        if type(self.value) == Intersection:
            return Term(self.sign, self.value.clean_up())
        else:
            return self.value

    def __repr__(self):
        return str(self)

    def __str__(self):
        lb = "{"
        rb = "}"
        return str(self.sign) + 'E_' + lb + str(self.value) + rb


def make_fragments(n_fragments):
    some_letters = "IJKLMNOPQRS"
    fragments = []
    for i in range(n_fragments):
        fragments.append(some_letters[i])
    return fragments

def make_nmers(trunc_order, frags):
    nmers = []
    if trunc_order == 1:
        return [Term('+', Union(x)) for x in frags]

    for nmer in combinations(frags, trunc_order):
        temp = Union(nmer[0], nmer[1])
        for i in range(2, len(nmer)):
            temp = Union(temp, nmer[i])
        nmers.append(Term('+', temp))
    return nmers


def make_intersections(nmers):
    if len(nmers) == 1:
        return []

    ovps = []

    for order in range(2, len(nmers) + 1):
        for ovp in combinations(nmers, order):
            temp = Intersection(ovp[0].value, ovp[1].value)
            for i in range(2, order):
                temp = Intersection(temp, ovp[i].value)
            if order % 2 == 0:
                ovps.append(Term('-', temp))
            else:
                ovps.append(Term('+', temp))

    return ovps

def print_equation(nmers, ovps):
    rv = ""
    for nmer in nmers:
        rv += str(nmer)
    for ovp in ovps:
        rv += str(ovp)#.clean_up())
    return rv

if __name__ == "__main__":
    n_fragments = 3
    trunc_order = 2
    frags = make_fragments(n_fragments)
    nmers = make_nmers(trunc_order, frags)
    ovps  = make_intersections(nmers)
    print(ovps[0].clean_up())
    print(print_equation(nmers, ovps))
