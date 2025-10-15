#include <stdio.h>

int main() {
    int n, bt[10], at[10], wt[10], tat[10], i, ft[10];
    float awt = 0, att = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst times:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &bt[i]);
    }

    printf("Enter arrival times:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &at[i]);
    }

    // Calculate waiting times and finish times
    wt[0] = 0;
    ft[0] = bt[0];  // Finish time of first process
    for(i = 1; i < n; i++) {
        wt[i] = ft[i-1] - at[i];
        if(wt[i] < 0) wt[i] = 0;   // Handle idle time
        ft[i] = wt[i] + bt[i] + at[i];
    }

    for(i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    for(i = 0; i < n; i++) {
        awt += wt[i];
        att += tat[i];
    }
    awt /= n;
    att /= n;

    // Print Gantt Chart
    printf("\nGANTT CHART\n");
    for(i = 0; i < n; i++)
        printf("|  P%d  ", i+1);
    printf("|\n");

    for(i = 0; i < n; i++)
        printf("%d\t", (i == 0 ? 0 : ft[i-1]));
    printf("%d\n", ft[n-1]);

    // Print process details
    printf("\nProcess\tBT\tAT\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, bt[i], at[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time: %.2f", awt);
    printf("\nAverage Turnaround Time: %.2f\n", att);

    return 0;
}
