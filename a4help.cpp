#include <iostream>
#include <fstream>
#include <cstring>
#include "GroceryList.h"

using namespace std;


GroceryList::GroceryList(){ // when a object is created

    head.next = &tail; // head is an actual node
    tail.prev = &head; // tail is an actual node
}

GroceryList::~GroceryList(){ // activates once the program finishes

    GroceryPtr headPtr = &head; // create a pointer to the head dummy node
    headPtr = headPtr->next;
    GroceryPtr temp = NULL;

    while (headPtr != &tail) { // deletes all nodes stored on the heap until it pointer reaches the dummy tail node

        temp = headPtr;
        headPtr = headPtr->next;
        delete temp;
    }

    head.next = &tail;
    tail.prev = &head;
}

/*

    contains: Takes a name as an argument and searches the grocery list
              to determine if that name is in the list. It does this by calling
              the search function with a pointer to the head of the list and setting the
              found variable to true if the name is found in the list.
              The function returns the value of found,
              indicating whether or not the name was found in the list.

*/

bool GroceryList::contains(const NAME aName){

    GroceryPtr headPtr = &head; // points at dummy node
    bool found;
    search(aName, headPtr, found);

    return found;

}

/*
    getQuantity: Takes a name
                 It first initializes a pointer headPtr to point to the dummy head node of the list
                 and a boolean variable found to false. It then calls the search function to find
                 the grocery item in the list with the given NAME and updates the found variable accordingly.
                 Finally, it returns the quantity value of the grocery item if found is true,
                 which is pointed to by the headPtr pointer.
*/

int GroceryList::getQuantity(const NAME aName){
    GroceryPtr headPtr = &head;
    bool found;
    search(aName, headPtr, found);

    return headPtr->quantity;

}

/*
    updateQuantity: Takes a name and quantity.
                    The function first creates a pointer headPtr
                    that points to the dummy node of the list.
                    It then uses the search helper function to find if the item exists in the list.
                    If the item is found, the function adds the input quantity to the existing quantity of the node.
                    If the item is not found, the function does nothing.
*/

void GroceryList::updateQuantity(const NAME aName, int quantity){

    GroceryPtr headPtr = &head; // points at dummy node
    bool found;
    search(aName, headPtr, found);
    if(found)
    {
        headPtr->quantity += quantity;
    }
}

/*

    insertItem: Takes the name and quantity of an item and
                creates a list in sorted order
                while each entry of an item remains sorted

                Details:
                If the list is empty, it creates a new node
                and makes it the head and tail of the list.
                If the list is not empty, the function traverses through the
                list to find the appropriate location to insert the new node,
                based on the alphebtical ordering of the names. Once the appropriate location is found,
                the new node is inserted into the list and
                the pointers of the adjacent nodes are updated accordingly.

*/

void GroceryList::insertItem(const NAME aName, int quantity){
// creates a node for inserting items

    GroceryPtr newNode = NULL; // initializes a node poitner

    GroceryPtr headPtr = &head; // sets the adress of head
    GroceryPtr tailPtr = &tail; // sets the adress of tail

    newNode = new GroceryNode; // creates a new node
    newNode->quantity = quantity; // stores the quantity
    strncpy(newNode->name, aName, MAX_ITEM_NAME_LEN); // stores the name

    if (head.next == &tail && tail.prev == &head){ // if the item is the first entry to place in the list
        head.next = newNode;
        tail.prev = newNode;

        newNode->prev = &head;
        newNode->next = &tail;

    } else // if there is already an item in the list
    {
        if(strncmp(newNode->name, head.next->name, MAX_ITEM_NAME_LEN) < 0){ // if the new item is less than the node next to the head
            head.next->prev = newNode;

            newNode->next = head.next;
            newNode->prev = &head;

            head.next = newNode;
        } else // if the item is not less than the node next to the head
        {
            headPtr = headPtr->next; // points at the next node from the dummy head node

            while(headPtr != tailPtr && (strncmp(newNode->name, headPtr->name, MAX_ITEM_NAME_LEN) >= 0))

            {// loop through the list to find the first iteration where the item is less than the next item
                headPtr = headPtr->next;
            }

            if (headPtr == tailPtr){

                newNode->prev = tail.prev;
                tail.prev->next = newNode;

                tail.prev = newNode; // set the previous dummy node to the new node
                newNode->next = &tail;

            } else
            {
                newNode->prev = headPtr->prev;
                headPtr->prev->next = newNode;

                headPtr->prev = newNode;
                newNode->next = headPtr;
            }
        }
    }
}

/*
    removeItem: Takes a name
                Remove an item from the grocery list given its name.
                Returns true if the item was found and removed successfully, and false otherwise.
                It uses the search helper function to look for the item in the list, and if found,
                removes it by updating the pointers of the neighboring nodes and deleting the node.
                If the item is not found, the function returns false.
*/


bool GroceryList::removeItem(const NAME aName){
    GroceryPtr headPtr = &head;

    bool found;
    search(aName, headPtr, found);
    if (found){

        headPtr->prev->next = headPtr->next;
        headPtr->next->prev = headPtr->prev;

        delete headPtr;
        return true;

    } else
    {
        return false;
    }
}

/*
    write: Takes in a ofstream out
           Writes in the entire contents of the list
           into an output file
           it iterates through each node until it reaches the tail
*/

void GroceryList::write(ostream &out){

    GroceryPtr headPtr = &head;
    headPtr = headPtr->next;
    if ((head.next == &tail) && (tail.prev == &head)){
        out << "Empty grocery list" << endl;
    }else{

        while (headPtr != &tail){
            out << headPtr->quantity << " " << headPtr->name << endl;
            headPtr = headPtr->next;
        }
    }
    return;
}

/*
 *
 *     search     takes a name
 *                the grocery list is search for this name and if it is found,
 *                the boolean, found, parameter is set to true and the pointer,
 *                here, is set to point to the node containing the name;
 *                otherwise if the name is not found, the found parameter is
 *                set to false and here is set to point to the node with the
 *                name that would follow the name being searched for,
 *                i.e. the name’s alphabetic successor.
 *
 *                Details:
 *                Since the list can be traversed in either direction, this
 *                function will start searching from the head node for names
 *                that start with the letters 'a' through 'm'; vthe search will
 *                start from the tail node for names starting with the letters
 *                'n' through 'z'.
 *
 */

void GroceryList::search(const NAME aName, GroceryPtr &here, bool &found) const{ // helper function for public members
    found = false;

    if (strncmp(aName,"Marbles",MAX_ITEM_NAME_LEN) <= 0){
        here = here->next; // move to actual first node

        while(here != &tail && !found){
            if(strncmp(here->name, aName, MAX_ITEM_NAME_LEN) == 0){
                found = true;
                return;
            }

            here = here->next;
        }

    }else{

        here = tail.prev; // move to the actual last node

        while(here != &head && !found){
            if(strncmp(here->name, aName, MAX_ITEM_NAME_LEN) == 0){
                found = true;
                return;
            }
            here = here->prev;
        }
    }
    return;
}
