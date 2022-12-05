#pragma once
#include "maze.h"
#include<iostream>
#include<queue>

class BFS : public TreeSearch {
   public:
    BFS();
    bool solve();

    bool addNode(const NodePtr& node);

   private:
    std::queue<NodePtr>q_list;

};
using BFSPtr = std::shared_ptr<BFS>;
