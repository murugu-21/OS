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
void findavgTime(char *processes[], int n, int bt[], int at[], int priority[])
{
    int wt[n], tat[n], ct[n];
    // Function to find waiting time of all processes
    ct[0]=bt[0]+at[0];
    tat[0]=ct[0]-at[0];
    wt[0]=tat[0]-bt[0];
    int temp,value;
    
    for(int i=1;i<n;i++)
    {
        temp=ct[i-1];
        int threshold=priority[i];
        for(int j=i;j<n;j++)
        {
            if(temp>=at[j] && threshold >= priority[j])
            {
                value=j;
            }
        }
        ct[value]=temp+bt[value];
        tat[value]=ct[value]-at[value];
        wt[value]=tat[value]-bt[value];

                int temp=at[value];
                at[value]=at[i];
                at[i]=temp;

                int temp1=bt[value];
                bt[value]=bt[i];
                bt[i]=temp1;

                char* temp2=processes[value];
                processes[value]=processes[i];
                processes[i]=temp2;

                int temp3=ct[value];
                ct[value]=ct[i];
                ct[i]=temp3;

                int temp4=tat[value];
                tat[value]=tat[i];
                tat[i]=temp4;

                int temp5=wt[value];
                wt[value]=wt[i];
                wt[i]=temp5;
}
    printf("\nGantt chart\n ");
    for (int i = 0; i < n; i++){
        printf("%s ", processes[i]);
    }
    printf("\n%d  ", at[0]+wt[0]);
    for (int i = 0; i < n; i++)
    {
        printf("%d  ", ct[i]);
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
    int i, j, key, temp_burst, n, *burst_time, *arrival_time, *priority, temp_prior;
    char **processes, *temp_proc;
    freopen("non-premptive.in", "r", stdin);
    //printf("\nEnter no of processes: ");
    scanf("%d", &n);
    processes = (char **)malloc(n * sizeof(char *));
    burst_time = (int *)malloc(n * sizeof(int));
    arrival_time = (int *)malloc(n * sizeof(int));
    priority = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        //printf("\nEnter process name: ");
        processes[i] = (char *)malloc(10 * sizeof(char));
        scanf("%s", processes[i]);
        //printf("\nEnter burst time: ");
        scanf("%d", burst_time + i);
        //printf("\nEnter arrival time: ");
        scanf("%d", arrival_time + i);
        scanf("%d", priority + i);
    }

    //insertion sort by arrival time
    for (i = 1; i < n; i++) {
        key = arrival_time[i];
        temp_burst = burst_time[i];
        temp_proc = processes[i];
        temp_prior = priority[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arrival_time[j] > key) {
            arrival_time[j + 1] = arrival_time[j];
            burst_time[j + 1] = burst_time[j];
            processes[j + 1] = processes[j];
            priority[j + 1] = priority[j];
            j = j - 1;
        }
        arrival_time[j + 1] = key;
        burst_time[j + 1] = temp_burst;
        processes[j + 1] = temp_proc;
        priority[j + 1] = temp_prior;
    }
    //int n = sizeof processes / sizeof processes[0];
    //freopen("fcfs.out", "w", stdout);
    findavgTime(processes, n, burst_time, arrival_time, priority);
    free(processes);
    free(burst_time);
    free(arrival_time);
    free(priority);
    return 0;
}