/*
*  GPLv3 License.
*  A collection of basic statistics functions for use in business.
*/
#ifndef OC_BUSINESSSTATS_H
#define OC_BUSINESSSTATS_H
/* Data structures */
typedef struct pricePoint; 
/* Contains information about a single price point, defined by 
selling price and cost price*/
/* ------------------------------------------------------------------------- */
typedef struct { /* Contains business statistics for a single product
    defined by its fixed cost */
    unsigned m_capPrcPt; /* Capacity of price points that can be 
    stored */
    unsigned m_noPrcPt; /* Total no. of selling price points */
    unsigned m_totUnits; /* Total no. of units of product */
    float m_fixedCost;  /* Total cost defining this product */
    float m_totRevenue; /* Total revenue */
    float m_totCost; /* Total cost */
    float m_profit; /* Total profit */
    float m_profitpUnit; /* Profit per unit */
    float m_profitMargin; /* Profit/totalcost*/
    float m_propUnitCost; /* Proportion of variable cost in total cost */
    float m_costpUnit; /* Total cost per unit */
    pricePoint* m_pricePoints; /* Price points for product */
} productStats;
/* Functions */
void initializePricePoints(const unsigned a_noPrcPt,
    const float a_price[],const float a_cost[],
    const unsigned a_noUnits[],pricePoint** a_prcPt);
/* Function to initialize an array of price points
Inputs: a_noPrcPt = no. of price points existing in array
        a_price = array of selling price of each new price point
        a_cost = array of cost price of each new price point
        a_noUnits = array of no. of units sold at each new price point
        a_prcPt = array of price points
*/
void destroyPricePoints(pricePoint* a_prcPt);
/* Function to destroy array of pricePoints
Inputs: a_prcPt = array of pricePoints to free
*/
void initializeProductStats(productStats** a_stats,
    const float a_fixedCost);
/* Function to initialize ProductStats struct
*  Inputs: a_stats = pointer to struct containing all product stats
           a_fixedCost = fixed Cost of product 
*/
void destroyProductStats(productStats* a_stats);
/* Function to destroy ProductStats struct
Inputs: a_stats = pointer to struct containing all product stats
*/
void findPricePoint(const productStats* a_stats,
    const unsigned a_noPrcPt,
    const pricePoint* a_prcPt,int a_locs[]);
/* Function to find a given price point in ProductStats
 * Inputs:
 * a_stats = pointer to struct array containing all product stats
 * a_noPrcPt = no. of price points to find
 * a_prcPt = price points to find
 * a_locs = locations of price points in a_stats, -1 if not found
*/
void printPricePointStats(const productStats* a_stats,
    const unsigned a_noPrcPt, 
    const pricePoint* a_prcPt);
/* Function to print selected ProductStats
Inputs: a_stats = pointer to struct containing all product stats 
        a_noPcPt = no. of price points for which stat is requested
        a_prcPt = price points for which stat is requested 
*/
void printProductStats(const productStats* a_stats);
/* Function to print all ProductStats
Inputs: a_stats = pointer to struct containing all product stats
*/
void calculateProductStats(productStats* a_stats);
/*Function to calculate business stats about a single product
Inputs: a_stats = pointer to struct containing all product stats
*/
void removePricePoints(productStats* a_stats, 
    const unsigned a_noPrcPt, const pricePoint* a_prcPt);
/* Function to remove price points from product stats
Inputs: a_stats = product stats
        a_noPrcPt = no. of price points to remove
        a_prcPt = price points to remove
*/
void extendProductStats(productStats* a_stats,
    const unsigned a_entries);
/* Function to expand price points in product stats struct if out of space
Inputs: a_stats = product stats
        a_entries = no. of entries to extend by, effective only if
                    > INITIALIZER_PRODUCTSTATS
*/
void updatePricePoints(productStats* a_stats,
    const unsigned a_noPrcPt,const pricePoint* a_prcPt);
/*Function to update price points of a product
Inputs: a_stats = pointer to struct containing all product stats
        a_noPrcPt = no. of price points in array a_prcPt
        a_prcPt = array of pointers to pricePoints to be updated into a_stats 
*/
void updateProductStats(productStats* a_stats,
    const float a_fixedCost);
/*Function to update produce stats due to chang in fixed Cost
Inputs: a_stats = pointer to struct containing all product stats
        a_fixedCost = new fixed cost
*/
void breakevenCalculator(const productStats* a_stats,
    const unsigned a_noPrcPt,const pricePoint* a_prcPt);
/* Function to compute no. of units to be sold for breakeven for a
range of price points
Inputs: a_stats = pointer to struct containting product stats
        a_noPrcPt = no. of price points in array a_prcPt
        a_prcPt = array of pointers to structs containing price points
*/
#endif
