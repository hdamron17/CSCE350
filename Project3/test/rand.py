#! /usr/bin/env python3

from random import getrandbits, randint

def randbignum(bindigits):
    return ("-" if randint(0,1) else "") + str(getrandbits(randint(1, bindigits)))

bindigits = 40000
print(randbignum(bindigits))
print(randbignum(bindigits))
