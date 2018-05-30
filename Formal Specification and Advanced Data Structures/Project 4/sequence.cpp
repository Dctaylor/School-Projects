//
//  sequence.cpp
//  David Taylor
//  COEN70L Lab 4
//
//
//

#include "sequence.h"
#include <cassert>

using namespace coen70;
namespace coen70 {
    sequence::sequence() {
        used = 0;
        current_index = -1;
    }

    void sequence::start() {
        if(used == 0)
            current_index = -1;
    
        current_index = 0;
    }

    void sequence::advance() {
        assert(is_item());
    
        ++current_index;
        if(current_index == used)
            current_index = -1;
    }

    void sequence::insert(const value_type& entry) {
        assert(size() < CAPACITY);
        size_type i;
    
        if(!is_item())
            current_index = 0;
    
        for(i = used; i > current_index; --i)
            data[i] = data[i-1];
    
        data[current_index] = entry;
        ++used;
    }

    void sequence::attach(const value_type& entry) {
        assert(size() < CAPACITY);
        size_type i;
    
        if(!is_item())
            current_index = used;
    
        for(i = used; i > current_index + 1; --i)
            data[i] = data[i-1];
    
        data[current_index] = entry;
        ++used;
    }

    void sequence::remove_current() {
        assert(is_item());
    
        size_type i;
        for(i = current_index; i < used; ++i)
            data[i-1] = data[i];
    
        --used;
    }

    sequence::size_type sequence::size() const {
        return used;
    }

    bool sequence::is_item() const {
        if(current_index < used && current_index >= 0)
            return true;
        else
            return false;
    }

    sequence::value_type sequence::current() const {
        assert(is_item());
        return data[current_index];
    }

    void sequence::insert_front(const value_type& entry) {
        assert(size() < CAPACITY);
        size_type i;
    
        if(used == 0)
            current_index = 0;
    
        for(i = used; i > 1; --i)
            data[i] = data[i-1];
    
        data[0] = entry;
        ++used;
    }

    void sequence::remove_front() {
        assert(used > 0);
        size_type i;
    
        for(i = 1; i < used; ++i)
            data[i-1] = data[i];
    
        current_index = 0;
        --used;
    }

    void sequence::attach_back(const value_type& entry) {
        assert(size_type() < CAPACITY);
        data[used] = entry;
        current_index = used;
        ++used;
    }

    void sequence::end() {
        if(used == 0)
            current_index = -1;
    
        current_index = used - 1;
    }

    sequence sequence::operator +=(const sequence& s2) {
        assert(size() + s2.size() <= CAPACITY);
        size_type i;
        size_type temp_used;
    
        for(i = 0; i < temp_used; ++i) {
            data[used] = data[i];
            ++used;
        }
    
        return *this;
    }

    sequence sequence::operator +(const sequence& s2) {
        assert(size() + s2.size() <= CAPACITY);
        sequence answer;
    
        answer += *this;
        answer += s2;
        return answer;
    }

    sequence::value_type sequence::operator[](sequence::size_type index) const {
        assert(index < used && index >= 0);
        return data[index];
    }
}











