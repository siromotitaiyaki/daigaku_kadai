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

def generate_prime(n, k): #素数生成
    for _ in range(k):
        p = random.getrandbits(n-1) | (1 << (n-1)) #ランダムな2進数生成
        if miller_rabin_test(p, k) == True:
            return p
    return False

n = int(input("bit:")) #ビット数
k = 100 #繰り返し回数
prime = generate_prime(n, k) #素数生成
if prime == False:
    print("素数が見つかりませんでした。")
else:
    print("生成された素数:", prime)