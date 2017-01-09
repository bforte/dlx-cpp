#!/usr/bin/env python

import dlx_python.libexactcover as ec

s = ec.Solution([[0, 0, 1, 0, 1, 1, 0],
                 [1, 0, 0, 1, 0, 0, 1],
                 [0, 1, 1, 0, 0, 1, 0],
                 [0, 0, 0, 0, 1, 0, 0],
                 [1, 0, 0, 1, 0, 0, 0],
                 [0, 1, 0, 0, 0, 0, 1],
                 [0, 0, 0, 1, 1, 0, 1]])

print("Listing all {!s} solutions:".format(s.number_of_solutions))

for sol in s.solutions:
    print(sol)
