class Calculator:

    def __init__(self):
        self.last_entry = 0

    def add(self, a, b=None):
        result = a + b if b else a + self.last_entry
        self.last_entry = result
        return result

    def multiply(self, a, b=None):
        result = a * b if b else a * self.last_entry
        self.last_entry = result
        return result

# use the Calculator class to add up a list of numbers
# the first line of the input file is an integer N: how many numbers are in the list
# the next N lines each contain an integer
def driver():
    # there are a lot of ways to do this!
    # this way is more verbose than necessary, but hopefully pretty clear
    c = Calculator()
    with open('lab1.data') as f:
        n = int(f.readline().strip())
        for _ in range(n):
            c.add(int(f.readline().strip()))
    print(c.last_entry)


if __name__=='__main__':
    driver()
