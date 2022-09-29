##################################
## Lecture Material             ##
## for Probability & Statistics ##
## Jiwon Lee                    ##
## 2022-09-28                   ##
##################################

setRepositories(ind = 1:7)

#install.packages("devtools")
#install_github('jhk0530/Rstat')
#install.packages("ggVennDiagram")
#install.packages("animation")

library(devtools)
library(Rstat)
library(ggVennDiagram)
library(animation)
library(dplyr)
library(scatterplot3d)


#####################################################################


## Set two fair dice (Self-Checking 1)
nsides <- 6
times <- 2

temp <- list()

for (i in 1:times) {
  temp[[i]] <- 1:nsides
}


## Sample Space S
S <- expand.grid(temp, KEEP.OUT.ATTRS = FALSE)
names(S) <- c(paste(rep("Dice_", times), 1:times, sep = ""))
nrow(S)


## For combination
S

for(i in 1:nrow(S)){
  S[i,] <- sort(as.numeric(S[i,]))
}

distinct(S)
S <- distinct(S)
nrow(S)


## Get Event A
eventA <- subset(S, ((Dice_1+Dice_2) %% 2)==0)
element(eventA)

## Get Event B
eventB <- subset(S, (Dice_1+Dice_2) >=8)
element(eventB)

## Get Event C
eventC <- subset(S, abs(Dice_1 - Dice_2) <= 1)
element(eventC)


## Intersection
AB <- intersect2(eventA, eventB)
element(AB)

AC <- intersect2(eventA, eventC)
element(AC)

BC <- intersect2(eventB, eventC)
element(BC)


## Complement
Ac <- setdiff(S, eventA)
element(Ac)

Bc <- setdiff(S, eventB)
element(Bc)

Cc <- setdiff(S, eventC)
element(Cc)


## Drawing Venn-diagram
vennData <- list(A = element(eventA),
                 B = element(eventB),
                 C = element(eventC))

ggVennDiagram(vennData)


####################################################################


## Simulation of law of large numbers (Self-Checking 2)
ani.options(nmax = 1000, interval = 0.00001)
win.graph(7,4)

lln.ani(FUN = function(n, mu) rbinom(n, size=1, prob = mu), mu = 0.5, type="n", col.poly="blue")

title(main = "Law of Large Numbers (Korea Univ.)")


## Self-Checking non-amination version
nTimes <- 1000

eventCoin <- c()

for(i in 1:nTimes){
  eventCoin[i] <- rbinom(1, size=1, prob = 0.5)
  print(paste0(i, " times drawing... Prob(Head) = ", (sum(eventCoin == 1) / length(eventCoin))))
}


## For dice problem
nTimes <- 100000

eventDice <- c()
expectedOutcome <- 1:6

for(i in 1:nTimes){
  eventDice[i] <- (sample(expectedOutcome)[1])
  print(paste0(i, " times drawing... Prob(eachValue) = ", (sum(eventDice == 1) / length(eventDice))))
}


####################################################################


## Toss coin (Self-Checking 3)
times <- 4

temp <- list()
for (i in 1:times) {
  temp[[i]] <- c("H", "T")
}

S <- expand.grid(temp, KEEP.OUT.ATTRS = FALSE)
names(S) <- c(paste(rep("X", times), 1:times, sep = ""))

S <- S[order(S$X1, S$X2, S$X3, S$X4),]
element(S)

countHeadFunction <- function(x) sum(x == "H")

A <- subset(S, apply(S, 1, countHeadFunction) >= 2)
pprt(A, nrow(S))
nrow(A) / nrow(S)


####################################################################


## rolling four dices at the same time (Self-Checking 4)
S <- rolldie2(4) # r에서 제공하는 주사위 function 

# event A
A <- subset(S, X1+X2+X3+X4 >= 15)
pprt(A, nrow(S))

# event B
B <- subset(S, apply(S, 1, max)==6)
pprt(B, nrow(S))

# event C 
C <- subset(S, apply(S, 1, min)==1)
pprt(C, nrow(S))


AB <- intersect2(A,B)
AC <- intersect2(A,C)
BC <- intersect2(B,C)

ABC <- intersect2(AB,C) 


pprt(AB, nrow(S))
pprt(AC, nrow(S))
pprt(BC, nrow(S))
pprt(ABC, nrow(S))


# Drawing Venn-diagram
vennData <- list(A = element(A),
                 B = element(B),
                 C = element(C))

ggVennDiagram(vennData)


########################################################3


## Self-Checking 5
AuB <- union2(A,B)
AuC <- union2(A,C)
BuC <- union2(B,C)
AuBuC <- union2(AuB,C)

pprt(AuB, nrow(S))
pprt(AuC, nrow(S))
pprt(BuC, nrow(S))
pprt(AuBuC, nrow(S))


########################################################3


