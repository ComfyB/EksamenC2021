#include "source.h"

int main(void)
{

    pthread_mutex_init(&lock_data, NULL); //initialize mutex lock, makes sure that two threads dont access same shared memory at the same time.
    pthread_cond_init(&read_data, NULL);  //and two condidtions which are used to pause the main and workthread read_data will be used for signal from main to workthread for it to start writing
    pthread_cond_init(&write_data, NULL); //write_data will be used when the data is finised writing to file and start main again.

    Buffer *structBuffer = malloc(sizeof(Buffer)); //malloc buffer which is shared in a struct.
    if (structBuffer == NULL)
    {
        printf("error allocation memory for structBuffer");
        return (1);
    }
    memset(structBuffer, 0, sizeof(Buffer));

    pthread_t thread_1;

    pthread_create(&thread_1, NULL, workThread, structBuffer);
    while (strncmp(structBuffer->input, "quit", 4))
    {
        // printf("main_threadId: %ld\n",syscall(SYS_gettid)); //to see which thread id we're in useful for debugging

        if (fgets(structBuffer->input, 10, stdin))
            ;                                       //take input
        pthread_cond_signal(&read_data);            //sender signal for å kjøre while loopen en gang
        pthread_cond_wait(&write_data, &lock_data); //kjører whileloopeb når den får signal
    }

    pthread_cond_signal(&read_data); //sender signal for å kjøre while loopen i workthread en gang til for å være sikker på at den har fått med seg at det står quit
    printf("--Main Thread Ready to Join!--\n");

    pthread_join(thread_1, NULL); //wait for workthread to join the threads
    printf("--Joined threads--\n");

    pthread_mutex_unlock(&lock_data); //cleanup mutexes
    pthread_mutex_destroy(&lock_data);

    pthread_cond_destroy(&read_data); //cleanup conditions
    pthread_cond_destroy(&write_data);

    free(structBuffer);
    printf("\nCleanup Done!\n");

    return 0;
} //main end()

void *workThread(void *structPointer)
{

    Buffer *Buffer = structPointer; //initialise buffer pointer

    while (strncmp(Buffer->input, "quit", 4)) // compare input with string, if it is quit we escaoe the while and exits the thread
    {

        // printf("Thread_1_Id: %ld\n",syscall(SYS_gettid)); //to see which thread id we're in useful for debugging

        FILE *outPut = fopen("outPut.txt", "a");

        fprintf(outPut, "%s", Buffer->input);
        fclose(outPut);

        //kjører whileloopen når den får signal

        pthread_mutex_trylock(&lock_data);
        pthread_cond_signal(&write_data);
        pthread_cond_wait(&read_data, &lock_data);
        pthread_mutex_unlock(&lock_data);
    }
    pthread_cond_signal(&write_data); //sends signal to main that it can continue to the join if its not there.
    printf("\n--workThread is Ready to Join!--\n");
    pthread_exit(0);
} // workthread()end