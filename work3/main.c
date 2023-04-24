#include <pthread.h>
#include <stdio.h>

int sequence[100];


void *calc(int *destiny){
    int a = 0;
    int b = 1;
    sequence[0] = 0;
    sequence[1] = 1;
    int index = 2;
    while(b!=destiny&&index<100){
        int tmp = a + b;
        a = b;
        b = tmp;
        sequence[index] = b;
        index++;
    }
    pthread_exit(0);
}

int main(){
    int d;
    printf("input a fib num here: ");
    scanf("%d",&d);
    for(int i=0;i<100;i++){
        sequence[i] = -1;
    }
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid,&attr,calc,d);
    pthread_join(tid,NULL);
    for(int i=0;i<100;i++){
        if(sequence[i]==-1){
            break;
        }
        else if(sequence[i]>d){
            printf("...\nNo your input is not a fib num, thus there is not a valid sequence.");
            break;
        }
        else{
            printf("%d ",sequence[i]);
        }
    }
    printf("\n");
}
// 斐波那契数列。新开线程去处理，结束后由主线程输出
// 57121117倪哲振