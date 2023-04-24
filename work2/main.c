#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int input = 0;
    printf("input the number: ");
    int r = scanf("%d",&input);
    if(r==0){
        printf("not char.\n");
        return 0;
    }
    else if(input<=0){
            printf("number should be positive.\n");
            return 0;
    }
    

    pid_t who = fork();
    if(who==0){
        printf("child start running...printing the sequence...\n");
        while(input!=1){
            printf("%d ",input);
            if(input%2==0){
                input = input/2;
            }
            else{
                input = input*3+1;
            }
        }
        printf("1\n");
    }
    else if(who>0){
        wait(NULL);
        printf("child process done.[pid %d] parent running...\n",who);
    }
    else{
        printf("fork failed.\n");
    }
    printf("process done.\n");
    return 0;
}
// fork出一个子进程去处理任务
// 2023.3.18 16时
// 57121117倪哲振