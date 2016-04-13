/*
GPLv3 License.
Definitions of a collection of basic statistic functions in
OC_basicStats.h
*/
#include <math.h>
#include "OC_basicStats.h"

double meanSingleVector(const char a_type,const int a_size,
    const void* a_data)
{ 
/*  a_type = {i,f,...}
    a_type == 'i' means a_data is an integer array, 
           == 'f' means a_data is a float array 
    else         a_data is a double array
    a_size =  number of elements in the vector a_data
    a_data =  dataset whose mean is to be computed */
    double result = 0.0;
    if (a_type == 'i') {
        int* p = (int*) a_data; 
        /* this line is the only difference in the three cases */
        for (int i = 0; i < a_size; ++i)
            result += (p[i] -  result) / (i + 1);
    }
    else if (a_type == 'f') {
        float* p = (float*) a_data;
        for (int i = 0; i < a_size; ++i)
            result += (p[i] -  result) / (i + 1);
    }
    else {
        double* p = (double*) a_data;
        for (int i = 0; i < a_size; ++i)
            result += (p[i] -  result) / (i + 1);
    }
    return result;
}

void meanSdSingleVector(const int a_mode,const char a_type,const int a_size,
    const void* a_data,double a_result[2])
{
/* a_mode   = {0,1}
   a_mode   == 0 to compute population standard deviation
   a_mode   == 1 to compute sample standard deviation
   a_type   =  data type of a_data, as per meanSingleVector
   a_data   =  dataset whose standard deviation is to be computed
   a_result[0] = mean of dataset, nan if a_mode incorrect
   a_result[1] = std_dev of dataset, nan if a_size < 2
 */
    if ((a_mode < 0) || (a_mode > 1)) {
        a_result[0] = nan("");
        return;
    }
    if (a_size < 2) {
        a_result[1] = nan("");
        return;
    }
    double M2 = 0.0, mean = 0.0, delta;
    if (a_type == 'i') {
        int* p = (int*) a_data; 
        /* this line is the only difference in the three cases */
        for (int i = 0; i < a_size; ++i) {
        /* Following Wikipedia's algorithm for online variance */
            int x = p[i];
            delta = x - mean;
            mean += delta / (i + 1);
            M2 += delta * (x - mean);
        }
    }
    else if (a_type == 'f') {
        float* p = (float*) a_data; 
        for (int i = 0; i < a_size; ++i) {
            float x = p[i];
            delta = x - mean;
            mean += delta / (i + 1);
            M2 += delta * (x - mean);
        }
    }
    else {
        double* p = (double*) a_data; 
        for (int i = 0; i < a_size; ++i) {
            double x = p[i];
            delta = x - mean;
            mean += delta / (i + 1);
            M2 += delta * (x - mean);
        }
    }
    a_result[0] = mean;
    a_result[1] = sqrt(M2 / (a_size - a_mode) );
    /* Bessel's correction */
}

