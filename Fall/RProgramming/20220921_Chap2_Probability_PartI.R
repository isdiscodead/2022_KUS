##################################
## Lecture Material             ##
## for Probability & Statistics ##
## Jiwon Lee                    ##
## 2022-09-21                   ##
##################################

setRepositories(ind = 1:7)

# 외부 패키지 사용을 위한 패키지
# install.packages("devtools")
library(devtools)

# Github에서 패키지 다운로드
# install_github('jhk0530/Rstat') # devtool 있어야 사용 가능 
# install.packages("ggVennDiagram")
# install.packages("animation")

library(Rstat)
library(ggVennDiagram) # 벤다이어그램 시각화 패키지 
library(animation)
library(dplyr)



## Set two fair dice (Self-Checking 1)
nsides <- 6 # 6면체의 주사위 
times <- 2 # 2개의 주사위 

temp <- list() # 빈 list 생성 

for (i in 1:times) { # 두 개의 주사위 ... 
  temp[[i]] <- 1:nsides
}



## Sample Space S
S <- expand.grid(temp, KEEP.OUT.ATTRS = FALSE)
names(S) <- c(paste(rep("Dice_", times), 1:times, sep = ""))
nrow(S) # sample space의 원소 개수 6^2



## Setting For combination
S

for(i in 1:nrow(S)){
  S[i,] <- sort(as.numeric(S[i,]))
}

# no order ... (2,3) == (3, 2)
distinct(S) 
S <- distinct(S)
nrow(S)



## Event = Subset of sample space 

## Get Event A -> sum of the dice values is even
eventA <- subset(S, ((Dice_1+Dice_2) %% 2)==0)
element(eventA)

## Get Event B -> sum >= 8
eventB <- subset(S, (Dice_1+Dice_2) >= 8)
element(eventB)

## Get Event C -> | a - b | < 1
eventC <- subset(S, abs(Dice_1 - Dice_2) < 1)
element(eventC)



## Intersection ; 교집합 = and 
AB <- intersect2(eventA, eventB)
element(AB)
AC <- intersect2(eventA, eventC)
element(AC)
BC <- intersect2(eventB, eventC)
element(BC)


## Complement ; 여집합 = 전체 - 집합 
Ac <- setdiff(S, eventA) # 홀수 합 
element(Ac)
Bc <- setdiff(S, eventB) # 합 8보다 작음 
element(Bc)
Cc <- setdiff(S, eventC) # 같은 눈 X 
element(Cc)


## Drawing Venn-diagram ; 시각화
# 독립성 가지려면 벤다이어그램 떨어져있음 ... 
vennData <- list(A = element(eventA),
                 B = element(eventB),
                 C = element(eventC))

ggVennDiagram(vennData)



## Simulation of law of large numbers (Self-Checking 2) 대수의 법칙 
# relative frequency를 무한대로 늘리면 계산된 probability에 수렴 
ani.options(nmax = 1000, interval = 0.00001) # animation 라이브러리로 ... 중요한 내용은 아님 
win.graph(7,4)

lln.ani(FUN = function(n, mu) rbinom(n, size=1, prob = mu), mu = 0.5, type="n", col.poly="blue")

title(main = "Law of Large Numbers (Korea Univ.)")



## Self-Checking non-amination version
nTimes <- 5000 # 100일때 0.39, 1000일때 0.494, 5000일 때 0.5094

eventCoin <- c()

for(i in 1:nTimes){
  eventCoin[i] <- rbinom(1, size=1, prob = 0.5) # 확률 0.5로 0또는 1 생성 
  print(paste0(i, " times drawing... Prob(Head) = ", (sum(eventCoin == 1) / length(eventCoin))))
}



## 주사위 버전으로 만들어보기 
# 랜덤 넘버 생성 ... 
for(i in 1:nTimes){
  print(rbinom(1, size=6, prob = 1/6)) # 대부분 0~2 사이의 값이 나옴 
}

# 더 적절한 방법 
nTimes <- 1000 # 100일때 0.39, 1000일때 0.494, 5000일 때 0.5094
eventDice <- c()
expectedOutcome <- 1:6

for ( i in 1:nTimes ) {
  eventDice[i] <- sample(expectedOutcome)[1] # 자동으로 뽑아주는 ... sample()로 출력 ! 
  print(eventDice[i])
  print(paste0(i, " times drawing... Prob(Head) = ", (sum(eventDice == 1) / length(eventDice))))
}


