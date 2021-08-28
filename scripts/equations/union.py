class Union:
    """ Class representing a symbolic union of indices.
    """
    def __init__(self, lhs, rhs = None):
        """ Creates a Union between one or two things
        """
        self.terms = [lhs]
        if rhs and lhs != rhs:
            self.terms.append(rhs)

    def is_simple(self):
        for x in self.terms:
            is_str   = type(x) == str
            is_union = type(x) == Union
            if is_union:
                if not x.is_simple():
                    return False
            elif not is_str:
                return False
        return True

    def indices(self):
        idxs = set()
        for x in self.terms:
            if type(x) == str:
                idxs = idxs.union({x})
            else:
                idxs = idxs.union(x.indices())
        return idxs
 
    def print(self, sym):
        as_str0 = str(self.terms[0])
        if len(self.terms) == 1:
            return as_str0

        as_str1 = str(self.terms[1])

        if self.is_simple():
            return as_str0 + as_str1

        return "(" + as_str0 + ")" + sym + "(" + as_str1 + ")"


    def __repr__(self):
        return str(self)

    def __str__(self):
        return self.print("U")

    def __eq__(self, rhs):
        if type(rhs) == str:
            return False
        return self.terms == rhs.terms
