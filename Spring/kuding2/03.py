size, relation_size = tuple(map(int, input().split()))
relations = []

for i in range(relation_size):
    n1,n2,soju=list(map(int,input().split()))
    relations.append((n1,n2,soju))

relations = sorted(relations, key=lambda x: x[2])


union_list=[_ for _ in range(size+1)]


def get_parent(node1):
    if union_list[node1]==node1: 
        return node1
    else :
        parent=get_parent(union_list[node1]) 
        union_list[node1]=parent 
        return parent

def make_union(parent,child): 
    union_list[get_parent(child)]=get_parent(parent)


total_cost=0
line_num=0
for node1,node2,cost in relations:
    if get_parent(node1)!= get_parent(node2) :
        make_union(node1,node2)
        total_cost+=cost
        line_num+=1

    if line_num==size-1:
        break

if line_num != size-1 : 
    total_cost = -1
    
print(total_cost)