
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector rcpp_count_dbl(NumericVector status,
                               NumericVector group) {

 NumericVector group_uni = sort_unique(group);

 NumericVector out(group_uni.length());

 int i, j;

 for(i = 0; i < group_uni.length(); i++){

  for(j = 0; j < group.length(); j++){
   if(group[j] == group_uni[i]) out[i] += status[j];
  }

 }

 return(out);

}

