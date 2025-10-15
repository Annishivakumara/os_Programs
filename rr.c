#include <stdio.h>

int main() {
    int n, bt[20], at[20], rt[20], wt[20], tat[20];
    int tq, t = 0, remain, flag = 0;
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    remain = n;

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    printf("Enter burst time and arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d", &bt[i], &at[i]);
        rt[i] = bt[i];
    }

    printf("\n\t\tGANTT CHART\n");
    printf("--------------------------------------------------\n");

    int i = 0;
    while (remain != 0) {
        if (rt[i] > 0 && at[i] <= t) {
            if (rt[i] > tq) {
                printf("| P%d ", i + 1);
                t += tq;
                rt[i] -= tq;
            } else {
                printf("| P%d ", i + 1);
                t += rt[i];
                wt[i] = t - at[i] - bt[i];
                tat[i] = t - at[i];
                rt[i] = 0;
                remain--;
            }
        }
        i = (i + 1) % n;
        flag = 0;
        for (int j = 0; j < n; j++)
            if (rt[j] > 0 && at[j] <= t)
                flag = 1;
        if (!flag && remain != 0) t++;
    }

    printf("|\n--------------------------------------------------\n");

    printf("\nPROCESS\tBT\tAT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        if (wt[i] < 0) wt[i] = 0;
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, bt[i], at[i], wt[i], tat[i]);
        avgwt += wt[i];
        avgtat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", avgwt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat / n);

    return 0;
}
