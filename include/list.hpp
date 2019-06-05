#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <iostream>

using size_type = unsigned long;

namespace sc {
    template <typename T>
    class list {
        private:
        struct Node {
            T data;         //<! Data field
            Node *prev;     //<! Pointer to the previous node in the list
            Node *next;     //<! Pointer to the next node in the list

            /// Basic constructor
            Node (const T &d = T(), Node *p = nullptr, Node *n = nullptr) : data{d}, prev{p}, next{n} { }
        };      

        public:
        class const_iterator {
            public:
                /// Default constructor that creates an nullptr.
                const_iterator () : current{nullptr} {}

                /// Return a reference to the object located at the position pointed by the iterator.
                const T &operator*() const { return *current; } // *it

                /// Advances the iterator to the next location within the list and returns itself after that.
                const_iterator &operator++() // ++it;
                {
                    current = current->next;
                    return current;
                }

                /// Advances the iterator to the next location within the list and returns itself before that.
                const_iterator operator++(int) // it++;
                {
                    const_iterator temp(current);
                    current = current->next;                    
                    return temp;
                }

                /// Backs the iterator to the previous location within the list and returns itself after that.
                const_iterator &operator--() // --it;
                {
                    current = current->prev;
                    return const_iterator(current);
                }

                /// Backs the iterator to the previous location within the list and returns itself before that.
                const_iterator operator--(int) // it--;
                {
                    const_iterator temp(current);
                    current = current->prev;
                    return temp;
                }

                /// Returns true if both iterators refer to same location within the list, and false otherwise.
                bool operator==(const const_iterator &rhs) const // it1 == it2
                {
                    return current == rhs.current;
                }

                /// Returns true if both iterators refer to differents location within the list, and false otherwise.
                bool operator!=(const const_iterator &rhs) const // it1 != it2
                {
                    return current != rhs.current;
                }

            protected:
                Node *current;                              //<! The pointer to the node data.
                const_iterator(Node *p) : current(p) {}     //<! Constructor that receives a pointer.
                friend class list<T>;                       //<! List can access members of iterator.
        };  
        
        class iterator {
            public:
                /// Default constructor that creates an nullptr.
                iterator() : current(nullptr) { }

                /// Return a const reference to the object located at the position pointed by the iterator.
                const T & operator* () const { return current->data; } // *it
                
                /// Return a reference to the object located at the position pointed by the iterator.
                T & operator* () { return current->data; }

                /// Advances the iterator to the next location within the list and returns itself after that.
                iterator operator++() { // ++it
                    current = current->next;
                    return iterator(current);
                }  

                /// Advances the iterator to the next location within the list and returns itself before that.
                iterator operator++(int n) {
                    iterator temp(current);
                    current = current->next;
                    return temp;                    
                }   

                /// Advances to the n-th successor node of the iterator and returns it.
                iterator operator+(int n) {
                    for (int i = 0; i < n; i++) {
                        current = current->next;
                    }

                    return current;
                }           
                
                /// Backs the iterator to the previous location within the list and returns itself after that.
                iterator &operator--() // --it
                {
                    current = current->prev;
                    return iterator(current);
                }

                /// Backs the iterator to the previous location within the list and returns itself before that.
                iterator operator--(int n) // it--
                {
                    iterator temp(current);
                    current = current->prev;
                    return temp;
                }    

                /// Returns the distance between the nodes (not between the adresses).
                size_type operator- (iterator rhs)
				{
					size_type dis = 0;
                    iterator cur(current);

                    while  (rhs != cur) {
                        dis++;
                        rhs++;
                    }
                    std::cout << "DIS: " << dis << std::endl;
					return dis;
				}

                /// Returns true if both iterators refer to same location within the list, and false otherwise.
                bool operator==(const iterator &rhs) const // it1 == it2
                {
                    return current == rhs.current;
                }

                /// Returns true if both iterators refer to differents location within the list, and false otherwise.
                bool operator!=(const iterator &rhs) const // it1 != it2
                {
                    return current != rhs.current;
                }    

