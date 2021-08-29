class Index:
    def __init__(self, value):
        self.value = value
    
    def print_type(self):
        return "Index"

    def clean_up(self):
        return self

    def is_union(self):
        return False

    def is_intersection(self):
        return False

    def is_index(self):
        return True

    def associate(self):
        return self

    def distribute(self):
        return self

    def __len__(self):
        return 1

    def __repr__(self):
        return str(self)
    
    def __str__(self):
        return str(self.value)

    def __eq__(self, rhs):
        if type(rhs) == Index:
            return self.value == rhs.value
        return False