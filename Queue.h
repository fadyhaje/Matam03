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
    class Iterator;
    class ConstIterator;

    Iterator begin() ;

    ConstIterator begin() const;

    Iterator end() ;

    ConstIterator end() const;

    T& front();

    const T& front() const;

    Queue():m_size(0),m_member(nullptr){}

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
                Queue<T>::Node* temp=m_member;
                while(m_member!=nullptr)
                {
                    temp=m_member;
                    m_member=m_member->m_next;
                    delete temp;
                }
                m_size=0;
                throw exception;
            }
            current_first_node=current_first_node->m_next;
        }
         m_size=queue.m_size;
    }
}

template <class T>
Queue<T>::~Queue()
{
    Queue<T>::Node* temp=m_member;
    while(m_member!=nullptr)
    {
        temp=m_member;
        m_member=m_member->m_next;
        delete temp;
    }
    m_size=0;
}

template <class T>
Queue<T>& Queue<T>:: operator=(const Queue<T>& queue){
  if (this==&queue)
  {
    return *this;
  }
  if(queue.m_member==nullptr){
    while(m_member!=nullptr){
      Queue<T>::Node* tmp=m_member;
      m_member=m_member->m_next;
      delete tmp;
    }
    return *this;
  }
    Queue<T>::Node* src=queue.m_member;
    Queue<T>::Node* start_target=new Queue<T>::Node();
    start_target->m_data=src->m_data;
    Queue<T>::Node* target=start_target;
    Queue<T>::Node* newNode=nullptr;
    src=src->m_next;
    while(src!= nullptr){
      try{
        newNode=new Queue<T>::Node();
      }
      catch(std::bad_alloc& exception){
        while(start_target!=nullptr){
          Queue<T>::Node* tmp=start_target;
          start_target=start_target->m_next;
          delete tmp;
        }
        throw exception;
      }
      newNode->m_data=(src->m_data);
      target->m_next=newNode;
      target=target->m_next;
      src=src->m_next;
      }
      while(m_member!=nullptr){
        Queue<T>::Node* tmp=m_member;
        m_hmember=m_member->m_next;
        delete tmp;
      }
      m_member=start_target;
      m_size=queue.m_size;
      return *this;
}
/*


template <class T>
Queue<T>& Queue<T>:: operator=(const Queue<T>& queue)
{
    Queue<T>::Node* temp_first_node=new Node();
    Queue<T>::Node* temp=temp_first_node;
    Queue<T>::Node* other_queue=queue.m_member;
    temp_first_node->m_data=other_queue->m_data;
    temp_first_node->m_next=other_queue->m_next;
    other_queue=other_queue->m_next;
    Queue<T>::Node* single_node=nullptr;
    if (this==&queue)
    {
        return *this;
    }
    if(other_queue!=nullptr){
        while(other_queue!=nullptr)
        {
            try
            {
                single_node=new Node();
            }
            catch(std::bad_alloc& exception){
                Queue<T>::Node* helper=nullptr;
                while(temp_first_node!=nullptr)
                {
                    helper=temp_first_node;
                    temp_first_node=temp_first_node->m_next;
                    delete helper;
                }
                throw exception;
            }
            temp->m_next=single_node;
            single_node->m_data=other_queue->m_data;
            other_queue=other_queue->m_next;
            temp=temp->m_next;
        }
        Queue<T>::Node* helper=nullptr;
        while(m_member!=nullptr)
        {
            helper=m_member;
            m_member=m_member->m_next;
            delete helper;
        }
        m_size=queue.size();
        m_member=temp_first_node;
        return *this;
    }
    else
    {
        Queue<T>::Node* helper=nullptr;
        while(m_member!=nullptr){
            helper=m_member;
            m_member=m_member->m_next;
            delete helper;
        }
        return *this;
    }
}
*/
template <typename T,typename P>
Queue<T> filter(const Queue<T> &queue,P function)
{
    Queue<T> result;
    for(typename Queue<T>::ConstIterator index=queue.begin(); index!= queue.end();++index)
    {
        if(!function(*index))
        {
            continue;
        }
        result.pushBack(*index);
    }
    return result;
}
/*
   Queue<T> result;
   for(const T& member : queue)
   {
       if(c(member))
       {
           result.pushBack(member);
       }

   }
   return result;


}*/


template <typename T,typename P>
void transform( Queue<T> &queue,P function)
{
    for(typename Queue<T>::Iterator index=queue.begin(); index!= queue.end();++index)
    {
        function(*(index));
    }
}

