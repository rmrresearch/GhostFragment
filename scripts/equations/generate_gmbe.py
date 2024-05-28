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

    def __eq__(self, rhs):
        return (self.coeff == rhs.coeff) and (self.value == rhs.value)

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
        nmers.append(Term(1.0, Union(*nmer)))
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


def diff_ovps(old_nmers, new_nmer):
    old_ovps = make_intersections(old_nmers)
    new_nmers = old_nmers + [new_nmer]
    new_ovps = make_intersections(new_nmers)
    return [x for x in new_ovps if x not in old_ovps]


def print_equation(nmers, ovps, clean_up=False):
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
    ovps = make_intersections(nmers)
    for x in ovps:
        if len(x.value.associate()) == 3:
            print(x, x.clean_up())
    #print(print_equation(nmers, ovps, True))
    nmers = [
        Term(1.0, Union(Index("I"), Index("J"))),
        Term(1.0, Union(Index("I"), Index("K"))),
        Term(1.0, Union(Index("J"), Index("K"))),
        Term(1.0, Union(Index("I"), Index("L"))),
        Term(1.0, Union(Index("J"), Index("L")))
    ]
    diff = diff_ovps(nmers, Term(1.0, Union(Index("K"), Index("L"))))
    #print(print_equation(nmers, diff, True))
