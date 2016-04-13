/*
GPLv3 License.
A collection of basic statistic functions.
*/
#ifndef OC_BASICSTATS_H
#define OC_BASICSTATS_H

double meanSingleVector(const char a_type,const int a_size,
    const void* a_data);
/* Computes the mean of a single data series */
void meanSdSingleVector(const int a_mode,const char a_type,const int a_size,
    const void* a_data,double a_result[2]);
/* Computes the standard deviation of a single data series */
double correlationCoefficient2Variables(const int a_size,
    const char a_type1,const void* a_data1,const char a_type2,
    const void* a_data2);
/* Computes correlation coefficient between 2 data series */



/* Some more potential functions to consider
compoundInterestCalculator()
percentageChangeCalculator(compute %change w.r.t. for vectors)
linearRegression()
Function to find top grossing price point (in terms of unitDist /
revenueDist / profitDist) 
*/
#endif
