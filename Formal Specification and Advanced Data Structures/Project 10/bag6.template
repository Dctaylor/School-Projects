// ----------------------
// Implementation section
#include <cassert>

namespace scu_coen70_10
{

    //ToolKit Functions
    

    
    template <class Item>
    void bst_remove_max(binary_tree_node<Item>*& root_ptr, Item& removed)
    // Precondition: root_ptr is a root pointer of a non-empty binary
    // search tree.
    // Postcondition: The largest item in the binary search tree has been
    // removed, and root_ptr now points to the root of the new (smaller)
    // binary search tree. The reference parameter, removed, has been set
    // to a copy of the removed item.
    {
        binary_tree_node<Item>* oldroot_ptr;
        assert(root_ptr != NULL);
        
        if(root_ptr->right() == NULL) {
            removed = root_ptr->data();
            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->left();
            delete oldroot_ptr;
        }
        else
            bst_remove_max(root_ptr->right(), removed);
    }
    
    template <class Item>
    bool bst_remove(binary_tree_node<Item>*& root_ptr, const Item& target)
    // Precondition: root_ptr is a root pointer of a binary search tree
    // or may be NULL for an empty tree).
    // Postcondition: If target was in the tree, then one copy of target
    // has been removed, and root_ptr now points to the root of the new
    // (smaller) binary search tree. In this case the function returns true.
    // If target was not in the tree, then the tree is unchanged (and the
    // function returns false).
    {
        binary_tree_node<Item> *oldroot_ptr;
        
        if (root_ptr == NULL)
        {   // Empty tree
            return false;
        }
        
        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree
            // Note: Any change made to root_ptr->left by this recursive
            // call will change the actual left pointer (because the return
            // value from the left() member function is a reference to the
            // actual left pointer.
            return bst_remove(root_ptr->left( ), target);
        }
        
        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree
            // Note: Any change made to root_ptr->right by this recursive
            // call will change the actual right pointer (because the return
            // value from the right() member function is a reference to the
            // actual right pointer.
            return bst_remove(root_ptr->right( ), target);
        }
        
        if (root_ptr->left( ) == NULL)
        {   // Target was found and there is no left subtree, so we can
            // remove this node, making the right child be the new root.
            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->right();
            delete oldroot_ptr;
            return true;
        }
        
        // If code reaches this point, then we must remove the target from
        // the current node. We'll actually replace this target with the
        // maximum item in our left subtree.
        // Note: Any change made to root_ptr->left by bst_remove_max
        // will change the actual left pointer (because the return
        // value from the left() member function is a reference to the
        // actual left pointer.
        bst_remove_max(root_ptr->left( ), root_ptr->data( ));
        return true;
    }
    
    template <class Item>
    typename bag<Item>::size_type bst_remove_all
    (binary_tree_node<Item>*& root_ptr, const Item& target)
    // Precondition: root_ptr is a root pointer of a binary search tree
    // or may be NULL for an empty tree).
    // Postcondition: All copies of target have been removed from the tree
    // has been removed, and root_ptr now points to the root of the new
    // (smaller) binary search tree. The return value tells how many copies
    // of the target were removed.
    {
        /** STUDENT WORK
         ** Note: This implementation is similar to bst_remove, except that
         ** all occurrences of the target must be removed, and the return
         ** value is the number of copies that were removed.
         */
        
        binary_tree_node<Item> *oldroot_ptr;
        
        if (root_ptr == NULL)
        {   // Empty tree
            return 0;
        }
        
        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree
            return bst_remove_all(root_ptr->left(), target);
        }
        
        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree
            return bst_remove_all(root_ptr->right(), target);
        }
        
        if (root_ptr->left( ) == NULL)
        {   // Target was found and there is no left subtree, so we can
            // remove this node, making the right child be the new root.
            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->right( );
            delete oldroot_ptr;
            return 1;
        }
        
        // If code reaches this point, then we must remove the target from
        // the current node. We'll actually replace this target with the
        // maximum item in our left subtree. We then continue
        // searching for more copies of the target to remove.
        // This continued search must start at the current root (since
        // the maximum element that we moved up from our left subtree
        // might also be a copy of the target).
        bst_remove_max(root_ptr->left(), root_ptr->data());
        return 1 + bst_remove_all(root_ptr, target);
        
    }
    
    //MEMBER FUNCTIONS
    template <class Item>
    bag<Item>::bag() {
        root_ptr = NULL;
    }

    template <class Item>
    bag<Item>::bag(const bag<Item>& source)
    // Library facilities used: bintree.h
    {
        root_ptr = tree_copy(source.root_ptr);
    }
    
    template <class Item>
    bag<Item>::~bag( )
    // Header file used: bintree.h
    {
        tree_clear(root_ptr);
    }
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::size( ) const
    // Header file used: bintree.h
    {
        return tree_size(root_ptr);
    }
    
    
    template <class Item>
    void bag<Item>::insert(const Item& entry)
    // Header file used: bintree.h
    {
        binary_tree_node<Item> *cursor = root_ptr;
        bool done = false;
        
        if (root_ptr == NULL)
        {
            root_ptr = new binary_tree_node<Item>(entry);
            return;
        }
        
        do
        {
            if (cursor->data( ) >= entry)
            {   // Go left
                if(cursor->left() == NULL) {
                    cursor->left() = new binary_tree_node<Item>(entry);
                    done = true;
                }
                cursor = cursor->left();
            }
            else
            {   // Go right
                if(cursor->right() == NULL) {
                    cursor->right() = new binary_tree_node<Item>(entry);
                    done = true;
                }
                cursor = cursor->right();
            }
            
        } while (!done);
    }
    
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::count(const Item& target) const
    {
        size_type answer = 0;
        binary_tree_node<Item> *cursor;
        
        cursor = root_ptr;
        while(cursor != NULL) {
            if(cursor->data() > target)
                cursor = cursor->left();
            
            else if(cursor->data() < target)
                cursor = cursor->right();
            
            else {
                ++answer;
                cursor = cursor->left();
            }
        }
        
        return answer;
    }
    
    template <class Item>
    typename bag<Item>::size_type bag<Item>::erase(const Item& target)
    {
        return bst_remove_all(root_ptr, target);
    }
    
    template <class Item>
    bool bag<Item>::erase_one(const Item& target)
    {
        return bst_remove(root_ptr, target);
    }
    
    template <class Item>
    void bag<Item>::operator =(const bag<Item>& source)
    // Header file used: bintree.h
    {
        if(this == &source)
            return;
        
        tree_clear(root_ptr);
        insert_all(source.root_ptr);
    }
    
    template <class Item>
    void bag<Item>::operator +=(const bag<Item>& addend)
    {
        if (root_ptr == addend.root_ptr)
        {
            bag<Item> copy = addend;
            insert_all(copy.root_ptr);
        }
        else
            insert_all(addend.root_ptr);
    }
    
    template <class Item>
    bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2)
    {
        bag<Item> answer = b1;
        answer += b2;
        return answer;
    }
    
    template <class Item>
    void bag<Item>::insert_all(binary_tree_node<Item>* addroot_ptr)
    // Precondition: addroot_ptr is the root pointer of a binary search tree that
    // is separate for the binary search tree of the bag that activated this
    // method.
    // Postcondition: All the items from the addroot_ptr's binary search tree
    // have been added to the binary search tree of the bag that activated this
    // method.
    {
        if (addroot_ptr != NULL)
        {
            insert(addroot_ptr->data( ));
            insert_all(addroot_ptr->left( ));
            insert_all(addroot_ptr->right( ));
        }
    }
}
