#include "maze.h"
#include "bfs.h"
#include "dfs.h"

/** \brief Return the valid next states from a given state */
std::vector<State> ProblemDefinition::validStates(const State &state) const
{
    // HINT: use isStateValid()
    // --- Your code here
    std::vector<State> offsets = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    std::vector<State> valid_offsets;
    std::vector<State> offsets1 = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    // std::vector<State> valid_offsets1;
    if (allow_diagonal_ == true)
    {
        for (int i = 0; i < offsets.size(); i++)
        {
            State neighbor;
            neighbor.x = state.x + offsets[i].x;
            neighbor.y = state.y + offsets[i].y;

            if (isStateValid(neighbor) == true)
            {
                valid_offsets.push_back(neighbor);
            }
        }
    }
    else
    {
        for (int i = 0; i < offsets1.size(); i++)
        {
            State neighbor;
            neighbor.x = state.x + offsets1[i].x;
            neighbor.y = state.y + offsets1[i].y;
            if (isStateValid(neighbor) == true)
            {
                valid_offsets.push_back(neighbor);
            }
        }

        // ---
    }
    return valid_offsets;
}

/** \brief Given a node, extract the path from it to the root */
void TreeSearch::extractPath(NodePtr node)
{
    // --- Your code here
    Node curr_node = *node.get();
    while (curr_node.parent != nullptr)
    {
        path_.push_back(curr_node.state);
        curr_node = *curr_node.parent.get();
    }
    std::reverse(path_.begin(), path_.end());
    // ---
}

/** \brief Solve the planning problem. Override TreeSearch::solve() */
bool BFS::solve()
{
    // check start and goal are valid
    if (!pdef_.isStateValid(pdef_.startState()) ||
        !pdef_.isStateValid(pdef_.goalState()))
    {
        return false;
    }

    // if start and goal coincide, terminate
    auto start = pdef_.startState();
    if (pdef_.isGoal(start))
    {
        // std::cout << "Start and goal are e ,, n      ,llk,qual\n";
        return true;
    }

    NodePtr solution;
    // --- Your code here
    Node start_1;
    start_1.state = pdef_.startState();
    start_1.parent = nullptr;
    NodePtr startnodeptr;
    startnodeptr = std::make_shared<Node>(start_1);
    q_list.push(startnodeptr);
    visited_.push_back(start);

    while (!q_list.empty() == true)
    {

        NodePtr first = q_list.front();
        q_list.pop();
        bool end_cond = addNode(first);
        if (end_cond == true)
        {
            solution = first;
            break;
        }
    }

    // ---

    // get the path from last node to root
    extractPath(solution);

    return true;
}

/** \brief add node to the tree */
bool BFS::addNode(const NodePtr &node)
{
    // --- Your code here
    Node n = *node.get();
    State f = n.state;
    std::vector<State> neighbhors = pdef_.validStates(f);

    for (int i = 0; i < neighbhors.size(); i++)
    {
        // if (pdef_.isGoal(f))
        // {
        //     return true;
        // }
        Node pt;
        pt.state = neighbhors[i];
        pt.parent = node;

        NodePtr ptr;
        ptr = std::make_shared<Node>(pt);
        if (isVisited(ptr) == false)
        {
            visited_.push_back(neighbhors[i]);
            q_list.push(ptr);
        }
    }

    if (pdef_.isGoal(f))
    {
        return true;
    }
    // visited_.push_back(f);
    // q_list.pop();
    return false;
    // ---
}

/** \brief Solve the planning problem. Override TreeSearch::solve() */
bool DFS::solve()
{
    // check start and goal are valid
    if (!pdef_.isStateValid(pdef_.startState()) ||
        !pdef_.isStateValid(pdef_.goalState()))
    {
        return false;
    }

    // if start and goal coincide, terminate
    auto start = pdef_.startState();
    if (pdef_.isGoal(start))
    {
        std::cout << "Start and goal are equal\n";
        return true;
    }

    NodePtr solution;
    // --- Your code here
    Node start_1;
    start_1.state = pdef_.startState();
    start_1.parent = nullptr;
    NodePtr startnodeptr;
    startnodeptr = std::make_shared<Node>(start_1);
    stack_list.push(startnodeptr);
    visited_.push_back(start);

    while (!stack_list.empty() == true)
    {

        NodePtr first = stack_list.top();
        stack_list.pop();
        bool end_cond = addNode(first);
        if (end_cond == true)
        {
            solution = first;
            break;
        }
    }

    // ---

    // get the path from last node to root
    extractPath(solution);

    return true;
}

/** \brief add node to the tree */
bool DFS::addNode(const NodePtr &node)
{
    // --- Your code here
    Node n = *node.get();
    State f = n.state;
    std::vector<State> neighbhors = pdef_.validStates(f);
    if (pdef_.isGoal(f))
    {
        return true;
    }

    for (int i = 0; i < neighbhors.size(); i++)
    {

        Node pt;
        pt.state = neighbhors[i];
        pt.parent = node;

        NodePtr ptr;
        ptr = std::make_shared<Node>(pt);
        if (isVisited(ptr) == false)
        {
            visited_.push_back(neighbhors[i]);
            stack_list.push(ptr);
        }
    }

    // if (pdef_.isGoal(f))
    // {
    //     return true;
    // }
    // visited_.push_back(f);
    // q_list.pop();
    return false;
    // ---
}