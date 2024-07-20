def exgcd(a,b): #拡張ユークリッド
    if a == 0:
        return b,0,1
    else:
        gcd,x,y = exgcd(b%a,a)
        return gcd, y-(b//a)*x, x

def mod_inverse(a,N): #乗法逆元
    gcd,x,y = exgcd(a,N)
    if gcd != 1:
        raise ValueError(f"乗法逆元は存在しません")
    else:
        return x%N

a = int(input('a='))
N = int(input('b='))
print(f"乗法逆元:",mod_inverse(a,N))