import math

class Frac:
    def __init__(self, num, den):
        self.num = num
        self.den = den
        if(self.den == 0):
            raise ValueError("分母不能为0")
        self.simplify()

    def simplify(self):
        gcd = math.gcd(self.num, self.den)
        self.num //= gcd
        self.den //= gcd

    def __str__(self):
        return f"{self.num}/{self.den}"

    
a=Frac(2,6)
print(a)
