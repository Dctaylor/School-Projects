//
//  sequence.h
//  David Taylor
//  COEN70L Lab 4
//
//
//

#ifndef sequence_h
#define sequence_h

#include <stdio.h>

namespace coen70 {
    class sequence{
    public:
        typedef double value_type;
        typedef int size_type;
        static const size_type CAPACITY = 50;
        
        /*
         Precondition: None
         Postcondition: The sequence has been initialized as an empty sequence.
         Big O: O(1)
         */
        sequence();
        
        /*
         Precondition: The sequence must have been initialized
         Postcondition: The first item on the sequence becomes the current item (but if the sequence is empty, then there is no current item).
         Big O: O(1)
         */
        void start();
        
        /*
         Precondition: is_item returns true
         Postcondition: If the current item was already the last item in the sequence, then there is no longer any current item. Otherwise, the new current item is the item immediately after the original current item.
         Big O: O(1)
         */
        void advance();
        
        /*
         Precondition: size() < CAPACITY
         Postcondition: A new copy of entry has been inserted in the sequence before the current item. If there was no current item, then the new entry has been inserted at the front of the sequence. In either case, the newly inserted item is now the current item of the sequence.
         Big O: O(n)
         */
        void insert(const value_type& entry);
        
        /*
         Precondition: size() < CAPACITy
         Postcondition: A new copy of entry has been inserted in the sequence after the current item.  If there was no current item, then the new entry has been attached to the end of the sequence.  In either case, the new inserted item is now the current item of the sequence.
         Big O: O(n)
         */
        void attach(const value_type& entry);
        
        /*
         Precondition: is_item returns true
         Postcondition: The current item has been removed from the sequence, and the item after this (if there is one) is now the new current item.
         Big O:O(n)
         */
        void remove_current();
        
        /*
         Precondition: None
         Postcondition: The return value is the number of items in the sequence.
         Big O: O(1)
         */
        size_type size() const;
        
        /*
         Precondition: Sequence object must be initialized
         Postcondition: A true return value indicates that there is a valid "current" item that may be retrieved by activating the current member function (listed below). A false return value indicates that there is no valid current item.
         Big O: O(1)
         */
        bool is_item() const;
        
        /*
         Precondition: is_item( ) returns true.
         Postcondition: The item returned is the current item in the sequence.
         Big O: O(1)
         */
        value_type current() const;
        
        /*
         Precondition: size() < CAPACITY
         Postcondition: A new copy of entry has been inserted at the front of the sequence. The new front item is now the current item of the sequence.
         Big O: O(n)
         */
        void insert_front(const value_type& entry);
        
        /*
         Precondition: The sequence cannot be empty (used > 0)
         Postcondition: The first item has been removed from the sequence, and the new front item is now the new current item.
         Big O: O(n)
         */
        void remove_front();
        
        /*
         Precondition: size() < CAPACITY
         Postcondition: A new copy of entry has been inserted at the end of the sequence. The new inserted item is now the current item of the sequence.
         Big O: O(1)
         */
        void attach_back(const value_type& entry);
        
        /*
         Precondition: None
         Postcondition: The last item in the sequence is now the current item.  If the sequence is empty, there is no current item
         Big O: O(1)
         */
        void end();
        
        /*
         Precondition: The sum of the sizes of both objects must be less than CAPACITY.
         Postcondition: A new sequence that contains the data of both the sequences is returned
         Big O: O(n)
         */
        sequence operator+(const sequence& s2);
        
        /*
         Precondition: The sum of the sizes of both objects must be less than CAPACITY.
         Postcondition: The sequence on the left of the left of the operator is returned now containing the data from the given arguement
         Big O: O(n)
         */
        sequence operator+=(const sequence& s2);
        
        /*
         Precondition: index < size() && index >=0
         Postcondition: The item returned is the item at the given index
         Big O: O(1)
         */
        value_type operator[](size_type index) const;
        
        
    private:
        value_type data[CAPACITY];
        size_type used;
        int current_index;
    };
}

#endif /* sequence_hpp */
