set.seed(100)
abc <- ts(5 + matrix(sort(rnorm(2400)), ncol = 4, nrow = 6000))
g <- rbind(c(1,1,2,2), c(1,2,1,2))
y <- gts(abc, groups = g)
h <- 1200000
ally <- aggts(y)
allf <- matrix(NA,nrow = h,ncol = ncol(ally))
for(i in 1:ncol(ally))
  allf[,i] <- forecast(auto.arima(ally[,i]),h = h)$mean
allf <- ts(allf, start = 51)
y.f <- combinef(allf, groups = get_groups(y), keep ="gts", algorithms = "lu")
y.f2 <- combinef2(allf, groups = get_groups(y), keep ="gts", algorithms = "lu")

library(microbenchmark)
testResult1 = microbenchmark(combinef(allf, groups = get_groups(y), keep ="gts", algorithms = "lu"),
                             combinef2(allf, groups = get_groups(y), keep ="gts", algorithms = "lu"),times = 50) 
testResult1
