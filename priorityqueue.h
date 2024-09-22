#ifndef PROJECT_5___AIR_TRAFFIC_CONTROLLER_PRIORITYQUEUE_H
#define PROJECT_5___AIR_TRAFFIC_CONTROLLER_PRIORITYQUEUE_H

#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

struct Node {
    double x;
    double y;
    double rad;
    int speed;
    int priority;
    struct Node *next;
};

struct ListRecord {
    struct Node *head;
    struct Node *tail;
    int size;
};

typedef struct ListRecord *List;


List CreateList(int);
void MakeEmptyList(List);
void Check_prio_d_i(List l, List m);
int ListSize(List);
int GetElementAtPosition(List, double);
int GetSpeedAtPosition(List l, double pos);
int GetxAtPosition(List l, double pos);
int GetyAtPosition(List l, double pos);
int GetpriorityAtPosition(List l, double pos);
int GetradAtPosition(List l, double pos);
int GetPositionOfPrio(List, double);
int changepriorityAtPosition(List l, double pos, double p);
int changexAtPosition(List l, double pos, double x);
int changeyAtPosition(List l, double pos, double y);
int changespeedAtPosition(List l, double pos, int s);
int changeradAtPosition(List l, double pos, double r);
void InsertList(List, double, double, int, double, double);
int DeleteList(List);
int HeadOfList(List);
int TailOfList(List);
int IsEmptyList(List);
void DisplayList(List);
void DisplayListPrio(List l);
void Short_queue(List l, List m);

int flag = 1;
int noke = 1;

List CreateList(int size) {
    List l;

    l = (struct ListRecord *) malloc(sizeof(struct ListRecord));
    if (l == NULL)
        printf("Out of memory!\n");

    MakeEmptyList(l);

    return l;
}


void MakeEmptyList(List l) {
    flag = 1;
    l->head = (struct Node *) malloc(sizeof(struct Node));
    if (l->head == NULL)
        printf("Out of memory!\n");

    l->head->next = NULL;
    l->tail = l->head;
    l->size = 0;
}


int IsEmptyList(List l) {
    return (l->size == 0);
}


int ListSize(List l) {
    return (l->size);
}

int GetSpeedAtPosition(List l, double pos) {
    struct Node *search;
    int i;

    if (pos > l->size) {
        printf("Linked list is shorter than %d elements\n", pos);
        return -1;
    } else {
        search = l->head;
        for (i = 0; i < pos; i++)
            search = search->next;

        return search->speed;
    }
}

int GetxAtPosition(List l, double pos) {
    struct Node *search;
    int i;

    if (pos > l->size) {
        printf("Linked list is shorter than %d elements\n", pos);
        return -1;
    } else {
        search = l->head;
        for (i = 0; i < pos; i++)
            search = search->next;

        return search->x;
    }
}

int GetyAtPosition(List l, double pos) {
    struct Node *search;
    int i;

    if (pos > l->size) {
        printf("Linked list is shorter than %d elements\n", pos);
        return -1;
    } else {
        search = l->head;
        for (i = 0; i < pos; i++)
            search = search->next;

        return search->y;
    }
}

int GetpriorityAtPosition(List l, double pos) {
    struct Node *search;
    int i;

    if (pos > l->size) {
        printf("Linked list is shorter than %d elements\n", pos);
        return -1;
    } else {
        search = l->head;
        for (i = 0; i < pos; i++)
            search = search->next;

        return search->priority;
    }
}

int GetradAtPosition(List l, double pos) {
    struct Node *search;
    int i;

    if (pos > l->size) {
        printf("Linked list is shorter than %d elements\n", pos);
        return -1;
    } else {
        search = l->head;
        for (i = 0; i < pos; i++)
            search = search->next;

        return search->rad;
    }
}


int GetPositionOfPrio(List l, double priority) {
    struct Node *search;

    int i = 0;
    search = l->head->next;

    while ((search != NULL) && (search->priority != priority)) {
        search = search->next;
        i++;
    }

    if (search == NULL) {
        //printf("Element %dPrio not found in linked list\n", priority);
        return 0;
    } else
        return i + 1;
}


void InsertList(List l, double x, double y, int speed, double rad, double priority) {
    struct Node *insert, *temp;
    int i, p, pos;
    noke = 1;

    temp = l->head;


    while (1) {
        if (temp->next == NULL) {
            pos = 1;
            flag = 0;
            break;
        }


        while (temp != NULL && priority > temp->next->priority) {
            if (temp->next == NULL) {

                break;
            }
            temp = temp->next;

            if (temp->next == NULL) {

                break;
            }
        }
        /* if(noke == 0){
             break;
         }*/
        if (priority == temp->priority) {
            pos = GetPositionOfPrio(l, temp->priority) + 1;
            break;
        }
        if (temp->next == NULL) {
            pos = GetPositionOfPrio(l, temp->priority) + 1;
            break;
        }
        if (priority > temp->priority) {
            pos = GetPositionOfPrio(l, temp->priority) + 1;
            break;
        }
        if (priority < temp->priority) {
            pos = GetPositionOfPrio(l, temp->priority) - 1;
            break;
        }
    }


    insert = (struct Node *) malloc(sizeof(struct Node));

    insert->x = x;
    insert->y = y;
    insert->speed = speed;
    insert->rad = rad;
    insert->priority = priority;
    insert->next = NULL;

    if (pos > (l->size) + 1)
        pos = (l->size) + 1;

    if (pos == l->size + 1) {
        l->tail->next = insert;
        l->tail = insert;
    } else {
        temp = l->head;
        for (i = 1; i < pos; i++) {
            temp = temp->next;
        }

        insert->next = temp->next;
        temp->next = insert;
    }
    l->size++;


}


