#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>  // For sleep()
#include <stdlib.h>  // For rand()

int student_total = 19;
sem_t sem_office;   // 办公室,初值1
sem_t sem_chairs;   // 椅子,初值3
sem_t sem_awake;    // 助教醒着,初值0
sem_t ask_done;     // 学生提问结束
sem_t answer_done;  // TA解答结束
sem_t mutux;        // 互斥读取sem_chairs的值



void *student(void *threadid) 
{
    while(1){
        sleep(rand() % 18);
        printf("[Student %d] coming...\n", *(int*)threadid);
        sem_wait(&mutux);
        int value;
        sem_getvalue(&sem_chairs, &value);
        if(value>0){
            sem_wait(&sem_chairs);
            sem_post(&mutux);
            printf("[Student %d] take a seat.\n", *(int*)threadid);
            sem_wait(&sem_office);
            sem_post(&sem_chairs);
            sem_post(&sem_awake);
            printf("[Student %d] asking...\n", *(int*)threadid);
            sleep(rand() % 8);
            sem_post(&ask_done);
            sem_wait(&answer_done);
            printf("[Student %d] finished.\n", *(int*)threadid);
            sem_post(&sem_office);
            break;
        }
        else{
            sem_post(&mutux);
            printf("[Student %d] Seats all taken, leave.\n", *(int*)threadid);
        }
    }

    return NULL;
}

void *teacher_assistance(void *threadid) 
{
    printf("teacher assistance created.\n");
    while(1){
        sem_wait(&sem_awake);
        sem_wait(&ask_done);
        printf("TA helping a student...\n");
        sem_post(&answer_done);
    }
    return NULL;
}




int main() 
{
    srand(time(NULL)); 
    sem_init(&sem_office, 0, 1);  
    sem_init(&sem_chairs, 0, 3);
    sem_init(&sem_awake, 0, 0);
    sem_init(&ask_done, 0, 0);
    sem_init(&answer_done, 0, 0);
    sem_init(&mutux, 0, 1);  



    pthread_t teacher_thread;
    pthread_create(&teacher_thread, NULL, teacher_assistance, NULL);
    // pthread_join(teacher_thread, NULL); 

    pthread_t student_threads[student_total];
    int tids[student_total];
    for (int i = 0; i < student_total; i++) {
        tids[i] = i+1;
    }
    for (int i = 0; i < student_total; i++) {
        pthread_create(&student_threads[i], NULL, student, &tids[i]);
    }
    for (int i = 0; i < student_total; i++) {
        pthread_join(student_threads[i], NULL); 
    }

    printf("Main() completed.\n");
    return 0;
}
