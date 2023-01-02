#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include <assert.h>
#include <new>
using namespace std;
///////////////QUEUE CLASS/////////////////
template<class T>
class Queue
{
public:
    class Iterator;
    class ConstIterator;

    Iterator begin() ;

    ConstIterator begin() const;

    Iterator end() ;

    ConstIterator end() const;

    T& front();

    const T& front() const;

    Queue();

    void pushBack(const T& new_member);

    Queue<T>& popFront();

    int size() const;

    class EmptyQueue{};

    Queue<T>(const Queue<T>&);

    Queue<T>& operator=(const Queue<T>&);

    ~Queue();


private:
    class Node;
    int m_size;
    Node* m_member;
};

template<class T>
class Queue<T>::Node{
public:

    /*
     * C'tor of Node class
     *the constructor is the default constructor
     */

    Node()=default;

    /*
     * d’tor of Node class
     *the destructor is the default destructor
     *
    */
    ~Node()=default;

    /*
    *  *@param node
    *       The node that will be copied
    *
    * Copy C’tor of Node class
    *
    * @ return
    *     A copy of the the node
    * the copy constructor is the default copy constructor
    */
    Node(const Node& node)=default;

private:
    Queue<T>::Node* m_next;
    T m_data;
    friend class Queue<T>;

};

template <class T>
Queue<T>::Queue(const Queue<T>& queue):m_size(0),m_member(nullptr)
{
    Queue<T>::Node* current_first_node=queue.m_member;
    if(current_first_node!=nullptr)
    {
        while(current_first_node!=nullptr)
        {
            try
            {
                this->pushBack(current_first_node->m_data);
            }
            catch(std::bad_alloc& exception){
                while(m_member!=nullptr)
                {
                    Queue<T>::Node* temp=m_member;
                    m_member=m_member->m_next;
                    delete temp;
                }
                m_size=0;
                throw exception;
            }
            current_first_node=current_first_node->m_next;
        }
    }
    else{
        return;
    }
}

template <class T>
Queue<T>::~Queue()
{
    while(m_member!=nullptr)
    {
        Queue<T>::Node* temp=m_member;
        m_member=m_member->m_next;
        delete temp;
    }
    m_size=0;
}
template <class T>
Queue<T>::Queue()
{
    m_size=0;
    m_member=nullptr;
}

template <class T>
Queue<T>& Queue<T>:: operator=(const Queue<T>& queue){
    Queue<T>::Node* single_node= nullptr;
    Queue<T>::Node* result_begin=new Queue<T>::Node();
    Queue<T>::Node* other_queue=queue.m_member;
    result_begin->m_data=other_queue->m_data;
    Queue<T>::Node* result=result_begin;
    other_queue=other_queue->m_next;
    if (this==&queue)
    {
        return *this;
    }
    if(queue.m_size!=0){
        while(other_queue!= nullptr){
            try{
                single_node=new Queue<T>::Node();
            }
            catch(std::bad_alloc& exception){
                Queue<T>::Node* temp=result_begin;
                while(result_begin!=nullptr){
                    temp=result_begin;
                    result_begin=result_begin->m_next;
                    delete temp;
                }
                throw exception;
            }
            result->m_next=single_node;
            single_node->m_data=(other_queue->m_data);
            other_queue=other_queue->m_next;
            result=result->m_next;
        }
        (*this).~Queue();
        m_size=queue.m_size;
        m_member=result_begin;
        return *this;
    }
    else{
        (*this).~Queue();
        return *this;
    }
}

template <typename T,typename Predict>
Queue<T> filter(const Queue<T> &queue,Predict function){
    Queue<T> result;
    for(typename Queue<T> :: ConstIterator index=queue.begin(); index!= queue.end();++index){
        if(!function(*index)){
            continue;
        }
        result.pushBack(*index);
    }
    return result;
}

template <typename T,typename Predict>
void transform( Queue<T> &queue,Predict function)
{
    for(typename Queue<T>::Iterator index=queue.begin(); index!= queue.end();++index)
    {
        function(*(index));
    }
}


