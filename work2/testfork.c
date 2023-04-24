#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t who = fork();
    if(who==0){
        printf("child running\n");
    }
    else if(who>0){
        printf("parent waiting...");
        wait(NULL);
        printf("parent running, child pid is %d\n", who);
    }
    else{
        printf("fork failed.\n");
    }
    printf("done.\n");
    return 0;
}
// 观察到无论wait在花括号哪里，两句printf必定是同时输出的
// 仅仅当wait在两句printf的末尾时才会连续两个done