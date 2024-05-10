import numpy
import pylab
import random

n = 100000
x = numpy.zeros(n)
y = numpy.zeros(n)

children = 10




for child in range(children):
    for i in range(1, n):
        val = random.randint(1, 4)
        if val == 1:
            x[i] = x[i - 1] + 1
            y[i] = y[i - 1]
        elif val == 2:
            x[i] = x[i - 1] - 1
            y[i] = y[i - 1]
        elif val == 3:
            x[i] = x[i - 1]
            y[i] = y[i - 1] + 1
        else:
            x[i] = x[i - 1]
            y[i] = y[i - 1] - 1

    pylab.plot(x, y)
# plotting stuff:
# pylab.title("Random Walk ($n = " + str(n) + "$ steps)")
# pylab.savefig("rand_walk" + str(n) + ".png", bbox_inches="tight", dpi=600)
pylab.show()