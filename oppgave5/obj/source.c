#include "source.h"

int main(void)
{
    char *tmpInput;
    tmpInput = malloc(sizeof(char) * 11);
    if (tmpInput == NULL)
    {
        printf("error allocation memory for tmpInput");
        return (1);
    }
    memset(tmpInput, 0, sizeof(char) * 11);

    pthread_mutex_init(&lock_data, NULL);
    pthread_cond_init(&read_data, NULL);
    pthread_cond_init(&write_data, NULL);

    Buffer *structBuffer = malloc(sizeof(Buffer));
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

        tmpInput = fgets(structBuffer->input, 10, stdin); //take input
        pthread_cond_signal(&read_data);                  //sender signal for å kjøre while loopen en gang
        pthread_cond_wait(&write_data, &lock_data);       //kjører whileloopeb når den får signal
        tmpInput = "0";
        //sleep(1);//for feilsøking av tråder
    }

    pthread_cond_signal(&read_data); //sender signal for å kjøre while loopen en gang
    printf("\n--Main Thread Ready to Join!--\n");

    pthread_join(thread_1, NULL);
    printf("--Joined threads--\n");

    pthread_mutex_unlock(&lock_data);
    pthread_mutex_destroy(&lock_data);

    pthread_cond_destroy(&read_data);
    pthread_cond_destroy(&write_data);

    free(structBuffer);
    printf("\nCleanup Done!\n");

    return 0;
}

void *workThread(void *structPointer)
{

    Buffer *Buffer = structPointer;
    *Buffer->input = 0;

    while (strncmp(Buffer->input, "quit", 4))
    {

        // printf("Thread_1_Id: %ld\n",syscall(SYS_gettid));

        FILE *outPut = fopen("outPut.txt", "a");

        fprintf(outPut, "%s", Buffer->input);
        fclose(outPut);

        //kjører whileloopen når den får signal

        pthread_mutex_trylock(&lock_data);
        pthread_cond_signal(&write_data);
        pthread_cond_wait(&read_data, &lock_data);
        pthread_mutex_unlock(&lock_data);
    }

    pthread_cond_signal(&write_data);
    printf("\n--workThread is Ready to Join!--\n");
    pthread_exit(0);
}