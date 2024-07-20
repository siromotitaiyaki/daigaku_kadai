#!/usr/bin/python
import sys

date_pos = 0

def max_min(filename):
    f   = open(filename)

    for i in range(1,9): #気象データ数だけループ
        f.seek(0) #先頭の行へ
        max = 0 #最大値初期化
        min = 100 #最小値初期化
        for line in f.readlines(): #各行処理
            ln  = line.split()
            if (ln[date_pos] == "Date"):
                print(ln[i]) #データ名
                continue
            if (max < float(ln[i])): #最大値探索
                date_max = ln[date_pos]
                max     = float(ln[i])
            if (min > float(ln[i])): #最小値探索
                date_min = ln[date_pos]
                min     = float(ln[i])
        print("最大:"+date_max)
        print("最小:"+date_min)
        
# main
max_min(sys.argv[1])