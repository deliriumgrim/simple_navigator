#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

#include "../graph/s21_graph.h"
#include "../graph_algorithms/s21_graph_algorithms.h"

class ConsoleInterface {
 public:
  auto start() -> void;

 private:
  Graph _graph;
  GraphAlgorithms _alg;

  auto showMenu() -> void;
  auto getInput() -> int;
  auto depthAlg() -> void;
  auto breadAlg() -> void;
  auto dijkstraAlg() -> void;
  auto floydWarshallAlg() -> void;
  auto primsAlg() -> void;
  auto tspAlg() -> void;
  auto executeCommand(int number) -> void;
};

#endif
