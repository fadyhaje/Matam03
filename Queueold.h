#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include <iostream>
#include <new>
#include <assert.h>

template <class T>
class Queue {
    public:
    /* 
     * C'tor of Queue class
     *
     * @return
     *      A new Queue.
    */ 

    //default constructor
    Queue();

  
    /*
     * d’tor of Queue class
     *
     *   
    */ 
    ~Queue();

    /*
     *  *@param Queue
     *       The queue we want to copy 
     *
     * Copy C’tor of Queue class
     *
     * @ return
     *     A copy of a queue
    */ 
    Queue(const Queue<T>& queue);

    /* Assignment operator
    *  removes all current elements and add the queue elements
    * param queue
         the queue we want to change our queue according to
    */

    Queue& operator=(const Queue<T>& queue);

/*
     *
     *param newData
     *   the parameter we wantd to add to the queue(add from the back)
     * return :
     *       void   
    */ 
    void pushBack(const T& newData);

    /*
     *return
     *  reference to the first element in the queue (the element can be changed)
    */

    T& front();

    /*
     *return
     * reference to the first element in the queue (the element can not be changed)
    */

    const T& front() const;

    /*
    *  removing the last element in the queue(the one thaw was added last)
     *return
     *    void
    */

    Queue<T>& popFront();

 /*
    *  
     *return
     *     the current size of the queue
    */

    int size() const;

 /*
    *  updating all the elements in the queue according the function that was sent
    *  param function
    *      the function that is used to change the elements in the queue
     *return
     *    void
    */

    //void transform(void (*function)(T& data));

 /*
    *  
     *    in case of an illegal operation on an empty queue
    */
    class EmptyQueue{};

    class Iterator;


 /*
    *  
     *return
     *    an iterator pointing at the start of the queue
    */
    Iterator begin() ;

/*
    *  
     *return
     *    an iterator pointing at the end of the queue
    */
    Iterator end() ; 

    class ConstIterator;

/*
    *  
     *return
     *    a const iterator pointing at the start of the const queue
    */
    ConstIterator begin() const ;

/*
    *  
     *return
     *    a const iterator pointing at the end of the const queue
    */
    ConstIterator end() const; 


    private:
    class Node;
    int m_size;
    Node* m_head;

};

    /*
    *  updating all the elements in the queue according the function that was sent
    *  param function
    *      the function that is used to change the elements in the queue according to its return value
    *  in case of true adding the element to a new queue
    *  otherwise, doesn't add them
    *  return
    *    a new queue containing elements from the original queue (there return value in the function is true)
    */
  template <typename T,typename P>
  Queue<T> filter(const Queue<T> &queue,P function);

    /*
    *  updating all the elements in the queue according the function that was sent
    *  param function
    *      the function that is used to change the elements in the queue
     *return
     *    void
    */

  template <typename T,typename P>
  void transform(Queue<T> &queue,P Function);

// implementing Queue class


// default constructor
template <class T>
Queue<T> :: Queue(){
    m_size=0;
    m_head = nullptr;
}

// copy constructor
template <class T>
Queue<T>:: Queue(const Queue<T>& queue): m_size(0), m_head(nullptr) {
  if(queue.m_head==nullptr){
    return;
  }
  Queue<T>::Node* holder=queue.m_head;
  while(holder!= nullptr){
    try{
      this->pushBack(holder->m_data);
    }
    catch(std::bad_alloc& exception){
      while(m_head!=nullptr){
        Queue<T>::Node* tmp=m_head;
        m_head=m_head->m_next;
        delete tmp;
      }
      m_size=0;
     throw exception;
    }
    holder=holder->m_next;
  }
}

// destructor
template <class T>
Queue<T>::~Queue(){
  while(m_head!=nullptr){
    Queue<T>::Node* tmp=m_head;
    m_head=m_head->m_next;
    delete tmp;
  }
  m_size=0;
}


//Assignment
template <class T>
Queue<T>& Queue<T>:: operator=(const Queue<T>& queue){
  if (this==&queue)
  {
    return *this;
  }
  if(queue.m_head==nullptr){
    while(m_head!=nullptr){
      Queue<T>::Node* tmp=m_head;
      m_head=m_head->m_next;
      delete tmp;
    }
    return *this;
  }
    Queue<T>::Node* src=queue.m_head;
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
      while(m_head!=nullptr){
        Queue<T>::Node* tmp=m_head;
        m_head=m_head->m_next;
        delete tmp;
      }
      m_head=start_target;
      m_size=queue.m_size;
      return *this;      
    } 

    



template <class T>
void Queue<T> :: pushBack(const T& newData){
  Queue<T>::Node* ptr=new Queue<T>::Node();
  ptr->m_data=newData;
  // adding the first element/node
  if(m_size==0)
    {
      m_head = ptr;
    }
    else {
     Queue<T>::Node* tmp=m_head;
     while(tmp->m_next!=nullptr){
       tmp=tmp->m_next;
     }
    tmp->m_next=ptr;
    }
    m_size++;
}


template <class T>
T& Queue<T> :: front() { 
  if(m_size==0){
      throw Queue<T>::EmptyQueue();
  }
  Queue<T>::Iterator i=this->begin();
  return *i;
}


template <class T>
const T& Queue<T> :: front() const{ 
  if(m_size==0){
      throw Queue<T>::EmptyQueue();
  }
  Queue<T>:: ConstIterator i=this->begin();
  return *i;   
}

