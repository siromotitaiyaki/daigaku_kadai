#!/usr/bin/python
import sys

country_pos    = 0
per_person_pos = 1
total_pos      = 2

def beer_japanese_average(filename):
    f   = open(filename)

    for line in f.readlines(): #Japan探索
        ln  = line.split()
        if (ln[country_pos] == "Japan"):
            per_person_pos_Japan = float(ln[per_person_pos])
            total_pos_Japan = float(ln[total_pos])
        
    with open('beer_japanese_average.dat', 'a') as output_file: #ファイルopen
        f.seek(0) #先頭の行へ
        for line in f.readlines(): #各行処理
            ln  = line.split()
            if (ln[country_pos] == "Countries"):
                continue
            ln[per_person_pos] = float(ln[per_person_pos]) / per_person_pos_Japan
            ln[total_pos] = float(ln[total_pos]) / total_pos_Japan
            output_file.write(f"{ln[country_pos]} {ln[per_person_pos]} {ln[total_pos]}\n")
        
# main
with open('beer_japanese_average.dat', 'w') as output_file: #ファイル初期化
    output_file.write(f"")
beer_japanese_average(sys.argv[1])