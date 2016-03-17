You have to include:

        #include <linux/list.h>

list_head struct:

        struct list_head {
                struct list_head *next;
                struct list_head *prev;
        };

Embed list_head in your struct:

        struct person {
                char name[16];
                int age;
                struct list_head list;
        };

API
=========================

LIST_HEAD(name)
list_empty(const struct list_head *head)

LINK:
- http://lxr.free-electrons.com/source/include/linux/list.h
