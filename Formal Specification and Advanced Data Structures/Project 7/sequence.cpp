//
//  sequence.cpp
//  David Taylor
//  COEN70L Lab 7
//
//
//

#include "sequence.h"
#include <cassert>
#include <cstdlib>


namespace coen70_lab7 {
    // CONSTRUCTORS and DESTRUCTOR
    sequence::sequence( ) {
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
        
    }
    
    sequence::sequence(const sequence& source) {
        many_nodes = source.many_nodes;
        
        if(source.cursor == NULL) {
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            cursor = NULL;
            precursor = NULL;
        }
        else if(source.cursor == head_ptr) {
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            start();
        }
        else {
            list_piece(source.head_ptr, source.precursor, head_ptr, precursor);
            list_piece(source.cursor, source.tail_ptr, cursor, tail_ptr);
            precursor->set_link(cursor);
        }
    }
    
    sequence::~sequence( ) {
        list_clear(head_ptr);
    }

    // MODIFICATION MEMBER FUNCTIONS
    void sequence::start( ) {
        if(many_nodes == 0) {
            cursor = NULL;
            precursor = NULL;
            return;
        }
        
        cursor = head_ptr;
        precursor = NULL;
    }
    
    void sequence::end() {
        size_t pretail;
        if(many_nodes == 0) {
            cursor = NULL;
            precursor = NULL;
            return;
        }
        
        cursor = tail_ptr;
        pretail = list_length(head_ptr) - 1;
        precursor = list_locate(head_ptr, pretail);
    }

    void sequence::advance( ) {
        assert(is_item());
        if(cursor == tail_ptr) {
            cursor = NULL;
            precursor = NULL;
            return;
        }
        
        cursor = cursor->link();
        precursor = precursor->link();
    }

    void sequence::insert(const value_type& entry) {
        if(cursor == NULL)
            list_head_insert(head_ptr, entry);
        
        else
            list_insert(precursor, entry);
        
        cursor = precursor->link();
    }

    void sequence::attach(const value_type& entry) {
        if(cursor == NULL) {
            end();
            list_insert(cursor, entry);
        }
        
        else
            list_insert(cursor, entry);
        
        precursor = cursor;
        cursor = cursor->link();
    }
    
    void sequence::operator =(const sequence& source) {
        if(this == &source)
            return;
        many_nodes = source.many_nodes;
        
        if(source.cursor == NULL) {
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            cursor = NULL;
            precursor = NULL;
        }
        else if(source.cursor == head_ptr) {
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            start();
        }
        else {
            list_piece(source.head_ptr, source.precursor, head_ptr, precursor);
            list_piece(source.cursor, source.tail_ptr, cursor, tail_ptr);
            precursor->set_link(cursor);
        }
    }
    
    void sequence::remove_current( ) {
        assert(is_item());
        node *temp;
        if(cursor == NULL)
            return;
        
        if(cursor == head_ptr) {
            list_head_remove(head_ptr);
            start();
            return;
        }
        
        if(cursor == tail_ptr) {
            tail_ptr = precursor;
            delete cursor;
            end();
            return;
        }
        
        temp = cursor->link();
        list_remove(precursor);
        cursor = temp;
    }
    // CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size( ) const {
        return list_length(head_ptr);
    }
    
    bool sequence::is_item( ) const {
        if(cursor != NULL)
            return true;
        return false;
    }
    
    sequence::value_type sequence::current( ) const {
        assert(is_item());
        return cursor->data();
    }

}