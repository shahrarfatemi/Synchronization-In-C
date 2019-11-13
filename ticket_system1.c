#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define PHONE_CALLS 245
#define PHONE_LINES 5
#define OPERATORS   3
#define NUMBER_OF_SEATS   240

static int connected = 0;
int arr1[PHONE_CALLS];
int arr2[PHONE_CALLS];
int k1 = 0, k2 = 0;
int next_id = 0,tickets_sold = 0;
sem_t lock;
sem_t operators;

void * phone_call(void * ptr)
{
    int id = next_id++;
    if(tickets_sold < NUMBER_OF_SEATS){
        if(connected<PHONE_LINES) {
            printf("Thread[%d] has available line, call ringing.\n", id);
        }
        else{
            printf("Thread[%d] is calling line, busy signal.\n", id);
        }

        while(connected>=PHONE_LINES) /*printf("Caller[%d] is waiting\n", id)*/;

        // Critical section
        sem_wait(&lock);
        connected++;
        sem_post(&lock);
        printf("Thread[%d] is waiting for an operator\n", id);

        sem_wait(&operators);
        if(tickets_sold < NUMBER_OF_SEATS){
            arr1[k1++] = id;
            printf("Thread[%d] is speaking to operator.\n", id);
            Sleep(3000);
            printf("Thread[%d] has bought a ticket.\n", id);
            tickets_sold++;
            arr2[k2++] = id;
        }
        else{
            printf("Thread[%d] has no available ticket.\n", id);
        }
        sem_post(&operators);
        printf("Thread[%d] has hung up.\n", id);

        sem_wait(&lock);
        connected--;
        sem_post(&lock);
    }
    else{
        printf("Thread[%d] has no available ticket.\n", id);
    }
}

int main()
{
    freopen("output1.txt", "w", stdout);
    pthread_t thread[PHONE_CALLS];

    sem_init(&lock, 0, 1);
    sem_init(&operators, 0, OPERATORS);
    int i;
    for(i=0; i<PHONE_CALLS; i++)
    {
        pthread_create(&thread[i], NULL, phone_call, (void *)i);
    }

    for(i=0; i<PHONE_CALLS; i++)
    {
        pthread_join(thread[i], NULL);
    }

    sem_destroy(&lock);
    sem_destroy(&operators);
    for(i=0; i<PHONE_CALLS; i++) printf("> %d\t%d\n", arr1[i], arr2[i]);
    return 0;
}
