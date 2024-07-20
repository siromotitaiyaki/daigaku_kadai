def next(x, CL):
    map_x = x[0] #x軸
    map_y = x[1] #y軸
    if not OL: #オープンリストが空
        return False
    OL.remove(x)
    if x == Goal: #ゴールに到達
        return True
    if data[map_x-1][map_y]=='0': #上
        flag = 0
        for l in CL: #クローズドリストチェック
            if l == [map_x-1,map_y]:
                flag = 1
                break
        if flag == 0:
            OL.append([map_x-1,map_y])
    if data[map_x][map_y-1]=='0': #左
        flag = 0
        for l in CL: #クローズドリストチェック
            if l == [map_x,map_y-1]:
                flag = 1
                break
        if flag == 0:
            OL.append([map_x,map_y-1])
    if data[map_x+1][map_y]=='0': #下
        flag = 0
        for l in CL: #クローズドリストチェック
            if l == [map_x+1,map_y]:
                flag = 1
                break
        if flag == 0:
            OL.append([map_x+1,map_y])
    if data[map_x][map_y+1]=='0': #右
        flag = 0
        for l in CL: #クローズドリストチェック
            if l == [map_x,map_y+1]:
                flag = 1
                break
        if flag == 0:
            OL.append([map_x,map_y+1])
    CL.append(x)
    return

import os
import numpy as np
from tabulate import tabulate

filepath = '/home/kazuma/実験2A/6055/'
width_Order = [0] * 100 #幅優先計算量
depth_Order = [0] * 100 #深さ優先計算量
width_Memory = [0] * 100 #幅優先メモリ量
depth_Memory = [0] * 100 #深さ優先メモリ量
for curDir, dirs, files in os.walk("6055"):
    for file in files: #ディレクトリ走査
        num = int(file[3:]) #マップ番号
        f = open(filepath + file, 'r')
        data = f.read()
        f.close()
        data = data.split()
        for i in range(0,100):
            data[i] = list(data[i])

        #初期化
        Start = [1,1] #スタート
        Goal = [99,99] #ゴール
        OL = [Start] #オープンリスト
        CL = [] #クローズドリスト
        memory_max = 0 #メモリ最大値
        while True:
            width_Order[num] += 1 #マップ毎の計算量
            if memory_max < len(OL):
                memory_max = len(OL)
            if next(OL[0], CL) == True: #オープンリスト先頭から
                break
            width_Memory[num] = memory_max
        
        #初期化
        Start = [1,1] #スタート
        Goal = [99,99] #ゴール
        OL = [Start] #オープンリスト
        CL = [] #クローズドリスト
        memory_max = 0 #メモリ最大値
        while True:
            depth_Order[num] += 1 #マップ毎の計算量
            if memory_max < len(OL):
                memory_max = len(OL)
            if next(OL[-1], CL) == True: #オープンリスト末尾から
                break
            depth_Memory[num] = memory_max
#計算
#幅優先
width_O_ave = np.mean(width_Order) #計算量平均
width_O_var = np.var(width_Order) #計算量分散
width_O_max = max(width_Order) #計算量最大値
width_O_min = min(width_Order) #計算量最小値
width_M_ave = np.mean(width_Memory) #メモリ量平均
width_M_var = np.var(width_Memory) #メモリ量分散
width_M_max = max(width_Memory) #メモリ量最大値
width_M_min = min(width_Memory) #メモリ量最小値
#深さ優先
depth_O_ave = np.mean(depth_Order) #計算量平均
depth_O_var = np.var(depth_Order) #計算量分散
depth_O_max = max(depth_Order) #計算量最大値
depth_O_min = min(depth_Order) #計算量最小値
depth_M_ave = np.mean(depth_Memory) #メモリ量平均
depth_M_var = np.var(depth_Memory) #メモリ量分散
depth_M_max = max(depth_Memory) #メモリ量最大値
depth_M_min = min(depth_Memory) #メモリ量最小値
#出力
print('幅優先探索')
headers = ['', 'ave', 'var', 'max', 'min']
table = [['Order', width_O_ave, width_O_var, width_O_max, width_O_min],
         ['Memory', width_M_ave, width_M_var, width_M_max, width_M_min]]
result = tabulate(table, headers, tablefmt='grid')
print(result)
print('深さ優先探索')
headers = ['', 'ave', 'var', 'max', 'min']
table = [['Order', depth_O_ave, depth_O_var, depth_O_max, depth_O_min],
         ['Memory', depth_M_ave, depth_M_var, depth_M_max, depth_M_min]]
result = tabulate(table, headers, tablefmt='grid')
print(result)