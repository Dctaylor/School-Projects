//
//  pqueue.cpp
//  
//
//  Created by david cameron taylor on 3/9/17.
//
//

#include "pqueue.h"
#include <cassert>
#include <cstdlib>

namespace coen70_lab9 {

    //Helper functions
    void list_clear(node*& head_ptr) {
        while (head_ptr != NULL) {
            node* remove_ptr;
            remove_ptr = head_ptr;
            head_ptr = head_ptr->link();
            delete remove_ptr;
        }
    }
    
    void list_copy(const node* source_ptr, node*& head_ptr) {
        head_ptr = NULL;
        
        if (source_ptr == NULL)
            return;
        
        head_ptr = new node(source_ptr->data(), source_ptr->priority(), head_ptr);
        
        source_ptr = source_ptr->link();
        node* previous_ptr = head_ptr;
        node* temp;
        while (source_ptr != NULL) {
            temp = new node(source_ptr->data(), source_ptr->priority(), previous_ptr->link());
            previous_ptr->set_link(temp);
            previous_ptr = previous_ptr->link( );
            source_ptr = source_ptr->link( );
        }
    }

    //Constructor
    PriorityQueue::PriorityQueue() {
        head_ptr = NULL;
        many_nodes = NULL;
    }
    
    //Copy Constructor
    PriorityQueue::PriorityQueue(const PriorityQueue& source) {
        list_copy(source.head_ptr, head_ptr);
        many_nodes = source.many_nodes;
    }
    
    //Destructor
    PriorityQueue::~PriorityQueue() {
        list_clear(head_ptr);
        many_nodes = 0;
    }
    
    //Insert function
    void PriorityQueue::insert(const Item& entry, unsigned int priority) {
        node* newNode = new node(entry, priority, NULL);
        if(head_ptr == NULL) {
            head_ptr = newNode;
            ++many_nodes;
            return;
        }
        
        if(priority > head_ptr->priority()) {
            newNode->set_link(head_ptr);
            head_ptr = newNode;
            ++many_nodes;
            return;
        }
        
        node* insert_ptr = head_ptr;
        while(insert_ptr->link() != NULL) {
            node *temp = insert_ptr->link();
            if(priority < temp->priority())
                insert_ptr = insert_ptr->link();
            
            else if(priority == temp->priority())
                insert_ptr = insert_ptr->link();
            
            else
                break;
        }
        
        newNode->set_link(insert_ptr->link());
        insert_ptr->set_link(newNode);
        ++many_nodes;
    }
    
    PriorityQueue::Item PriorityQueue::get_front() {
        assert(size() > 0);
        node* temp = head_ptr->link();
        Item data = head_ptr->data();
        delete head_ptr;
        head_ptr = temp;
        --many_nodes;
        return data;
    }
    
    void PriorityQueue::operator =(const PriorityQueue& source) {
        if(this == &source)
            return;
        
        list_clear(head_ptr);
        list_copy(source.head_ptr, head_ptr);
        many_nodes = source.many_nodes;
    }
}
