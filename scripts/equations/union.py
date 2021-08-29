from index import Index
class Union:
    """ Class representing a symbolic union of indices.
    """
    def __init__(self, *args):
        """ Creates a Union between two indices
        """
        self.terms = args

    def print_type(self):
        rv = "Union("
        for x in self.terms:
            rv += x.print_type() + ","
        return rv + ")"

    def is_union(self):
        return True

    def is_intersection(self):
        return False

    def is_index(self):
        return False

    def clean_up(self):
        all_idx
        for x in terms.self:

        return self

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

    def __repr__(self):
        return str(self)

    def __getitem__(self, idx):
        return self.terms[idx]

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
            return self.terms == rhs.terms
        return False
        



