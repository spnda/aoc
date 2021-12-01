a=open('program.txt').read().split("\n")[:-1]

def bootcode(code):
    acc=0
    i=0
    visited=[]
    looped=False
    while i < len(code):
        visited+=[i]
        line=code[i].split(' ')
        if line[0]=='acc':
            acc+=int(line[1])
            i+=1
        elif line[0]=='jmp':
            i+=int(line[1])
        elif line[0]=='nop':
            i+=1
        if i in visited:
            visited.reverse()
            looped=True
            break
    return acc,visited,looped

firstrun=bootcode(a)
print('part1',firstrun[0])
p2=0
for i in firstrun[1][1:]:
    l=a[i].split(' ')
    saved=a[i]
    if l[0]=='jmp':
        a[i]='nop ' + l[1]
    elif l[0]=='nop':
        a[i]='jmp ' + l[1]
    run=bootcode(a)
    p2=run[0]
    if run[2]:
        a[i]=saved
    else:
        print('error at line', i, saved)
        break
print('part2',p2)
