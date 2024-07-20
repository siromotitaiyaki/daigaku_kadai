#!/usr/bin/python
import tarfile

id = 0
status = 1
hours = 2
symptom = 3

def rack(filename, dic, count): #各理由の数え上げ
    f = open(filename)
    for line in f.readlines():
        ln  = line.split()
        if ln[id] == "ID":
            continue
        count += 1
        if ln[symptom] == "MAINTENANCE":
            dic['MAINTENANCE'] += 1
        if ln[symptom] == "DISK":
            dic['DISK FAILURE'] += 1
        if ln[symptom] == "POWER":
            dic['POWER FAILURE'] += 1
        if ln[symptom] == "CPU":
            dic['CPU ERROR'] += 1
        if ln[symptom] == "MEMORY":
            dic['MEMORY ERROR'] += 1
        if ln[symptom] == "UNKNOWN":
            dic['UNKNOWN ERROR'] += 1
    return dic, count
        
def log():
    count = 0
    #辞書型
    dic = {'MAINTENANCE':0, 'DISK FAILURE':0, 'POWER FAILURE':0, 'CPU ERROR':0, 'MEMORY ERROR':0, 'UNKNOWN ERROR':0}
    for i in range(1, 101):
        filename = "racklogs/rack"+str(i)+".log"
        dic, count = rack(filename, dic, count)
    dic['MAINTENANCE'] /= count
    dic['DISK FAILURE'] /= count
    dic['POWER FAILURE'] /= count
    dic['CPU ERROR'] /= count
    dic['MEMORY ERROR'] /= count
    dic['UNKNOWN ERROR'] /= count
    dic = sorted(dic.items(), key=lambda x:x[1], reverse=True) #辞書型のvalueを降順ソート
    for l in range(0, 6): #ソート後の辞書型を1つずつ出力
        print(dic[l])

#main
with tarfile.open('racklogs.tar.gz', 'r:gz') as tar: #tar.gzファイル解凍
    tar.extractall()
log()