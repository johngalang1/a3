void insert_item(Grocery_Item_Ptr &head){ 

    combine_items(head); 
    organize_list(head);

    return;
}

void combine_items(Grocery_Item_Ptr &head){ 
    int compare;
    
    Grocery_Item_Ptr temp3 = head; // temp3 is set to our head

    while (temp3!= NULL){ // until the link is done

        Grocery_Item_Ptr temp1 = temp3; // set temp1 to temp3
        Grocery_Item_Ptr temp2 = temp3->next; // set temp2 to be the next after temp

        while(temp2 != NULL){ //temp2 will go through each node in the list until it reaches a NULL

            compare = strncmp(temp3->name, temp2->name, SIZE); // checks if they're equal

            if (compare == 0){ 

                temp3->quantity += temp2->quantity;  // increment quantity
                temp1->next = temp2->next; //the node will connect to the node after the next node
                delete temp2; // then we delete the next node 
                temp2 = temp1->next;  //then we set this next node to be the next of our temp1 node

            } else{ 

                temp1 = temp2;     // temp1 is now at temp2
                temp2 = temp2->next; // temp2 will become the upcoming node
            }
        }
        temp3 = temp3->next; // iterate to the next node if there are any duplicates throughout the node
    }
    return;
}

void organize_list(Grocery_Item_Ptr &head){ 
    int counter = 0;
    Grocery_Item_Ptr current = head; 
    while(current!= NULL){ 
        counter++; 
        current = current->next;
    }
    Grocery_Item_Ptr temp1 = NULL, temp2 = NULL, temp3 = NULL; 
    int compare;

    for (int i=0; i < counter - 1; i++){   

        temp3 = head; 
        temp1 = temp3->next; 
        temp2 = temp1->next;

        for(int j = 0; j < counter - 2; j++){  

            compare = strncmp(temp1->name,temp2->name,SIZE); 

            if (compare < 0){ // If there the character is less than the next one, compare the next pair of nodes
                temp1 = temp1->next; 
                temp2 = temp2->next;
            } else {  //If there character is greater than the next one
                temp1->next = temp2->next; // Set the next node of temp1 to the next node of temp2
                temp2->next = temp3->next; // Set the next node of temp2 to the next node after the head
                temp3->next = temp2; // set the next node of the head towards temp2

                head->next = temp3->next; // now actually set head

                temp2 = temp1->next; // make temp2 to compare for the next node

            } 
        }
    }
    return;
}
