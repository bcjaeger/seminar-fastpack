library(aorsf)
library(dplyr)
library(microbenchmark)
library(data.table)
library(Rcpp)
library(readr)

# Think about
# 1. data copies and casting
# 1. number of operations
# 1. RcppArmadillo

# Think about
# function names
# documenting expectations

results <- list()

sourceCpp('src/count_events.cpp')

status = sample(x = c(0L, 1L), size = 1e5, replace = TRUE)
group = sample(x = 0:2, size = 1e5, replace = TRUE)

bm_1 <- microbenchmark(
 table              = table(status, group)[2, ],
 tapply             = tapply(status, group, sum),
 rcpp_count_dbl     = rcpp_count_dbl(status, group, n_groups = 3),
 rcpp_count_int     = rcpp_count_int(status, group, n_groups = 3),
 rcpp_count_1loop_int = rcpp_count_1loop_int(status, group, n_groups = 3),
 arma_count_1loop_int  = arma_count_1loop_int(status, group, n_groups = 3),
 times = 1000
)

write_rds(bm_1, 'benchmark.rds')

for(j in 1:8){

 pbc_temp <- pbc_orsf %>%
  transmute(status = as.integer(status),
         stage = as.integer(stage) -1L)

 for(i in 1:j)
  pbc_temp <- rbind(pbc_temp, pbc_temp)

 setDT(pbc_temp)

 bm <- microbenchmark(

  table = table(pbc_temp$status, pbc_temp$stage),

  tapply = tapply(pbc_temp$status, pbc_temp$stage, sum),

  dt = pbc_temp[, .(answer = sum(status)), keyby = stage],

  cpp = rcpp_count_dbl(pbc_temp$status, pbc_temp$stage),

  cpp_int = rcpp_count_int(pbc_temp$status, pbc_temp$stage),

  cpp_minop = count_events_min_oper(pbc_temp$status, pbc_temp$stage),

  cpp_arma = arma_count_1loop_int(pbc_temp$status, pbc_temp$stage),

  times = 1000

 )

 results[[j]] <-
  tibble::tibble(expr = bm$expr,
                 time = bm$time)
}

data_results <- bind_rows(results, .id = 'run') %>%
 mutate(run = nrow(pbc_orsf)*2^(as.numeric(run))) %>%
 group_by(run, expr) %>%
 summarize(time = median(time))

library(ggplot2)

ggplot(data_results) +
 aes(x = run, y = time, color = expr) +
 geom_line() +
 geom_point() +
 scale_y_log10() +
 scale_x_log10()




x = pbc_orsf$status
g = as.integer(pbc_orsf$stage)

g_uni = unique(g)

out = integer(length = length(g_uni))

for(i in seq_along(g_uni)){

 for(j in seq_along(g)){
  if(g[j] == g_uni[i]) out[i] = out[i] + x[j]
 }

}
