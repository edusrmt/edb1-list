#ifndef LIST_H
#define LIST_H

namespace sc {
    template <typename T>
    class list {
        private:
        struct Node {
            T data;
            Node *prev;
            Node *next;
        };

        using size_type = unsigned long;
        size_type SIZE;
        Node *head;
        Node *tail;        

        public:
        list () : SIZE{0}, head{new Node}, tail{new Node} {
            head->prev = nullptr;
            head->next = tail;
            tail->prev = head;
            tail->next = nullptr;
        }

        size_type size () {
            return SIZE;
        }

        bool empty () {
            return SIZE == 0;
        }
    };
}

#endif