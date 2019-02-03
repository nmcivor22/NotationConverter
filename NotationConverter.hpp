#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include<iostream>
#include <string>
#include "NotationConverterInterface.hpp"

const char OPEN_PARANTH = '(';
const char CLOSE_PARANTH = ')';
const char MULT = '*';
const char DIV = '/';
const char ADD = '+';
const char SUB = '-';

class NotationConverter: public NotationConverterInterface{
    public:
    NotationConverter(){};
    ~NotationConverter(){
        while(head != NULL){
            removefront(); 
        }
    };
    std::string infixToPostfix(std::string inStr);
    std::string infixToPrefix(std::string inStr);
    std::string postfixToInfix(std::string inStr);
    std::string prefixToInfix(std::string inStr);
    std::string postfixToPrefix(std::string inStr);
    std::string prefixToPostfix(std::string inStr);

    private:
        struct Node {
            std::string op;
            Node* prev;
            Node* next;
        };
         Node* head = NULL;
         Node* tail = NULL;
        
        //Insert Node at front of List
        void frontinsert(std::string ch){
             if (head == NULL && tail == NULL)
             {
                 Node* newnode = new Node;
                newnode -> op = ch ; //fill the node stack to start with paranth
                newnode -> prev = NULL; //point new node to NULL
                newnode -> next = NULL;
                head = newnode; //point head to new node
                tail = newnode;  // point tail to new node*/
             }
             else {
                Node* newnode = new Node;
                newnode -> op = ch;
                newnode -> next = head;
                newnode -> prev = head -> prev;
                head -> prev = newnode; 
                head = newnode;
             }
        };

        //Remove node from front of list
        void removefront(){
            Node* old;
            old = head; 
            if (old -> next == NULL && old ->prev == NULL){
                head = NULL;
                tail = NULL;
                delete old;
            }
            else {
                head = old -> next;
                head -> prev = NULL; 
                delete old;
            }
        };

        //Insert Node at back of list
        void insertback(std::string c){
            Node* newnode = new Node;
            newnode ->op = c;
            newnode -> prev = tail; 
            newnode -> next = tail -> next;
            tail = newnode;
        };

        //Check for any invalid characters within the string
        void checkValidInp(std::string check){
            for(unsigned int i = 0; i < check.size(); i++){ //push prefix on stack
                if (check[i] < 'A' || (check[i] > 'Z' && check[i] < 'a') || check[i] > 'z'){
                    if (check[i] != MULT && 
                        check[i] != DIV &&  
                        check[i] != ADD &&  
                        check[i] != SUB && 
                        check[i] != OPEN_PARANTH && 
                        check[i] != CLOSE_PARANTH && 
                        check[i] != ' ')
                        throw std::invalid_argument("no2");
                }
            }
        };
};

#endif
