# Endo: conditional inference in case-contrl studies 
# http://www.openbugs.info/Examples/Endo.html

# In this example, three methods of different 
# model specifications are used for one equivalent
# model. This is method 1. 

# status: not tested (not complilable) since stan is broken somehow 

data {
  int n10; 
  int n01; 
  int n11; 
  int I;
  int J;
} 

derived data {
  int Y[I, 2]; 
  int est[I, 2]; 
  for (i in 1:I) {
    Y[i, 1] <- 1; 
    Y[i, 2] <- 1; 
  } 
  for (i in 1:n10) {
    est[i, 1] <- 1; 
    est[i, 2] <- 0; 
  } 
  for (i in (n10 + 1):(n10 + n01)) {  
    est[i, 1] <- 0;
    est[i, 2] <- 1;
  }
  for (i in (n10 + n01 + 1):(n10 + n01 + n11)) { 
    est[i, 1] <- 1;  
    est[i, 2] <- 1;
  }
  for (i in (n10 + n01 + n11 + 1):I ) { 
    est[i, 1] <- 0;  
    est[i, 2] <- 0;
  }
} 

parameters {
  double beta; 
} 

model {
  # METHOD 1: Logistic regression 
  beta ~ normal(1, 1000); 
  for (i in 1:I)  
    Y[i, 1] ~ binomial(1, inv_logit(beta * (est[i, 1] - est[i, J])));
} 
