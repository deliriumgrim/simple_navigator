#include "s21_graph.h"

Graph::~Graph() { this->_clearMatrix(); }

void Graph::_clearMatrix(void) {
  if (this->_matrix) {
    for (int i = 0; i < this->_size; ++i) {
      delete[] this->_matrix[i];
    }
    delete[] this->_matrix;
    this->_matrix = nullptr;
    this->_size = 0;
  }
}

void Graph::loadGraphFromFile(std::string filename) {
  _matrixValidation(filename);
  std::ifstream file(filename);
  this->_clearMatrix();
  file >> this->_size;
  this->_matrix = new int *[this->_size];
  for (int i = 0; i < this->_size; ++i) {
    this->_matrix[i] = new int[this->_size];
    for (int j = 0; j < this->_size; ++j) {
      file >> this->_matrix[i][j];
    }
  }
  file.close();
  int **matrix = this->_matrix;
  this->_ifSymmetric = true;
  for (int i = 0; i < this->_size; ++i) {
    for (int j = 0; j < this->_size; ++j) {
      if (matrix[i][j] != matrix[j][i]) {
        this->_ifSymmetric = false;
      }
    }
  }
  for (int i = 0; i < this->_size; ++i) {
    for (int j = 0; j < this->_size; ++j) {
      if (matrix[i][j] < 0) {
        this->_clearMatrix();
        throw InvalidGraph();
      }
    }
  }
  _checkConnection();
}

void Graph::exportGraphToDot(std::string filename) {
  if (this->_size == 0 || this->_matrix == nullptr) {
    throw InvalidGraph();
  }
  std::ofstream out;
  std::string temp;
  std::string sign;
  int **matrix = this->_matrix;
  out.open(filename + ".dot");
  if (!out.is_open()) {
    throw FileErrorException();
  }
  if (this->_ifSymmetric) {
    out << "graph graphname {" << std::endl;
    sign = "--";
  } else {
    out << "digraph graphname {" << std::endl;
    sign = "->";
  }
  for (int i = 0; i < this->_size; ++i) {
    for (int j = 0; j < this->_size; ++j) {
      if (i == j && matrix[i][j] == 0) {
        continue;
      } else if (matrix[i][j] == 0) {
        continue;
      } else if (matrix[i][j] != matrix[j][i]) {
        temp += std::to_string(i + 1) + sign + std::to_string(j + 1) +
                " [label=" + std::to_string(matrix[i][j]) + "]" + ";";
        out << temp << std::endl;
      } else if (i < j && this->_ifSymmetric) {
        temp += std::to_string(i + 1) + sign + std::to_string(j + 1) +
                " [label=" + std::to_string(matrix[i][j]) + "]" + ";";
        out << temp << std::endl;
      } else if (!this->_ifSymmetric) {
        temp += std::to_string(i + 1) + sign + std::to_string(j + 1) +
                " [label=" + std::to_string(matrix[i][j]) + "]" + ";";
        out << temp << std::endl;
      }
      temp.clear();
    }
  }
  out << "}";
  out.close();
  temp = "dot " + filename + ".dot " + "-Tpng -o " + filename + "_pic.png";
  system(temp.c_str());
}

void Graph::_matrixValidation(std::string filename) {
  if (this->_matrix != nullptr) {
    _clearMatrix();
  }
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw FileErrorException();
  }
  std::string tmp;
  int count1 = 0;
  int count2;
  int number;
  std::stringstream stream;
  getline(file, tmp, '\n');
  stream << tmp;
  while (stream >> this->_size) {
    count1++;
  }
  stream.clear();
  if (count1 != 1) {
    file.close();
    throw InvalidGraph();
  }
  count1 = 0;
  while (getline(file, tmp, '\n')) {
    count1++;
    stream << tmp;
    count2 = 0;
    while (stream >> number) {
      count2++;
    }
    if (count2 != this->_size) {
      file.close();
      throw InvalidGraph();
    }
    stream.clear();
  }

  if (count1 != this->_size) {
    file.close();
    throw InvalidGraph();
  }
  file.close();
}

void Graph::_checkConnection() {
  s21::Queue<int> queue;
  int **matrix = getMatrix();
  int *res = new int[getSize()];
  int count;
  int vertex[getSize()];
  for (int i = 1; i <= getSize(); ++i) {
    count = 0;
    for (int f = 0; f < getSize(); f++) {
      vertex[f] = 0;
      res[f] = 0;
    }
    queue.push(i - 1);
    while (!queue.isEmpty()) {
      int node = queue.pop();
      vertex[node] = 1;
      for (int j = 0; j < getSize(); j++) {
        if (matrix[node][j] != 0 && vertex[j] == 0) {
          queue.push(j);
          vertex[j] = 1;
        }
      }
      res[count++] = node + 1;
    }
    for (int j = 0; j < getSize(); ++j) {
      if (res[j] == 0) {
        delete[] res;
        _clearMatrix();
        throw InvalidGraph();
      }
    }
  }
  delete[] res;
}

int Graph::getSize() { return (this->_size); }

int **Graph::getMatrix() { return (this->_matrix); }

const char *Graph::FileErrorException::what() const noexcept {
  return ("Exception: file open error");
}

const char *Graph::InvalidGraph::what() const noexcept {
  return ("Exception: invalid graph");
}

Graph::Graph() : _size(0), _matrix(nullptr), _ifSymmetric(true) {}
