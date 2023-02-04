#ifndef GRAPHS_S21_GRAPH_H
#define GRAPHS_S21_GRAPH_H
#include <fstream>
#include <iostream>
#include <sstream>

#include "../containers/simple_queue/simple_queue.h"

class Graph {
 private:
  int _size;
  int **_matrix;
  bool _ifSymmetric;

  void _clearMatrix(void);
  void _matrixValidation(std::string filename);
  void _checkConnection(void);
  class FileErrorException : public std::exception {
   public:
    const char *what() const noexcept;
  };

  class InvalidGraph : public std::exception {
   public:
    const char *what() const noexcept;
  };

 public:
  ~Graph();
  Graph();
  void loadGraphFromFile(std::string filename);
  void exportGraphToDot(std::string filename);

  int getSize();
  int **getMatrix();
};

#endif
