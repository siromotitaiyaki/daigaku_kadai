def gcd(a,b): #ユークリッド
    while b != 0:
        a,b = b,a%b
    return a

a = int(input('a='))
b = int(input('b='))
print(f"最大公約数:",gcd(a,b))