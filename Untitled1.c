#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
int a, b;
sem_t sem;
static int call = 3;
static int line = 5;
static int current_call = 0;
static int current_line = 0;
void ScanNumbers(void *ptr){
    for (;;){
        printf("%s", (char *)ptr);
        scanf("%d %d", &a, &b);
        sem_post(&sem);
        usleep(100 * 1000);
    }
}
void SumAndPrint(void *ptr){
    for (;;){
        sem_wait(&sem);
        printf("%s %d\n", (char *)ptr, a + b);
    }
}

void CallAndPrint(void *ptr){
    //printf("Thread: %d\n",(int *)ptr);
    while(current_line < line){
        current_line++;
        callThem(ptr);
        Sleep(1000);
        current_line--;
        return;
    }
    printf("Thread[%d]: Go away\n",(int *)ptr);
}

void callThem(void * ptr){
    if(current_call >= call){
        printf("Thread[%d]: Waiting for the operator\n",(int *)ptr);
    }
    while(current_call >= call){}
    current_call++;
    //printf("Thread: %d\n",(int *)ptr);
    printf("Thread[%d]: Calling\n",(int *)ptr);
    printf("Thread[%d]: Ordering in progress\n",(int *)ptr);
    Sleep(3000);
    current_call--;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    pthread_t thread5;
    pthread_t thread6;
    pthread_t thread7;
    pthread_t thread8;
    pthread_t thread9;
    char *Msg1 = "Enter Number Two No\n";
    char *Msg2 = "sum = ";
    int *t1 = 1;
    int *t2 = 2;
    int *t3 = 3;
    int *t4 = 4;
    int *t5 = 5;
    int *t6 = 6;
    int *t7 = 7;
    int *t8 = 8;
    int *t9 = 9;
    /*
    int sem_init(
        sem_t *sem          // pointer to semaphore variable    ,
        int pshared         // If = 0: can be used in threads only, else in process,
        unsigned int value  // initial value of the semaphore counter
    );
    return value 0 on successful & -1 on failure
    */
    sem_init(&sem, 0, 0);   // Can also use `sem = sem_open( "SemaphoreName", O_CREAT, 0777, 0);`
    pthread_create(&thread1, NULL, (void *)CallAndPrint, (void *)t1);
    pthread_create(&thread2, NULL, (void *)CallAndPrint, (void *)t2);
    pthread_create(&thread3, NULL, (void *)CallAndPrint, (void *)t3);
    pthread_create(&thread4, NULL, (void *)CallAndPrint, (void *)t4);
    pthread_create(&thread5, NULL, (void *)CallAndPrint, (void *)t5);
    pthread_create(&thread6, NULL, (void *)CallAndPrint, (void *)t6);
    pthread_create(&thread7, NULL, (void *)CallAndPrint, (void *)t7);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);
    pthread_join(thread7, NULL);
    Sleep(4000);
    pthread_create(&thread8, NULL, (void *)CallAndPrint, (void *)t8);
    pthread_create(&thread9, NULL, (void *)CallAndPrint, (void *)t9);
    pthread_join(thread8, NULL);
    pthread_join(thread9, NULL);
    Sleep(4000);
    printf("Wait For Both Thread Finished\n");
    sem_destroy(&sem);      // Can also use `sem_unlink( "SemaphoreName");`
    return 0;
}
