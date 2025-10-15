#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, smallest, count = 0, time;
    int p[20], bt[20], at[20], rt[20], finish[20];
    float avgwt = 0, avgtat = 0;
    
    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);

    printf("\nENTER PROCESS NUMBER, BURST TIME, AND ARRIVAL TIME:\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d %d", &p[i], &bt[i], &at[i]);
        rt[i] = bt[i];  // remaining time = burst time
    }

    int complete = 0, t = 0, minm = INT_MAX, shortest = 0, finish_time;
    int check = 0;

    while (complete != n) {
        // find process with minimum remaining time among arrived processes
        for (i = 0; i < n; i++) {
            if ((at[i] <= t) && (rt[i] < minm) && rt[i] > 0) {
                minm = rt[i];
                shortest = i;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        // reduce remaining time by 1 (since it's preemptive)
        rt[shortest]--;
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // if process finished
        if (rt[shortest] == 0) {
            complete++;
            check = 0;

            finish_time = t + 1;

            // calculate waiting time
            int wt = finish_time - bt[shortest] - at[shortest];
            if (wt < 0) wt = 0;

            avgwt += wt;
            avgtat += finish_time - at[shortest];
        }
        t++;
    }

    printf("\nAVERAGE WAITING TIME = %.2f", avgwt / n);
    printf("\nAVERAGE TURNAROUND TIME = %.2f\n", avgtat / n);

    return 0;
}
