# Modify with your own file path here:
sourceCpp("F:/UW/C++/Homework7/egarchVolatility.cpp")

# Generate daily returns:
alphaZero <- -0.0883
alphaOne <- 0.1123
beta <- 0.9855
gamma <- -0.0925
seed <- 520
bufferSize <- 100
initSigma<- 0.25

r <- simVolatilties(alphaZero, alphaOne, gamma, beta, initSigma, bufferSize, seed)
head(r)  #first 5
tail(r)  #last 5

# 0.2500000 0.2550483 0.2535960 0.2633956 0.2611238 0.2577743 (first 5)
# 0.5443895 0.5273319 0.5116723 0.4994663 0.5051057 0.5207231 (last 5)
