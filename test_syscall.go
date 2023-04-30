// https://zhuanlan.zhihu.com/p/58285124

package main

import (
	"fmt"
	"syscall"
)

func main(){

	pid,_,_:=syscall.Syscall(39,0,0,0)
	fmt.Println("current process id: ",pid)
}
