#課題１
f = open('map1010', 'r') #ファイル読み込み
data = f.read()
print(data) #表示
f.close()
data = data.split() #行毎に分割
for i in range(0,10): #列毎に分割
    data[i] = list(data[i])

#課題２
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

#課題３
#初期化
Start = [1,1] #スタート
Goal = [9,9] #ゴール
OL = [Start] #オープンリスト
CL = [] #クローズドリスト
print('幅優先探索')
while True:
    print('現在地', end=':')
    print(OL[0], end='')
    if next(OL[0], CL) == True: #オープンリスト先頭から
        break
    print(', オープンリスト', end=':')
    print(OL)
print('\n')

#課題４
#初期化
Start = [1,1] #スタート
Goal = [9,9] #ゴール
OL = [Start] #オープンリスト
CL = [] #クローズドリスト
print('深さ優先探索')
while True:
    print('現在地', end=':')
    print(OL[-1], end='')
    if next(OL[-1], CL) == True: #オープンリスト末尾から
        break
    print(', オープンリスト', end=':')
    print(OL)
print('\n')