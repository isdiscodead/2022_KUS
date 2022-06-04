import sys 

size = int(input())
park = [[0 for num in range(size)] for i in range(size)]
target = []

count = int(input())

def rule2( x, y ) :
    if ( y == size-1 ) :
        if ( park[x][y-1] ):
            return False
    elif ( y == 0 ) :
        if (park[x][y+1]) :
            return False
    else :
        if ( park[x][y-1] ):
            return False
        if ( park[x][y+1] ) :
            return False

    if ( x == size -1) :
        if (park[x-1][y]):
            return False
    elif ( x == 0 ) :
        if ( park[x+1][y]) :
            return False
    else :
        if (park[x-1][y]):
            return False
        if ( park[x+1][y]) :
            return False
    return True


def rule1( x, y ) :
    if ( x != 0 and y != 0 and x != size-1 and y!= size-1 ):
        return False
    return True


for i in range(count) :
    xy = input().split()
    x = int(xy[0])
    y = int(xy[1])
    park[x][y] = 1
    target.append((x,y))


flag1 = False
flag2 = False 

for i in target :
    if ( not rule1( i[0], i[1] ) ) :
        print("("+ str(i[0])  +","+ str(i[1]) +")");
        flag1 = True

for i in target :
    if ( not rule2( i[0], i[1]) and not flag1 ):
        print("("+str(i[0])+","+str(i[1])+")")
        flag2 = True


if flag1 :
    print("!")
elif flag2 :
    print("?")
else :
    print(1)