# 모든 node( item )을 방문했는지 확인하는 함수 
def is_every_item_visited(visited):
    for x in visited:
        if x==False:
            return False
    return True

def fractional_knapsack_naive(currWeight,currValue,items,visited):
    global resValue,resWeight,resVector # 재귀 호출 시에도 유지되어야 하므로 global 키워드로 전역 변수 사용 

    # 현재 배낭의 무게가 제한을 초과하지 않았는지 확인 
    if currWeight <= W :
        # 현재 value가 지금까지 중 가장 크다면 정보 기록하기 
        if currValue > resValue :
            resValue = currValue
            resWeight = currWeight
            resItems = items[:]

    # 모든 노드 방문 시 함수 종료 ( base line )
    if is_every_item_visited(visited):
        return

    # 모든 경우를 확인하기 위해 순차 탐색
    for i in range(n):
        # 방문한 노드라면 넘기기 
        if visited[i]:
            continue

        # 새 아이템을 담았을 때 무게가 넘치면 쪼개기 
        if currWeight + weights[i] > W : 
            frac = (W-currWeight) / weights[i] # 얼마나 담을지 비율 
            incWeight = frac*weights[i]
            incValue = frac*values[i]

            items[i]=frac # 각 아이템의 어느정도를 담았는지... 
            visited[i]=True # 방문했음을 표시 
            fractional_knapsack_naive(currWeight+incWeight,currValue+incValue,items,visited) # 재귀 호출하여 다음 선택
            
            # 일종의 backtrack으로, 재귀 호출이 모두 종료될 경우 ( 끝까지 탐색 ) 다음 탐색을 위해 방문 X 노드로 표시 
            visited[i]=False 
            items[i]=0

        #if including an item doesn't exceed the knapsack capacity then include it wholly
        else:
            items[i]=1 # indicate that item is taken wholly
            visited[i]=True# mark the item as visited
            fractional_knapsack_naive(currWeight+weights[i],currValue+values[i],items,visited)
            # backtrack
            visited[i]=False
            items[i]=0

        #don't include the item and check for further items
        visited[i]=True
        fractional_knapsack_naive(currWeight,currValue,items,visited)
        visited[i]=False


# 문제 정의 
weights=[2,3,5,7,1,4,1]
values=[10,5,15,7,6,18,3]
W=15 # capacity
n=len(weights)

# results 
resValue=0 # 최종 value
resWeight=0 # 최종 무게
resItems=[] # 담은 아이템 비율 목록 
fractional_knapsack_naive(0,0,[0 for i in range(n)],[False for i in range(n)])
print("Knapsack weight:",resWeight)
print("Maximum profit:",resValue)
print("Solution vector:",resItems)