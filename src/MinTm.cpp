#include <RcppArmadillo.h>
#include <cmath>
// [[Rcpp::depends(RcppArmadillo)]]
using namespace arma;
using namespace Rcpp;
// [[Rcpp::export]]


mat MinTm(vec fcasts,mat smat, mat vmat,char alg,Function chol,Function lu,
          Function cg){
  int totalts = smat.n_cols;
  bool allow = TRUE;

  if (fcasts.size() != totalts) {
    cout<<"Argument fcasts requires all the forecasts.";
  }
    if (alg == char('chol')) {
      //Function CHOLFromR = Environment::global_env()["CHOLR"];
      NumericVector allf= chol(fcasts,smat, vmat,allow);
      return allf;
      //undefined allf= CHOL(fcasts,smat, vmat,allow);
      //此处调用tracemin中的LU,CHOL,CG函数
    } 
    else if (alg == char('lu')) {
      NumericVector allf = lu(fcasts,smat, vmat,allow);
      return allf;
    } else {
      NumericVector allf = cg(fcasts, smat, vmat,allow);
      return allf;
    }
}