#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

struct node {
    int data;
    struct node *next;
};

void print_list(struct node *head);
void free_list(struct node *head);

struct node *head = NULL;

struct node* new_node(int data) {
    struct node *new_node = kmalloc(sizeof(struct node), GFP_KERNEL);
    if (!new_node) {
        printk(KERN_ERR "Nahi nahi!, memory allocation failed\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void print_list(struct node *head) {
    struct node *current_node = head;
    while (current_node != NULL) {
        printk(KERN_INFO "%d ", current_node->data);
        current_node = current_node->next;
    }
}

void free_list(struct node *head) {
    struct node *current_node = head;
    struct node *next_node;
    while (current_node != NULL) {
        next_node = current_node->next;
        kfree(current_node);
        current_node = next_node;
    }
}

int simple_init(void) {
    printk(KERN_INFO "Initializing demo module\n");

    head = new_node(1);
    if (!head) {
        printk(KERN_ERR "Arey!,Failed to create head node\n");
        return -ENOMEM;
    }

    head->next = new_node(2);
    if (!head->next) {
        printk(KERN_ERR "Not again!, Failed to create second node\n");
        kfree(head);
        return -ENOMEM;
    }

    head->next->next = new_node(3);
    if (!head->next->next) {
        printk(KERN_ERR "Not fair!,Failed to create third node\n");
        kfree(head->next);
        kfree(head);
        return -ENOMEM;
    }

    print_list(head);

    return 0;
}

void simple_exit(void) {
    printk(KERN_INFO "Removing demo module\n");
    free_list(head);
    printk(KERN_INFO "demo module Unloaded\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple demo module with Linked List");
MODULE_AUTHOR("Aditya Yedurkar 221080076");