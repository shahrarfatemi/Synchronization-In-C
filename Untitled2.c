#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
int a, b;
sem_t sem;
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
int main()
{
    pthread_t thread1;
    pthread_t thread2;
    char *Msg1 = "Enter Number Two No\n";
    char *Msg2 = "sum = ";
    /*
    int sem_init(
        sem_t *sem          // pointer to semaphore variable    ,
        int pshared         // If = 0: can be used in threads only, else in process,
        unsigned int value  // initial value of the semaphore counter
    );
    return value 0 on successful & -1 on failure
    */
    sem_init(&sem, 0, 3);   // Can also use `sem = sem_open( "SemaphoreName", O_CREAT, 0777, 0);`
    pthread_create(&thread1, NULL, (void *)ScanNumbers, (void *)Msg1);
    pthread_create(&thread2, NULL, (void *)SumAndPrint, (void *)Msg2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Wait For Both Thread Finished\n");
    sem_destroy(&sem);      // Can also use `sem_unlink( "SemaphoreName");`
    return 0;
}
