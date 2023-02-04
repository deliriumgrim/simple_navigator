#include <gtest/gtest.h>

#include "../graph/s21_graph.h"
#include "../graph_algorithms/s21_graph_algorithms.h"

TEST(s21Graph, loadGraphFromFileTests) {
  Graph graph;

  ASSERT_NO_THROW(graph.loadGraphFromFile("tests/src/test_graph"));
  ASSERT_THROW(graph.loadGraphFromFile("exception"), std::exception);
  system("chmod 000 tests/src/test_graph");
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/test_graph"), std::exception);
  system("chmod 777 tests/src/test_graph");
  int expect[3][3] = {{0, 2, 3}, {2, 0, 3}, {3, 3, 0}};
  graph.loadGraphFromFile("tests/src/test_graph");
  int **current = graph.getMatrix();
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      ASSERT_EQ(expect[i][j], current[i][j]);
    }
  }
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/test_graph_negative"),
               std::exception);
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/not_connected_graph"),
               std::exception);
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/non_valid1"), std::exception);
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/non_valid2"), std::exception);
}

TEST(s21Graph, exportGraphToDotTests) {
  Graph graph;

  graph.loadGraphFromFile("tests/tmp/test_graph");
  ASSERT_NO_THROW(graph.exportGraphToDot("test1"));
  system("chmod 000 test1.dot");
  ASSERT_THROW(graph.exportGraphToDot("test1"), std::exception);
  system("chmod 777 test1.dot");
  ASSERT_NO_THROW(graph.exportGraphToDot("test1"));
  graph.loadGraphFromFile("tests/tmp/floyd_warshall");
  graph.exportGraphToDot("test2");
  system("rm -rf test1.dot");
  system("rm -rf test1_pic.png");
  system("rm -rf test2.dot");
  system("rm -rf test2_pic.png");
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/empty_graph"),
               std::exception);
  ASSERT_THROW(graph.exportGraphToDot("test3"), std::exception);
  system("rm -rf test3_pic.png");
  system("rm -rf test3.dot");
  ASSERT_NO_THROW(graph.loadGraphFromFile("tests/src/test_export"));
  ASSERT_NO_THROW(graph.exportGraphToDot("test4"));
  system("rm -rf test4_pic.png");
  system("rm -rf test4.dot");
}

TEST(s21GraphAlgorithms, breadSearchTests) {
  Graph graph;
  GraphAlgorithms alg;
  int expect[] = {1, 2, 3, 7, 4, 6, 5};
  int *current;

  graph.loadGraphFromFile("tests/src/depth_bread_search");
  current = alg.breadFirstSearch(graph, 1);
  for (int i = 0; i < 7; ++i) {
    ASSERT_EQ(expect[i], current[i]);
  }
  delete[] current;
  ASSERT_NO_THROW(current = alg.breadFirstSearch(graph, 1));
  delete[] current;
  ASSERT_THROW(current = alg.breadFirstSearch(graph, 0), std::exception);
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/empty_graph"),
               std::exception);
  ASSERT_THROW(alg.breadFirstSearch(graph, 1), std::exception);
}

TEST(s21GraphAlgorithms, depthSearchTests) {
  Graph graph;
  GraphAlgorithms alg;
  int expect[] = {1, 2, 3, 4, 5, 6, 7};
  int *current;

  graph.loadGraphFromFile("tests/src/depth_bread_search");
  current = alg.depthFirstSearch(graph, 1);
  for (int i = 0; i < 7; ++i) {
    ASSERT_EQ(expect[i], current[i]);
  }
  delete[] current;
  ASSERT_NO_THROW(current = alg.depthFirstSearch(graph, 1));
  delete[] current;
  ASSERT_THROW(current = alg.depthFirstSearch(graph, 0), std::exception);
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/empty_graph"),
               std::exception);
  ASSERT_THROW(alg.depthFirstSearch(graph, 1), std::exception);
}

TEST(s21GraphAlgorithms, deikstraTests) {
  Graph graph;
  GraphAlgorithms alg;
  int expect = 20;
  int current;

  graph.loadGraphFromFile("tests/src/deikstra");
  current = alg.getShortestPathBetweenVertices(graph, 1, 4);
  ASSERT_EQ(expect, current);
  ASSERT_NO_THROW(alg.getShortestPathBetweenVertices(graph, 2, 4));
  ASSERT_THROW(alg.getShortestPathBetweenVertices(graph, 0, 4), std::exception);
  ASSERT_THROW(alg.getShortestPathBetweenVertices(graph, 1, 7), std::exception);
  ASSERT_THROW(alg.getShortestPathBetweenVertices(graph, 1, 7), std::exception);
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/empty_graph"),
               std::exception);
  ASSERT_THROW(alg.getShortestPathBetweenVertices(graph, 1, 7), std::exception);
}

TEST(s21GraphAlgorithms, floydTests) {
  Graph graph;
  GraphAlgorithms alg;
  int expect[6][6] = {{0, 7, 9, 20, 20, 11}, {7, 0, 10, 15, 21, 12},
                      {9, 10, 0, 11, 11, 2}, {20, 15, 11, 0, 6, 13},
                      {20, 21, 11, 6, 0, 9}, {11, 12, 2, 13, 9, 0}};
  int **current;

  graph.loadGraphFromFile("tests/src/deikstra");
  current = alg.getShortestPathsBetweenAllVertices(graph);
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      ASSERT_EQ(expect[i][j], current[i][j]);
    }
    delete[] current[i];
  }
  delete[] current;
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/empty_graph"),
               std::exception);
  ASSERT_THROW(current = alg.getShortestPathsBetweenAllVertices(graph),
               std::exception);
}

TEST(s21GraphAlgorithms, primsTests) {
  Graph graph;
  GraphAlgorithms alg;
  int expect[5][5] = {{0, 3, 4, 0, 1},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 2, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0}};
  int **current;

  graph.loadGraphFromFile("tests/src/spanning_tree");
  current = alg.getLeastSpanningTree(graph);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      ASSERT_EQ(expect[i][j], current[i][j]);
    }
    delete[] current[i];
  }
  delete[] current;
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/empty_graph"),
               std::exception);
  ASSERT_THROW(current = alg.getLeastSpanningTree(graph), std::exception);
}

TEST(s21GraphAlgorithms, SalesmanTests) {
  Graph graph;
  GraphAlgorithms alg;
  TsmResult expect;
  TsmResult current;

  ASSERT_THROW(graph.loadGraphFromFile("tests/src/salesman_dont_work_alg"),
               std::exception);
  ASSERT_THROW(current = alg.solveTravelingSalesmanProblem(graph),
               std::exception);
  ASSERT_EQ(expect.vertices.empty(), current.vertices.empty());
  graph.loadGraphFromFile("tests/src/deikstra");
  current = alg.solveTravelingSalesmanProblem(graph);
  expect.vertices.push_back(1);
  ASSERT_EQ(expect.vertices.empty(), current.vertices.empty());
  ASSERT_THROW(graph.loadGraphFromFile("tests/src/empty_graph"),
               std::exception);
  ASSERT_THROW(current = alg.solveTravelingSalesmanProblem(graph),
               std::exception);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