template <class T>
Queue<T>& Queue<T> :: popFront(){
  if(m_size==0){
    throw Queue<T>::EmptyQueue();
  }
  // there is just one node
  if(m_size == 1){ 
    delete m_member;
    m_member=nullptr;
    m_size--;
    return *this;
  }
  Queue<T>::Node* temp=m_member->m_next;
  m_member->m_data=temp->m_data;
  m_member->m_next=temp->m_next;
  delete temp;
  m_size--;
  return *this;
}
/*
template<class T>
Queue<T>& Queue<T>::popFront()
{
    if(m_size!=0)
    {
        Queue<T>::Node *temp = m_member->next;
        if (m_size != 1) {
            m_member->next=temp->m_next;
            m_member->m_data=temp->m_data;
            delete temp;
        } else {
            delete m_member;
            m_member = nullptr;
        }
        m_size--;
        return *this;
    }
    throw Queue<T>::EmptyQueue();
}*/


template<class T>
int Queue<T>::size() const{
    return m_size;
}

template<class T>
T& Queue<T>::front()
{
    if(m_size!=0)
    {
        return m_member->m_data;
    }
    throw Queue<T>::EmptyQueue();
}

template<class T>
const T& Queue<T>::front() const
{
    if(m_size!=0)
    {
        return m_member->m_data;
    }
    throw Queue<T>::EmptyQueue();
}


template <class T>
void Queue<T> :: pushBack(const T& newData){
    Queue<T>::Node* added=new Queue<T>::Node();
    added->m_data=newData;
    if(m_size==0)
    {
        m_member = added;
    }
    else
    {
        Queue<T>::Node* temp=m_member;
        while(temp->m_next!=nullptr){
            temp=temp->m_next;
        }
        temp->m_next=added;
    }
    m_size++;
}

/*
template<class T>
void Queue<T>::pushBack(const T& new_member)
{
    Queue<T>::Node* added_member=new Queue<T>::Node();
    added_member->m_data=new_member;
    //added_member->m_next=nullptr;
    if(m_size!=0)
    {
        Queue<T>::Node* temp=m_member;
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
}*/

/*template<class T>
T& Queue<T>:: front() const
{
    return m_member->m_data;

}*/
/*
template<class T>
class Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this,0);
}

template<class T>
class Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this, 0);
}

template<class T>
class Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(this, m_size);
}

template<class T>
class Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(this, m_size);
}

//NODE CLASS//
template<class T>
class Queue<T>::Node{

public:
    Node()=default;
    ~Node()=default;
    Node(const Node& node)=default;

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
    const T& operator*() const;

    Iterator& operator++();

    bool operator!=(const Iterator& it) const;

    Iterator(const Iterator&)=default;

    Iterator& operator=(const Iterator&)=default;

};

//////CONSTITERATOR CLASS/////////////////////////////////////////////////
template<class T>
class Queue<T>::ConstIterator{
    const Node* m_queue;

    ConstIterator( const Node* queue):m_queue(queue){}

    friend class Queue<T>;

public:

    const T& operator*() const;

    ConstIterator& operator++();

    bool operator!=(const ConstIterator& it) const;

    ConstIterator(const ConstIterator&)=default;

    ConstIterator& operator=(const ConstIterator&)=default;

};


template<class T>
const T& Queue<T>::Iterator:: operator*() const
{
    return m_queue->m_data;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& it) const
{
    return (m_queue!=it.m_queue);
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if(m_queue)
    {
        m_queue=m_queue->m_next;

    }

    return *this;
}


template<class T>
const T& Queue<T>::ConstIterator:: operator*() const
{
    return m_queue->m_data;
}


template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& it) const{
    return (m_queue!=it.m_queue);
}


template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++(){
    Queue<T>::Node* temp;
    if(m_queue)
    {
        temp=m_queue->m_next;
    }
    *this=temp;
    return *this;
}
*/

template<class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this, 1);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    if(!(this))
    {
        throw typename Queue<T>::Iterator::InvalidOperation();
    }
    return Iterator(this,m_size+1);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this,1);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    if(!(this))
    {
        throw typename Queue<T>::ConstIterator::InvalidOperation();
    }


    return ConstIterator(this,m_size+1);
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
    if(queue==other.queue) {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    return (other.index==index);
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& other) const
{
    return !(other == *this);
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if((*this)!=queue->end())
    {
        index++;
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
    assert((index >= 0) && (index < (queue->size()))+1);
    if(queue!= nullptr&&!this)
    {
        Queue<T>::Node* temp=queue->m_member;
        for(int i=0;i<index;i++)
        {
            temp=temp->m_next;
        }
        return temp->m_data;
    }
    throw Queue<T>::Iterator::InvalidOperation();


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
    if(queue==other.queue) {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    return (other.index==index);
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& other) const
{
    return !(other == *this);
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
        ++(*this);
        return final_result;
    }
    throw Queue<T>::ConstIterator::InvalidOperation();
}

template<class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    assert((index >= 0) && (index < (queue->size())+1));
    if(queue!= nullptr&&!this)
    {        Queue<T>::Node* temp=queue->m_member;
        for(int i=0;i<index;i++)
        {
            temp=temp->m_next;
        }
        return temp->m_data;}
    throw Queue<T>::ConstIterator::InvalidOperation();

}

#endif //UNTITLED2_QUEUE_H
