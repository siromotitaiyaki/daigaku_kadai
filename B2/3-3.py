#!/usr/bin/python
import sys

date_pos = 0

def compare_city(filename1, filename2, filename3):
    for i in range(1,4):
        #F市
        f   = open(filename1)
        f.seek(0) #先頭の行へ
        max1 = 0 #最大値初期化
        min1 = 100 #最小値初期化
        for line in f.readlines(): #各行処理
            ln  = line.split()
            if (ln[date_pos] == "Date"):
                print(ln[i])
                continue
            if (max1 < float(ln[i])):
                date_max1 = ln[date_pos]
                max1    = float(ln[i])
            if (min1 > float(ln[i])):
                date_min1 = ln[date_pos]
                min1    = float(ln[i])
        f.close()
        #K市
        f   = open(filename2) #F市と同様の処理を行う
        f.seek(0)
        max2 = 0
        min2 = 100
        for line in f.readlines():
            ln  = line.split()
            if (ln[date_pos] == "Date"):
                continue
            if (max2 < float(ln[i])):
                date_max2 = ln[date_pos]
                max2    = float(ln[i])
            if (min2 > float(ln[i])):
                date_min2 = ln[date_pos]
                min2    = float(ln[i])
        f.close()
        #W市
        f   = open(filename3) #F市と同様の処理を行う
        f.seek(0)
        max3 = 0
        min3 = 100
        for line in f.readlines():
            ln  = line.split()
            if (ln[date_pos] == "Date"):
                continue
            if (max3 < float(ln[i])):
                date_max3 = ln[date_pos]
                max3    = float(ln[i])
            if (min3 > float(ln[i])):
                date_min3 = ln[date_pos]
                min3    = float(ln[i])
        f.close()
        #出力
        if max1 > max2 and max1 > max3:
            print("最大:"+str(max1)+"   "+date_max1+"(F市)")
        elif max2 > max3:
            print("最大:"+str(max2)+"   "+date_max2+"(W市)")
        else:
            print("最大:"+str(max3)+"   "+date_max3+"(K市)")
        if min1 < min2 and min1 < min3:
            print("最小:"+str(min1)+"   "+date_min1+"(F市)")
        elif min2 < min3:
            print("最小:"+str(min2)+"   "+date_min2+"(W市)")
        else:
            print("最小:"+str(min3)+"   "+date_min3+"(K市)")
    
# main
compare_city(sys.argv[1], sys.argv[2], sys.argv[3])