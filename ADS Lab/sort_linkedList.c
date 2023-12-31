#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} linkedList;

linkedList* createNewNode(int value);
void insertAtHead(linkedList** head, int value);
void printLinkedList(linkedList* head);
void mergeTwoSortedLinkedList(linkedList** head1, linkedList** head2, linkedList** head3);
void mergeSort(linkedList** head);
void splitList(linkedList* source, linkedList** frontRef, linkedList** backRef);

int main() {
    linkedList* head1 = NULL;
    linkedList* head2 = NULL;
    linkedList* head3 = NULL;
    int n, value;

    printf("Enter the number of elements for the first linked list: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &value);
        insertAtHead(&head1, value);
    }

    printf("Enter the number of elements for the second linked list: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &value);
        insertAtHead(&head2, value);
    }

    printf("Linked List 1 (unsorted):\n");
    printLinkedList(head1);
    printf("Linked List 2 (unsorted):\n");
    printLinkedList(head2);

    mergeSort(&head1);
    mergeSort(&head2);

    printf("Linked List 1 (sorted):\n");
    printLinkedList(head1);
    printf("Linked List 2 (sorted):\n");
    printLinkedList(head2);

    mergeTwoSortedLinkedList(&head1, &head2, &head3);

    printf("Merged Linked List (sorted):\n");
    printLinkedList(head3);

    return 0;
}

linkedList* createNewNode(int value) {
    linkedList* newNode = (linkedList*)malloc(sizeof(linkedList));
    if (newNode == NULL) {
        puts("Memory Allocation Error");
        exit(0);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insertAtHead(linkedList** head, int value) {
    linkedList* newNode = createNewNode(value);
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        newNode->next = *head;
        *head = newNode;
    }
}

void printLinkedList(linkedList* head) {
    linkedList* tempNode = head;
    while (tempNode != NULL) {
        printf("%d\n", tempNode->value);
        tempNode = tempNode->next;
    }
}

void mergeTwoSortedLinkedList(linkedList** head1, linkedList** head2, linkedList** head3) {
    linkedList* temp1 = *head1;
    linkedList* temp2 = *head2;
    *head3 = NULL;
    linkedList** tail = head3;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->value <= temp2->value) {
            insertAtHead(tail, temp1->value);
            temp1 = temp1->next;
        }
        else {
            insertAtHead(tail, temp2->value);
            temp2 = temp2->next;
        }
        tail = &((*tail)->next);
    }

    while (temp1 != NULL) {
        insertAtHead(tail, temp1->value);
        temp1 = temp1->next;
        tail = &((*tail)->next);
    }

    while (temp2 != NULL) {
        insertAtHead(tail, temp2->value);
        temp2 = temp2->next;
        tail = &((*tail)->next);
    }
}

void splitList(linkedList* source, linkedList** frontRef, linkedList** backRef) {
    linkedList* fast;
    linkedList* slow;
    if (source == NULL || source->next == NULL) {
        *frontRef = source;
        *backRef = NULL;
    }
    else {
        slow = source;
        fast = source->next;
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}

void mergeSort(linkedList** head) {
    linkedList* current = *head;
    linkedList* a;
    linkedList* b;

    if ((current == NULL) || (current->next == NULL)) {
        return;
    }

    splitList(current, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *head = NULL;
    mergeTwoSortedLinkedList(&a, &b, head);
}
