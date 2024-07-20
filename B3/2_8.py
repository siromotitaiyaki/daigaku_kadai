import random

#素数生成アルゴリズム用関数
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

#暗号化、複合化用関数
def gcd(a,b): #ユークリッド
    while b != 0:
        a,b = b,a%b
    return a

def exgcd(a,b): #拡張ユークリッド
    if a == 0:
        return b,0,1
    else:
        gcd,x,y = exgcd(b%a,a)
        return gcd, y-(b//a)*x, x

def generate_keys(): #鍵生成
    p_list = [101,109,131,193,223,263,347,439,523,797] #ランダムな素数
    q_list = [181,191,251,349,499,509,631,821,911,997] #ランダムな素数
    p = p_list[random.randint(0, 9)]
    q = q_list[random.randint(0, 9)]
    N = p*q #N
    phi = (p-1)*(q-1)
    
    e = random.randint(2,phi-1) #公開鍵
    while gcd(e,phi) != 1:
        e = random.randint(2,phi-1)

    _, d, _ = exgcd(e,phi) #秘密鍵
    d = d % phi
    if d < 0:
        d += phi

    return (e,N),(d,N)

def encrypt(m, public_key): #暗号化
    e, N = public_key
    encrypted_m = pow(m, e, N)
    return encrypted_m

def decrypt(encrypted_m, private_key): #複合化
    d, N = private_key
    decrypted_m = pow(encrypted_m, d, N)
    return decrypted_m

n = int(input("bit:")) #ビット数
k = 100 #繰り返し回数
prime = generate_prime(n, k) #素数生成
if prime == False:
    print("素数が見つかりませんでした。")
else:
    print("生成された素数:", prime)
    public_key, private_key = generate_keys() #鍵生成
    encrypted_m = encrypt(prime, public_key) #暗号化
    decrypted_m = decrypt(encrypted_m, private_key) #複合化
    print("暗号化文:", encrypted_m)
    print("復号化文:", decrypted_m)