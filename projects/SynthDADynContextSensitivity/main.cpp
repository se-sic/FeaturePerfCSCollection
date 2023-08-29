#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <string_view>
#include <vector>

/// TODO: implement context sensitive case

/// This synthetic case study targets cases of dynamic context sensitivity.
///
/// --reverse   : reverse input order
/// --max       : print largest single value
///
/// The key idea is that code is sometimes only conditionally dependent on
/// configuration options. However, depending on how this code is instrumented
/// and measured dynamic analyses can wrongly measure configuration-specific
/// code.

struct Node {
  Node(uint32_t data) { this->Data = data; }

  void printInOrder() {
    std::cout << "[";
    if (Left) {
      Left->printInOrder();
    }
    std::cout << " " << Data << " ";
    if (Right) {
      Right->printInOrder();
    }
    std::cout << "]";
  }

  uint32_t Data;
  std::unique_ptr<Node> Left, Right;
};

struct BinaryTree {
  BinaryTree(){};
  BinaryTree(int RootValue) : RootNode{std::make_unique<Node>(RootValue)} {};

  Node *root() { return RootNode.get(); }
  void addNewNode(uint32_t Value) {
    if (!RootNode) {
      RootNode = std::make_unique<Node>(Value);
      return;
    }

    std::queue<Node *> NodeQueue;
    NodeQueue.push(RootNode.get());

    while (!NodeQueue.empty()) {
      Node *CurrentNode = NodeQueue.front();
      NodeQueue.pop();

      if (!CurrentNode->Left) {
        CurrentNode->Left = std::make_unique<Node>(Value);
        break;
      }
      if (!CurrentNode->Right) {
        CurrentNode->Right = std::make_unique<Node>(Value);
        break;
      }

      NodeQueue.push(CurrentNode->Left.get());
      NodeQueue.push(CurrentNode->Right.get());
    }
  }

  void printInOrder() {
    if (!RootNode) {
      return;
    }

    RootNode->printInOrder();
    std::cout << '\n';
  }

private:
  std::unique_ptr<Node> RootNode;
};

uint32_t findSum(Node *CurrentNode, uint32_t TmpSum) {

  if (!CurrentNode) {
    return 0;
  }

  TmpSum = TmpSum * 10 + CurrentNode->Data;

  if (!CurrentNode->Left && !CurrentNode->Right) {
    return TmpSum;
  }

  return findSum(CurrentNode->Left.get(), TmpSum) +
         findSum(CurrentNode->Right.get(), TmpSum);
}

uint32_t findMax(Node *CurrentNode) {
  uint32_t LeftMax = 0;
  uint32_t RightMax = 0;
  if (CurrentNode->Left) {
    LeftMax = findMax(CurrentNode->Left.get());
  }
  if (CurrentNode->Right) {
    RightMax = findMax(CurrentNode->Right.get());
  }

  return std::max(CurrentNode->Data, std::max(LeftMax, RightMax));
}

int findRootToLeafPathsSum(BinaryTree &Tree) { return findSum(Tree.root(), 0); }

// ./DynContextSensitivity (--reverse) INPUT_DATA
// where INPUT_DATA = 1,2,3,4,5,6
// INPUT_DATA needs to be at least one value
//
//            1
//        2       3
//      4   5   6   _
//
int main(int argc, char *argv[]) {

  bool __attribute__((feature_variable("Reverse"))) Reverse =
      fp_util::isFeatureEnabled(argc, argv, "--reverse");
  bool __attribute__((feature_variable("Max"))) PrintMax =
      fp_util::isFeatureEnabled(argc, argv, "--max");

  BinaryTree Tree;

  std::string_view TreeString = argv[argc - 1];
  std::vector<uint32_t> Values;
  size_t Start = 0;
  while (Start < TreeString.length()) {
    size_t NextDelim =
        std::min(TreeString.find_first_of(',', Start), TreeString.length());
    uint32_t Val =
        std::stol(std::string(TreeString.substr(Start, NextDelim - Start)));
    Values.push_back(Val);

    Start = NextDelim + 1;
  }
  if (Reverse) {
    std::reverse(Values.begin(), Values.end());
  }
  for (auto Val : Values) {
    Tree.addNewNode(Val);
  }
  std::cout << "Got input data: ";
  Tree.printInOrder();

  std::cout << findRootToLeafPathsSum(Tree) << '\n';

  if (PrintMax) {
    std::cout << "MaxValue: " << findMax(Tree.root()) << '\n';
  }

  return 0;
}
