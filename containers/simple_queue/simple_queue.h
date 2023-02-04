#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

#include "../node.h"

namespace s21 {
template <class T>
class Queue {
 public:
  Queue(void);
  ~Queue(void);

  bool isEmpty(void);

  void init(void);
  void push(T _data);
  T pop(void);
  T peek(void);

 private:
  Node<T> *_node;
  int _size;

  void popInLoop(void);
  void backToHead(void);
};
}  // namespace s21

template <class T>
s21::Queue<T>::Queue(void) : _node(nullptr), _size(0) {}

template <class T>
void s21::Queue<T>::init(void) {
  if (!this->_node) {
    return;
  } else {
    this->popInLoop();
  }
}

template <class T>
void s21::Queue<T>::push(T _data) {
  if (!this->_node) {
    this->_node = new Node<T>;
    this->_node->data = _data;
    this->_size++;
  } else {
    while (this->_node->next) {
      this->_node = this->_node->next;
    }
    this->_node->next = new Node<T>;
    this->_node->next->next = nullptr;
    this->_node->next->prev = this->_node;
    this->_node->next->data = _data;
    this->backToHead();
    this->_size++;
  }
}

template <class T>
T s21::Queue<T>::pop(void) {
  if (!this->_node) {
    throw std::out_of_range("Error: stack is empty");
  } else {
    Node<T> *tmp = this->_node;
    T _data = this->_node->data;
    this->_node = this->_node->next;
    delete tmp;
    if (this->_node) {
      this->_node->prev = nullptr;
    }
    this->_size--;
    return (_data);
  }
}

template <class T>
T s21::Queue<T>::peek(void) {
  if (!this->_node) {
    throw std::out_of_range("Error: stack is empty");
  }
  return (this->_node->data);
}

template <class T>
void s21::Queue<T>::popInLoop(void) {
  while (this->_node) {
    this->pop();
  }
}

template <class T>
void s21::Queue<T>::backToHead(void) {
  while (this->_node->prev) {
    this->_node = this->_node->prev;
  }
}

template <class T>
bool s21::Queue<T>::isEmpty() {
  return (this->_node == NULL);
}

template <class T>
s21::Queue<T>::~Queue(void) {
  if (!this->_node) {
    return;
  }
  this->popInLoop();
}

#endif
