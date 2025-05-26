#include <iostream>
#include "LinkedList.h"
#include "Stack.h"

using namespace std;

int main() {
	LinkedList list;
	Stack stack;

	// Append a node to the end of the linked list
	list.appendListNode(1.1);
	cout << "Testing append to an empty list" << endl;
	cout << "Modified linked list: ";
	list.displayList();
	list.appendListNode(3.3);
	cout << "Testing append to a non-empty list" << endl;
	cout << "Modified linked list: ";
	list.displayList();
	list.appendListNode(5.5);
	list.appendListNode(2.2);
	list.appendListNode(6.6);
	list.appendListNode(4.5);
	cout << "New Linked list: ";
	list.displayList();

	cout << "Testing return value of isEmpty on non-empty list" << endl;
	cout << boolalpha << list.isEmpty() << ": ";
	cout << "Non-Empty linked list: ";
	list.displayList();
	cout << "Testing length, should be 1: "
		<< list.lengthList() << endl;
	list.~LinkedList();
	cout << "Testing removelist: should leave an empty list" << endl;
	cout << "Testing length, list should be empty: "
		<< list.lengthList();
	list.displayList();
	cout << "Testing return value of isEmpty)() on empty list\n";
	cout << boolalpha << list.isEmpty() << ": ";
	cout << "Empty linked list: ";
	list.displayList();
	cout << endl << endl;

	// Insert some nodes at the front of the linked list again
	list.appendListNode(1.1);
	list.appendListNode(3.3);
	list.appendListNode(5.5);
	list.appendListNode(2.2);
	list.appendListNode(6.6);
	list.appendListNode(4.5);
	cout << "Rebuilt Linked list: ";
	list.displayList();
	// Remove a node from the linked list
	list.removeListNodeN(6);
	cout << "Testing removeNodeN for 6th and last node" << endl;
	cout << "Modified linked list: ";
	list.displayList();

	// Remove a node from the linked list
	cout << "Testing removeNodeN for 1st node" << endl;
	list.removeListNodeN(1);
	cout << "Modified linked list: ";
	list.displayList();

	// Remove a node from the linked list
	cout << "Testing removeNodeN for 2nd remaining node" << endl;
	list.removeListNodeN(2);
	cout << "Modified linked list: ";
	list.displayList();
	list.~LinkedList();
	cout << "List destroyed";
	cout << endl << endl << endl;


	cout << "value of stack.isEmpty() is: " << stack.isEmpty() << endl;
	cout << "top element of empty list " << stack.pop() << endl;
	// Push elements onto the stack
	stack.push(10);
	printf("after pushing 10 onto the stack:");
	stack.displayStack();
	stack.push(2);
	printf("after pushing 2 onto the stack:");
	stack.displayStack();
	stack.push(7);
	printf("after pushing 7 onto the stack:");
	stack.displayStack();
	stack.push(23);
	printf("after pushing 23 onto the stack:");
	stack.displayStack();

	// Display the stack
	cout << "Stack: ";
	stack.displayStack();
	cout << "value of stack.isEmpty() is: " << stack.isEmpty() << endl;


	// Pop an element from the stack
	cout << "the 1st value popped off the stack is " << stack.pop() << endl;
	cout << "the 2nd value popped off the stack is " << stack.pop() << endl;
	// Display the stack after popping
	cout << "Stack after pop: ";
	stack.displayStack();
	stack.~Stack();
	cout << "Destructor successful" << endl;
	cout << "value of stack.isEmpty() is: " << stack.isEmpty() << endl;
	stack.pop();
	cout << endl << endl;

	//create and sort stack
	Stack stack1;

	int heightOfStack = 0;
	int counter = 0;
	stack1.push(6.7);
	heightOfStack++;
	stack1.push(2.5);
	heightOfStack++;
	stack1.push(3.3);
	heightOfStack++;
	stack1.push(4.5);
	heightOfStack++;
	stack1.push(9.2);
	heightOfStack++;
	stack1.push(1.1);
	heightOfStack++;
	stack1.push(5.4);
	heightOfStack++;	
	stack1.push(6.7);
	heightOfStack++;
	stack1.push(1.1);
	heightOfStack++;
	stack1.push(9.2);
	heightOfStack++;
	stack1.push(9.2);
	heightOfStack++;

	//Test height() and displayStack methods
	printf("count of nodes %d ", heightOfStack);
	printf("height of stack %d\n", stack1.height());
	stack1.displayStack();

	//sort stack1  in place (using only the existing list
	stack1.sortStack();
	cout << "Selection sort sorted linked list:" << endl;
	stack1.displayStack();


	return 0;
}
