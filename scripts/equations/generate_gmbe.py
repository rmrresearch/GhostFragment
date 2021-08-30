from itertools import combinations
from union import Union
from intersection import Intersection
from index import Index


class Term:
    def __init__(self, coeff, value):
        self.coeff = coeff
        self.value = value

    def clean_up(self):
        return Term(self.coeff, self.value.distribute().clean_up())

    def __repr__(self):
        return str(self)

    def __str__(self):
        lb = "{"
        rb = "}"
        str_coeff = str(self.coeff)
        if self.coeff >= 0:
            str_coeff = "+" + str_coeff
        return str_coeff + 'E_' + lb + str(self.value) + rb


def make_fragments(n_fragments):
    some_letters = "IJKLMNOPQRS"
    fragments = []
    for i in range(n_fragments):
        fragments.append(Index(some_letters[i]))
    return fragments

def make_nmers(trunc_order, frags):
    nmers = []
    if trunc_order == 1:
        return [Term(1.0, x) for x in frags]

    for nmer in combinations(frags, trunc_order):
        temp = Union(nmer[0], nmer[1])
        for i in range(2, len(nmer)):
            temp = Union(temp, nmer[i])
        nmers.append(Term(1.0, temp))
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
                ovps.append(Term(-1.0, temp))
            else:
                ovps.append(Term(1.0, temp))

    return ovps

def print_equation(nmers, ovps, clean_up = False):
    rv = ""
    for nmer in nmers:
        rv += str(nmer)
    for ovp in ovps:
        if clean_up:
            rv += str(ovp.clean_up())
        else:
            rv += str(ovp)
    return rv

if __name__ == "__main__":
    n_fragments = 4
    trunc_order = 2
    frags = make_fragments(n_fragments)
    nmers = make_nmers(trunc_order, frags)
    ovps  = make_intersections(nmers)
    print(print_equation(nmers, ovps))
    print("***")
    print(print_equation(nmers, ovps, True))
