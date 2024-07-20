#!/usr/bin/python
import sys

country_pos    = 0
per_person_pos = 1
total_pos      = 2

def max_total_pos(filename):
    f   = open(filename)
    max = 0
    
    for line in f.readlines():
        ln  = line.split()
        if (ln[country_pos] == "Countries"):
            continue
        if (max < float(ln[total_pos])):
            country = ln[country_pos]
            max     = float(ln[total_pos])

    print(country)
        
# main
max_total_pos(sys.argv[1])