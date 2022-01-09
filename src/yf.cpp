#include <RcppArmadillo.h>
//#include <Rcpp.h>
#include <cmath>
// [[Rcpp::depends(RcppArmadillo)]]
using namespace arma;
//using namespace Rcpp;
// [[Rcpp::export]]

  mat yf(mat w1,mat smat,mat fcasts){
    mat w=w1.i();
    mat z=smat.t();
    mat f=fcasts.t();
    mat wy=w * f;
    mat y=z * wy;
    return y;
  }
  

  // [[Rcpp::export]]  
  mat zsbf(mat smat,mat b){
    mat z=smat.t();
    mat sb=smat*b;
    mat zsb=z * sb;
    return zsb;
  }
  
