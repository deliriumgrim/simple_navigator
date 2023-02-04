#include "s21_graph_algorithms.h"

#include "../aco/colony.h"

int *GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) {
  if (graph.getSize() == 0 || graph.getMatrix() == nullptr) {
    throw EmptyGraphException();
  }
  if (startVertex <= 0 || startVertex > graph.getSize()) {
    throw IncorrectVertexException();
  }
  s21::Stack<int> stack;
  int *res = new int[graph.getSize()];
  int count = 0;
  int vertex[graph.getSize()];
  int **matrix = graph.getMatrix();
  for (int i = 0; i < graph.getSize(); i++) {
    vertex[i] = 0;
  }
  stack.push(startVertex - 1);
  while (!stack.isEmpty()) {
    int node = stack.pop();
    if (vertex[node] == 1) continue;
    vertex[node] = 1;
    for (int j = graph.getSize() - 1; j >= 0; j--) {
      if (matrix[node][j] != 0 && vertex[j] != 1) {
        stack.push(j);
      }
    }
    res[count++] = node + 1;
  }
  return res;
}

int *GraphAlgorithms::breadFirstSearch(Graph &graph, int startVertex) {
  if (graph.getSize() == 0 || graph.getMatrix() == nullptr) {
    throw EmptyGraphException();
  }
  if (startVertex <= 0 || startVertex > graph.getSize()) {
    throw IncorrectVertexException();
  }
  s21::Queue<int> queue;
  int **matrix = graph.getMatrix();
  int *res = new int[graph.getSize()];
  int count = 0;
  int vertex[graph.getSize()];
  for (int i = 0; i < graph.getSize(); i++) {
    vertex[i] = 0;
  }
  queue.push(startVertex - 1);
  while (!queue.isEmpty()) {
    int node = queue.pop();
    vertex[node] = 1;
    for (int j = 0; j < graph.getSize(); j++) {
      if (matrix[node][j] != 0 && vertex[j] == 0) {
        queue.push(j);
        vertex[j] = 1;
      }
    }
    res[count++] = node + 1;
  }
  return res;
}

int GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  if (graph.getSize() == 0 || graph.getMatrix() == nullptr) {
    throw EmptyGraphException();
  }
  if (vertex1 <= 0 || vertex1 > graph.getSize() || vertex2 <= 0 ||
      vertex2 > graph.getSize()) {
    throw IncorrectVertexException();
  }
  int size = graph.getSize();
  int **matrix = graph.getMatrix();
  int distance[size];
  int vertex[size];
  int tmp, min_index, min;
  int begin_index = vertex1 - 1;
  for (int i = 0; i < size; i++) {
    distance[i] = INT32_MAX;
    vertex[i] = 0;
  }
  distance[begin_index] = 0;
  do {
    min_index = INT32_MAX;
    min = INT32_MAX;
    for (int i = 0; i < size; i++) {
      if ((vertex[i] == 0) && (distance[i] < min)) {
        min = distance[i];
        min_index = i;
      }
    }
    if (min_index != INT32_MAX) {
      for (int i = 0; i < size; i++) {
        if (matrix[min_index][i] > 0) {
          tmp = min + matrix[min_index][i];
          if (tmp < distance[i]) {
            distance[i] = tmp;
          }
        }
      }
      vertex[min_index] = 1;
    }
  } while (min_index < INT32_MAX);
  return distance[vertex2 - 1];
}

int **GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph) {
  if (graph.getSize() == 0 || graph.getMatrix() == nullptr) {
    throw EmptyGraphException();
  }
  int size = graph.getSize();
  int **copy_from = graph.getMatrix();
  double **matrix = new double *[size];
  for (int i = 0; i < size; ++i) {
    matrix[i] = new double[size];
  }
  int **result = new int *[size];
  for (int i = 0; i < size; ++i) {
    result[i] = new int[size];
  }
  for (int i = 0; i < graph.getSize(); ++i) {
    for (int j = 0; j < graph.getSize(); ++j) {
      matrix[i][j] = static_cast<double>(copy_from[i][j]);
      if (i == j) {
        matrix[i][j] = 0;
      } else if (i != j && matrix[i][j] == 0) {
        matrix[i][j] = INFINITY;
      }
    }
  }
  for (int k = 0; k < size; k++) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
      }
    }
  }
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      result[i][j] = static_cast<int>(matrix[i][j]);
    }
  }
  for (int i = 0; i < size; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
  return result;
}

int **GraphAlgorithms::getLeastSpanningTree(Graph &graph) {
  if (graph.getSize() == 0 || graph.getMatrix() == nullptr) {
    throw EmptyGraphException();
  }
  int size = graph.getSize();
  int **matrix = graph.getMatrix();
  int count = 0;
  int selected[size];
  int x, y;
  int **result = new int *[size];
  for (int i = 0; i < size; ++i) {
    result[i] = new int[size];
  }
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      result[i][j] = 0;
    }
  }
  for (int i = 0; i < size; ++i) {
    selected[i] = 0;
  }
  selected[0] = 1;
  while (count < size - 1) {
    int min = INT32_MAX;
    x = 0;
    y = 0;
    for (int i = 0; i < size; i++) {
      if (selected[i]) {
        for (int j = 0; j < size; j++) {
          if (!selected[j] && matrix[i][j]) {
            if (min > matrix[i][j]) {
              min = matrix[i][j];
              x = i;
              y = j;
            }
          }
        }
      }
    }
    result[x][y] = matrix[x][y];
    selected[y] = 1;
    count++;
  }
  return result;
}

TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph) {
  if (graph.getSize() == 0 || graph.getMatrix() == nullptr) {
    throw EmptyGraphException();
  }
  int num_of_ants = graph.getSize();
  int max_iter = 100;
  int iter_without_upgrade = 30;
  TsmResult result, prev_result;
  Colony colony(graph);

  result.distance = INFINITY;
  prev_result.distance = INFINITY;

  while (iter_without_upgrade) {
    colony.createAnts(num_of_ants);
    colony.findPath();
    colony.updateFeromon();
    colony.updateResult(result);

    if (result.distance == prev_result.distance) {
      iter_without_upgrade--;
    } else {
      prev_result = result;
      iter_without_upgrade = max_iter;
    }
  }
  for (int &a : result.vertices) {
    a++;
  }
  return result;
}

const char *GraphAlgorithms::IncorrectVertexException::what() const noexcept {
  return ("Exception: incorrect vertex");
}
const char *GraphAlgorithms::EmptyGraphException::what() const noexcept {
  return ("Exception: Graph is empty");
}
