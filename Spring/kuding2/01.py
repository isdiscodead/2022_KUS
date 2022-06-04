size = int(input())
jobs = []

if size < 8 :
    input()
    print("실패")

else :    
    for i in range(size):
        jobs.append(input())
    
    count = 0
    for i in range(size):
        if (jobs[i] == "Bard" or jobs[i] == "Paladin") :
            count += 1 
    
    if size - count < 6 :
        print("실패")
    else :
        print("성공")