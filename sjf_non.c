#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, j;
    int bt[20], at[20], wt[20], tat[20], finish[20];
    int completed[20] = {0};
    int t = 0, completedCount = 0;
    float avgwt = 0, avgtat = 0;
    int gantt[100], gcount = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("\nEnter Burst Time and Arrival Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d", &bt[i], &at[i]);
    }

    // SJF Non-Preemptive Scheduling
    while (completedCount != n) {
        int shortest = -1;
        int min_bt = INT_MAX;

        // Find process with minimum BT among arrived and not completed
        for (i = 0; i < n; i++) {
            if (at[i] <= t && completed[i] == 0 && bt[i] < min_bt) {
                min_bt = bt[i];
                shortest = i;
            }
        }

        // If no process arrived yet
        if (shortest == -1) {
            t++;
            continue;
        }

        gantt[gcount++] = shortest + 1; // Record for Gantt chart
        t += bt[shortest];              // Move time forward
        finish[shortest] = t;
        tat[shortest] = finish[shortest] - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];
        if (wt[shortest] < 0)
            wt[shortest] = 0;
        completed[shortest] = 1;
        completedCount++;
    }

    printf("\nProcess\tBT\tAT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, bt[i], at[i], wt[i], tat[i]);
        avgwt += wt[i];
        avgtat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", avgwt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat / n);

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    for (i = 0; i < gcount; i++) {
        printf(" P%d |", gantt[i]);
    }
    printf("\n");

    return 0;
}
