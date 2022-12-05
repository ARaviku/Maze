#pragma once
#include "maze.h"
#include<iostream>
#include<stack>

class DFS : public TreeSearch {
   public:
    DFS();
    bool solve();
    bool addNode(const NodePtr& node);

   private:
    std::stack<NodePtr>stack_list;
};
using DFSPtr = std::shared_ptr<DFS>;