template <class T>
Queue<T>& Queue<T> :: popFront(){
  if(m_size==0){
    throw Queue<T>::EmptyQueue();
  }
  // there is just one node
  if(m_size == 1){ 
    delete m_head;
    m_head=nullptr;
    m_size--;
    return *this;
  }
  Queue<T>::Node* ptr=m_head->m_next;
  m_head->m_data=ptr->m_data;
  m_head->m_next=ptr->m_next;
  delete ptr;
  m_size--;
  return *this;
}

template <class T>
int Queue<T> :: size() const{
  return(m_size);
}


template<class T>
typename Queue<T>::Iterator Queue<T>::begin() {
  return Iterator(this,0);
}
    

template<class T>
typename Queue<T>::Iterator Queue<T>::end()  {
  return Iterator(this, m_size);
}


template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const {
  return ConstIterator(this, 0);
}


template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const {
  return ConstIterator(this, m_size);
}

template <typename T,typename P>
Queue<T> filter(const Queue<T> &queue,P function){
  Queue<T> tmp;
  for(typename Queue<T> :: ConstIterator i=queue.begin(); i!= queue.end();++i){
    if(function(*i)){
      tmp.pushBack(*i);
    }
  }
  return tmp;
}


template <typename T,typename P>
void transform(Queue<T> &queue,P Function){
  for(typename Queue<T> :: Iterator i=queue.begin(); i!= queue.end();++i){
    Function(*i);
  }
}

/////////////////////////////// the end of implementing the class Queue /////////////////////////////////

template<class T>
class Queue<T>::Node{
public:
    
    /* 
     * C'tor of Node class
     *default constructor
     */

    Node()=default;

    /*
     * d’tor of Node class
     *
     *   
    */ 
    ~Node()=default;
    
    /*
    *  *@param node
    *       The node we want to copy 
    *
    * Copy C’tor of Node class
    *
    * @ return
    *     A copy of the mnode
    * default copy constructpr
    */ 
    Node(const  Node& node)=default;

    private:
    T m_data;  
    Queue<T>::Node* m_next;
    friend class Queue<T>;

};

///////////////////////// the end of implementing class Node //////////////////////////////////



////////////////////////////////// class Iterator ////////////////////////////////////////
template<class T>
class Queue<T>::Iterator {

public:


T& operator*() const;

Iterator& operator++();

Iterator operator++(int);

bool operator==(const Iterator& other) const;

bool operator!=(const Iterator& other) const;

Iterator(const Iterator&) = default;

Iterator& operator=(const Iterator&) = default;

class InvalidOperation{};


private:

  Queue<T>* queue;

  int index;

  Iterator(Queue<T>* queue, int index);

  friend class Queue<T>;

};

template<class T>
Queue<T>::Iterator::Iterator( Queue<T>* queue, int index) :
queue(queue), index(index)
{}


template<class T>
T& Queue<T>::Iterator::operator*() const {
  assert(index >= 0 && index < queue->size());
  Queue<T>::Node* tmp=queue->m_head;
  for(int i=0;i<index;i++){
    tmp=tmp->m_next; 
  }
  return tmp->m_data;
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++() {
  if(*this==queue->end()){
    throw Queue<T>::Iterator::InvalidOperation();
  }
  ++index;
  return *this;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int) {
  if(this==queue->end()){
    throw Queue<T>::Iterator::InvalidOperation();
  }
  Iterator result = *this;
  ++*this;
  return result;
}

template<class T>
bool Queue<T>::Iterator::operator==(const Iterator& other) const {
  assert(queue == other.queue);
  return index == other.index;
} 

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& other) const {
  return !(*this == other);
}

////////////////////////// the end of implementing class Iterator ////////////////////////////////


template<class T>
class Queue<T>::ConstIterator {

public:

const T& operator*() const;

ConstIterator& operator++();

ConstIterator operator++(int);

bool operator==(const ConstIterator& other) const;

bool operator!=(const ConstIterator& other) const;

ConstIterator(const ConstIterator&) = default;

ConstIterator& operator=(const ConstIterator&) = default;

class InvalidOperation{};


private:

const Queue<T>* queue;

int index;

ConstIterator(const Queue<T>* queue, int index);

friend class Queue<T>;

};


template<class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, int index) :
queue(queue), index(index)
{}


template<class T>
const T& Queue<T>::ConstIterator::operator*() const {
  assert(index >= 0 && index < queue->size());
  Queue<T>::Node* tmp=queue->m_head;
  for(int i=0;i<index;i++){
    tmp=tmp->m_next; 
  }
  return tmp->m_data;
}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++() {
  if(*this==queue->end()){
    throw Queue<T>::ConstIterator::InvalidOperation();
  }
  ++index;
  return *this;
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int) {
  if(this==queue->end()){
    throw Queue<T>::ConstIterator::InvalidOperation();
  }
  ConstIterator result = *this;
  ++*this;
  return result;
}

template<class T>
bool Queue<T>::ConstIterator::operator==(const ConstIterator& other) const {
  assert(queue == other.queue);
  return index == other.index;
} 

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& other) const {
  return !(*this == other);
}

////////////////////////// the end of implementing class ConstIterator ////////////////////////////////

#endif //EX3_QUEUE_H
