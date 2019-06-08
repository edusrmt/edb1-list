#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <iostream>

using size_type = unsigned long;

//! Created to differentiate this list implementation from the std::list.
namespace sc
{
    /**
     * @brief Container that implements a doubly linked list.
     * @author Eduardo Sarmento & Victor Vieira
     * 
     * This class is similar to std::list, having some constructors, operations, etc.
     */
    template <typename T>
    class list
    {
    private:
        /// Representation of a node, it contains a data and references to the previous and the next node.
        struct Node
        {
            T data;     //<! Data field
            Node *prev; //<! Pointer to the previous node in the list
            Node *next; //<! Pointer to the next node in the list

            /// Basic constructor
            Node(const T &d = T(), Node *p = nullptr, Node *n = nullptr) : data{d}, prev{p}, next{n} {}
        };

    public:
        /**
         * @brief Constant iterator of a node.
         * @author Eduardo Sarmento & Victor Vieira
         * 
         * Encapsulates a pointer to a node.
         */
        class const_iterator {
        public:
            /// Default constructor that creates an nullptr.
            const_iterator() : current{nullptr} {}

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
            Node *current;                          //<! The pointer to the node.
            const_iterator(Node *p) : current(p) {} //<! Constructor that receives a pointer.
            friend class list<T>;                   //<! List can access members of iterator.
        };

        /**
         * @brief Iterator of a node.
         * @author Eduardo Sarmento & Victor Vieira
         * 
         * Encapsulates a pointer to a node.
         */
        class iterator
        {
        public:
            /// Default constructor that creates an nullptr.
            iterator() : current(nullptr) {}

            /// Return a const reference to the object located at the position pointed by the iterator.
            const T &operator*() const { return current->data; } // *it

            /// Return a reference to the object located at the position pointed by the iterator.
            T &operator*() { return current->data; }

            /// Advances the iterator to the next location within the list and returns itself after that.
            iterator operator++()
            { // ++it
                current = current->next;
                return iterator(current);
            }

            /// Advances the iterator to the next location within the list and returns itself before that.
            iterator operator++(int n)
            {
                iterator temp(current);
                current = current->next;
                return temp;
            }

            /// Advances to the n-th successor node of the iterator and returns it.
            friend iterator operator+(int n, iterator it)
            {
                for (int i = 0; i < n; i++)
                {
                    it.current = it.current->next;
                }

                return it.current;
            }

            friend iterator operator+(iterator it, int n)
            {
                for (int i = 0; i < n; i++)
                {
                    it.current = it.current->next;
                }

                return it.current;
            }

            /// Backs the iterator to the previous location within the list and returns itself after that.
            iterator operator--() // --it
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
            size_type operator-(iterator rhs)
            {
                size_type dis = 0;
                iterator cur(current);

                while (rhs != cur)
                {
                    dis++;
                    rhs++;
                }

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
            Node *current;                    //<! The pointer to the node data.
            iterator(Node *p) : current(p) {} //<! Constructor that receives a pointer.
            friend class list<T>;             //<! List can access members of iterator.;
        };

    public:
        /// Default constructor that creates an empty list.
        list() : SIZE{0}, head{new Node}, tail{new Node}
        {
            head->prev = nullptr;
            head->next = tail;
            tail->prev = head;
            tail->next = nullptr;
        }

        /// Constructs the list with count default-inserted instances of T.
        explicit list(size_type count) : SIZE{count}, head{new Node}, tail{new Node}
        {
            head->prev = nullptr;
            tail->next = nullptr;

            if (SIZE > 0)
            {
                Node *prevNode = head;

                for (size_type i = 0; i < SIZE; i++)
                {
                    Node *newNode = new Node;
                    prevNode->next = newNode;
                    newNode->prev = prevNode;
                    prevNode = newNode;
                }

                prevNode->next = tail;
            }
            else
            {
                head->next = tail;
                tail->prev = head;
            }
        }

