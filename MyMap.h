// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.
#include <iostream>
#include <string>

template<typename KeyType, typename ValueType>
class MyMap
{
public:
	MyMap()
    :m_items(0), m_root(nullptr)
    {}
    
    ~MyMap()
    {   
        clear(); // calls on the clear function
    }    
        
    void associate(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr)
        {
            m_root = new Node;
            m_root->m_left = nullptr;
            m_root->m_right = nullptr;
            m_root->m_key = key;
            m_root->m_value = value;
            m_items++; // increments the number of items
        }
        else
        {
            associateHelper(m_root, key, value); // calls on the associate Helper function
        }
    }
	  // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const
    {
        Node * ptr = findNode(key, m_root);
        if(ptr != nullptr)
            return &(ptr->m_value);
        else
            return nullptr;
    }
    

    	  // for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
	}
    void clear()
    {
        helpDestructor(m_root); // calls on helpDestrcutor with m_root as input
    }
    int size() const
    {
        return m_items;
    }

	  // C++11 syntax for preventing copying and assignment
	MyMap(const MyMap&) = delete;
	MyMap& operator=(const MyMap&) = delete;

private:
    struct Node
    {
        KeyType m_key;
        ValueType m_value;
        Node * m_left = nullptr; 
        Node * m_right = nullptr;
    };
    
    int m_items;
    Node * m_root;
    Node * findNode(const KeyType& key, Node * temp) const // finds the node associated with the spcific key/ helper function
    {
        if (temp == nullptr)
            return nullptr;
        else if (temp->m_key == key)
        {
            return temp;
        }
        else if (key>temp->m_key)
        {
            return findNode(key, temp->m_right);
        }
        else if (key < temp->m_key)
        {
            return findNode(key, temp->m_left);
        }
        
        return nullptr;
    }
    void helpDestructor(Node * temp) // helper function for clear, which later helps the destructor
    {
        if(temp == nullptr) 
        return;
        helpDestructor(temp->m_left);
        helpDestructor(temp->m_right);
        
        delete temp;
    }
    void associateHelper(Node* temp, const KeyType& key, const ValueType& value) // helper function for add
    {
        if(temp != nullptr)
        {
            if(temp->m_key == key)
            {
                temp->m_value = value;
                return;
            }
            
            Node* next; 
            if(key < temp->m_key)
            {
                next = temp->m_left;
                if(temp->m_left == nullptr)
                {
                    temp->m_left = new Node;
                    m_items++;
                    temp->m_left->m_value = value;
                    temp->m_left->m_key = key;
                    temp->m_left->m_left = nullptr;
                    temp->m_left->m_right = nullptr;
                    return;
                }
            }
            else
            {
                next = temp->m_right;
                if(temp->m_right == nullptr) // checks if temp's right pointer is a nullptr or not
                {
                    temp->m_right = new Node;
                    m_items++;
                    temp->m_right->m_value = value;
                    temp->m_right->m_key = key;
                    temp->m_right->m_left = nullptr;
                    temp->m_right->m_right = nullptr;
                    return;
                }
            }
            associateHelper(next, key, value); // calls associate helper recursively
        }
    }
    
};
