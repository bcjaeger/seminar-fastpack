
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



#include <Rcpp.h>
#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// rcpp_count_dbl
NumericVector rcpp_count_dbl(NumericVector status, NumericVector group);
RcppExport SEXP sourceCpp_1_rcpp_count_dbl(SEXP statusSEXP, SEXP groupSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type status(statusSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type group(groupSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_count_dbl(status, group));
    return rcpp_result_gen;
END_RCPP
}