double correlationCoefficient2Variables(const int a_size,
    const char a_type1,const void* a_data1,const char a_type2,
    const void* a_data2)
{
/* a_size  =  size of datasets
   a_type1 = data type of a_data1, same connotation as in 
                meanSingleVector
   a_data1 = dataset 1
   a_type2 = data type of a_data2, same connotation as in 
                meanSingleVector
   a_data2 = dataset 2 */
    if (a_size < 2) return nan("");
    double mean1 = 0.0, mean2 = 0.0, var1 = 0.0, var2 = 0.0, var12 = 0.0,
        delta1, delta2;
    if ((a_type1 == 'i') && (a_type2 == 'i')) {
        int* p1 = (int*) a_data1;
        int* p2 = (int*) a_data2;
        /* These two lines are the only difference between the cases */
        for (int i = 0; i < a_size; ++i) {
            /* Following Wikipedia's algorithm for 
                online covariance */
            delta1 = (p1[i] - mean1) / (i + 1);
            mean1 += delta1;
            delta2 = (p2[i] - mean2) / (i + 1);
            mean2 += delta2;
            var12 += i * delta1 * delta2 - var12 / (i + 1);
            var1 += i * delta1 * delta1 - var1 / (i + 1);
            var2 += i * delta2 * delta2 - var2 / (i + 1);
        }
    }
    else if ((a_type1 == 'i') && (a_type2 == 'f')) {
        int* p1 = (int*) a_data1;
        float* p2 = (float*) a_data2;
        for (int i = 0; i < a_size; ++i) {
            delta1 = (p1[i] - mean1) / (i + 1);
            mean1 += delta1;
            delta2 = (p2[i] - mean2) / (i + 1);
            mean2 += delta2;
            var12 += i * delta1 * delta2 - var12 / (i + 1);
            var1 += i * delta1 * delta1 - var1 / (i + 1);
            var2 += i * delta2 * delta2 - var2 / (i + 1);
        }
    }
    else if ((a_type1 == 'f') && (a_type2 == 'i')) {
        float* p1 = (float*) a_data1;
        int* p2 = (int*) a_data2;
        for (int i = 0; i < a_size; ++i) {
            delta1 = (p1[i] - mean1) / (i + 1);
            mean1 += delta1;
            delta2 = (p2[i] - mean2) / (i + 1);
            mean2 += delta2;
            var12 += i * delta1 * delta2 - var12 / (i + 1);
            var1 += i * delta1 * delta1 - var1 / (i + 1);
            var2 += i * delta2 * delta2 - var2 / (i + 1);
        }
    }
    else if ((a_type1 == 'f') && (a_type2 == 'f')) {
        float* p1 = (float*) a_data1;
        float* p2 = (float*) a_data2;
        for (int i = 0; i < a_size; ++i) {
            delta1 = (p1[i] - mean1) / (i + 1);
            mean1 += delta1;
            delta2 = (p2[i] - mean2) / (i + 1);
            mean2 += delta2;
            var12 += i * delta1 * delta2 - var12 / (i + 1);
            var1 += i * delta1 * delta1 - var1 / (i + 1);
            var2 += i * delta2 * delta2 - var2 / (i + 1);
        }
    }
    else if (a_type1 == 'i') {
        int* p1 = (int*) a_data1;
        double* p2 = (double*) a_data2;
        for (int i = 0; i < a_size; ++i) {
            delta1 = (p1[i] - mean1) / (i + 1);
            mean1 += delta1;
            delta2 = (p2[i] - mean2) / (i + 1);
            mean2 += delta2;
            var12 += i * delta1 * delta2 - var12 / (i + 1);
            var1 += i * delta1 * delta1 - var1 / (i + 1);
            var2 += i * delta2 * delta2 - var2 / (i + 1);
        }
    }
    else if (a_type1 == 'f') {
        float* p1 = (float*) a_data1;
        double* p2 = (double*) a_data2;
        for (int i = 0; i < a_size; ++i) {
            delta1 = (p1[i] - mean1) / (i + 1);
            mean1 += delta1;
            delta2 = (p2[i] - mean2) / (i + 1);
            mean2 += delta2;
            var12 += i * delta1 * delta2 - var12 / (i + 1);
            var1 += i * delta1 * delta1 - var1 / (i + 1);
            var2 += i * delta2 * delta2 - var2 / (i + 1);
        }
    }
    else if (a_type2 == 'i') {
        double* p1 = (double*) a_data1;
        int* p2 = (int*) a_data2;
        for (int i = 0; i < a_size; ++i) {
            delta1 = (p1[i] - mean1) / (i + 1);
            mean1 += delta1;
            delta2 = (p2[i] - mean2) / (i + 1);
            mean2 += delta2;
            var12 += i * delta1 * delta2 - var12 / (i + 1);
            var1 += i * delta1 * delta1 - var1 / (i + 1);
            var2 += i * delta2 * delta2 - var2 / (i + 1);
        }
    }
    else if (a_type2 == 'f') {
        double* p1 = (double*) a_data1;
        float* p2 = (float*) a_data2;
        for (int i = 0; i < a_size; ++i) {
            delta1 = (p1[i] - mean1) / (i + 1);
            mean1 += delta1;
            delta2 = (p2[i] - mean2) / (i + 1);
            mean2 += delta2;
            var12 += i * delta1 * delta2 - var12 / (i + 1);
            var1 += i * delta1 * delta1 - var1 / (i + 1);
            var2 += i * delta2 * delta2 - var2 / (i + 1);
        }
    }
    else {
        double* p1 = (double*) a_data1;
        double* p2 = (double*) a_data2;
        for (int i = 0; i < a_size; ++i) {
            delta1 = (p1[i] - mean1) / (i + 1);
            mean1 += delta1;
            delta2 = (p2[i] - mean2) / (i + 1);
            mean2 += delta2;
            var12 += i * delta1 * delta2 - var12 / (i + 1);
            var1 += i * delta1 * delta1 - var1 / (i + 1);
            var2 += i * delta2 * delta2 - var2 / (i + 1);
        }
    }
    return var12 / sqrt(var1 * var2);
    /* From formula for correlation coefficient, which takes
       the same form for population and sample */
}
