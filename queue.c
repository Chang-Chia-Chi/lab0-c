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
    int s_len = strlen(s);
    /* Don't forget space for \0 */
    newh->value = malloc(sizeof(char) * (s_len + 1));
    if (!newh->value) {
        free(newh->value);
        free(newh);
        return false;
    }
    strncpy(newh->value, s, s_len + 1);
    newh->next = q->head;
    q->head = newh;
    if (!q->tail)
        q->tail = newh;
    (q->size)++;
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
    int s_len = strlen(s);
    /* Don't forget space for \0 */
    newh->value = malloc(sizeof(char) * (s_len + 1));
    if (!newh->value) {
        free(newh->value);
        free(newh);
        return false;
    }
    strncpy(newh->value, s, s_len + 1);
    if (!q->head) {
        q->head = newh;
        q->tail = newh;
    } else {
        q->tail->next = newh;
        q->tail = q->tail->next;
    }
    /* To avoid forming linked list cycle */
    q->tail->next = NULL;
    (q->size)++;
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
    (q->size)--;
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
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
