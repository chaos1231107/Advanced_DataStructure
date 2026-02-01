#include <stdio.h>
#include <stdlib.h>

// 구조체를 node라는 자료형으로 정의
typedef struct _node {
    int key;
    struct _node *next;
} node;

//node *LinkedList;
node *head, *tail;

void init_list() {
    head = (node*)malloc(sizeof(node));
    tail = (node*)malloc(sizeof(node));
    head->next = tail; //머리가 꼬리를 참조
    tail->next = tail; //꼬리가 꼬리를 참조
}

int delete_next(node *t) {
    node *s;
    if (t -> next == tail)
        return 0;
    s = t -> next;
    t -> next = t -> next -> next; // t의 다음은 한단계 건너뛴다.
    free(s);
    return 1;
}

node *insert_after(int k, node *t) {
    node *s;
    s = (node*)malloc(sizeof(node));
    s -> key = k;
    s -> next = t;
    s -> next = t -> next;
    t -> next = s;
    return s;
}

node *find_node(int k) {
    node *s;
    s = head->next;
    while (s -> key != k && s -> next != tail)
        s = s -> next;
    return s;
}

int delete_node(int k) {
    node *s;
    node *p;
    p = head;
    s = p -> next;
    while (s -> key != k && s -> next != tail) {
        p = p -> next;
        s = s -> next;
    }
    if (s != tail) {
        p -> next = s -> next;
        free(s);
        return 1;
    }
    else {
        return 0;
    }
}

node *insert_node(int t, int k) {
    node *s;
    node *p;
    node *r;
    p = head;
    s = p -> next;

    while (s -> key != k && s -> next != tail) {
        p = p -> next;
        s = s -> next;
    }

    if (s != tail) {
        r = (node*)malloc(sizeof(node));
        r -> key = t;
        p -> next = r;
        r -> next = s;
    }
    return p -> next;
}

// linked list가 오름차순으로 정렬되어 있다고 가정, 새로 주어지는 키 값에 대해 노드를 만들어 정렬 순서를 깨지 않게 하는 함수
node *ordered_insert(int k) {
    node *s;
    node *p;
    node *r;
    p = head;
    s = p -> next;

    while (s -> key <= k && s -> next != tail) {
        p = p -> next;
        s = s -> next;
    }
    r = (node*)malloc(sizeof(node));
    r -> key = k;
    p -> next = r;
    r -> next = s;
    return r;
}

void print_list(node *t) {
    printf("\n");
    while (t != tail) {
        printf("%-8d", t -> key);
        t = t -> next;
    }
    printf("\n");
}

node *delete_list() {
    node *s;
    node *t;
    t = head->next;

    while (t != tail) {
        s = t; // 삭제할 노드를 물고있는 노드 s
        t = t -> next; // 다음 노드로 건너뛰면서 순차적으로 삭제
        free(s); // s메모리 해제
    }

    head->next = tail;
    return head;
}

node *delete_all() {
    node *s;
    node *t;
    t = head->next;
    while (t != tail) {
        s = t;
        t = t -> next;
        free(s);
    }
    head->next = tail;
    return head;
}

int main() {
    node *t;

    init_list();
    ordered_insert(10);
    ordered_insert(5);\
    ordered_insert(8);
    ordered_insert(3);
    ordered_insert(1);
    ordered_insert(7);
    ordered_insert(8);

    printf("\nInitial Linked list is ");
    print_list(head -> next);

    printf("\nFinding 4 is %successful", find_node(4) == tail ? "un" : "");

    t = find_node(5);
    printf("\nFinding 5 is %successful", t == tail ?  "un" : "");

    printf("\nInserting 9 after 5");
    insert_after(9, t);
    print_list(head -> next);

    t = find_node(10);
    printf("\nDeleting next last node");
    delete_next(t);
    print_list(head -> next);

    t = find_node(3);
    printf("\nDeleting next last node");
    delete_next(t);
    print_list(head -> next);

    printf("\nInserting node 2 before 3");
    insert_node(2, 3);
    print_list(head -> next);

    printf("\nDeleting node 2");
    if (!delete_node(2)) {
        printf("\nDeleting 2 is not succesful");
    }
    print_list(head -> next);

    printf("/nDeleting node 1");
    delete_node(1);
    print_list(head -> next);

    printf("\nDeleting all node");
    delete_all();
    print_list(head -> next);

    return 0;

}
