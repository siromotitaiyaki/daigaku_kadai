#!/usr/bin/python
import sys

country_pos    = 0
per_person_pos = 1
total_pos      = 2

def beer_bottle(filename):
    f   = open(filename)

    with open('beer_bottle.dat', 'a') as output_file: #ファイルopen
        for line in f.readlines(): #各行処理
            ln  = line.split()
            if (ln[country_pos] == "Countries"):
                continue
            ln[per_person_pos] = float(ln[per_person_pos]) / 0.633
            output_file.write(f"{ln[country_pos]} {ln[per_person_pos]} {ln[total_pos]}\n")
        
# main
with open('beer_bottle.dat', 'w') as output_file: #ファイル初期化
    output_file.write(f"")
beer_bottle(sys.argv[1])