## Self-Checking 6
cprt(A, B)
cprt(A, C)
cprt(A, BC)
cprt(A, BuC)


########################################################3


## Self-Checking 7
S <- rolldie2(5)

evenEventFunction <- function(x){
  (sum(x)%%2)==0
} 

span5EventFunction <- function(x){
  (max(x)-min(x))==5
}

evenEventFunction(S[1,])
span5EventFunction(S[1,])

evenEventFunction(S[6,])
span5EventFunction(S[6,])

A <- subset(S, apply(S, 1, evenEventFunction))
nrow(A)

B <- subset(S, apply(S, 1, span5EventFunction))
nrow(B)

N <- nrow(S)

cprt2 <- function(a, an, b, bn) {
  ab = intersect2(a, b)
  cat(paste0("P(",an,"|",bn,") ="), nrow(ab),"/",nrow(b),
      "=", nrow(ab)/nrow(b))
}

pprt2 <- function(x, xn, n, prt=TRUE) {
  if (prt==TRUE) cat(paste0("P(", xn, ") ="), nrow(x), "/", n, 
                     "=", nrow(x)/n,"\n")
  invisible(nrow(x)/n)
}

indep.event(A, B, N)


########################################################3


## Self-Checking 8
prior <- c(0.2, 0.4, 0.3, 0.1)
cond <- c(4, 2, 1, 5)/100
tot <- prior*cond
tot
stot <- sum(tot)



## Self-Checking 9
post <- tot / stot
bayes.plot(prior, post)



######################################################
## Lab code for Chap.2 (Cont.)                      ##
######################################################


## Self-Checking 1
S <- tosscoin2(3) # 1. sample space 생성 ... event 적용 

countT <- function(x){ # 2. random variable = function
  sum(x == "T") # how many ... 
}

X <- apply(S, 1, countT) # apply random variable -> real value 

pX <- table(X) / nrow(S) # 3. pdf/pmf -> full case frequency
pX
plot(pX) 


## Self-Checking 2
# 동시에 4개의 주사위 던짐 ... 
nTimes <- 4

S <- rolldie2(nTimes)

N <- nrow(S) 
X <- apply(S, 1, sum) # random var ... sum of 4 dices 

X.freq <- table(X)
print(addmargins(X.freq)) # all cases ... pdf 

X.prob <- X.freq/N
print(round(addmargins(X.prob), 4)) # 확률... pmf 

X.val <- as.numeric(names(X.freq))

EX <- sum(X.val * X.prob)
EX2 <- sum(X.val^2 * X.prob)
VX <- EX2 - EX^2
DX <- sqrt(VX)

Xmin <- min(X.val)
Xmax <- max(X.val)

win.graph(7, 5)
plot(X.prob, type = "h", col = "red", main = paste0("Probability Distribution of the Sum of ", nTimes, " Dice"), lwd = 4, ylim = c(0, max(X.prob) + 0.01))

fitnorm <- function(x) dnorm(x, EX, DX)
curve(fitnorm, Xmin, Xmax, add = T, col = 4)
text(Xmin:Xmax, X.prob, labels = X.freq, pos = 3, col = 4, 
     cex = 1)
legend("topright", c(paste("S-S.Size =", N), paste("E(X) =", EX), paste("D(X) =", round(DX, 4))), bg = "white")



## Self-Checking 3
xv <- 0:3
xp <- choose(3, 0:3)

xname <- deparse(substitute(xv))
if (sum(xp) > 1) {
  xp <- xp/sum(xp)
}

xcdf <- c(0, cumsum(xp))
sf <- stepfun(xv, xcdf)

plot(sf, verticals = F, pch = 19, lwd = 2, cex = 1.2, col = 2, xlab = "x", ylab = "F(x)")
grid(col = 3)
points(xv, xcdf[-length(xcdf)], col = 2, cex = 1)
text(xv, xcdf[-1], labels = round(xcdf[-1], 3), cex = 1, 
     col = 4, pos = 2)
EX <- sum(xv * xp)
EX2 <- sum(xv^2 * xp)
VX <- EX2 - EX^2
DX <- sqrt(VX)
legend("bottomright", c(paste("E(X) =", round(EX, 4)), paste("D(X) =", round(DX, 4))), bg = "white")



## Self-Checking 4
S <- rolldie2(2)
N <- nrow(S)

X <- apply(S, 1, max)
Y <- apply(S, 1, min)

disc.joint2(X, Y, plot = T)



## Self-Checking 5
X <- c(-3, -1, 1, 3)*100
P <- c(1, 3, 3, 1)/8
disc.exp(X, P, plot = T)


## Self-Checking 6
x <- 1:6
f <- rep(1,6)
disc.exp(x, f)


## Self-Checking 7
x <- 1:6
f <- rep(1,6)
y <- 100*x - 400
disc.exp(y, f)




