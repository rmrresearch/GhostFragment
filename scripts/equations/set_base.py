class SetBase:
    def __init__(self, *args):
        self.terms = []
        # This makes sure we only add unique elements
        for x in args:
            is_good = True
            for y in self.terms:
                if x == y:
                    is_good = False
                    break
            if is_good:
                self.terms.append(x)
        self.terms.sort()

    def count(self, elem):
        # This exploits that only unique elements are stored
        for x in self.terms:
            if x == elem:
                return 1
        return 0

    def is_union(self):
        return False

    def is_intersection(self):
        return False

    def is_index(self):
        return False

    def __len__(self):
        return len(self.terms)

    def __repr__(self):
        return str(self)

    def __getitem__(self, idx):
        return self.terms[idx]
