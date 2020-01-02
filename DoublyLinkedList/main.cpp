//
//  main.cpp
//  DoublyLinkedList
//
//  Created by adeeb mohammed on 15/12/19.
//  Copyright © 2019 adeeb mohammed. All rights reserved.
//

#include <iostream>
/*
 various operations in a doubly linked list
 
*/

class Node{
public:
    int value;
    Node *prev;
    Node *next;
    Node(int value){
        this->value = value;
        this->prev  = NULL;
        this->next  = NULL;
    }
};

class DoublyLinkedList{
public:
    Node *head;
    Node *tail;
    
    DoublyLinkedList(){
        this->head = NULL;
        this->tail = NULL;
    }
   
   //setting the head node of the doubly linked list
    // space complexity o(1) and time complexity o(1)
   void setHead(Node *node) {
       if(this->head == NULL){
           this->head = node;
           this->tail = node;
           return;
       }
       this->insertBefore(this->head, node);
   }

   // function for setting the tail node
   void setTail(Node *node) {
       if(this->tail == NULL){
           setHead(node);
           return;
       }
       this->insertAfter(this->tail, node);
   }
    
  //inserting a node before o(1) space complexity
    /*
     this function aims do the following things
   a node can be inserted before any node,
             whether it is acutally exisiting in the same linked list
             means if its next and prev pointers having anyother relationship,
             we shall remove that relationship gracefully. this way we can avoid
             the loop behaviour inside a linked list
             
             1) check whether the linked list has only one node and
                we are going to insert again
             2) remove the exisiting relationship of the node
             3) assign the next and previous node of the nodetoInsert
             4) assign the next pointer of the previous node of the current node
             5) assign the previous pointer of the current node as nodeToInsert
    */
   void insertBefore(Node *node, Node *nodeToInsert) {
       // head and tail node is same as the nodeToInsert
       if(this->head == nodeToInsert && this->tail == nodeToInsert){
           return;
       }
       // remove the existing relationships gracefully from the new node
       remove(nodeToInsert);
       nodeToInsert->next = node;
       nodeToInsert->prev = node->prev;
       // check whether the new node is a head node
       if(node->prev == NULL){
           this->head = nodeToInsert;
       }else{
           node->prev->next = nodeToInsert;
       }
       node->prev = nodeToInsert;
   }

   // here we are adding the node after a node
   // this is just opposite to insertBefore function
   void insertAfter(Node *node, Node *nodeToInsert) {
       // there is only one node and we are inserting the node again
       if(this->head == nodeToInsert && this->tail == nodeToInsert){
           return;
       }
       remove(nodeToInsert);
       // set the next and prev node of the new node
       nodeToInsert->prev = node;
       nodeToInsert->next = node->next;
       //check whether the new node is a tail node
       if(node->next == NULL){
           this->tail = nodeToInsert;
       }else{
           node->next->prev = nodeToInsert;
       }
       node->next = nodeToInsert;
   }

   // time complexity o(n) and space complexity o(1)
   void insertAtPosition(int position, Node *nodeToInsert) {
       // condition for setting the head node
       if(1 == position){
           setHead(nodeToInsert);
           return;
       }
       int currentPosition = 1;
       Node *node = this->head;
       while((currentPosition++ != position) && (node != NULL)){
           node = node->next;
        }
       // ensure this is not a tail node
       if(node != NULL){
           insertBefore(node, nodeToInsert);
       }else{
           setTail(nodeToInsert);
       }
   }
    
   // this function will remove all the node with a particular value
   void removeNodesWithValue(int value) {
       Node * node = this->head;
       while(node != NULL){
           Node *nodeToRemove = node;
           node = node->next;
           if(nodeToRemove->value == value){
               remove(nodeToRemove);
           }
       }
   }

   void remove(Node *node) {
       if(this->head == node){
           this->head = this->head->next;
       }
       if(this->tail == node){
           this->tail = this->tail->prev;
       }
       removeNodeBindings(node);
   }

    // function to check whehter a value exists in the
    // linked list
    bool containsNodeWithValue(int value) {
        Node *node = this->head;
        while(node != NULL){
            if(node->value == value){
                return true;
            }
            node = node->next;
        }
        return false;
    }
    // function for removing the prev and next binding of a node
    void removeNodeBindings(Node *node){
        if(node->prev != NULL){
            node->prev->next = node->next;
        }
        if(node->next != NULL){
            node->next->prev = node->prev;
        }
        node->next = NULL;
        node->prev = NULL;
    }
    
    // additional functiosn defined for debug purpose
 
    void traverseFront(){
        Node *node = this->head;
        while(node != NULL ){
            std::cout << node->value << " ";
            node = node->next;
        }
    }
    
    void traverseBack(){
        Node *node = this->tail;
        while(node != NULL){
            std::cout << node->value << " ";
            node = node->prev;
        }
    }
    
};

int main(int argc, const char * argv[]) {
    
    std::cout << "Program for implementing doubly linked list"<<std::endl;
    DoublyLinkedList *pDoublyLinkedList = new DoublyLinkedList();
    
    //test value for setting the head node
    Node *headNode = new Node(1);
    Node *oneNode = new Node(5);
    pDoublyLinkedList->setHead(headNode);
    pDoublyLinkedList->insertBefore(headNode, oneNode);
    std::cout << "Traverse Front:" ;
    pDoublyLinkedList->traverseFront();
    std::cout << std::endl;
    std::cout << "Traverse Back:" ;
    pDoublyLinkedList->traverseBack();
    std::cout << std::endl;
    
    if(pDoublyLinkedList != NULL){
        delete pDoublyLinkedList;
    }
    
    
    return 0;
}
