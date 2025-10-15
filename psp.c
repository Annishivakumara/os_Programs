#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    int bt[20], at[20], pr[20], rt[20], wt[20], tat[20], finish[20];
    int complete = 0, t = 0, shortest = 0, min_priority = INT_MAX;
    int gantt[100], gcount = 0;
    float avgwt = 0, avgtat = 0;

    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);

    printf("\nENTER BURST TIME, ARRIVAL TIME AND PRIORITY FOR EACH PROCESS:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d %d", &bt[i], &at[i], &pr[i]);
        rt[i] = bt[i];  // remaining time
    }

    // Simulate CPU scheduling
    while (complete != n) {
        int check = 0, min_priority = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (at[i] <= t && rt[i] > 0 && pr[i] < min_priority) {
                min_priority = pr[i];
                shortest = i;
                check = 1;
            }
        }

        if (!check) {
            t++;
            continue;
        }

        // Record the process executed at this time
        gantt[gcount++] = shortest + 1;

        rt[shortest]--;
        if (rt[shortest] == 0) {
            complete++;
            finish[shortest] = t + 1;
            wt[shortest] = finish[shortest] - bt[shortest] - at[shortest];
            if (wt[shortest] < 0) wt[shortest] = 0;
            tat[shortest] = finish[shortest] - at[shortest];
        }
        t++;
    }

    // Calculate averages
    for (int i = 0; i < n; i++) {
        avgwt += wt[i];
        avgtat += tat[i];
    }
    avgwt /= n;
    avgtat /= n;

    // Print Results
    printf("\nPREEMPTIVE PRIORITY SCHEDULING:\n");
    printf("\nPROCESS\tBT\tAT\tPR\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, bt[i], at[i], pr[i], wt[i], tat[i]);

    printf("\nAVERAGE WAITING TIME = %.2f", avgwt);
    printf("\nAVERAGE TURNAROUND TIME = %.2f\n", avgtat);

    // Print Gantt Chart
    printf("\n\nGANTT CHART:\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < gcount; i++)
        printf("| P%d ", gantt[i]);
    printf("|\n------------------------------------------------\n");
    for (int i = 0; i <= gcount; i++)
        printf("%d\t", i);
    printf("\n");

    return 0;
}
