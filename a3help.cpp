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