template<class T>
Queue<T>& Queue<T>::popFront()
{
    if(m_size!=0 && m_size!=1)
    {    Queue<T>::Node *temp = m_member->m_next;
        m_member->m_data=temp->m_data;
        m_member->m_next=temp->m_next;
        delete temp;
        m_size--;
        return *this;
    }
    else if(m_size!=0 && m_size==1){
        delete m_member;
        m_member = nullptr;
        m_size--;
        return *this;
    }
    throw Queue<T>::EmptyQueue();
}


template<class T>
int Queue<T>::size() const{
    return m_size;
}

template<class T>
T& Queue<T>::front()
{
    if(m_size!=0)
    {
        Queue<T>::Iterator index=this->begin();
        return *index;
    }
    throw Queue<T>::EmptyQueue();
}

template<class T>
const T& Queue<T>::front() const
{
    if(m_size!=0)
    {
        Queue<T>:: ConstIterator index=this->begin();
        return *index;
    }
    throw Queue<T>::EmptyQueue();
}


template <class T>
void Queue<T> :: pushBack(const T& new_member){
    Queue<T>::Node* added_member=new Queue<T>::Node();
    Queue<T>::Node* temp=m_member;
    added_member->m_data=new_member;
    if(m_size!=0)
    {
        while(temp->m_next!=nullptr)
        {
            temp=temp->m_next;
        }
        temp->m_next=added_member;
    }
    else
    {
        m_member=added_member;
    }
    m_size++;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this, 0);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end()
{

    return Iterator(this,m_size);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this,0);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(this,m_size);
}

template<class T>
class Queue<T>::Iterator {

public:
    Iterator(const Iterator&)=default;
    Iterator& operator=(const Iterator&)=default;
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
    Iterator& operator++();
    Iterator operator++(int);
    T& operator*() const;
    class InvalidOperation{};

private:
    friend class Queue<T>;
    Queue<T>* queue;
    int index;
    Iterator(Queue<T>* queue, int index);
};

template<class T>
Queue<T>::Iterator::Iterator(Queue<T>* queue, int index):queue(queue),index(index)
{
}

template<class T>
bool Queue<T>::Iterator::operator==(const Iterator& other) const
{
    assert(queue==other.queue);
    return (other.index==index);
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& other) const
{
    return !(*this== other);
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if(*this!=queue->end())
    {
        ++index;
        return *this;
    }
    throw Queue<T>::Iterator::InvalidOperation();
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    if(this!=queue->end())
    {
        Iterator final_result=*this;
        ++(*this);
        return final_result;
    }
    throw Queue<T>::Iterator::InvalidOperation();
}

template<class T>
T& Queue<T>::Iterator::operator*() const
{
    assert((index >= 0) && (index < queue->size()));
    Queue<T>::Node* temp=queue->m_member;
    for(int i=0;i<index;i++)
    {
        temp=temp->m_next;
    }
    return temp->m_data;
}

template<class T>
class Queue<T>::ConstIterator {

public:
    ConstIterator(const ConstIterator&)=default;
    ConstIterator& operator=(const ConstIterator&)=default;
    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;
    ConstIterator& operator++();
    ConstIterator operator++(int);
    const T& operator*() const;
    class InvalidOperation{};

private:
    friend class Queue<T>;
    const Queue<T>* queue;
    int index;
    ConstIterator(const Queue<T>* queue, int index);
};

template<class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, int index):queue(queue),index(index)
{
}

template<class T>
bool Queue<T>::ConstIterator::operator==(const ConstIterator& other) const
{
    assert(queue==other.queue) ;
    return index==other.index;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& other) const
{
    return !(*this==other);
}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if((*this)!=queue->end())
    {
        ++index;
        return *this;
    }
    throw Queue<T>::ConstIterator::InvalidOperation();
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
    if(this!=queue->end())
    {
        ConstIterator final_result=*this;
        ++*this;
        return final_result;
    }
    throw Queue<T>::ConstIterator::InvalidOperation();
}

template<class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    assert((index >= 0) && (index < queue->size()));
    Queue<T>::Node* temp=queue->m_member;
    for(int i=0;i<index;i++)
    {
        temp=temp->m_next;
    }
    return temp->m_data;
}



#endif //UNTITLED2_QUEUE_H*/