int DeleteList(List l) {
    struct Node *remove, *temp;

    if (!IsEmptyList(l)) {
        temp = l->head;
        if (temp->next == NULL)
            printf("Element  not found in linked list\n");
        else {
            remove = temp->next;
            temp->next = temp->next->next;
            free(remove);
            l->size--;
        }

        if (l->size == 0)
            l->tail = l->head;
    } else
        printf("The linked list is empty\n");

}


int HeadOfList(List l) {
    if (!IsEmptyList(l))
        return l->head->next->priority;
    else {
        printf("The linked list is empty\n");
        return -1;
    }
}


int TailOfList(List l) {
    if (!IsEmptyList(l))
        return l->tail->priority;
    else {
        printf("The linked list is empty\n");
        return -1;
    }
}


void DisplayList(List l) {
    struct Node *p;

    p = l->head->next;
    printf("List content:\n");

    while (p != NULL) {
        printf("--> %d\t", p->speed);
        p = p->next;
    }
}


int changeradAtPosition(List l, double pos, double r) {
    struct Node *search;
    int i;

    if (pos > l->size) {
        printf("Linked list is shorter than %g elements\n", pos);
        return -1;
    } else {
        search = l->head;
        for (i = 0; i < pos; i++)
            search = search->next;

        search->rad = r;
    }
}

int changexAtPosition(List l, double pos, double x) {
    struct Node *search;
    int i;

    if (pos > l->size) {
        printf("Linked list is shorter than %g elements\n", pos);
        return -1;
    } else {
        search = l->head;
        for (i = 0; i < pos; i++)
            search = search->next;

        search->x = x;
    }
}

int changeyAtPosition(List l, double pos, double y) {
    struct Node *search;
    int i;

    if (pos > l->size) {
        printf("Linked list is shorter than %g elements\n", pos);
        return -1;
    } else {
        search = l->head;
        for (i = 0; i < pos; i++)
            search = search->next;

        search->y = y;
    }
}

int changespeedAtPosition(List l, double pos, int s) {
    struct Node *search;
    int i;

    if (pos > l->size) {
        printf("Linked list is shorter than %g elements\n", pos);
        return -1;
    } else {
        search = l->head;
        for (i = 0; i < pos; i++)
            search = search->next;

        search->speed = s;
    }
}

int changepriorityAtPosition(List l, double pos, double p) {
    struct Node *search;
    int i;

    if (pos > l->size) {
        printf("Linked list is shorter than %g elements\n", pos);
        return -1;
    } else {
        search = l->head;
        for (i = 0; i < pos; i++)
            search = search->next;

        search->priority = p;
    }
}

void DisplayListPrio(List l) {
    struct Node *p;

    p = l->head->next;
    printf("List content:\n");

    while (p != NULL) {
        printf("--> %g\t", p->priority);
        p = p->next;
    }
}

void Check_prio_d_i(List l, List m) {
    flag = 1;
    struct Node *remove, *temp, *p;
    int speed;
    double x, y, priority, rad;
    p = l->head->next;

    while (p != NULL) {
        if (!IsEmptyList(l)) {
            temp = l->head;
            if (temp->next == NULL)
                printf("Element  not found in linked list\n");
            else {
                remove = temp->next;
                temp->next = temp->next->next;
                x = remove->x;
                y = remove->y;
                speed = remove->speed;
                rad = remove->rad;
                priority = remove->priority;
                InsertList(m, x, y, speed, rad, priority);
                free(remove);
                l->size--;
            }

            if (l->size == 0)
                l->tail = l->head;
        } else
            printf("The linked list is empty\n");
        p = l->head->next;
    }
    flag = 1;
}

int Is_100(List l) {
    struct Node *p;
    int count = 0;
    if (l->size == 0) {
        return 0;
    }
    p = l->head->next;


    while (p != NULL) {
        if (count == 100) {
            return 1;
        }
        count++;
        p = p->next;
    }
    return 0;
}

void Short_queue(List l, List m) {

    Check_prio_d_i(l, m);
    Check_prio_d_i(m, l);
}

void Check_delete(List l, List m) {
    struct Node *p;

    p = l->head->next;


    while (p != NULL) {
        if (p->priority == 0) {
            Short_queue(l, m);
            DeleteList(l);
            break;
        }
        p = p->next;
    }

}

#endif
