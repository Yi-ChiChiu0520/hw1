/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
/* Add a prototype for a helper function here if you need */
void splitHelper(Node*& in, Node*& odds, Node*& lastOdd, Node*& evens, Node*& lastEven); 

void split(Node*& in, Node*& odds, Node*& evens)
{
  Node* lastOdd = nullptr;
  Node* lastEven = nullptr;
  splitHelper(in, odds, lastOdd, evens, lastEven);
  in=nullptr; // Make sure in is null after recursion 
}

/* If you needed a helper function, write it here */
void splitHelper(Node*& in, Node*& odds, Node*& lastOdd, Node*& evens, Node*& lastEven) {
    if (in == nullptr) {
        // Base case: end of the input list
        return;
    }

    Node* nextNode = in->next; // Save the next node
    in->next = nullptr; // Disconnect the node from the input list

    if (in->value % 2 == 1){ // If in's value is odd
        // Odd case
        if (lastOdd != nullptr) { // If odds list is not empty
            lastOdd->next = in; // LastOdd should point to in 
        } else {
            odds = in; // If odds list is empty, first element should be in 
        }
        lastOdd = in; // LastOdd should be in because it is the last node 
    }
    else { // If in's value is even
        // Even case
        if (lastEven != nullptr) { // If evens list is not empty
            lastEven->next = in; // LastEven should point to in 
        } else {
            evens = in; // If evens list is empty, first element should be in 
        }
        lastEven = in; // LastEven should be in because it is the last node 
    }

    // Recursive call
    splitHelper(nextNode, odds, lastOdd, evens, lastEven);
}
