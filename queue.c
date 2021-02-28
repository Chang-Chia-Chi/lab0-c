#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}
/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;
    list_ele_t *tmp = q->head;
    while (tmp) {
        q->head = tmp->next;
        if (tmp->value)
            free(tmp->value);
        free(tmp);
        tmp = q->head;
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        free(newh);
        return false;
    }
    if (s) {
        int s_len = strlen(s);
        /* Don't forget space for \0 */
        newh->value = malloc(sizeof(char) * (s_len + 1));
        if (!newh->value) {
            free(newh->value);
            free(newh);
            return false;
        }
        strncpy(newh->value, s, s_len + 1);
    }
    newh->next = q->head;
    q->head = newh;
    if (!q->tail)
        q->tail = newh;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        free(newh);
        return false;
    }
    if (s) {
        int s_len = strlen(s);
        /* Don't forget space for \0 */
        newh->value = malloc(sizeof(char) * (s_len + 1));
        if (!newh->value) {
            free(newh->value);
            free(newh);
            return false;
        }
        strncpy(newh->value, s, s_len + 1);
    }
    if (!q->head) {
        q->head = newh;
        q->tail = newh;
    } else {
        q->tail->next = newh;
        q->tail = q->tail->next;
    }
    /* To avoid forming linked list cycle */
    q->tail->next = NULL;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head)
        return false;
    if (q->head->value) {
        if (sp) {
            strncpy(sp, q->head->value, bufsize);
            sp[bufsize - 1] = '\0';
        }
        free(q->head->value);
    }
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    free(tmp);
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || !q->head)
        return;
    list_ele_t *prev;
    list_ele_t *curr = q->head;
    list_ele_t *next = q->head->next;
    curr->next = NULL;
    q->tail = curr;
    prev = curr;
    while (next) {
        curr = next;
        next = next->next;
        curr->next = prev;
        prev = curr;
    }
    q->head = curr;
    return;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
list_ele_t *merge(list_ele_t *n1, list_ele_t *n2)
{
    list_ele_t *dummy = NULL;
    list_ele_t *tmp = NULL;
    if (strcasecmp(n1->value, n2->value) <= 0) {
        dummy = n1;
        n1 = n1->next;
    } else {
        dummy = n2;
        n2 = n2->next;
    }
    tmp = dummy;
    while (n1 && n2) {
        if (strcasecmp(n1->value, n2->value) <= 0) {
            tmp->next = n1;
            tmp = tmp->next;
            n1 = n1->next;
        } else {
            tmp->next = n2;
            tmp = tmp->next;
            n2 = n2->next;
        }
    }
    if (!n1)
        tmp->next = n2;
    if (!n2)
        tmp->next = n1;
    return dummy;
}

list_ele_t *merge_sort(list_ele_t *head)
{
    if (!head || !head->next)
        return head;
    list_ele_t *prev;
    list_ele_t *slow = head;
    list_ele_t *fast = head;
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = NULL;
    list_ele_t *n1 = merge_sort(head);
    list_ele_t *n2 = merge_sort(slow);
    return merge(n1, n2);
}

void q_sort(queue_t *q)
{
    if (!q || !q->head || !q->head->next)
        return;
    q->head = merge_sort(q->head);
    list_ele_t *tmp = q->head;
    while (tmp->next) {
        tmp = tmp->next;
    }
    q->tail = tmp;
    return;
}