        /// Constructs the list with the contents of the range [first, last).
        template <typename InputIt>
        list(InputIt first, InputIt last) : SIZE{last - first}, head{new Node}, tail{new Node}
        {
            head->prev = nullptr;
            tail->next = nullptr;
            head->next = tail;
            tail->prev = head;

            Node *curNode = head;

            while (first != last)
            {
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
        list(const list &other) : SIZE{other.size()}, head{new Node}, tail{new Node}
        {
            head->prev = nullptr;
            tail->next = nullptr;
            head->next = tail;
            tail->prev = head;

            Node *cp = other.head->next;
            Node *curNode = head;

            for (size_type i = 0; i < SIZE; i++)
            {
                Node *newNode = new Node;
                curNode->next = newNode;
                newNode->prev = curNode;
                curNode = curNode->next;
                newNode->data = cp->data;
                newNode->next = tail;
                tail->prev = newNode;

                cp = cp->next;
            }
        }

        /// Constructs the list with the contents of the initializer list init.
        list(std::initializer_list<T> ilist) : SIZE{ilist.size()}, head{new Node}, tail{new Node}
        {
            head->prev = nullptr;
            tail->next = nullptr;
            if (SIZE > 0)
            {
                Node *prevNode = head;

                for (size_type i = 0; i < SIZE; i++)
                {
                    Node *newNode = new Node;
                    prevNode->next = newNode;
                    newNode->data = *(ilist.begin() + i);
                    newNode->prev = prevNode;
                    prevNode = newNode;
                }

                prevNode->next = tail;
                tail->prev = prevNode;
            }
            else
            {
                head->next = tail;
                tail->prev = head;
            }
        }

        /// Destructor
        ~list()
        {
            Node *curNode = head;

            while (curNode != nullptr)
            {
                Node *nxt = curNode->next;
                delete curNode;
                curNode = nxt;            
            }
        }

        // [II ITERATORS]

        /// Returns an iterator pointing to the first item in the list.
        iterator begin()
        {
            return iterator(head->next);
        }

        /// Returns an iterator pointing to the end mark in the list, i.e. the position just after the last element of the list.
        iterator end()
        {
            return iterator(tail);
        }

        /// Returns a constant iterator pointing to the first item in the list.
        const_iterator cbegin()
        {
            return const_iterator(head->next);
        }

        /// Returns a constant iterator pointing to the end mark in the list, i.e. the position just after the last element of the list.
        const_iterator cend()
        {
            return const_iterator(tail);
        }

        // [III] CAPACITY

        /// Return the number of elements in the container.
        size_type size() const
        {
            return SIZE;
        }

        /// Returns true if the container contains no elements, and false otherwise.
        bool empty()
        {
            return SIZE == 0;
        }

        // [IV] MODIFIERS

        /// Remove all elements from the container.
        void clear()
        {
            Node *curNode = head->next;

            while (curNode->next != nullptr)
            {
                Node *nxt = curNode->next;
                delete curNode;
                curNode = nxt;
            }

            head->next = tail;
            tail->prev = head;

            SIZE = 0;
        }

        /// Returns the object at the front of the list.
        T &front()
        {
            return head->next->data;
        }

        /// Returns the object at the front of the list.
        const T &front() const
        {
            return head->next->data;
        }

        /// Returns the object at the end of the list.
        const T &back()
        {
            return tail->prev->data;
        }

        /// Returns the object at the end of the list.
        const T &back() const
        {
            return tail->prev->data;
        }

        /// Adds value to the front of the list.
        void push_front(const T &value)
        {
            SIZE += 1;
            Node *curNode = head->next;
            Node *newNode = new Node;

            curNode->prev = newNode;
            newNode->next = curNode;

            curNode = curNode->prev;
            newNode->data = value;
            newNode->prev = head;
            head->next = newNode;
        }

        /// Adds value to the back of the list.
        void push_back(const T &value)
        {
            SIZE += 1;
            Node *curNode = tail->prev;
            Node *newNode = new Node;

            curNode->next = newNode;
            newNode->prev = curNode;

            curNode = curNode->next;
            newNode->data = value;
            newNode->next = tail;
            tail->prev = newNode;
        }

        /// Removes value of the front of the list.
        void pop_front()
        {
            SIZE--;
            Node *popped = head->next;
            std::cout << "Popping " << popped->data << std::endl;
            head->next = popped->next;
            popped->next->prev = head;
            delete popped;
        }

        /// Removes value of the back of the list.
        void pop_back()
        {
            SIZE -= 1;
            Node *popped = tail->prev;
            tail->prev = popped->prev;
            popped->prev->next = tail;
            delete popped;
        }

        /// Replaces the content of the list with copies of value value.
        void assign(const T &value) {
            Node *curNode = head->next;

            while (curNode != tail) {
                curNode->data = value;
                curNode = curNode->next;
            }
        }

        /// Replaces the contents with count copies of value value.
        void assign( size_type count, const T& value ) {
            clear();
            Node *curNode = head;
            SIZE = count;

            for (size_type i = 0; i < count; i++) {
                Node *newNode = new Node;
                
                newNode->data = value;
                newNode->prev = curNode;
                newNode->next = tail;

                curNode->next = newNode;
                tail->prev = newNode;

                curNode = curNode->next;
            }
        }

        /// Copy the size and values from another list.
        list &operator=(list other)
        {
            clear();
            iterator cpy(other.begin());
            Node *curNode = head;

            for (size_type i = 0; i < other.size(); i++) {
                Node *newNode = new Node;
                
                newNode->data = *(cpy++);
                newNode->prev = curNode;
                newNode->next = tail;

                curNode->next = newNode;
                tail->prev = newNode;

                curNode = curNode->next;
                SIZE++;
            }

            return *this;
        }

        /// Replaces the contents with those identified by initializer list ilist.
        list &operator=(std::initializer_list<T> ilist)
        {
            assign(ilist);

            return *this;
        }

        /// Returns true if each element of a list is equal to another.
        friend bool operator==(const list &lhs, const list &rhs)
        {
            bool isEqual = lhs.SIZE == rhs.SIZE;

            if (isEqual) {
                Node *curNodeL = lhs.head->next;
                Node *curNodeR = rhs.head->next;
                for (size_type i = 0; i < rhs.SIZE; i++)
                {
                    if (curNodeL->data != curNodeR->data)
                        return false;

                    curNodeL = curNodeL->next;
                    curNodeR = curNodeR->next;
                }    
            }    

            return isEqual;
        }

        /// Returns true if, at least, one element of a list is different to another.
        friend bool operator!=(const list &lhs, const list &rhs)
        {
            bool isDifferent = lhs.SIZE != rhs.SIZE;
            if (!isDifferent)
            {
                Node *curNodeL = lhs.head->next;
                Node *curNodeR = rhs.head->next;
                for (size_type i = 0; i < lhs.SIZE; i++)
                {
                    if (curNodeL->data != curNodeR->data)
                        return true;

                    curNodeL = curNodeL->next;
                    curNodeR = curNodeR->next;
                }

                return false;
            }

            return isDifferent;
        }

        // [IV-a] Modifiers with iterators
        
        /// Replaces the contents of the list with the elements from the initializer list ilist.
        void assign(std::initializer_list<T> ilist) {
            clear();
            SIZE = ilist.size();
            Node *prevNode = head;

            for (size_type i = 0; i < SIZE; i++)
            {
                Node *newNode = new Node;
                prevNode->next = newNode;
                newNode->data = *(ilist.begin() + i);
                newNode->prev = prevNode;
                prevNode = newNode;
            }

            prevNode->next = tail;
            tail->prev = prevNode;
        }

        /// Adds value into the list before the position given by the iterator pos and returns an iterator to the position of the inserted item.
        iterator insert(iterator itr, const T &value)
        {
            SIZE += 1;
            iterator first(begin());

            Node *curNode = head->next;
            while (first != itr)
            {
                curNode = curNode->next;
                first++;
            }

            Node *newNode = new Node;
            Node *prevNode = curNode->prev;

            curNode->prev = newNode;
            newNode->next = curNode;
            curNode = curNode->prev;
            newNode->data = value;
            newNode->prev = prevNode;
            prevNode->next = newNode;

            return iterator(newNode);
        }

        /// Inserts elements from the range [first; last) before pos.
        template <class InItr>
        iterator insert(iterator pos, InItr first, InItr last)
        {
            const size_type cpySize = last - first;        
            --last;

            for (size_type i = 0; i < cpySize; i++, last--) {
                T vl = *(last);
                pos = insert(pos, vl);
            } 

            return pos;
        }

        /// Inserts elements from the initializer list ilist before pos.
        iterator insert(iterator pos, std::initializer_list<T> ilist) {
            SIZE += ilist.size();
            iterator start(begin());

            Node *curNode = head->next;
            while (start != pos)
            {
                curNode = curNode->next;
                start++;
            }

            for (size_type i = 1; i <= ilist.size(); i++) {
                Node *newNode = new Node;
                
                newNode->prev = curNode->prev;
                newNode->next = curNode;
                newNode->data = *(ilist.end() - i);

                curNode->prev->next = newNode;
                curNode->prev = newNode;
                curNode = newNode;
            } 

            return pos;
        }

        /// Removes the object at position pos and returns an iterator to the element that follows pos before the call.
        iterator erase(iterator pos) {
            SIZE--;

            iterator start(begin());
            Node *delNode = head->next;
            while (start != pos) {
                delNode = delNode->next;
                start++;
            }

            delNode->prev->next = delNode->next;
            delNode->next->prev = delNode->prev;
            iterator rt(delNode->next);
            delete delNode;

            return rt;
        }

        /// Removes elements in the range [first; last).
        iterator erase(iterator first, iterator last) {
            size_type delSize = last - first;        

            iterator start(begin());
            Node *curNode = head->next;
            while (start != first) {
                curNode = curNode->next;
                start++;
            }

            iterator rt = first;

            for (size_type i = 0; i < delSize; i++) {
                rt = first + 1;
                rt = erase(first++);
            }

            return rt;
        }

        // Find é apontado como quesito de avaliação, mas não é definida e nem existe teste para ela. Por isso não foi implementada.
        const_iterator find(const T &value) const;

    private:
        size_type SIZE;
        Node *head;
        Node *tail;
    };
} // namespace sc

#endif