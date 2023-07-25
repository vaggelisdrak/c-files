import math
'''M = [0,5,10,15,20,25,30]
N = [1487,1482,1469,1456,1442,1429,1409]
Pmech = []

j=0
for i in M:
    p = i * 0.231 * 2 * math.pi * N[j] /60
    j+=1
    p = round(p, 2)
    Pmech.append(p)
    print(p)

print('\n\n\n')

S = [i*math.sqrt(3)*380 for i in [0.9,0.9,1,1.3,2.1,3,4.9]]
for u in S:
    u = round(u,2)
    print(u)

print("\n\n")

Pen = [3,4,5,7,9,11,13]
l=0
for k in S:
    cosf = Pen[l]*120 / k
    q = math.sqrt(k*k - Pen[l])
    l+=1
    cosf = round(cosf,2)
    #print(cosf)
    q= round(q, 2)
    print(q)

print("\n\n")

r=0
for i in Pmech:
    p = i/(Pen[r] * 120)
    r+=1
    p = round(p, 2)
    print(p)
    '''

Vs = [100,150,200,250,300,350,380]
M = [i for i in range(28)]
Mn = []

for i in M:
    if i%2==0:
        Mn.append(i)
Mn.append(27)

for k in Mn:
    print(k)

rpm = [1492,
1485,
1478,
1461,
1448,
1453,
1444,
1408,
1393,
1412,
1382,
1372,
1380,
1330,
1341]
Pen = [119.5,
432.1,
752.5,
1065.6,
1401.6,
1722.1,
2055.0,
2358.3,
2695.4,
3029.7,
3253.4,
3603.4,
4309.6,
4171.7,
5238.2]

print("\n\n")
P = []
l=0
for j in Mn:
    p = 2*math.pi*rpm[l]*j/60
    p = round(p, 2) 
    print(p)
    P.append(p)
    l+=1


f = 0
for j in P:
    h = j/Pen[f]
    h = round(h,2)
    print(h)
    f = round(f,2)
    f+=1



# Q = sqrt(S*S - Pen)
# h = Pmech/Pen
