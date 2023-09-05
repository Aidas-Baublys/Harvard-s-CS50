class Jar:
    def __init__(self, capacity=12):
        self.cap = capacity
        self.s = 0

    def __str__(self):
        return "🍪" * self.size

    def deposit(self, n):
        if self.s + n < self.cap:
            self.s += n
        else:
            raise ValueError("Over capacity")

    def withdraw(self, n):
        if self.s - n >= 0:
            self.s -= n
        else:
            raise ValueError("Not enough cookies")

    @property
    def capacity(self):
        return self.cap

    @property
    def size(self):
        return self.s
    