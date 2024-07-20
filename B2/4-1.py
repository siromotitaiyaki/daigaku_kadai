#!/usr/bin/python
import tarfile

id = 0
status = 1
hours = 2
symptom = 3

def rack(filename, all_rack, num): #稼働数数え上げ
    f = open(filename)
    ok = 0
    down = 0
    count = 0
    ave_hours = 0.0
    for line in f.readlines(): #各行処理
        ln  = line.split()
        if ln[id] == "ID":
            continue
        if ln[status] == "OK": #稼働中
            ok += 1
            count += 1
            num += 1
        if ln[status] == "DOWN": #停止中
            down += 1
            count += 1
            num += 1
        ave_hours += float(ln[hours])
    all_rack += ok
    ave_hours /= count
    with open('ave_hours.log', 'a') as output_file: #新たなlogファイルに一時保存
        output_file.write(f"{filename} {ave_hours}\n")
    return all_rack, num

def max_rack3():
    all_rack = 0.0
    num = 0
    for i in range(1, 101):
        filename = "racklogs/rack"+str(i)+".log"
        all_rack, num = rack(filename, all_rack, num)
    all_rack = all_rack / num #稼働率算出
    print("稼働率:"+str(all_rack))
    #上位3位の処理
    with open('ave_hours.log', 'r') as file:
        lines = file.readlines()
    data = [(line.split()[0], float(line.split()[1])) for line in lines]
    sorted_data = sorted(data, key = lambda x: x[1], reverse=True) #降順ソート
    print("平均稼働時間上位3位")
    for i in range(min(3, len(sorted_data))): #上位3位出力
        print(f'{sorted_data[i][0][9:]} {sorted_data[i][1]}')

#main
with tarfile.open('racklogs.tar.gz', 'r:gz') as tar: #tar.gzファイル解凍
    tar.extractall()
with open('ave_hours.log', 'w') as output_file: #ファイル初期化
    output_file.write(f"")
max_rack3()