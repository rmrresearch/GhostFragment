from index import Index
from union import Union

class Intersection:
    """ Class representing a symbolic intersection of indices.
    """
    def __init__(self, *args):
        """ Creates an intersection between two things
        """
        self.terms = args
 

    def print_type(self):
        rv = "Intersection("
        for x in self.terms:
            rv += x.print_type() + ","
        return rv + ")"

    def clean_up(self):
        
        new_terms = [x.clean_up() for x in self.distribute().terms]


    def is_union(self):
        return False

    def is_intersection(self):
        return True

    def is_index(self):
        return False

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
        
                
    def __repr__(self):
        return str(self)
 
    def __getitem__(self, idx):
        return self.terms[idx]

    def __len__(self):
        return len(self.terms)

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
            return self.terms == rhs.terms
        return False


    
    
