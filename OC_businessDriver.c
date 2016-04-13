/*
GPLv3 License.
Driver for business statistic functions in OC_businessStats.h
*/

#define MY_DEBUG 1
#include <stdio.h>
#include "OC_businessStats.c"

int main(int narg,char* argv[])
{
    productStats* stats = NULL;
    float fixedCost = 100.0;
    initializeProductStats(&stats,fixedCost);
    const unsigned noPricePoints = 3;
    float sellingPrice[noPricePoints] = {10.0,15.0,20.0};
    float costPrice[noPricePoints] = {5.0,5.0,5.0};
    unsigned noUnits[noPricePoints] = {25,15,10};
    pricePoint* pricePoints;
    initializePricePoints(noPricePoints,sellingPrice,costPrice,noUnits,
                            &pricePoints);
    updatePricePoints(stats,noPricePoints,pricePoints);
    printProductStats(stats);
    pricePoints[2].m_noUnits = 8;
    updatePricePoints(stats,noPricePoints,pricePoints);
    printProductStats(stats);
    removePricePoints(stats,1,&pricePoints[1]);
    printPricePointStats(stats,1,&pricePoints[1]);
    printProductStats(stats);
    pricePoints[1].m_noUnits = 50;
    pricePoints[1].m_price = 5.0;
    pricePoints[1].m_cost = 5.0;
    updatePricePoints(stats,3,pricePoints);
    printProductStats(stats);
    printPricePointStats(stats,1,&pricePoints[0]);
    printPricePointStats(stats,1,&pricePoints[1]);
    printPricePointStats(stats,1,&pricePoints[2]);
    breakevenCalculator(stats,3,pricePoints);
    updateProductStats(stats,50.0);
    printProductStats(stats);
    breakevenCalculator(stats,3,pricePoints);
    destroyPricePoints(pricePoints);
    destroyProductStats(stats);
    return 0;
}
