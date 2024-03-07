#include <stdio.h>
#include <stdlib.h>

// easier storage of months to sort later
struct sales_month {
    char month[10];
    float sales;
};

// comparison function for qsort
int compareSales(const void *a, const void *b) {
    return (*(struct sales_month *)b).sales - (*(struct sales_month *)a).sales;
}

// average function for a range of months
float getAverage(struct sales_month *sales, int start, int end) {
    float total = 0;
    for (int i = start; i < end; i++) {
        total += sales[i].sales;
    }
    return total / (end - start);
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error: file not found\n");
        return 1;
    }

    char line[16]; // numbers shouldn't be longer than this
    char * months[12] = {
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
    };

    struct sales_month annual_sales[12];
    struct sales_month sorted_sales[12]; // duplicate for a sorted version
    // initializing the struct array and printing values directly
    printf("Monthly Sales Report for 2022:\n");
    printf("  Month     Sales\n");
    for (int i = 0; i < 12; i++) {
        fgets(line, sizeof(line), file);
        float sales = atof(line); // string to float conversion of each line
        annual_sales[i].sales = sales;
        sorted_sales[i].sales = sales;
        
        sprintf(annual_sales[i].month, "%s", months[i]);
        sprintf(sorted_sales[i].month, "%s", months[i]);
        // the %-9s formatting is to left justify the month (longest is 9 chars)
        printf("%-9s $%.2f\n", annual_sales[i].month, annual_sales[i].sales);
    }

    // sorting the sales for 1 sorted and 1 unsorted array
    qsort(sorted_sales, 12, sizeof(struct sales_month), compareSales);

    // summarizing the sales in min, max, and avg
    printf("\nSales Summary\n");
    printf("%16s  $%.2f    (%s)\n", "Minimum sales:", sorted_sales[11].sales, sorted_sales[11].month);
    printf("%16s  $%.2f    (%s)\n", "Maximum sales:", sorted_sales[0].sales, sorted_sales[0].month);
    printf("%16s  $%.2f\n", "Average sales:", getAverage(annual_sales, 0, 12));

    // creating the 6 month moving average
    printf("\nSix-Month Moving Average Report\n");
    for (int window = 0; window < 7; window++) {
        printf("%-9s - %-9s: $%.2f\n", months[window], months[window + 5], getAverage(annual_sales, window, window + 6));
    }

    // printing a highest-lowest sales report
    printf("\nSales Report (Highest to Lowest):\n");
    printf("  Month     Sales\n");
    for (int i = 0; i < 12; i++) {
        printf("%-9s $%.2f\n", sorted_sales[i].month, sorted_sales[i].sales);
    }

    return 0;
}
