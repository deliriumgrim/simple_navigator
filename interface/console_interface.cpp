#include "console_interface.h"

auto ConsoleInterface::showMenu() -> void {
  std::cout << "1. Load graph file" << std::endl
            << "2. Bread-search algorithm" << std::endl
            << "3. Depth-search algorithm" << std::endl
            << "4. Dijkstra's algorithm" << std::endl
            << "5. Floyd–Warshall's algorithm" << std::endl
            << "6. Prim's algorithm" << std::endl
            << "7. Travelling salesman problem algorithm" << std::endl
            << "8. Export graph to DOT" << std::endl
            << "9. Exit" << std::endl;
}

auto ConsoleInterface::getInput() -> int {
  std::string input;
  int result = 0;
  std::cout << ">> ";
  std::cin >> input;
  try {
    result = std::stoi(input);
  } catch (const std::exception &ex) {
  }
  return (result);
}

auto ConsoleInterface::depthAlg() -> void {
  int startVertex;
  int *arr = nullptr;
  std::cout << "Enter start vertex ";
  startVertex = this->getInput();
  try {
    arr = this->_alg.depthFirstSearch(this->_graph, startVertex);
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return;
  }
  for (int i = 0; i < this->_graph.getSize(); ++i) {
    std::cout << arr[i] << ' ';
  }
  std::cout << std::endl;
  delete[] arr;
}

auto ConsoleInterface::breadAlg() -> void {
  int startVertex;
  int *arr = nullptr;
  std::cout << "Enter start vertex ";
  startVertex = this->getInput();
  try {
    arr = this->_alg.breadFirstSearch(this->_graph, startVertex);
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return;
  }
  for (int i = 0; i < this->_graph.getSize(); ++i) {
    std::cout << arr[i] << ' ';
  }
  std::cout << std::endl;
  delete[] arr;
}

auto ConsoleInterface::dijkstraAlg() -> void {
  int startVertex;
  int endVertex;
  int result;
  std::cout << "Enter start vertex ";
  startVertex = this->getInput();
  std::cout << "Enter end vertex ";
  endVertex = this->getInput();
  try {
    result = this->_alg.getShortestPathBetweenVertices(this->_graph,
                                                       startVertex, endVertex);
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return;
  }
  std::cout << "Shortest path: " << result << std::endl;
}

auto ConsoleInterface::floydWarshallAlg() -> void {
  int **arr = nullptr;
  try {
    arr = this->_alg.getShortestPathsBetweenAllVertices(this->_graph);
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return;
  }
  std::cout << "Size of matrix: " << this->_graph.getSize() << std::endl;
  for (int i = 0; i < this->_graph.getSize(); ++i) {
    for (int j = 0; j < this->_graph.getSize(); ++j) {
      std::cout << arr[i][j] << ' ';
    }
    std::cout << std::endl;
    delete[] arr[i];
  }
  delete[] arr;
}

auto ConsoleInterface::primsAlg() -> void {
  int **arr = nullptr;
  try {
    arr = this->_alg.getLeastSpanningTree(this->_graph);
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return;
  }
  std::cout << "Size of matrix: " << this->_graph.getSize() << std::endl;
  for (int i = 0; i < this->_graph.getSize(); ++i) {
    for (int j = 0; j < this->_graph.getSize(); ++j) {
      std::cout << arr[i][j] << ' ';
    }
    std::cout << std::endl;
    delete[] arr[i];
  }
  delete[] arr;
}

auto ConsoleInterface::tspAlg() -> void {
  TsmResult tsm;
  std::cout << "Please wait...." << std::endl;
  try {
    tsm = this->_alg.solveTravelingSalesmanProblem(this->_graph);
  } catch (const std::exception &ex) {
    std::cout << ex.what() << std::endl;
    return;
  }
  if (tsm.distance == INFINITY) {
    std::cout << "Route not found" << std::endl;
    return;
  }
  std::cout << "Distance: " << tsm.distance << std::endl;
  std::cout << "Route: ";
  for (auto &elem : tsm.vertices) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
}

auto ConsoleInterface::executeCommand(int number) -> void {
  std::string path;
  switch (number) {
    case 1:
      std::cout << "Please enter path to graph file: ";
      std::cin >> path;
      try {
        this->_graph.loadGraphFromFile(path);
      } catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
      }
      break;
    case 2:
      this->breadAlg();
      break;
    case 3:
      this->depthAlg();
      break;
    case 4:
      this->dijkstraAlg();
      break;
    case 5:
      this->floydWarshallAlg();
      break;
    case 6:
      this->primsAlg();
      break;
    case 7:
      this->tspAlg();
      break;
    case 8:
      std::cout << "Enter file name: ";
      std::cin >> path;
      try {
        this->_graph.exportGraphToDot(path);
      } catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
      }
      break;
    default:
      std::cout << "Command not found" << std::endl;
  }
}

auto ConsoleInterface::start() -> void {
  int choice;
  std::string tmp;
  system("clear");
  while (true) {
    this->showMenu();
    choice = this->getInput();
    system("clear");
    if (choice == 9) {
      break;
    }
    this->executeCommand(choice);
    std::cout << "Press any button: ";
    std::cin >> tmp;
    system("clear");
  }
}