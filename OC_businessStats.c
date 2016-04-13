/* 
* GPLv3 License.
* Definitions of a collection of basic statistics functions in
* OC_businessStats.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "OC_businessStats.h"
/* Function definitions */
void initializePricePoints(const unsigned a_noPrcPt,
    const float a_price[],const float a_cost[],
    const unsigned a_noUnits[],pricePoint** a_prcPt)
{
    if (!a_noPrcPt || !a_noUnits || !a_price || !a_cost) 
    {
        printf("NO PRICE POINTS TO INITIALIZE\n");
        return;
    }
    pricePoint* pricePoints = (pricePoint*) malloc(a_noPrcPt *
                                sizeof(pricePoint));
    if (!pricePoints) {
        printf("PRICE POINT ARRAY ALLOCATION FAILED\n");
        exit(-1);
    }
    for (unsigned i = 0; i < a_noPrcPt; ++i) {
        pricePoints[i].m_noUnits = a_noUnits[i];
        pricePoints[i].m_price = a_price[i];
        pricePoints[i].m_cost = a_cost[i];
    }
    *a_prcPt = pricePoints;
}
/* ------------------------------------------------------------------------- */
void destroyPricePoints(pricePoint* a_prcPt)
{
    if (!a_prcPt) {
        printf("CANNOT DESTROY NULL PTR\n");
        exit(-2);
    }
    else free(a_prcPt);
}
/* ------------------------------------------------------------------------- */
void initializeProductStats(productStats** a_stats,
    const float a_fixedCost)
{
    productStats* stats = (productStats*) malloc( sizeof(productStats) );
    if (!stats) {
        printf("PRODUCT STATS ALLOCATION FAILED\n");
        exit(-1);
    }
    stats->m_pricePoints = (pricePoint*) 
        malloc(INITIALIZER_PRODUCTSTATS * sizeof(pricePoint));
    if( !(stats->m_pricePoints) ) {
            printf("PRICE POINTS ARRAY IN PRODUCT STATS ALLOCATION FAILED\n");
            exit(-1);
    }
    for (unsigned i = 0; i < INITIALIZER_PRODUCTSTATS; ++i) {
        stats->m_pricePoints[i].m_noUnits = 0;
        stats->m_pricePoints[i].m_price = 0.0;
        stats->m_pricePoints[i].m_cost = 0.0;
        stats->m_pricePoints[i].m_unitDist = 0.0;
        stats->m_pricePoints[i].m_revDist = 0.0;
        stats->m_pricePoints[i].m_profitDist = 0.0;
    }
    stats->m_capPrcPt = INITIALIZER_PRODUCTSTATS;
    stats->m_noPrcPt = 0;
    stats->m_totUnits = 0;
    stats->m_fixedCost = a_fixedCost;
    stats->m_totRevenue = 0.0;
    stats->m_totCost = 0.0;
    stats->m_profit = 0.0;
    stats->m_profitpUnit = 0.0;
    stats->m_profitMargin = 0.0;
    stats->m_propUnitCost = 0.0;
    stats->m_costpUnit = 0.0;
    *a_stats = stats;
}
/* ------------------------------------------------------------------------- */
void destroyProductStats(productStats* a_stats)
{
    if (!a_stats) {
        printf("CANNOT DESTROY NULL PTR\n");
        exit(-2);
    }
    else {
        destroyPricePoints(a_stats->m_pricePoints);
        free(a_stats);
    }
}
/* ------------------------------------------------------------------------- */
void findPricePoint(const productStats* a_stats,
    const unsigned a_noPrcPt,
    const pricePoint* a_prcPt,int a_locs[])
{
    if (!(a_stats) || !(a_noPrcPt) || !(a_prcPt) || !(a_locs)) {
        printf("NOTHING TO PRINT\n");
        return;
    }
    for (unsigned i = 0; i < a_noPrcPt; ++i) {
        a_locs[i] = -1; /* match not found initialization */
        for (int j = 0; j < a_stats->m_noPrcPt; ++j)
            if ( (fabs(a_prcPt[i].m_price - 
                    a_stats->m_pricePoints[j].m_price) < MONEY_TOL)
                && (fabs(a_prcPt[i].m_cost - 
                    a_stats->m_pricePoints[j].m_cost) < MONEY_TOL))
            {
                a_locs[i] = j;
                break;
            }
    }
}
/* ------------------------------------------------------------------------- */
void printPricePointStats(const productStats* a_stats,
    const unsigned a_noPrcPt, 
    const pricePoint* a_prcPt)
{
    if (!(a_stats) || !(a_prcPt) || !(a_noPrcPt)) {
        printf("NOTHING TO PRINT\n");
        return;
    }
    printf("--------------- SINGLE PRICE POINT STATS --------------\n");
    printf("Price point\t\tUnit Cost\t\tNo. of units sold\t\t");
    printf("Proportion of units sold\t\tProportion of revenue\t\t");
    printf("Proportion of profits (0 units sold means not a price point)\n");
    pricePoint* pricePoints = a_stats->m_pricePoints;
    int indices[a_noPrcPt];
    findPricePoint(a_stats,a_noPrcPt,a_prcPt,indices);
    for(unsigned i = 0; i < a_noPrcPt; ++i) {
        printf("-----------------------------------------------------\n");
        int k = indices[i];
        if (k >= 0) 
            printf("$%f\t\t$%f\t\t%u\t\t%f%%\t\t%f%%\t\t%f%%\n",
                            pricePoints[k].m_price,
                            pricePoints[k].m_cost,
                            pricePoints[k].m_noUnits,
                            pricePoints[k].m_unitDist,
                            pricePoints[k].m_revDist,
                            pricePoints[k].m_profitDist);
        else
            printf("$%f\t\t$%f\t\t0\t\t0.0\t\t0.0\t\t0.0\t\t\n",
                    a_prcPt[i].m_price,a_prcPt[i].m_cost);
    }
    printf("-----------------------------------------------------\n");
}
/* ------------------------------------------------------------------------- */
void printProductStats(const productStats* a_stats)
{
    if (!(a_stats)) {
        printf("CANNOT PRINT NULL PTR\n");
        return;
    }
    printf("---- SINGLE PRODUCT STATS ----\n");
    printf("Fixed Cost = $%f\n",a_stats->m_fixedCost);
    printf("Total Revenue = $%f\n",a_stats->m_totRevenue);
    printf("Total Cost = $%f\n",a_stats->m_totCost);
    printf("Profit = $%f\n",a_stats->m_profit);
    printf("Total no. of units = %u\n",a_stats->m_totUnits);
    printf("Profit per unit = $%f\n",a_stats->m_profitpUnit);
    printf("Profit Margin = %f%%\n",a_stats->m_profitMargin);
    printf("Proportion of variable cost = %f%%\n",
            a_stats->m_propUnitCost);
    printf("Cost per unit =$%f\n",a_stats->m_costpUnit);
    printf("--------------- SINGLE PRICE POINT STATS --------------\n");
    printf("Price point\t\tUnit Cost\t\tNo. of units sold\t\t");
    printf("Proportion of units sold\t\tProportion of revenue\t\t");
    printf("Proportion of profits\t\tComments\n");
    pricePoint* pricePoints= a_stats->m_pricePoints;
    for(unsigned k = 0; k < a_stats->m_noPrcPt; ++k) {
        printf("-----------------------------------------------------\n");
        printf("$%f\t\t$%f\t\t%u\t\t%f%%\t\t%f%%\t\t%f%%\n",
                        pricePoints[k].m_price,
                        pricePoints[k].m_cost,
                        pricePoints[k].m_noUnits,
                        pricePoints[k].m_unitDist,
                        pricePoints[k].m_revDist,
                        pricePoints[k].m_profitDist);
    }
    printf("-----------------------------------------------------\n");
}
/* ------------------------------------------------------------------------- */
void calculateProductStats(productStats* a_stats)
{ /* The idea is we'll first compute and store all the requisite values 
inside local variables and then transfer them at the end to the struct */
    if (!(a_stats) || !(a_stats->m_noPrcPt)) {
        printf("NOTHING TO PRINT\n");
        return;
    }
    unsigned noPrcPt = a_stats->m_noPrcPt;
    unsigned totalnoUnits = 0;
    pricePoint* pricePoints = a_stats->m_pricePoints;
    float totalRevenue = 0.0;
    float variableCost = 0.0;
    int noUnits[noPrcPt];
    float revenueDist[noPrcPt];
    for (unsigned i = 0; i < noPrcPt; ++i) {
        noUnits[i] = pricePoints[i].m_noUnits;
        totalnoUnits += noUnits[i];
        revenueDist[i] = noUnits[i] * pricePoints[i].m_price;
        totalRevenue += revenueDist[i];
        variableCost += noUnits[i] * pricePoints[i].m_cost;
    }
    float totalCost = a_stats->m_fixedCost + variableCost;
    float profit = totalRevenue - totalCost;
    float profitperUnit = profit / totalnoUnits;
    float profitMargin = 100.0 * (profit / totalCost);
    float unitCostProp = 100.0 * variableCost / totalCost;
    float costperUnit = totalCost / totalnoUnits;
    float unitDist[noPrcPt];
    float profitDist[noPrcPt];
    for (unsigned i = 0; i < noPrcPt; ++i) {
        unitDist[i]= 100.0 * noUnits[i] / totalnoUnits;
        profitDist[i] = 100.0 * (revenueDist[i] - costperUnit * 
            noUnits[i]) / profit;
        revenueDist[i] /=  totalRevenue / 100.0;
    }
    a_stats->m_totUnits = totalnoUnits;
    a_stats->m_totRevenue = totalRevenue;
    a_stats->m_totCost = totalCost;
    a_stats->m_profit = profit;
    a_stats->m_profitpUnit = profitperUnit;
    a_stats->m_profitMargin = profitMargin;
    a_stats->m_propUnitCost = unitCostProp;
    a_stats->m_costpUnit = costperUnit;
    for (unsigned i = 0; i < noPrcPt; ++i) {
        pricePoints[i].m_unitDist = unitDist[i];
        pricePoints[i].m_revDist = revenueDist[i];
        pricePoints[i].m_profitDist = profitDist[i];
    }
}
/* ------------------------------------------------------------------------- */
void removePricePoints(productStats* a_stats, 
    const unsigned a_noPrcPt, const pricePoint* a_prcPt)
{
    if (!(a_stats) || !(a_prcPt) || !(a_noPrcPt)) {
        printf("NOTHING TO REMOVE\n");
        return;
    }
    int indices[a_noPrcPt];
    findPricePoint(a_stats,a_noPrcPt,a_prcPt,indices);
    pricePoint* pricePoints = a_stats->m_pricePoints;
    for (unsigned i = 0; i < a_noPrcPt; ++i) {
        int j = indices[i];
        if (j >= 0) {
            for (unsigned k = j; k < a_stats->m_noPrcPt; ++k) {
                pricePoints[k].m_noUnits = 
                    pricePoints[k+1].m_noUnits; 
                pricePoints[k].m_price = pricePoints[k+1].m_price; 
                pricePoints[k].m_cost = pricePoints[k+1].m_cost; 
            }
            --a_stats->m_noPrcPt;
            calculateProductStats(a_stats);
        }
        else 
            printf("WARNING: Price point $%f, Unit cost $%f not found\n",
                a_prcPt[i].m_price,a_prcPt[i].m_cost);
    }
}
/* ------------------------------------------------------------------------- */
void extendProductStats(productStats* a_stats, 
    const unsigned a_noEntries)
{
    if (!(a_stats) || !(a_noEntries)) {
        printf("NOTHING TO EXTEND\n");
        return;
    }
    unsigned extender = (a_noEntries > INITIALIZER_PRODUCTSTATS) ? a_noEntries
    : INITIALIZER_PRODUCTSTATS;
    pricePoint* pricePoints = (pricePoint*) 
        realloc( a_stats->m_pricePoints,
        (a_stats->m_capPrcPt+extender) * sizeof(pricePoint) );
    if(!(pricePoints)) {
        printf("ARRAY REALLOCATION FAILED\n");
        exit(-1);
    }
    else {
        a_stats->m_capPrcPt += extender;
        a_stats->m_pricePoints = pricePoints;
    }
}
/* ------------------------------------------------------------------------- */
void updatePricePoints(productStats* a_stats,
    const unsigned a_noPrcPt,const pricePoint* a_prcPt)
{
    if (!(a_stats) || !(a_prcPt) || !(a_noPrcPt)) {
        printf("NOTHING TO UPDATE \n");
        return;
    }
    int indices[a_noPrcPt];
    findPricePoint(a_stats,a_noPrcPt,a_prcPt,indices);
    pricePoint*  pricePoints = a_stats->m_pricePoints;
    for (unsigned i = 0; i < a_noPrcPt; ++i) {
        int j = indices[i];
        if (j >= 0) { /* price point exists */
            if (a_prcPt[i].m_noUnits)  /* update if +ve quantity */
                pricePoints[j].m_noUnits = a_prcPt[i].m_noUnits;
            else /* remove if no. of units = 0 */
                removePricePoints(a_stats,1,&a_prcPt[i]);
        }
        else { /* new price point */
            if (a_stats->m_noPrcPt == a_stats->m_capPrcPt) { 
            /* extend if reqd */
                extendProductStats(a_stats,1);
                pricePoints = a_stats->m_pricePoints;
                /* must correct where pricePoints to now */
            }
            pricePoints[a_stats->m_noPrcPt].m_noUnits = 
                a_prcPt[i].m_noUnits;
            pricePoints[a_stats->m_noPrcPt].m_price = 
                a_prcPt[i].m_price;
            pricePoints[a_stats->m_noPrcPt].m_cost = 
                a_prcPt[i].m_cost;
            ++a_stats->m_noPrcPt;
        }
    }
    calculateProductStats(a_stats);
}
/* ------------------------------------------------------------------------- */
void updateProductStats(productStats* a_stats,
    const float a_fixedCost)
{
    if(!(a_stats)) {
        printf("NOTHING TO UPDATE IN PRODUCT STATS\n");
        return;
    }
    a_stats->m_fixedCost = a_fixedCost;
    calculateProductStats(a_stats);
}
/* ------------------------------------------------------------------------- */
void breakevenCalculator(const productStats* a_stats,
    const unsigned a_noPrcPt,const pricePoint* a_prcPt)
{
    printf("------------ BREAKEVEN CALCULATOR ------------\n");
    if (!(a_stats) || !(a_prcPt) || !(a_noPrcPt)) {
        printf("NOTHING TO BREAKEVEN \n");
            return;
        }
    printf("Price Point\t\tUnit Cost\t\tBreakeven no. of units ");
    printf("(0 implies can't breakeven)\n");
    for (int i = 0; i < a_noPrcPt; ++i) {
        float profitperUnit = a_prcPt[i].m_price - 
                                a_prcPt[i].m_cost;
        unsigned breakeven = 0;
        if (profitperUnit > 0) breakeven = a_stats->m_fixedCost / 
                                    profitperUnit + 1;
        /* +1 to make sure profit >= 0, also makes 0 error-value */
        printf("$%f\t\t$%f\t\t%u\n",a_prcPt[i].m_price,
            a_prcPt[i].m_cost,breakeven);
    }
    printf("-----------------------------------------------------\n");
}
