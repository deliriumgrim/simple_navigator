#ifndef STACK_H
#define STACK_H

#include <iostream>

#include "../node.h"

namespace s21 {
template <class T>
class Stack {
 public:
  Stack(void);
  ~Stack(void);

  bool isEmpty(void);

  void init(void);
  void push(T _data);
  T pop(void);
  T peek(void);

 private:
  Node<T> *_node;
  int _size;

  void popInLoop(void);
};
}  // namespace s21

template <class T>
s21::Stack<T>::Stack(void) : _node(nullptr), _size(0) {}

template <class T>
void s21::Stack<T>::init(void) {
  if (!this->_node) {
    return;
  } else {
    this->popInLoop();
  }
}

template <class T>
void s21::Stack<T>::push(T _data) {
  if (!this->_node) {
    this->_node = new Node<T>;
    this->_node->data = _data;
    this->_size++;
  } else {
    this->_node->next = new Node<T>;
    this->_node->next->prev = this->_node;
    this->_node->next->next = nullptr;
    this->_node->next->data = _data;
    this->_node = this->_node->next;
    this->_size++;
  }
}

template <class T>
T s21::Stack<T>::pop(void) {
  if (!this->_node) {
    throw std::out_of_range("Error: stack is empty");
  } else {
    T _data = this->_node->data;
    Node<T> *tmp = this->_node;
    this->_node = this->_node->prev;
    delete tmp;
    this->_size--;
    return (_data);
  }
}

template <class T>
T s21::Stack<T>::peek(void) {
  if (!this->_node) {
    throw std::out_of_range("Error: stack is empty");
  }
  return (this->_node->data);
}

template <class T>
void s21::Stack<T>::popInLoop(void) {
  while (this->_node) {
    this->pop();
  }
}

template <class T>
bool s21::Stack<T>::isEmpty() {
  return (this->_node == NULL);
}

template <class T>
s21::Stack<T>::~Stack(void) {
  if (!this->_node) {
    return;
  }
  this->popInLoop();
}

#endif
