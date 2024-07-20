import random

def miller_rabin_test(p, s): #Miller-Rabinテスト
    if p<2 or p%2 == 0:
        return False
    u = 0
    v = p-1
    while v%2 == 0: #p-1=2^u*vの探索
        u += 1
        v //= 2
    for _ in range(s):
        a = random.randint(2, p-1)
        if pow(a, p-1, p) != 1:
            return False
        for j in range(1,u): #Miller-Rabinの追加部分
            if pow(a, (2^j)*v, p) == 1 and abs(pow(a, (2^(j-1))*v, p)) != 1:
                return False        
    return True

s_num = [1,3,5] #繰り返し回数
not_prime_num = [0,0,0]
j = 0
carmichael = [561, 1105, 1729, 2465, 2821, 6601, 8911] #カーマイケル数
for s in s_num: #繰り返し回数の候補だけループ
    not_prime = 0
    for p in carmichael:
        if miller_rabin_test(p, s) == False: #素数でないと判定
            not_prime += 1    
    not_prime_num[j] = not_prime #素数と判定された総数
    j += 1
print(not_prime_num)
print("繰り返し回数1回:", (len(carmichael)-not_prime_num[0])*100/len(carmichael), '%')
print("繰り返し回数3回:", (len(carmichael)-not_prime_num[1])*100/len(carmichael), '%')
print("繰り返し回数5回:", (len(carmichael)-not_prime_num[2])*100/len(carmichael), '%')