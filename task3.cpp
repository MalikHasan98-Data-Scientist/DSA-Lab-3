// Part 3 - Singly Linked List
#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
Node* head = NULL;   // this always points to the first node of the list

// 1. insert a new node at the very beginning of the list
void insertAtHead(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;   // new node points to the old head
    head = newNode;          // new node becomes the head
    cout << value << " inserted at the head." << endl;
}
// 2. insert a new node at the 3rd position of the list
void insertAtThird(int value) {
    Node* newNode = new Node();
    newNode->data = value;

    if (head == NULL || head->next == NULL) {
        cout << "List has fewer than 2 nodes, so inserting at the end instead." << endl;
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
        } else {
            head->next = newNode;
        }
        return;
    }
    Node* second = head->next;
    newNode->next = second->next;
    second->next = newNode;
    cout << value << " inserted at position 3." << endl;
}
// 3. print out every value in the list, from head to tail
void displayList() {
    if (head == NULL) {
        cout << "The list is empty." << endl;
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}
// 4. delete the last node in the list
void deleteLast() {
    if (head == NULL) {
        cout << "List is already empty, nothing to delete." << endl;
        return;
    }
    if (head->next == NULL) {
        delete head;
        head = NULL;
        cout << "Only node deleted, list is now empty." << endl;
        return;
    }
    Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    delete temp->next;     // delete the actual last node
    temp->next = NULL;     // this node is now the new last node
    cout << "Last node deleted." << endl;
}
// 5. count how many nodes the list currently has
int countNodes() {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}
// 6. reverse the list iteratively (no recursion here)
void reverseList() {
    Node* prev = NULL;
    Node* current = head;
    Node* nextNode = NULL;

    while (current != NULL) {
        nextNode = current->next;   // remember what comes next before we overwrite it
        current->next = prev;       // flip the arrow so it points backwards
        prev = current;             // move prev one step forward
        current = nextNode;         // move current one step forward
    }
    head = prev;   // prev is sitting on the old last node, which is now the new head
    cout << "List has been reversed." << endl;
}
// 7. search the list for a given value
void searchValue(int value) {
    Node* temp = head;
    int position = 0;

    while (temp != NULL) {
        if (temp->data == value) {
            cout << value << " found at position " << position << " (0 = head)." << endl;
            return;
        }
        temp = temp->next;
        position++;
    }
    cout << value << " was not found in the list." << endl;
}
void freeList() {
    Node* temp = head;
    while (temp != NULL) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    head = NULL;
}
int main() {
    int choice = 0;
    int value;

    while (choice != 8) {
        cout << "\n========= Linked List Menu =========" << endl;
        cout << "1. Insert at head" << endl;
        cout << "2. Insert at 3rd position" << endl;
        cout << "3. Display the list" << endl;
        cout << "4. Delete the last node" << endl;
        cout << "5. Count nodes" << endl;
        cout << "6. Reverse the list" << endl;
        cout << "7. Search for a value" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a value to insert: ";
                cin >> value;
                insertAtHead(value);
                break;

            case 2:
                cout << "Enter a value to insert: ";
                cin >> value;
                insertAtThird(value);
                break;

            case 3:
                cout << "Current list: ";
                displayList();
                break;

            case 4:
                deleteLast();
                displayList();
                break;

            case 5:
                cout << "Number of nodes in the list: " << countNodes() << endl;
                break;

            case 6:
                reverseList();
                displayList();
                break;

            case 7:
                cout << "Enter a value to search for: ";
                cin >> value;
                searchValue(value);
                break;

            case 8:
                cout << "Exiting the program, bye!" << endl;
                break;

            default:
                cout << "That's not a valid option, please try again." << endl;
        }
    }

    freeList();   // clean up all remaining nodes before we quit
    return 0;
}