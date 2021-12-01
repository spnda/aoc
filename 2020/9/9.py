def t1(k,d):
  for i in range(k-25,k):
    for j in range(i+1,k):
      if d[i]+d[j] == d[k]:
        return True
  return False

def s1(d):
  for i in range(25,len(d)):
    if not t1(i,d):
      return i,d[i]

def s2(d,k):
  for i in range(0,k):
    for l in range(1,k-i):
      t = sum(d[i:i+l])
      if t==n:
        return i,i+l
      if t>n:
        break

d = list(map(int,open("input.txt","rt").read().split()))
k,n = s1(d); print(n)
j,m = s2(d,k); print(min(d[j:m])+max(d[j:m]))