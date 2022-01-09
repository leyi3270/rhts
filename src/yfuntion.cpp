#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
using namespace arma;
// [[Rcpp::export]]

mat yfuntion(int alg,mat weights,mat smat,mat fcasts,int a){
  mat y;
  if(alg==1){
    if(a==1){
      mat sqwt = sqrt(weights);
      mat w = 1/sqwt;
      mat z = smat.t() * w ;// Sparse. z %*% t(z) = t(s) %*% L %*% s
      mat wy = sqwt % fcasts.t();
      mat y = z * wy ;// t(s) %*% L %*% yhat
    }
    else{
      mat z = smat.t(); //Sparse. z %*% t(z) = t(s) %*% s
      mat y = z * fcasts.t(); //t(s) %*% yhat
    }
  }
  else if (alg ==2){
    if (a==1){
      mat sqwt=sqrt(weights) ; 
      vec v = sqwt.as_col();
      mat w = diagmat(v);
      //seqts = seq(nrow(smat));
      //mat w = sparseMatrix(i = seqts, j = seqts, x = sqwt) 
      mat z = smat.t() * w; // Sparse. z %*% t(z) = t(s) %*% L %*% s
      mat wy = sqwt % fcasts.t();
      mat y = z * wy; // t(s) %*% L %*% yhat
    }
    else{
      mat z = smat.t(); //Sparse. z %*% t(z) = t(s) %*% s
      mat y = z * fcasts.t(); // t(s) %*% yhat
    }
  }
  return y;
}