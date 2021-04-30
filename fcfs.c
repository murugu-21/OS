#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Function to find the waiting time for all
// processes
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
        printf("Processes\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\tCompletion Time");
    int total_wt = 0, total_tat = 0;
    for (int i = 0 ; i < n ; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        int compl_time = tat[i] + at[i];
        printf("\n%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d",processes[i],bt[i],at[i],wt[i],tat[
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
    int i, j, min_idx, n, *burst_time, *arrival_time;
    char **processes;
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

    //selection sort by arrival time
    for (i = 0; i < n-1; i++) 
    { 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
            if (arrival_time[j] < arrival_time[min_idx]) 
                min_idx = j; 
  
        // Swap the found minimum element with the first element 
        swap(&arrival_time[min_idx], &arrival_time[i], sizeof(arrival_time[i]));
        swap(&burst_time[min_idx], &burst_time[i], sizeof(burst_time[i]));
        swap(&processes[min_idx], &processes[i], sizeof(processes[i]));
    }
    //int n = sizeof processes / sizeof processes[0];
    //freopen("fcfs.out", "w", stdout);
    findavgTime(processes, n, burst_time, arrival_time);
    free(processes);
    free(burst_time);
    free(arrival_time);
    return 0;
}