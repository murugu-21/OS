#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list{
    int data;
    struct list *next;
}list;

list *q;
int size = 0;

void insert(int value){
    list *temp = q, *l;

    //create list l and store value
    l = (list *) malloc(sizeof(list));
    l->data = value;
    l->next = NULL;

    //base case q is null, point q to l and terminate
    if(q == NULL){
        q = l;
        return;
    }

    //traverse list till last element and set last element next pointer to l
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = l;
}

int delete(){
    int t;
    list *temp = q;//meant for deallocating
    if(q == NULL){
        return -1;
    }
    t = q->data;
    q = q->next;
    free(temp); // deallocate memory
    return t;
}
void swap(void* a, void* b, size_t s){
    void* tmp = malloc(s);
    memcpy(tmp, a, s);
    memcpy(a, b, s);
    memcpy(b, tmp, s);
    free(tmp);
}
void findavgTime(char *processes[], int n, int bt[], int at[], int priority[], int quantum)
{
    int i, wt[n], rem_bt[n], time = 0;
    for (i = 0; i < n; i++)
        rem_bt[i] = bt[i];
        // Function to find waiting time of all processes
    insert(0);
    printf("\nGantt chart\n %d", time);
    while (q != NULL)
    {

        i = delete();
        // If burst time of a process is greater than 0
        // then only need to process further
        

        if (rem_bt[i] > quantum)
        {
            
            for (int j = i + 1; j < n; j++){
                if(at[j] >= time && at[j] < time + quantum){
                    insert(j);
                }
            }
            // Increase the value of t i.e. shows
            // how much time a process has been processed
                time += quantum;

            // Decrease the burst_time of current process
            // by quantum
            rem_bt[i] -= quantum;
            insert(i);
        }

        // If burst time is smaller than or equal to
        // quantum. Last cycle for this process
        else
        {
            
            for (int j = i + 1; j < n; j++){
                if(at[j] >= time && at[j] < time + rem_bt[i]){
                    insert(j);
                }
            }
            // Increase the value of t i.e. shows
            // how much time a process has been processed
            time += rem_bt[i];

            // Waiting time is current time minus time
            // used by this process
            wt[i] = time - bt[i] - at[i];

            // As the process gets fully executed
            // make its remaining burst time = 0
            rem_bt[i] = 0;
        }
        printf(" %s %d", processes[i], time);
    }
  
        // If all processes are done
    
    printf("\n");
        // Display processes along with all details
        printf("Processes\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time Completion Time");
    int total_wt = 0, total_tat = 0;
    for (int i = 0 ; i < n ; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + wt[i] + bt[i];
        int compl_time = wt[i] + at[i] + bt[i];
        printf("\n%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t  %d",processes[i],bt[i],at[i],wt[i],wt[
        i] + bt[i],compl_time);
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
    findavgTime(processes, n, burst_time, arrival_time, priority, 2);
    free(processes);
    free(burst_time);
    free(arrival_time);
    free(priority);
    return 0;
}