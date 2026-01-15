def comb(m,n):
    sum = 1;
    for i in range(1,n+1):
        sum = sum * (m-i+1)/i 
    return int(sum)

print(f"fun(0,0)={comb(0,0)}")
print(f"fun(5,2)={comb(5,2)}")