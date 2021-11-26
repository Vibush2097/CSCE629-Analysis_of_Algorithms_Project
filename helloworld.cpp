#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

class Node {
	public:
	int data;
	Node *next;
};

void push(Node **head, int data) {
	Node *new_node = new Node();
	new_node->data = data;
	new_node->next = (*head);
	(*head) = new_node;
}

print_list(Node *head) {
	while(head!=NULL) {
		cout<<head->data<<" ";
		head = head->next;
	}
}

int main() {
	Node *head = NULL;
	push(&head, 10);
	print_list(head);
}