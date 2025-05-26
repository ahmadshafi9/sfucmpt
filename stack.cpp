#include "Stack.h"
#include "LinkedList.h" // Ensure LinkedList definitions are available
#include <iostream>      // For displayStack
#include <limits>        // For potentially returning specific error values

// Constructor
Stack::Stack() {
    // The LinkedList member 'list' is automatically constructed
    // using its default constructor.
}

// Destructor
Stack::~Stack() {
    // The LinkedList member 'list' is automatically destructed
    // when the Stack object goes out of scope, calling LinkedList's destructor.
}

// Return the current height of the stack
int Stack::height() const {
    return list.lengthList(); // Use LinkedList's length method
}

// Push a value onto the top of the stack
void Stack::push(double val) {
    // As per instructions: "adding to the top of the stack is appending to the linked list"
    list.appendListNode(val);
}

// Pop a value from the top of the stack
double Stack::pop() {
    if (list.isEmpty()) {
        // Driver output shows 0 for popping an empty stack
        return 0.0;
    }
    // As per instructions: "The top of the stack is the last node in the list"
    // We need to remove the last node (at index = length)
    int lastNodeIndex = list.lengthList();
    return list.removeListNodeN(lastNodeIndex);
}

// Check if the stack is empty
bool Stack::isEmpty() const {
    return list.isEmpty(); // Use LinkedList's isEmpty method
}

// Display the stack content (bottom to top)
void Stack::displayStack() const {
    list.displayList(); // Use LinkedList's display method
    std::cout << std::endl; // Ensure newline after display as per driver output
}

// Sort the stack using the LinkedList's selection sort
void Stack::sortStack() {
    list.selectionSort(); // Call LinkedList's sort method
}