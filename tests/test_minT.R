source("/Users/MC/Desktop/计算机基础/bpv.R")
source('/Users/MC/Desktop/计算机基础/combinefm.R')
source('/Users/MC/Desktop/计算机基础/combineg.R')
source('/Users/MC/Desktop/计算机基础/hts-package.R')
source('/Users/MC/Desktop/计算机基础/middleout.R')
source('/Users/MC/Desktop/计算机基础/recursive.R')
source('/Users/MC/Desktop/计算机基础/topdown.R')
source('/Users/MC/Desktop/计算机基础/tracemin.R')
source('/Users/MC/Desktop/计算机基础/window-gts.R')
source('/Users/MC/Desktop/计算机基础/MinTbpv2.R')
nodes <- list(2, c(3, 2))
abc <- ts(5 + matrix(sort(rnorm(500)), ncol = 5, nrow = 100))
htseg1 <- hts(abc, nodes)
#set.seed(100)
#abc <- ts(5 + matrix(sort(rnorm(2400)), ncol = 4, nrow = 600))
#g <- rbind(c(1,1,2,2), c(1,2,1,2))
#htseg1 <- gts(abc, groups = g)
h <- 12
ally <- aggts(htseg1)
n <- nrow(ally)
p <- ncol(ally)
allf <- matrix(NA, nrow = h, ncol = p)
res <- matrix(NA, nrow = n, ncol = p)
for(i in 1:p)
{
  fit <- auto.arima(ally[, i])
  allf[, i] <- forecast(fit, h = h)$mean
  res[, i] <- na.omit(ally[, i] - fitted(fit))
}
allf <- ts(allf, start = 51)


y.m <- MinT(allf, get_nodes(htseg1), residual = res, covariance = "shr",
            keep = "gts", algorithms = "lu")#这是改写的函数
yp.m <- MinT2(allf, get_nodes(htseg1), residual = res, covariance = "shr",
            keep = "gts", algorithms = "lu")
testResult = microbenchmark(y.m ,yp.m ,times = 50) 
testResult

