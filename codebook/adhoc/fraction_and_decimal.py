from decimal import *
getcontext().prec = 87 # set precision
d1 = Decimal(1)
d2 = Decimal('3.14')
d3 = Decimal(3.14) # not recommend
d1 * d2, d2 ** d1
getcontext().rounding = ROUND_UP
# ROUND_CEILING, ROUND_DOWN,  ROUND_FLOOR, ROUND_HALF_DOWN, ROUND_HALF_EVEN, ROUND_HALF_UP, ROUND_UP, ROUND_05UP
d2.sqrt(), d1.log10(), d3.exp(), d1.ln()

from fractions import Fraction
Fraction(16, -10)
Fraction(123)
Fraction('3/7')
Fraction('-3/7')
Fraction('2.25')
Fraction(1.1) # not recommend
Fraction(Decimal('1.1'))

from math import pi, cos
Fraction(cos(pi/3)).limit_denominator(max_denominator=1000000) # 1/2
