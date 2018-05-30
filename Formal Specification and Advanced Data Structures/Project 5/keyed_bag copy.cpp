//
//  keyed_bag.cpp
//  David Taylor
//  COEN70L Lab 5s
//
//
//

#include "keyed_bag.h"
#include <cstdlib>
#include <string>
#include <cassert>
using namespace coen70_lab;
namespace coen70_lab {
    bool keyed_bag::erase(const key_type& key) {
        size_type i;
        size_type k;
        for(i = 0; i < used; i++) {
            if (key == keys[i]) {
                data[i] = data[used];
                keys[i] = keys[used];
                --used;
                return true;
            }
        }
        
        return false;
    }
    
    void keyed_bag::insert(const value_type& entry, const key_type& key) {
        assert((size() < CAPACITY) && !has_key(key));
        
        keys[used] = key;
        data[used] = entry;
        ++used;
    }
    
    keyed_bag keyed_bag::operator +=(const keyed_bag& addend) {
        assert((size() + addend.size() < CAPACITY) && !hasDuplicateKey(addend));
        size_type i;
        size_type j = 0;
        
        
        for(i = used; i < used + addend.used; ++i) {
            keys[i] = addend.keys[j];
            data[i] = addend.data[j];
            ++j;
        }
        
        used+=addend.used;
        return *this;
    }
    
    bool keyed_bag::has_key(const key_type& key) const {
        size_type i;
        for(i = 0; i < used; ++i) {
            if(keys[i] == key)
                return true;
        }
        
        return false;
    }
    
    keyed_bag::value_type keyed_bag::get(const key_type& key) const {
        assert(has_key(key));
        size_type i;
        
        for(i = 0; i < used; ++i)
            if(keys[i] == key)
                return data[i];
    }
    
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        size_type i;
        for(i = 0; i < used; i++)
            if(otherBag.has_key(keys[i]))
                return true;
        
        return false;
    }
    
    keyed_bag::size_type keyed_bag::count(const value_type& target) const {
        size_type counter;
        size_type i;
        
        for(i = 0; i < used; ++i)
            if(data[i] == target)
                ++counter;
        
        return counter;
    }
    
    
    keyed_bag operator+(const keyed_bag& b1, const keyed_bag& b2) {
        assert(b1.size() + b2.size() < keyed_bag::CAPACITY);
        keyed_bag newBag;
        newBag+=b1;
        newBag+=b2;
        return newBag;
    }
}
