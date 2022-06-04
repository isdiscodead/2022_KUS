names = input().split(',')[1:]
content = []
dates = []
result = []

def into_amount(string) :
    if (string == "아메리카노"):
        return 2000
    elif (string == "아아"):
        return 2500
    elif (string == "아바라"):
        return 4000
    elif (string == "딸기 에이드"):
        return 4500
    elif (string == "청포도 에이드"):
        return 4500
    elif (string == "레몬 에이드"):
        return 4500
    else:
        return 0


while True:
    try:
        content.append(input())

    except EOFError:
        break


for i in content:
    splited = i.split(',')
    arr = [0 for i in range(len(names))]

    if splited[0] != '' : 
        dates.append(splited[0])
        for j in range(len(names)):
            arr[j] = into_amount(splited[j+1])
        result.append(arr)

    else : 
        for j in range(len(names)):
            result[-1][j] += into_amount(splited[j+1])


print(",김A,이B,김C,박D,하E")
for i in range(len(result)):
    print(dates[i][:4]+'-'+dates[i][6:8]+'-'+dates[i][10:12],end=",")
    for j in range(len(result[i])):
        if ( j == len(result[i])-1):
            print(result[i][j])
        else: 
            print(result[i][j], end=",")