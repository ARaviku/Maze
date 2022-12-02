#pragma once
#include "maze.h"
// other includes
// --- Your code here
#include<iostream>
#include<queue>



// ---

/** \brief Breadth First Search solver */
class BFS : public TreeSearch {
   public:
    BFS();

    /** \brief Solve the planning problem. Override TreeSearch::solve() */
    bool solve();

    /** \brief add node to the tree */
    bool addNode(const NodePtr& node);

   private:
    // decide what data structure you need
    // --- Your code here
    // queue
    std::queue<NodePtr>q_list;
    
    // ---
};
using BFSPtr = std::shared_ptr<BFS>;
