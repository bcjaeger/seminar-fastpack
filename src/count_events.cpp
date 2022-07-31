#include <RcppArmadillo.h>
#include <RcppArmadilloExtensions/sample.h>

// [[Rcpp::depends(RcppArmadillo)]]

using namespace Rcpp;
using namespace arma;


// [[Rcpp::export]]
NumericVector rcpp_count_dbl(NumericVector status,
                             NumericVector group,
                             int n_groups) {

 NumericVector out(n_groups);

 for( int i = 0; i < n_groups; i++ ){
  for( int j = 0; j < group.length(); j++ ){
   if(group[j] == i) out[i] += status[j];
  }
 }

 return(out);
}

// [[Rcpp::export]]
IntegerVector rcpp_count_int(IntegerVector status,
                             IntegerVector group,
                             int n_groups) {

 IntegerVector out(n_groups);

 for( int i = 0; i < n_groups; i++ ){
  for( int j = 0; j < group.length(); j++ ){
   if(group[j] == i) out[i] += status[j];
  }
 }

 return(out);
}

// (n + 2*n*g) / n

// [[Rcpp::export]]
IntegerVector rcpp_count_1loop_int(IntegerVector status,
                                   IntegerVector group,
                                   int n_groups) {

 IntegerVector out(n_groups);

 IntegerVector::iterator i;

 int j = 0;

 for(i = group.begin() ; i != group.end(); ++i, ++j){

  out[*i] += status[j];

 }

 return(out);

}

// [[Rcpp::export]]
arma::ivec arma_count_1loop_int(arma::ivec& status,
                                arma::ivec& group,
                                arma::uword n_groups) {

 ivec out(n_groups);

 ivec::iterator i;
 uword j = 0;

 for(i = group.begin() ; i != group.end(); ++i, ++j){

  out[*i] += status[j];

 }

 return(out);

}


