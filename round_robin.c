#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct{
    int id;
    int burst_time;
    int org_burst;
    int arrival_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
}process;


typedef struct node{
    process * data;
    struct node * nextdata;
}node;


node * queue = NULL;


node * inqueue(process * data){
    node * newNode = (node*) malloc(sizeof(node));

    newNode->data = data;
    newNode->nextdata = NULL;

    if(queue == NULL){
        queue = newNode;
    }else{

        node * temp = queue;

        while(temp->nextdata != NULL){

            temp = temp->nextdata;
        }
        temp->nextdata = newNode;

    }

}

node * dequeue(){
    node * temp = queue;

    if(queue->nextdata != NULL){
        queue = queue->nextdata;
    }
    free(temp);
}


node * showQueue(){
    node * temp = queue;

    printf("InQueue:\n");
    while (temp->nextdata != NULL){
        printf("ID: %d org_burst: %d -> " , temp->data->id, temp->data->org_burst);
        temp = temp->nextdata;
    }
    printf("ID: %d org_burst: %d\n\n" , temp->data->id, temp->data->org_burst);
}


void display_process(process * arry_of_process ,int size){

    float avg_tt = 0.0;
    float avg_wt = 0.0;

    int sum_tt = 0;
    int sum_wt = 0;

    printf("Processes:\n");
    for (int i = 0; i < size; i++){
        printf("[PID]: %d \t [AT] %d \t [BT]: %d \t [CT]: %d \t [TT]: %d \t [WT]: %d\n", arry_of_process[i].id, arry_of_process[i].arrival_time, arry_of_process[i].burst_time, arry_of_process[i].completion_time, arry_of_process[i].turn_around_time, arry_of_process[i].waiting_time);
        sum_tt += arry_of_process[i].turn_around_time;
        sum_wt += arry_of_process[i].waiting_time;
    }

    avg_tt = (float) sum_tt / size;
    avg_wt = (float) sum_wt / size;

    printf("AVERAGE TURN AROUND TIME: %.2f\nAVERAGE WAITING TIME: %.2f\n", avg_tt, avg_wt);
}

void sort(process * arry_of_process ,int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size-1; j++){
            if(arry_of_process[j].arrival_time > arry_of_process[j+1].arrival_time){
                process temp = arry_of_process[j+1];
                arry_of_process[j+1] = arry_of_process[j];
                arry_of_process[j] = temp;
            }
        }
        
    }
}


void round_robin(process *arry_of_process, int quantum, int size) {
    int completed = 0;
    int time_count = 0;
    int time_quantum = quantum;
    
    printf("Gantt Chart:\n");
    while (completed != size){
        
        for (int i = 0; i < size; i++) {
            if (time_count == arry_of_process[i].arrival_time) {
                inqueue(&arry_of_process[i]);
            }
        }
    
        if(queue != NULL){
            printf("{ \t Time: %d \t }", time_count);
            printf("| \t [PID]: %d \t |\n", queue->data->id);
            if(queue->data->org_burst == 0){
                completed++;
                queue->data->completion_time = time_count;
                queue->data->turn_around_time = (queue->data->completion_time - queue->data->arrival_time) ;
                queue->data->waiting_time = (queue->data->completion_time - queue->data->burst_time) ;
                dequeue();
                time_quantum = quantum;
            }

            if(time_quantum != 0){
                queue->data->org_burst--;
                time_quantum--;
            }else{
                inqueue(queue->data);
                dequeue();
                queue->data->org_burst--;
                time_quantum = quantum-1;
            }

        }
        
        time_count++;

    }
    
}

int main(){

    int process_num = 0;

    int quantum = 0;

    printf("Enter the number of process: ");
    scanf("%d", &process_num);
    printf("Enter the number of quantum time: ");
    scanf("%d", &quantum);

    process arry_of_process[process_num];

    int size = sizeof(arry_of_process) / sizeof(arry_of_process[0]);
    
    for(int i = 0; i < size; i++){
        printf("Enter the burst time of process[%d] [BT]: ", i+1);
        arry_of_process[i].id = i+1;
        scanf("%d", &arry_of_process[i].burst_time);
        arry_of_process[i].org_burst = arry_of_process[i].burst_time;
        printf("Enter the arrival time of process[%d] [AT]: ", i+1);
        scanf("%d", &arry_of_process[i].arrival_time);
    }

    round_robin(arry_of_process, quantum, size);
    display_process(arry_of_process, size);

    return 0;
}
