#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(void* a, void* b, size_t s){
    void* tmp = malloc(s);
    memcpy(tmp, a, s);
    memcpy(a, b, s);
    memcpy(b, tmp, s);
    free(tmp);
}

void findWaitingTime(char* processes[], int n, int bt[], int wt[], int at[])
{
    int service_time[n];
    service_time[0] = 0;
    wt[0] = 0;
    // calculating waiting time
    for (int i = 1; i < n ; i++)
    {
        // Add burst time of previous processes
        service_time[i] = service_time[i-1] + bt[i-1];
        // Find waiting time for current process =
        // sum - at[i]
        
        wt[i] = service_time[i] - at[i];
        // If waiting time for a process is in negative
        // that means it is already in the ready queue
        // before CPU becomes idle so its waiting time is 0
        if(wt[i] < 0)
            wt[i] = 0;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(char* processes[], int n, int bt[], int wt[], int tat[])
{
// Calculating turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}
// Function to calculate average waiting and turn-around
// times.
void findavgTime(char *processes[], int n, int bt[], int at[])
{
    int wt[n], tat[n];
    // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt, at);
    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);
    printf("\nGantt chart\n ");
    for (int i = 0; i < n; i++){
        printf("%s ", processes[i]);
    }
    printf("\n%d  ", at[0]+wt[0]);
    for (int i = 0; i < n; i++)
    {
        printf("%d  ", at[i]+wt[i]+bt[i]);
    }
    printf("\n");
        // Display processes along with all details
        printf("Processes\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time Completion Time");
    int total_wt = 0, total_tat = 0;
    for (int i = 0 ; i < n ; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        int compl_time = tat[i] + at[i];
        printf("\n%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t  %d",processes[i],bt[i],at[i],wt[i],tat[
        i],compl_time);
    }
    printf("\nAverage Waiting Time = %.2f",(float)(total_wt)/n);
    printf("\nAverage Turn Around Time = %.2f",(float)
    (total_tat)/n);
}

// Driver code
int main()
{
    // Process id's
    int i, j, key, temp_burst, n, *burst_time, *arrival_time;
    char **processes, *temp_proc;
    freopen("fcfs.in", "r", stdin);
    //printf("\nEnter no of processes: ");
    scanf("%d", &n);
    processes = (char **)malloc(n * sizeof(char *));
    burst_time = (int *)malloc(n * sizeof(int));
    arrival_time = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        //printf("\nEnter process name: ");
        processes[i] = (char *)malloc(10 * sizeof(char));
        scanf("%s", processes[i]);
        //printf("\nEnter burst time: ");
        scanf("%d", burst_time + i);
        //printf("\nEnter arrival time: ");
        scanf("%d", arrival_time + i);
    }

    //insertion sort by arrival time
    for (i = 1; i < n; i++) {
        key = arrival_time[i];
        temp_burst = burst_time[i];
        temp_proc = processes[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arrival_time[j] > key) {
            arrival_time[j + 1] = arrival_time[j];
            burst_time[j + 1] = burst_time[j];
            processes[j + 1] = processes[j];
            j = j - 1;
        }
        arrival_time[j + 1] = key;
        burst_time[j + 1] = temp_burst;
        processes[j + 1] = temp_proc;
    }
    //int n = sizeof processes / sizeof processes[0];
    //freopen("fcfs.out", "w", stdout);
    findavgTime(processes, n, burst_time, arrival_time);
    free(processes);
    free(burst_time);
    free(arrival_time);
    return 0;
}