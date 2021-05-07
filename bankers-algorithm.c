#include <stdio.h>
#include <stdlib.h>
int main()
{
    // P0, P1, P2, P3, P4 are the Process names here
  
    int n, m, i, j, k;
    freopen("bankers.in", "r", stdin);
    printf("Enter no of processes: ");
    scanf("%d", &n);
    printf("Enter no of resources: ");
    scanf("%d", &m);
    printf("Enter allocation matrix\n");
    int **alloc = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++){
        alloc[i] = (int *)malloc(m * sizeof(int));
        for (j = 0; j < m; j++){
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter max request matrix\n");
    int **max = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++){
        max[i] = (int *)malloc(m * sizeof(int));
        for (j = 0; j < m; j++){
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter available array\n");
    int *avail = (int *)malloc(m * sizeof(int)); // Available Resources
    for (i = 0; i < m; i++)
        scanf("%d", avail + i);
    
    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int *work = (int *)malloc(m * sizeof(int));
    for (i = 0; i < m; i++)
        work[i] = avail[i];
    int finish[n], ans[n], ind = 0, y;
    for (k = 0; k < n; k++) {
        finish[k] = 0;
    }
    while (ind < n)
    {
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
  
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]){
                        flag = 1;
                         break;
                    }
                }
  
                if (!flag) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        work[y] += alloc[i][y];
                    finish[i] = 1;
                }
            }
        }
    }

    printf("Following is the SAFE Sequence\n");
    for (i = 0; i < n - 1; i++)
        printf(" P%d ->", ans[i]);
    printf(" P%d", ans[n - 1]);
    free(alloc);
    free(max);
    free(avail);
    free(work);
    return (0);
}