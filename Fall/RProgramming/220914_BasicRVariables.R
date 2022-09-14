setRepositories() # interactive 모드로 database 종류 선택 ... CRAN 디폴트
# 어떤 레포지토리에 어떤 패키지가 있는지는 알 수 없음 ... 
# 그래서 모든 레포지토리를 선택할 수도 있음 -> 1 2 3 4 5 6 7 enter
setRepositories(ind=1:7) # 1 ~ 7 자동 선택 


getwd()
setwd("./Documents/KUS/2022/Fall/RProgramming")
getwd()


a <- 10 # 변수 할당 ... 자료형 신경 X 
A <- 20 # 대소문자 구분함 
print(a)
print(A)


help.start() # 메뉴얼을 보여주는 함수 ... 근데 메뉴얼 잘 안 씀 
?print() # 메서드나 패키지 등의 메뉴얼 확인 가능


install.packages("ggplot2") # ggplot2 패키지 설치
library(ggplot2) # load package
# MLDataR - A Package for ML datasets


variableOne <- 1:10
print(variableOne)
print(variableOne[1]) # 인덱스가 1부터 시작 ... 

variableTwo <- c("A", "B", "C") # c()는 배열 형식으로 묶어줌 
variableTwo[2] 
length(variableTwo)

variableThree <- c(1, 2, 3, "A", "B")
variableThree # 다 문자열로 처리됨 
