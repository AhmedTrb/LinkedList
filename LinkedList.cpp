#include <iostream>
#include <cstdlib>

using namespace std;

struct LinkedList {
    int data;
    LinkedList* next;
};

typedef LinkedList* Node;

Node createNode(int value) {
    Node temp = (Node)malloc(sizeof(LinkedList));
    if (!temp) {
        cerr<<"Memory allocation failed!"<<endl;
        exit(EXIT_FAILURE);
    }
    temp->data = value;
    temp->next = nullptr;
    return temp;
}

void addNode(Node& head, int value) {
    Node temp = createNode(value);
    if (!head) {
        head = temp;
    } else {
        Node p = head;
        while (p->next) {
            p = p->next;
        }
        p->next = temp;
    }
}

void insertNode(Node& head, int pos, int value) {
    if (pos < 0) {
        cerr << "Position cannot be negative!\n";
        return;
    }
    Node temp = createNode(value);
    if (pos == 0) {
        temp->next = head;
        head = temp;
        return;
    }
    Node p = head;
    for (int i = 0; i < pos - 1 && p; ++i) {
        p = p->next;
    }
    if (!p) {
        cerr << "Position out of bounds!\n";
        return;
    }
    temp->next = p->next;
    p->next = temp;
}

void deleteNode(Node& head, int pos) {
    if (pos < 0 || !head) {
        cerr<<"Invalid position or empty list!"<<endl;
        return;
    }

    if (pos == 0) {
        Node temp = head;
        head = head->next;
        free(temp);
        return;
    }

    Node p = head;
    for (int i=0; i<pos-1 && p->next;i++) {
        p = p->next;
    }

    if (!p->next) {
        cerr<<"Position out of bounds!"<<endl;
        return;
    }
    Node temp = p->next;
    p->next = temp->next;
    free(temp);
}

int linkedListSize(Node head) {
    int size = 0;
    while (head) {
        head = head->next;
        ++size;
    }
    return size;
}

void reverseLinkedList(Node& head) {
    Node prev = nullptr, cur = head, next;
    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    head = prev;
}

void printLinkedList(Node head) {
    if (!head) {
        cout<<"Empty list"<<endl;
        return;
    }

    while (head){
        cout<<head->data<< " -> ";
        head=head->next;
    }
    cout<<"NULL"<<endl;
}

bool detectLoop(Node head) {
    Node slow = head, fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

Node mergeTwoLists(Node l1, Node l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->data <= l2->data) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

void freeList(Node& head) {
    Node temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node head = nullptr;

    int n,x;
    cout<<"Enter the number of elements: ";
    cin>>n;

    for (int i=0;i<n; i++) {
        cin>>x;
        addNode(head, x);
    }

    cout <<"Linked list:"<<endl;
    printLinkedList(head);

    cout<<"Reversing the linkedlist"<<endl;
    reverseLinkedList(head);
    printLinkedList(head);

    freeList(head);
    return 0;
}
