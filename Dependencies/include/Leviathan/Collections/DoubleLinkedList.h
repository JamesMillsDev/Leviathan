#pragma once

#include <initializer_list>

using std::initializer_list;

namespace Leviathan
{
    template<typename T>
    class DoubleLinkedList
    {
    public:
        struct Node
        {
            T value;
            Node* next = nullptr;
            Node* prev = nullptr;

            Node(const T& _value) : value(_value) {}
        };

        struct Iterator
        {
        public:
            Node* node = nullptr;

        public:
            Iterator() : node(nullptr) {}
            Iterator(Node* _node) : node(_node) {}

            Iterator& Next()
            {
                if (node != nullptr)
                    node = node->next;

                return *this;
            }

            Iterator& Prev()
            {
                if (node != nullptr)
                    node = node->prev;

                return *this;
            }

        public:
            // Increment / Decrement operators
            Iterator& operator++() { return Next(); }
            Iterator& operator--() { return Prev(); }

            // Equality operators
            bool operator==(const Iterator& _rhs) { return node == _rhs.node; }
            bool operator!=(const Iterator& _rhs) { return node != _rhs.node; }

            // Iterator getters
            Iterator& operator+(const int _shiftAmount)
            {
                Iterator iter = *this;

                for (int i = 0; i < _shiftAmount; i++)
                {
                    if (iter.node->next != nullptr)
                        iter = iter.Next();
                    // Check if ended (if at the end of the iterator/list, return end)
                }

                return iter;
            }

            Iterator& operator-(const int _shiftAmount)
            {
                Iterator iter = *this;

                for (int i = _shiftAmount; i > 0; i--)
                {
                    if (iter.node->prev != nullptr)
                        iter = iter.Prev();
                    // check if we are outside the bounds of the list
                }

                return iter;
            }

            // Dereference operators
            T& operator*() { return node->value; }
            T* operator->() { return &node->value; }

        };

    public:
        LinkedList() = default;

        LinkedList(initializer_list<T> _list)
        {
            for (auto iter = _list.begin(); iter != _list.end(); ++iter)
                PushBack(*iter);
        }

        ~LinkedList() = default;

        void PushBack(T _value)
        {
            Node* node = new Node(_value);
            m_count++;

            if (Empty())
            {
                m_head = node;
                m_tail = node;
            }
            else
            {
                m_tail->next = node;
                node->prev = m_tail;
                m_tail = node;
            }
        }

        void PopBack()
        {
            if (Empty())
                return;

            Node* last = m_tail;
            m_tail = m_tail->prev;

            if (m_tail != nullptr)
                m_tail->next = nullptr;

            if (m_tail == nullptr)
                m_head = nullptr;

            delete last;
            m_count--;
        }

        void PushFront(T _value)
        {
            Node* node = new Node(_value);
            m_count++;

            if (IsEmpty())
            {
                m_first = node;
                m_last = node;
            }
            else
            {
                m_first->prev = node;
                node->next = m_first;
                m_first = node;
            }
        }

        void PopFront()
        {
            if (Empty())
                return;

            Node* first = m_first;
            m_first = m_first->next;

            if (m_first != nullptr)
                m_first->prev = nullptr;

            if (m_head == nullptr)
                m_tail = nullptr;

            delete first;
            m_count--;
        }

        void Clear()
        {
            while (!IsEmpty())
                PopFront();
        }

        // return the iterator that would be in this location after removing
        Iterator Remove(Iterator _iter)
        {
            if (_iter.node == nullptr)
                return nullptr;

            Node* current = _iter.node;
            Node* next = current->next;
            Node* prev = current->prev;
            Iterator result = Iterator(current->next);

            if (prev == nullptr)
                m_head = next;
            if (next == nullptr)
                m_tail = prev;

            if (next != nullptr)
                next->prev = prev;
            if (prev != nullptr)
                prev->next = next;

            delete current;
            m_count--;

            return result;
        }

        Iterator RemoveAt(const int _index)
        {
            Iterator current = Begin();

            for (int i = 0; i < _index; i++)
                ++current;

            return Remove(current);
        }

        void Insert(Iterator _iter, const T& _value)
        {
            if (_iter == End())
            {
                std::cout << "Invalid position." << std::endl;
                return;
            }

            if (_iter == Begin())
            {
                PushFront(value);
            }
            else if (_iter == Back())
            {
                PushBack(value);
            }
            else
            {
                Node* newNode = new Node(_value);
                Node* current = m_head;

                for (int i = 0; i < _iter - 1; i++)
                    current = current->next;

                newNode->prev = current;
                newNode->next = current->next;
                current->next->prev = newNode;
                current->next = newNode;
                m_count++;
            }
        }

        // Find the first iterator/node that contains this value
        Iterator Find(T _value)
        {
            for (Iterator iter = Begin(); iter != End(); ++iter)
            {
                if (iter.node->value == _value)
                    return iter;
            }

            return End();
        }

        // Return the value at this index
        T& At(const int _index)
        {
            Iterator current = Begin();

            for (int i = 0; i < _index; i++)
                ++current;

            return current.node->value;
        }

        // check if any nodes contain this value
        bool Contains(const T& _value)
        {
            for (Iterator iter = Begin(); iter != End(); ++iter)
            {
                if (iter.node->value == _value)
                    return true;
            }

            return false;
        }

        void Sort(int(*_comparer)(Iterator, Iterator))
        {
            for (int i = 0; i < m_count; i++)
            {
                Iterator iter = Begin() + i;

                for (Iterator jter = iter + 1; jter != End(); ++jter)
                {
                    if (_comparer(iter, jter) > 0)
                    {
                        auto ItVal = iter.node->value;
                        iter.node->value = jter.node->value;
                        jter.node->value = ItVal;
                    }
                }
            }
        }

        // Find the index of this value, otherwise return -1
        int IndexOf(const T& _value)
        {
            int i = 0;
            for (Iterator iter = Begin(); iter != End(); ++iter)
            {
                if (iter.node->value == _value)
                    return i;

                i++;
            }

            return -1;
        }

        bool Empty()
        {
            return m_head == nullptr && m_tail == nullptr;
        }

        // Amount of items in the list
        unsigned int Count()
        {
            return m_count;
        }

        Node* Head() { return m_head; }
        Node* Tail() { return m_tail; }

        Iterator Begin() { return Iterator(m_head); }
        Iterator Back() { return Iterator(m_tail); }
        Iterator End() { return Iterator(); }

    private:
        Node* m_head = nullptr;
        Node* m_tail = nullptr;

        unsigned int m_count = 0;
    };
}