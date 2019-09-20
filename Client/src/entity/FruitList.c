//
// Created by Jesus on 19/9/2019.
//
#include "FruitList.h"

void insertFirst(struct fruit* fruit) {
    //create a link
    struct fruitNode *link = (struct fruitNode*) malloc(sizeof(struct fruitNode));

    link->fruit = fruit;

    //point it to old first cocodrileNode
    link->next = head;

    //point first to new first cocodrileNode
    head = link;
}

//find a link with given key
struct fruitNode* find(int key) {

    //start from the first link
    struct fruitNode* current = head;

    //if list is empty
    if(head == NULL) {
        return NULL;
    }

    //navigate through list
    while(current->fruit->key != key) {

        //if it is last fruit
        if(current->next == NULL) {
            return NULL;
        } else {
            //go to next link
            current = current->next;
        }
    }

    //if data found, return the current Link
    return current;
}

struct fruit* delete(int key) {

    //start from the first link
    struct fruitNode* current = head;
    struct fruitNode* previous = NULL;

    //if list is empty
    if(head == NULL) {
        return NULL;
    }

    //navigate through list
    while(current->fruit->key != key) {

        //if it is last fruit
        if(current->next == NULL) {
            return NULL;
        } else {
            //store reference to current link
            previous = current;
            //move to next link
            current = current->next;
        }
    }
struct fruit* delete(int key)
    //found a match, update the link
    if(current == head) {
        //change first to point to next link
        head = head->next;
    } else {
        //bypass the current link
        previous->next = current->next;
    }

    return current;
}

struct fruitNode* returnHead() {
    return head;
}