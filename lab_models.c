/*fcfs scheduling simulation
19BCS027
MURUGAPPAN M*/
#include <stdio.h>
#include <stdlib.h>
void insertion_sort(int* process, int* bt, int* at, int n){
    //insertion sort by arrival time
    int i, key, temp_burst, temp_proc, j;
    for (i = 1; i < n; i++)
    {
        key = at[i];
        temp_burst = bt[i];
        temp_proc = process[i];
        j = i - 1;
 
        while (j >= 0 && at[j] > key) {
            at[j + 1] = at[j];
            bt[j + 1] = bt[j];
            process[j + 1] = process[j];
            j = j - 1;
        }
        at[j + 1] = key;
        bt[j + 1] = temp_burst;
        process[j + 1] = temp_proc;
    }
}

void fcfs(int* process, int* bt, int* at, int n){
    int i, wt[n], time = at[0];
    printf("Gantt chart\n");
    printf("%d ", at[0]);
    for (i = 0; i < n; i++)
    {
        if (at[i] > time)
        {
            time = at[i];
        }
        wt[i] = time - at[i];
        time += bt[i];
        printf("P%d %d ", process[i], time);
    }
    printf("\nProcesses\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time Completion Time");
    int total_wt = 0, total_tat = 0, c[n];
    for (i = 0; i < n; i++){
        total_wt += wt[i];
        total_tat += wt[i] + bt[i];
        c[i] = at[i] + wt[i] + bt[i];
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t  %d", process[i], bt[i], at[i], wt[i], wt[i] + bt[i], c[i]);
    }
}

int main(){
    int n, *process, *bt, *at, i;
    freopen("fcfs.in", "r", stdin);
    scanf("%d", &n);
    process = (int *)malloc(n * sizeof(int));
    bt = (int *)malloc(n * sizeof(int));
    at = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++){
        scanf("%d", process + i);
        scanf("%d", bt + i);
        scanf("%d", at + i);
    }
    insertion_sort(process, bt, at, n);
    fcfs(process, bt, at, n);
    return 0;
}