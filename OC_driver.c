/*
GPLv3 License.
Driver program to test the functions
*/
#include <stdio.h>
#include "OC_basicStats.c"

int main(int argc,char* argv[])
{
    double result;
    float fdata[6] = {6.0,9.0,9.0,6.0,5.0,7.0};
    double ddata[6] = {3.0,9.0,9.0,6.0,5.0,7.0};
    int idata[6] = {6,3,9,6,5,7};
    result = meanSingleVector('f',6,fdata);
    printf("The mean float result is %f\n",result);
    result = meanSingleVector('i',6,idata);
    printf("The mean int result is %f\n",result);
    result = meanSingleVector('x',6,ddata);
    printf("The mean double result is %f\n",result);
    result = correlationCoefficient2Variables(6,'d',ddata,'i',idata);
    printf("The correlation coefficient is %f\n",result);
    double result2[2];
    meanSdSingleVector(1,'f',6,fdata,result2);
    printf("The mean is %f and std dev is %f\n",
            result2[0],result2[1]);
    return 0;
}
