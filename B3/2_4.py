import time
import math

def souatari(n):
    if n == 1:
        return False, 0
    start_time = time.time()  # 開始時間を記録
    i = 2
    while math.sqrt(n) >= i:
        if n%i == 0:
            end_time = time.time()  # 終了時間を記録
            elapsed_time = end_time - start_time  # 経過時間を計算
            return False, elapsed_time
        i += 1
    end_time = time.time()  # 終了時間を記録
    elapsed_time = end_time - start_time  # 経過時間を計算
    return True, elapsed_time

n = int(input()) #数値入力
num, elapsed_time = souatari(n) #総当たり
if num == True:
    print(n, "は素数です")
else:
    print(n, "は素数ではありません")
print("判定にかかった時間:", elapsed_time, "秒")