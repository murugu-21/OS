#include <stdio.h>

int n, tail = -1,frame, no_page_fault = 0;
int queue[100], arr[100];

/* int arr[] = {1,2,3,4,5,3,4,1,6,7,8,7,8,9,7,8,9,5}, queue[100];
int n = sizeof arr / sizeof arr[0], head = -1, tail = -1, frame = 4, no_page_fault = 0; */

int checkPageFault(int ele){
    int fl = 1;
    for(int i=0;i<frame;i++){
        if(ele == queue[i]){
            fl = 0;
            break; 
        }
    }
    if(!fl) {
        
        return 0;
    }
    no_page_fault++;
    return 1;
}

void printqueue(){
    int i, j;
    printf(" ");
    for(i=0; i<frame; i++) {
        for(j=0; j<3; j++) printf("-");
        printf(" ");
    }
    printf("\n|");
    // middle position
    for(i=0; i<frame; i++) {
        for(j=0; j<1; j++) printf(" ");
        printf("%d", queue[i]);
        for(j=0; j<1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // bottom bar
    for(i=0; i<frame; i++) {
        for(j=0; j<3; j++) printf("-");
        printf(" ");
    }
    
}

void calc(){
    for(int i=0;i<n;i++){
        
        if(checkPageFault(arr[i])){
            tail = ++tail % frame;
            queue[tail] = arr[i];
            //printf("%d", arr[i]);
            printqueue();
            printf("PF");
            printf("\n");
            continue;
        }
        printqueue();
        printf("NPF");
        printf("\n");
    }
}

void main(){
    
    printf("enter the size of the frame: ");
    scanf("%d", &frame);
    printf("enter the size of the reference:");
    scanf("%d", &n);

    printf("enter the references: ");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    for(int i=0;i<frame;i++) queue[i]=0;

    calc();
    printf("\nNumber of Page Fault = %d",no_page_fault);
}
