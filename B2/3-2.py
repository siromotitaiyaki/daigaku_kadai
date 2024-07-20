#!/usr/bin/python
import sys

date_pos = 0
ave_temperature = 1
precipitation = 4
day_length = 5

def ave(filename):
    f   = open(filename)
    prev_month = 1
    prev_day = 1
    ave_temperature_ave = 0.0
    precipitation_ave = 0.0
    day_length_ave = 0.0
    
    for line in f.readlines(): #各行処理
        ln  = line.split()
        if (ln[date_pos] == "Date"):
            continue
        idx = ln[date_pos].split("/") #"/"で分けて配列に格納
        
        if (float(idx[1]) != prev_month): #月が変わった際の処理
            ave_temperature_ave /= prev_day
            precipitation_ave /= prev_day
            day_length_ave /= prev_day
            print("一日の平均気温："+str(ave_temperature_ave))
            print("降水量："+str(precipitation_ave))
            print("日照時間："+str(day_length_ave))
            #初期化
            ave_temperature_ave = 0.0
            precipitation_ave = 0.0
            day_length_ave = 0.0
        if (int(idx[1]) == 10 and int(idx[2]) == 31): #最後の月の処理
            ave_temperature_ave /= prev_day
            precipitation_ave /= prev_day
            day_length_ave /= prev_day
            print("一日の平均気温:"+str(ave_temperature_ave))
            print("降水量:"+str(precipitation_ave))
            print("日照時間:"+str(day_length_ave))
        if (idx[2] == '1'):
            print(idx[1]+'月')
        #各データに加算
        ave_temperature_ave += float(ln[ave_temperature])
        precipitation_ave += float(ln[precipitation])
        day_length_ave += float(ln[day_length])
        prev_month = int(idx[1])
        prev_day = int(idx[2])        

    f.seek(0) #先頭の行へ
               
# main
ave(sys.argv[1])