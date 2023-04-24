#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday{
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list);    // 声明birthday_list


int mymodule_init(void){
    printk(KERN_INFO "loading my birthday module...\n");
    struct birthday *person;    // 创建5个birthday实例
    person = kmalloc(sizeof(*person),GFP_KERNEL);
    person->day = 2;
    person->month = 8;
    person->year = 1995;
    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list,&birthday_list);

    person = kmalloc(sizeof(*person),GFP_KERNEL);
    person->day = 16;
    person->month = 5;
    person->year = 2006;
    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list,&birthday_list);

    person = kmalloc(sizeof(*person),GFP_KERNEL);
    person->day = 24;
    person->month = 9;
    person->year = 2002;
    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list,&birthday_list);

    person = kmalloc(sizeof(*person),GFP_KERNEL);
    person->day = 18;
    person->month = 11;
    person->year = 1992;
    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list,&birthday_list);

    person = kmalloc(sizeof(*person),GFP_KERNEL);
    person->day = 25;
    person->month = 10;
    person->year = 1998;
    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list,&birthday_list);

    // 遍历
    struct birthday *ptr,*next;
    list_for_each_entry_safe(ptr,next,&birthday_list,list){
        printk(KERN_INFO "birthday info: %d/%d/%d",ptr->year,ptr->month,ptr->day);
    }
    return 0;
}

void mymodule_exit(void){
    printk(KERN_INFO "removing my birthday module...\ndeleting data...\n");
    struct birthday *ptr,*next;
    list_for_each_entry_safe(ptr,next,&birthday_list,list){
        list_del(&ptr->list);
        kfree(ptr);
    }
}

module_init(mymodule_init);
module_exit(mymodule_exit);

MODULE_LICENSE("nop.");
MODULE_DESCRIPTION("my own module.");
MODULE_AUTHOR("redh3t");