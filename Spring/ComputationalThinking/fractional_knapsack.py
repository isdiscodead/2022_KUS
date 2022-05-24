from random import randint
import time

def random_weight(n):
    weights = [randint(1, 20) for i in range(n)]
    return weights

def random_value(n): 
    values = [randint(1, 100) for i in range(n)]
    return values



# 모든 node( item )을 방문했는지 확인하는 함수 
def is_every_item_visited(visited):
    for x in visited:
        if x==False:
            return False
    return True


# naive approach 
def fractional_knapsack_naive(currWeight, currValue, items, visited):
    global resValue # 재귀 호출, 함수 종료 시에도 유지되어야 하므로 global 키워드로 전역 변수 사용 

    # 현재 배낭의 무게가 제한을 초과하지 않았는지 확인 
    if currWeight <= W :
        # 현재 value가 지금까지 중 가장 크다면 정보 기록하기 
        if currValue > resValue :
            resValue = currValue

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
            # 정보 담기 
            frac = (W-currWeight) / weights[i] # 얼마나 담을지 비율 
            incWeight = frac*weights[i]
            incValue = frac*values[i]

            items[i] = frac # 각 아이템의 어느정도를 담았는지... 
            visited[i] = True # 방문했음을 표시 

            fractional_knapsack_naive(currWeight+incWeight, currValue+incValue, items,visited) # 재귀 호출하여 다음 선택
            
            # 일종의 backtrack으로, 재귀 호출이 모두 종료될 경우 ( 끝까지 탐색 ) 다음 탐색을 위해 방문 X 노드로 표시 
            visited[i] = False 
            items[i] = 0

        # 넘치지 않으면 그냥 전부 담기 
        else:
            items[i] = 1 # 전체 = 비율 1 
            visited[i] = True

            # 마찬가지로 서브트리 탐색 
            fractional_knapsack_naive(currWeight+weights[i], currValue+values[i], items, visited)
            
            visited[i] = False
            items[i] = 0

        # i번째 노드로 시작하는 subtree 탐색 종료! i를 방문한 노드로 표시 후 재귀 호출 -> i+1 시작 탐색 
        visited[i] = True
        fractional_knapsack_naive(currWeight,currValue,items,visited)
        visited[i] = False


# Greedy
def fractional_knapsack_greedy():
    global resValue
    capacity = W
    
    cost = [] # 가성비 ... v/w
    for i in range(n):
        cost.append(( values[i] / weights[i] , i ))
    cost.sort(reverse = True) # 내림차순 정렬 

    # 단가 순 fraction 계산
    for c in cost:
        if capacity >= weights[c[1]] :
            capacity -= weights[c[1]]
            resValue += values[c[1]]
        else:
            fraction = capacity / weights[c[1]]
            resValue += values[c[1]] * fraction
            break
     


# DP 
def fractional_knapsack_dp(): 
    global resValue

    # 각 size W를 넘지 않는 상태에서, i개의 아이템을 담은 상태에서 최대 profit을 담는 배열 
    P = [ [0 for x in range(W+1)] for x in range(n+1)] # [n+1][W+1] 0으로 초기화 

    for i in range(n+1):
        for w in range(W+1):
            if i==0 or w==0: # 0행 또는 0열은 skip 
                P[i][w] = 0;

            elif weights[i-1] <= w:
                P[i][w] = max( values[i-1] + P[i-1][w - weights[i-1]], P[i-1][w] )

            else:
                frac = 1 / weights[i-1] # weight 1 단위로 설정  ... dksl d어케함 ;;
                P[i][w] = max( frac*values[i-1] + P[i-1][w - 1], P[i-1][w] )

    resValue = P[n][W]



# 문제 정의 
weights = random_weight(7)
n = len(weights)
values = random_value(n)

W = 15 # capacity


# results of naive approach
resValue=0 # 최종 value
start = time.time()
fractional_knapsack_naive(0, 0, [0 for i in range(n)], [False for i in range(n)])
end = time.time()
print("### Naive Approach ####")
print("Maximum profit:",resValue)
print("Time: %.5f" % (end - start))


# results of greedy approach
resValue=0 # 최종 value
start = time.time()
fractional_knapsack_greedy()
end = time.time()
print("\n### Greedy Approach ####")
print("Maximum profit:",resValue)
print("Time: %.5f" % (end - start))


# results of dp
resValue=0 # 최종 value
start = time.time()
fractional_knapsack_dp()
end = time.time()
print("\n### Dynamic Programming ####")
print("Maximum profit:",resValue)
print("Time: %.5f" % (end - start))