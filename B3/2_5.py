import random

def fermat_test(p, s): #フェルマーテスト
    if p <= 1:
        return False
    if p == 2 or p == 3:
        return True
    for _ in range(s):
        a = random.randint(2, p-1)
        if pow(a, p-1, p) != 1:
            return False
    return True

p_max = 10000
s_num = [1,3,5,10] #繰り返し回数
prime_num = [0,0,0,0]
j = 0
carmichael = [561, 1105, 1729, 2465, 2821, 6601, 8911, 0] #カーマイケル数
for s in s_num: #繰り返し回数の候補だけループ
    prime = 0
    i = 0
    for p in range(1, p_max):
        if p == carmichael[i]: #カーマイケル数を除く
            i += 1
            continue
        if fermat_test(p, s) == True: #素数と判定
            prime += 1
    prime_num[j] = prime #素数と判定された総数
    j += 1
print(prime_num)
print("繰り返し回数1回:", (prime_num[0]-prime_num[3])*100/prime_num[0], '%')
print("繰り返し回数3回:", (prime_num[1]-prime_num[3])*100/prime_num[1], '%')
print("繰り返し回数5回:", (prime_num[2]-prime_num[3])*100/prime_num[2], '%')