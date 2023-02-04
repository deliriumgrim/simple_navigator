#ifndef NODE_H
#define NODE_H

template <class T>
struct Node {
  T data;
  Node *next;
  Node *prev;

  Node(void) : next(nullptr), prev(nullptr) {}
};

#endif
