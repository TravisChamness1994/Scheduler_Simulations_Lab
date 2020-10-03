#include "processQueue.h"

// the process table to hold all processes
PROCESS *processTable;
int processTableSize = 0;
int processTableCapacity;

// doubly-linked list to hold the ready queue
PROCESS *readyQueueHead = NULL;
PROCESS *readyQueueTail = NULL;

/***
 * constructor of the process table
 */
void createProcessTable(int capacity)
{
    processTable = (PROCESS *) malloc(capacity * sizeof(PROCESS));
    processTableCapacity = capacity;
}

/***
 * constructor of the ready queue
 */
void createReadyQueue(int capacity)
{
    readyQueueHead = NULL;
    readyQueueTail = NULL;
}

/***
 * adds a process and expands the table if necessary
 */
 //Check for table size : If it is == 0, then the new head and tail are the new process.
 //Else tack new process onto tail and sets next to NULL.
 //NOTE: &process works well as a reference because the struct itself is a pointer to information, it is just not a "Pointer type".
void addProcessToTable(PROCESS process)
{
    if (processTableSize >= processTableCapacity) //if array too small
    {
        processTableCapacity *= 2; //double capacity
        processTable = (PROCESS *) realloc(processTable, processTableCapacity * sizeof(PROCESS));
    }

// TODO: complete - Work

    processTable[processTableSize] = process;
    processTableSize++;
}

/***
 * display the processes table
 */
void displayProcessTable()
{
    printf("PROCESSES:\n\nName    \tEntry\tBurst\n");
    for (int i = 0; i < processTableSize; i++)
    {
        printf("%-8s\t%3d   \t%3d   \n", processTable[i].name, processTable[i].entryTime, processTable[i].burstTime);
    }
    printf("\n");
}

/***
 * determines if any processes in the process table still need to execute
 */
 //For loop : Short circuit if process determines to be incomplete. Just need one positive result.
bool processesLeftToExecute()
{
// TODO: implement - Work
    bool process_incomplete = false;
    for (int i = 0; !process_incomplete && i < processTableSize; ++i) {
        if(processTable[i].burstTime != 0)
            process_incomplete = true;
    }
    return process_incomplete; //return 0 if all processes are complete
}

/***
 * adds any processes that arrive at the current time to ready queue
 */
 //Look for an oncoming process at time, if there is a new process, point to that new process.
 //add that process to the readyQueueHead
void addArrivingProcessesToReadyQueue(int time)
{
// TODO: implement - Work
    bool nextProcess = false;
//    PROCESS *newProcess = (PROCESS*)malloc(sizeof(PROCESS));
    PROCESS *newProcess = (PROCESS*)malloc(sizeof(PROCESS));
     for (int i = 0; !nextProcess && i < processTableSize; ++i) {
        if(processTable[i].entryTime == time) {
            *newProcess = processTable[i];
            nextProcess = true;
        }
    }

    if(nextProcess)
    {
        if (readyQueueHead == NULL) {
            readyQueueHead = newProcess;
            readyQueueTail = newProcess;

//            readyQueueHead = newProcess;
//            readyQueueTail = newProcess;
            newProcess->next = NULL;
            newProcess->previous = NULL;
        } else {
            newProcess->previous = readyQueueTail;
            readyQueueTail->next = newProcess;
            readyQueueTail = newProcess;
            newProcess->next = NULL;
        }
    }
}

/***
 * adds a process to the ready queue and expands it if necessary
 */
void addProcessToReadyQueue(PROCESS *process)
{
    if(readyQueueHead == NULL)
    {
        *readyQueueHead = *process;
        *readyQueueTail = *process;
    }
    else
    {
        process->previous = readyQueueTail;
        readyQueueTail->next = process;
        readyQueueTail = process;
        process->next = NULL;
    }
// TODO: implement - Work
}

/***
 * removes a process from the ready queue and fills the "hole"
 */
void removeProcessFromReadyQueue(PROCESS *process)
{
// TODO: implement
    PROCESS *curr = readyQueueHead;
    if(readyQueueHead->next == NULL)
    {
        readyQueueHead == NULL;
        readyQueueTail ==NULL;
    }
    else {
        readyQueueHead = readyQueueHead->next;
        }

    free(curr);
}

/***
 * fetches the first process from the ready queue
 */
 //Set a current to the ready queue head
 //increment ready queue head to next.
PROCESS *fetchFirstProcessFromReadyQueue()
{
// TODO: implement - Work
    PROCESS *curr = readyQueueHead;
    if(readyQueueHead != NULL)
    {
        readyQueueHead = readyQueueHead->next;
    }
    return curr;
}

/***
 * finds the shortest job in the ready queue
 */
 //Does not guarantee a non NULL process return. Alternatives are not any better. No matter what a null will have to return.
PROCESS *findShortestProcessInReadyQueue()
{
// TODO: implement - Work
    PROCESS *shortest_job = readyQueueHead;
    PROCESS *curr = readyQueueHead->next;
    while(curr != NULL)
    {
        if(shortest_job->burstTime > curr->burstTime)
            shortest_job = curr;
    }
    return shortest_job;
}

/***
 * displays the contents of the ready queue
 */
void displayQueue()
{
    printf("QUEUE: ");

    if (readyQueueHead == NULL)
        printf("<empty>");
    else
    {
        for (PROCESS *curr = readyQueueHead; curr != NULL; curr = curr->next)
        {
            printf("%s(%d) ", curr->name, curr->burstTime);
        }
    }
}

/***
 * calculates and prints the average wait time using information in the process table
 */
void printAverageWaitTime()
{
    int i = 0;
    double sum = 0;
    for (i = 0; i < processTableSize; i++)
    {
        sum = sum + processTable[i].waitTime;
        printf("Process %s Wait Time: %.2lf\n", processTable[i].name, (double) processTable[i].waitTime);
    }
    printf("Average Wait Time: %.2lf\n", (sum / (double) processTableSize));
}

/***
 * clean up the process table
 */
void cleanUp()
{
    for (int i = 0; i < processTableSize; ++i) {
        free(processTable[i].next);
        free(processTable[i].previous);
    }
    free(processTable);
// TODO: implement - work
}





