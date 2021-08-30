from set_base import SetBase
from union import Union
class Intersection(SetBase):
    """ Class representing a symbolic intersection of indices.
    """

    def print_type(self):
        rv = "Intersection("
        for x in self.terms:
            rv += x.print_type() + ","
        return rv + ")"

    def is_proper_subset(self, rhs):
        """ Determines if the current Intersection instance is a proper subset
            of `rhs`.

        If
        """
        if rhs.is_index():
            if len(self) == 1:
                return False
            return self.count(rhs) == 1
        elif rhs.is_union():
            for x in self.terms:
               if rhs.count(x):
                   return True
            return False
        elif rhs.is_intersection():
            if len(rhs) >=  len(self):
                return False
            # Every term in rhs, must be in us
            for x in rhs.terms:
                if self.count(x) == 0:
                    return False
            return True



    def clean_up(self):
        new_terms = [x.clean_up() for x in self.terms]
        final_terms = new_terms
        if len(final_terms) == 1:
            return final_terms[0]
        return Intersection(*final_terms)

    def is_intersection(self):
        return True

    def associate(self):
        new_terms = []
        for i in range(len(self.terms)):
            new_term = self.terms[i].associate()
            if new_term.is_intersection():
                for x in new_term:
                    new_terms.append(x)
            else:
                new_terms.append(new_term)
        return Intersection(*new_terms)


    def distribute(self):
        new_terms = self.associate()
        nterms = len(new_terms)
        rv = []
        for i in range(nterms):
            newi = new_terms[i].distribute()
            if newi.is_union():
                lhs = rv
                rhs = new_terms[i + 1 : nterms]
                rv = [ ]
                for x in new_terms[i].terms:
                    rv.append(Intersection(*lhs, x, *rhs).distribute())
                return Union(*rv).associate()
            rv.append(newi)
        return Intersection(*rv).associate()


    def __str__(self):
        sym = "^"

        rv = ""
        for i in range(len(self.terms)):
            x_str = str(self.terms[i])

            if self.terms[i].is_union():
                x_str = "(" + x_str + ")"

            if i == 0:
                rv = x_str
                continue

            rv += sym + x_str
        return rv

    def __eq__(self, rhs):
        if type(rhs) == Intersection:
            if len(self.terms) != len(rhs.terms):
                return False
            for x in self.terms:
                if rhs.count(x) == 0:
                    return False
            return True
        return False
