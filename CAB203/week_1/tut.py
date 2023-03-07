import math

def modular_arithmetic():
    # 1
    print(17 % 5)
    # 2
    print(36 % 7)
    # 3
    print((5 + 7) % 3)
    # 4
    print((5 * 4) % 3)


def modular_arithmetic_5(a, b):
    return a % b == 0


def modular_arithmetic_6(a, b, c):
    return a == b % c


def modular_arithmetic_7(a, b):
    r = a % b
    print(a == r % b)


def modular_arithmetic_8(a, b, c, n):
    print(a == b % n)
    print(b == c % n)
    print(a == c % n)


def exponents():
    # 1
    print(f"{((2 ** 15) * (2 ** 3)) / 1024} kilobits")
    # 2
    print(f"2 ^ {math.log(8 ** 5, 2)} == 8 ^ 5")
    # 3
    print(math.log2(256/16))
    # 4
    print(math.log2(8 ** 3))


def exponents_5(n):
    print(math.ceil(math.log2(n)))


def exponents_6(n, a, b):
    temp = math.log(a * b, n)
    temp2 = math.log(a, n) + math.log(b, n)
    print(temp == temp2)


if __name__ == "__main__":
    exponents_6(2, 8, 16)
