#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

#define KTHREADD_PID 2

static int __init task_init(void)
{
	struct task_struct *kthreadd_task;
	struct task_struct *task;
	struct list_head *list;

	printk(KERN_INFO "task load\n");

	/* Find kthreadd task by PID */
	kthreadd_task = pid_task(find_vpid(KTHREADD_PID), PIDTYPE_PID);
	printk(KERN_INFO "Process name: %s\n", kthreadd_task->comm);

	/* Iterate over all children of kthreadd_task */
	list_for_each(list, &kthreadd_task->children) {
		/* Get next child */
		task = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "    Child name: %s\n", task->comm);
	}

	return 0;
}

static void __exit task_exit(void)
{
	printk(KERN_INFO "task exit\n");
}

module_init(task_init);
module_exit(task_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YogaPan <godhand1234567@gmail.com>");
MODULE_DESCRIPTION("task");
