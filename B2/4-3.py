#!/usr/bin/python
import tarfile

id = 0
status = 1
hours = 2
symptom = 3

def rack(filename):
    f = open(filename)
    for line in f.readlines():
        ln  = line.split()
        if ln[id] == "ID":
            continue
        idx = filename.split(".")
        idx2 = idx[0].split("/")
        server_rack = str(ln[id])+'-'+str(idx2[1])
        with open('log.csv', 'a') as output_file:
            #空白文字による名前のずれの修正
            if ln[symptom] == "DISK":
                ln[symptom] = "DISK FAILURE"
            if ln[symptom] == "POWER":
                ln[symptom] = "POWER FAILURE"
            if ln[symptom] == "CPU":
                ln[symptom] = "CPU ERROR"
            if ln[symptom] == "MEMORY":
                ln[symptom] = "MEMORY ERROR"
            if ln[symptom] == "UNKNOWN":
                ln[symptom] = "UNKNOWN ERROR"
            output_file.write(f"{server_rack},{ln[status]},{ln[hours]},{ln[symptom]}\n")

def log():
    for i in range(1, 11):
        filename = "racklogs/rack"+str(i)+".log"
        rack(filename)

#main
with tarfile.open('racklogs.tar.gz', 'r:gz') as tar: #tar.gzファイル解凍
    tar.extractall()
with open('log.csv', 'w') as output_file: #ファイル初期化
    output_file.write(f"")
log()