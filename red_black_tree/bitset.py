#!/usr/bin/python3

def bitset(n, k):
    return  (((n >> (k - 1)) & 1) == 1)