            protected:
                Node *current;                              //<! The pointer to the node data.
                iterator(Node *p) : current(p) {}          //<! Constructor that receives a pointer.
                friend class list<T>;                       //<! List can access members of iterator.;
        };        

        public:
        /// Default constructor that creates an empty list.
        list () : SIZE{0}, head{new Node}, tail{new Node} {
            head->prev = nullptr;
            head->next = tail;
            tail->prev = head;
            tail->next = nullptr;
        }

        /// Constructs the list with count default-inserted instances of T.
        explicit list( size_type count ) : SIZE{count}, head{new Node}, tail{new Node} {
            head->prev = nullptr;
            tail->next = nullptr;

            if (SIZE > 0) {
                Node *prevNode = head;

                for (size_type i = 0; i < SIZE; i++) {
                    Node *newNode = new Node;
                    prevNode->next = newNode;
                    newNode->prev = prevNode;
                    prevNode = newNode;
                }

                prevNode->next = tail;
            } else {
                head->next = tail;
                tail->prev = head;
            }
        }

        /// Constructs the list with the contents of the range [first, last).
        template <typename InputIt>
        list (InputIt first, InputIt last) : SIZE{last - first}, head{new Node}, tail{new Node} {
            head->prev = nullptr;
            tail->next = nullptr;
            head->next = tail;
            tail->prev = head;

            Node *curNode = head;

            while (first != last) {
                Node *newNode = new Node;
                curNode->next = newNode;
                newNode->prev = curNode;
                curNode = curNode->next;
                newNode->data = *(first++);
                newNode->next = tail;
                tail->prev = newNode;
            }
        }

        /// Copy constructor. Constructs the list with the deep copy of the contents of other.        
        list (const list & other) : SIZE{other.size()}, head{new Node}, tail{new Node} {
            head->prev = nullptr;
            head->next = tail;
            tail->prev = head;
            tail->next = nullptr;

            Node *cp = other.head->next;
            Node *curNode = head;

            for (size_type i = 0; i < SIZE; i++) {
                Node *newNode = new Node;
                curNode->next = newNode;
                newNode->prev = curNode;
                curNode = curNode->next;
                newNode->data = (cp++)->data;
                newNode->next = tail;
                tail->prev = newNode;
            }            
        }

        /// Constructs the list with the contents of the initializer list init.
        list( std::initializer_list<T> ilist) : SIZE{ilist.size()}, head{new Node}, tail{new Node} {
            head->prev = nullptr;
            tail->next = nullptr;
            if (SIZE > 0) {
                Node *prevNode = head;

                for (size_type i = 0; i < SIZE; i++) {
                    Node *newNode = new Node;
                    prevNode->next = newNode;
                    newNode->data = *(ilist.begin() + i);
                    newNode->prev = prevNode;
                    prevNode = newNode;
                }

                prevNode->next = tail; 
                tail->prev = prevNode;
            } else {
                head->next = tail;
                tail->prev = head;
            }
        }

        ~list () {
            Node *curNode = head->next;

            while (curNode != nullptr) {
                delete curNode->prev;
                
                if (curNode->next == nullptr) {
                    Node *prevNode = curNode;
                    curNode = curNode->next;
                    delete prevNode;
                } else {
                    curNode = curNode->next;
                }
            }
        }

        /// Return the number of elements in the container.
        size_type size () const {
            return SIZE;
        }

        /// Remove all elements from the container.
        void clear () {
            Node *curNode = head->next;

            while (curNode->next != nullptr) {
                curNode = curNode->next;
                delete curNode->prev;
            }

            head->next = tail;
            tail->prev = head;

            SIZE = 0;
        }

        /// Returns true if the container contains no elements, and false otherwise.
        bool empty () {
            return SIZE == 0;
        }

        iterator begin () {
            return iterator(head->next);
        }

        iterator end () {
            return iterator(tail);
        }

        private:
        size_type SIZE;
        Node *head;
        Node *tail;  
    };
}

#endif