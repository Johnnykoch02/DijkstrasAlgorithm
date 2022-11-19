#ifndef DEQUE_H
#define DEQUE_H

#include "Node.hpp"
#include <iostream>
#include <stdexcept>

/**
 * @brief node Deque template class intialization and definition
 * 
 * @param T 
 */


template <class T>
class Deque {
 protected:
    
    Node<T>* head,* tail;;
    unsigned int length;

    public:
    class Iterator {
      private: Node<T>* current;
      public:
        Iterator(Node<T>* beginning) {
            this->current = beginning;
        }
        T* operator*() {
            return current->getData();
        }
        T* operator->() {
            return current->getData();
        } 
        void operator++() {
          current = current->next;
        }
        void operator--() {
          current = current->prev;
        }
        
        bool operator!=(const Iterator& other) {
            return this->current!= other.current;
        }
        bool operator==(const Iterator& other) {
          return this->current == other->current;
        }
    };

    protected:

    void link(Node<T>* a, Node<T>* b) {
    /*This process puts node a's next to b, and b's prev to a*/
    if(nullptr != a)/*Cannot dereference null...*/
        a->next = b;
    if(nullptr != b)
        b->prev = a;
}

 public:
    /* Initialize Deque */
    Deque() {
      this->head = nullptr;
      this->tail = nullptr;
      this->length = 0;
    }
    /* Removes Node Deque */
    ~Deque() { 
      // Node<T>* DequePtr = this->tail;
      // Node<T>* above;
      // while (nullptr != DequePtr) {
      //   above = DequePtr;
      //   above->setData(nullptr);
      //   DequePtr = DequePtr->prev;
      //   if (nullptr!= above) delete above;
      // }
    }
    void Destroy() {
      while (this->head != nullptr) this->popRight();
    }

    Node<T> * start() {
      return this->head;
    }

    Deque(T* dataPtr) {
      this->head = nullptr;
      this->tail = nullptr;
      this->length = 0;
      this->pushRight(dataPtr);
    }

    Deque(const Deque& other) {
      this->head = nullptr;
      this->tail = nullptr;

      Node<T> *dequePtr = other.head;
      while (nullptr != dequePtr) {
        this->pushRight(dequePtr->getData());
        dequePtr = dequePtr->next;
      }
      this->length = other.length;
    }

    size_t getLength() const {
      return this->length;
    }

    /**
     * @brief Method to add an existing program element to the Deque
     * 
     * @param dataPtr 
     */
    void pushLeft(T* dataPtr) {
      //std::cout<<*this<<std::endl;
      Node<T>* node = new Node<T>(dataPtr);
      if (nullptr == this->head) { /* n < 1 */
        this->head = node;
        this->tail = this->head;
      }

      else if (!this->isEmpty()) {
        this->link(node, this->head);
      }

      if (node) {
          this->head = node;
          this->length++;
      }
    }
    
    void pushRight(T* dataPtr) {
      //std::cout<<*this<<std::endl;
      Node<T>* node = new Node<T>(dataPtr);
      if (nullptr == this->head) { /* n < 1 */
      this->head = node;
      this->tail = this->head;
      }
      else if (!this->isEmpty()) {
        this->link(this->tail, node);
      }
      if (node) {
        this->tail = node;
        this->length++;
      }
    }
    
    /**
     * @brief to view the element at the top of the Deque
     * Warning! This variable is meant to be used for inqiury, not for usage in a program.
     * @return Node<T>* 
     */

    T* peekLeft() const {
        if ( this->head == nullptr ) return nullptr;
        return this->head->getData(); /* Could create a new here, ask Corsova*/
    }
    T* peekRight() const {
        if (this->tail == nullptr) return nullptr;
        return this->tail->getData(); /* Could create a new here, ask Corsova*/
    }

    /**
     * @brief to remove an element from the top of the Deque
     * 
     * @return Node<T>* 
     */

    T* popLeft() {
      //std::cout<<*this<<std::endl;
      /* Change the Tail, and free the old Tails memory. Reflect this change in the total. */
      if(this->length == 0) {
          throw std::runtime_error("Error: Cannot remove from empty deque...");
      }
      T * returnData = this->head->getData();
      this->head->setData(nullptr);
      Node<T>* old_head = this->head;
      if ( nullptr != old_head && old_head->hasNext() ) {
          this->head = old_head->next;
          link(nullptr, this->head);
          this->length--;
      }
      else { /* Single Node List */
          this->head = nullptr; this->tail = nullptr;
          this->length = 0;
      }
      delete old_head;
      return returnData;
    }
    T* popRight() {
      //std::cout<<*this<<std::endl;
      /* Change the Tail, and free the old Tails memory. Reflect this change in the total. */
      if(this->length == 0) {
          throw std::runtime_error("Error: Cannot remove from empty deque...");
      }
      T * returnData = this->tail->getData();
      this->tail->setData(nullptr);
      Node<T>* old_tail = this->tail;
      if ( nullptr != old_tail && old_tail->hasPrev() ) {
          this->tail = old_tail->prev;
          link(this->tail, nullptr);
          this->length--;
      }
      else { /* Single Node List */
          this->head = nullptr; this->tail = nullptr;
          this->length = 0;
      }
      delete old_tail;
      return returnData;
    }
    
    /**
     * @brief to verify whether the top fo the Deque is empty
     * 
     * @return true 
     * @return false 
     */

    bool isEmpty() const {
        return nullptr == this->head;
    }
    friend std::ostream& operator<<(std::ostream& out, const Deque<T>& d) {
      Node<T>* curr = d.head;
      out<<"Deque: " << &d << "\n";    
      while(nullptr != curr) {
        out<< "Node Data: "<<  *(curr->getData()) << "\n";
        curr = curr->next;
      }
      return out;
    }
    

};

#endif