/*fcfs scheduling simulation
19BCS027
MURUGAPPAN M*/
#include <stdio.h>
#include <stdlib.h>
void insertion_sort(int* pid, int* bt, int* at, int n){
    //insertion sort by arrival time
    int i, key, temp_burst, temp_proc, j;
    for (i = 1; i < n; i++)
    {
        key = at[i];
        temp_burst = bt[i];
        temp_proc = pid[i];
        j = i - 1;
 
        while (j >= 0 && at[j] > key) {
            at[j + 1] = at[j];
            bt[j + 1] = bt[j];
            pid[j + 1] = pid[j];
            j = j - 1;
        }
        at[j + 1] = key;
        bt[j + 1] = temp_burst;
        pid[j + 1] = temp_proc;
    }
}

void fcfs(int* pid, int* bt, int* at, int n){
    int i, wt[n], time = at[0];
    printf("Gantt chart\n");
    printf("%d ", at[0]);
    for (i = 0; i < n; i++)
    {
        if (at[i] > time)
        {
            time = at[i];
            printf("%d ", time);
        }
        wt[i] = time - at[i];
        time += bt[i];
        printf("P%d %d ", pid[i], time);
    }
    printf("\npid\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time Completion Time");
    int total_wt = 0, total_tat = 0, c[n];
    for (i = 0; i < n; i++){
        total_wt += wt[i];
        total_tat += wt[i] + bt[i];
        c[i] = at[i] + wt[i] + bt[i];
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t  %d", pid[i], bt[i], at[i], wt[i], wt[i] + bt[i], c[i]);
    }
    printf("\nAverage Waiting Time(AWT) = %f", (float)total_wt / n);
    printf("\nAverage Turn Around Time(ATAT) = %f", (float)total_tat / n);
}

int main(){
    int n, *pid, *bt, *at, i;
    freopen("fcfs.in", "r", stdin);
    printf("Enter number of processes: ");
    scanf("%d", &n);
    pid = (int *)malloc(n * sizeof(int));
    bt = (int *)malloc(n * sizeof(int));
    at = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++){
        printf("Enter pid: ");
        scanf("%d", pid + i);
        printf("Enter burst time of %d: ", pid[i]);
        scanf("%d", bt + i);
        printf("Enter arrival time of %d: ", pid[i]);
        scanf("%d", at + i);
    }
    insertion_sort(pid, bt, at, n);
    fcfs(pid, bt, at, n);
    return 0;
}