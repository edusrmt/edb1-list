#ifndef LIST_H
#define LIST_H

#include <initializer_list>

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
        class const_iterator
        {
        public:
            /// Default constructor that creates an nullptr.
            const_iterator()
            {
                current = nullptr;
            }

            /// Returns a value from the iterator pointer.
            const T &operator*() const
            {
                return *current;
            }

            /// Advances the iterator to the next location within the list and returns itself before that.
            const_iterator &operator++() // ++it;
            {
                const_iterator temp = *this;
                current++;
                return temp;
            }

            /// Advances the iterator to the next location within the list and returns itself after that.
            const_iterator operator++(int n) // it++;
            {
                current++;
                return *this;
            }

            /// Backs the iterator to the previous location within the list and returns itself before that.
            const_iterator &operator--() // --it;
            {
                const_iterator temp = *this;
                current--;
                return temp;
            }

            /// Backs the iterator to the previous location within the list and returns itself after that.
            const_iterator operator--(int n) // it--;
            {
                current--;
                return *this;
            }

            /// Returns true if both iterators refer to same location within the list, and false otherwise.
            bool operator==(const const_iterator &rhs) const
            {
                return (current - rhs.current) == 0;
            }

            /// Returns true if both iterators refer to differents location within the list, and false otherwise.
            bool operator!=(const const_iterator &rhs) const
            {
                return (current - rhs.current) != 0;
            }

        protected:
            Node *current;                              //<! The pointer to the node data.
            const_iterator(Node *p) : current(p) {}
            friend class list<T>;
        };  

        
        class iterator : public const_iterator
        {
        public:
            iterator() : const_iterator()
            { /* Empty */ }
            const T &operator*() const
            {
                return this->current.clear();
            }
            
            T &operator*()
            {
                return this->current->data;  
            }
            iterator &operator++()
            {
                iterator temp = *this;
                (this->current)++;
                return temp;
            } 

            iterator operator++(int n)
            {
                (this->current)++;
                return *this;
            }
            
            iterator &operator--()
            {
                iterator temp = *this;
                (this->current)--;
                return temp;
            }

            iterator operator--(int n)
            {
                (this->current)--;
                return *this;
            }

        protected:
            iterator(Node *p) : const_iterator(p) {};
            friend class list<T>;
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

            if (SIZE > 0) {
                Node *prevNode = head;
                Node *curNode = first;

                for (size_type i = 0; i < SIZE; i++) {
                    Node *newNode = new Node;
                    newNode->data = curNode->data;
                    prevNode->next = newNode;
                    newNode->prev = prevNode;
                    prevNode = newNode;
                    curNode = curNode->next;
                }

                prevNode->next = tail;
            } else {
                head->next = tail;
                tail->prev = head;
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

        }

        /// Returns true if the container contains no elements, and false otherwise.
        bool empty () {
            return SIZE == 0;
        }

        iterator begin () {
            iterator it(head->next);
            return it;
        }

        iterator end () {
            iterator it(tail->prev);
            return it;
        }

        private:
        size_type SIZE;
        Node *head;
        Node *tail;  
    };
}

#endif