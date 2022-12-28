#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include "assert.h"
using namespace std;
///////////////QUEUE CLASS/////////////////
template<class T>
class Queue
{
public:
    class Node;
    class Iterator;
    class ConstIterator;

    Iterator begin() ;

    ConstIterator begin() const;

    Iterator end() ;

    ConstIterator end() const;

    T& front() const;

    Queue():m_member(NULL){}

    void pushBack(T new_member);

    void popFront();

    int size();

    class EmptyQueue{};

    Queue<T>(const Queue<T>&)=default;

    Queue<T>& operator=(const Queue<T>&)=default;

    ~Queue()=default;


private:
Node* m_member;

};


template<class T,class Condition>
Queue<T> filter(Queue<T>queue, Condition c )
{Queue<T> result;
    for(const typename Queue<T>::Node& member : queue)
    {
        if(c(member.get_M_data()))
        {
            result.pushBack(member.get_M_data());
        }

    }
    return result;


}


void Queue<T>::popFront()

{
    if(!(this))
    {
        throw Queue<T>::EmptyQueue();
    }
    if(!(m_member->m_next))  {
        Queue<T>::Node *temp=m_member;
        m_member= m_member->m_next;
        delete temp;
    }
}

template<class T>
void Queue<T>::pushBack(const T new_member)
{ Node* added_member=new Node;
    added_member->m_data=new_member;
    added_member->m_next=nullptr;
    if(!(m_member))
    {
        m_member=added_member;
    }
    else{
        Node* temp=m_member;
        while(temp->m_next)
        {
            temp=temp->m_next;
        }
        temp->m_next=added_member;
    }

}
//NODE CLASS//
template<class T>
class Queue<T>::Node{

public:
        Node()=default;
        ~Node()=default;
        Node(const Node& node)=default;
    T get_M_data() const
        {
            return m_data;
        }
private:
        T m_data;
        Queue<T>::Node* m_next;
        friend class Queue<T>;
    friend class Queue<T>::Iterator;

};


/////ITERATOR CLASS///////////////////////////////
template<class T>
class Queue<T>::Iterator{
  
  Node* m_queue;

   Iterator( Node* queue):m_queue(queue){}

   friend class Queue<T>;

public:
    const Queue<T>::Node& operator*() const;

    Iterator& operator++();

    bool operator!=(const Iterator& it) const;

    Iterator(const Iterator&)=default;

    Iterator& operator=(const Iterator&)=default;

};
//////CONSTITERATOR CLASS/////////////////////////////////////////////////
template<class T>
class Queue<T>::ConstIterator{
  const Queue<T>* m_queue;
  
  ConstIterator( const Queue<T>* queue):m_queue(queue){}

  friend class Queue<T>;

public:

    const Queue<T>& operator*() const;

    ConstIterator& operator++();

    bool operator!=(const ConstIterator& it) const;

    ConstIterator(const ConstIterator&)=default;

    ConstIterator& operator=(const ConstIterator&)=default;

};

////////////ITERATOR_CODE/////////////////////////////////////////////
template<class T>
const typename Queue<T>::Node& Queue<T>::Iterator:: operator*() const
{
     return *m_queue;
}


template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& it) const{
    return (m_queue!=it.m_queue);
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(){
  if(m_queue)
  {
      m_queue=m_queue->m_next;

  }

    return *this;
}
////////////CONSTITERATOR_CODE/////////////////////////////////////////////
template<class T>
const Queue<T>& Queue<T>::ConstIterator:: operator*() const
{
    return *m_queue;
}


template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& it) const{
    return (m_queue!=it.m_queue);
}


template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++(){
 /*   if(m_queue->m_member)
    {
        throw Queue<T>::EmptyQueue();
    }
    m_queue->m_member=m_queue->m_member->m_next;
    return *this;
}*//////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
template<class T>
typename Queue<T>::Iterator Queue<T>:: begin() {
    return Iterator(this);

}
template<class T>
typename Queue<T>::Iterator Queue<T>:: end() {

    return Iterator(nullptr);

}
template<class T>

typename Queue<T>::ConstIterator Queue<T>:: begin()const {
    return ConstIterator(this);

}
template<class T>
typename Queue<T>::ConstIterator Queue<T>:: end() const {

    return ConstIterator(nullptr);

}
#endif //UNTITLED2_QUEUE_H

