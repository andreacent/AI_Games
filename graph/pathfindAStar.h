#ifndef ASTART_H
#define ASTART_H

#include <queue>
#include <map>
#include <list>
#include <vector>
#include <set>

#include "graph.h"

std::list<glm::vec3> pathfindAStar(Graph graph, glm::vec3 posStart, glm::vec3 posEnd){ 
    //This structure is used to keep track of the information we need for each node
    struct NodeRecord{
        NodeRecord* father = NULL;
        Node node;
        float costSoFar;
        float estimatedTotalCost;
    };

    class CompareNodes {
    public:
        bool operator()(NodeRecord &n1, NodeRecord &n2) {
            if (n1.estimatedTotalCost  > n2.estimatedTotalCost ) return true;
            return false;
        }
    };

    //get start and goal nodes 
    std::list<glm::vec3> path;
    Node start,goal;
    if (!graph.getNode(posStart, start) || !graph.getNode(posEnd, goal)) return path;
    Heuristic heuristic = {goal};
        
    // Initialize the record for the start node
    NodeRecord startRecord;
    startRecord.node = start;
    startRecord.costSoFar = 0;
    startRecord.estimatedTotalCost = heuristic.estimate(start);//heuristic.estimate(start,goal);

    // Initialize the open and closed lists
    std::priority_queue<NodeRecord, std::vector<NodeRecord>, CompareNodes> open; //open = PathfindingList(); 
    std::map<int,float> openMap; //almaceno el id del nodo y el costSoFar minimo
    std::map<int,NodeRecord> closed; //alamceno el id de los nodos cerrados

    open.push(startRecord); 

    NodeRecord current = startRecord;
  
    // Iterate through processing each node
    while (!open.empty()){
        // Find the smallest element in the open list (using the estimatedTotalCost)
        //current = open.smallestElement();
        current = open.top();        
        open.pop();
        openMap.erase(current.node.id);
        //cout<<"--- expande nodo "<<current.node.id<<endl;
        
        // If it is the goal node, then terminate
        if (current.node.id == goal.id) break;

        // Loop through each connection in turn
        for (set<int>::iterator itAdj = current.node.adjacent.begin(); 
            itAdj != current.node.adjacent.end(); 
            ++itAdj ){ 
            // Get the cost estimate for the end node
            Node endNode = graph.nodes[(*itAdj)];

            float endNodeCost = current.costSoFar + graph.distances[make_pair(current.node.id,endNode.id)];

            float endNodeHeuristic;
            NodeRecord endNodeRecord;

            // If the node is closed we may have to skip, or remove it from the closed list.
            if(closed.count(endNode.id) > 0){
                endNodeRecord = closed[endNode.id];       
                //cout<<endNodeRecord.node.id<<" cerrado con "<<endNodeRecord.costSoFar<<" <= endNodeCost "<<endNodeCost<<endl;    

                // If we didn’t find a shorter route, skip
                if (endNodeRecord.costSoFar <= endNodeCost) continue;

                // Otherwise remove it from the closed list
                closed.erase(endNode.id);

                // We can use the node’s old cost values
                // to calculate its heuristic without calling
                // the possibly expensive heuristic function
                //cout<<"node sacado de cerrado "<<endNodeRecord.node.id<<endl;
                endNodeHeuristic = endNodeRecord.estimatedTotalCost - endNodeRecord.costSoFar;
            }
            // Skip if the node is open and we’ve not found a better route
            else if (openMap.count(endNode.id) > 0){
                // Here we find the record in the open list corresponding to the endNode.
                // If our route is no better, then skip 

                //cout<<endNode.id<<" abierto con "<<openMap[endNode.id]<<" <= endNodeCost "<<endNodeCost<<endl;
                if (openMap[endNode.id] <= endNodeCost) continue;

                // SOLUCION ANIMAL
                //creo una nueva cola de prioridad
                //voy sacando de open y metiendo los items en newOpen hasta que encuentro endNodeRecord
                //al encontrar endNodeRecord, lo saco de open y devuelvo los items de newOpen a open
                std::priority_queue<NodeRecord, std::vector<NodeRecord>, CompareNodes> newOpen;
                endNodeRecord = open.top();
                open.pop();
                while(endNodeRecord.node.id != endNode.id){
                    newOpen.push(endNodeRecord);
                    endNodeRecord = open.top();     
                    open.pop();
                }
                while(!newOpen.empty()){
                    open.push(newOpen.top());
                    newOpen.pop();
                }

                openMap.erase(endNodeRecord.node.id);

                // We can use the node’s old cost values
                // to calculate its heuristic without calling
                // the possibly expensive heuristic function
                endNodeHeuristic = endNodeRecord.estimatedTotalCost - endNodeRecord.costSoFar;
            }
            // Otherwise we know we’ve got an unvisited node, so make a record for it
            else{
                endNodeRecord.node = endNode;

                // We’ll need to calculate the heuristic value
                // using the function, since we don’t have an
                // existing record to use
                endNodeHeuristic = heuristic.estimate(endNode);
            }

            // We’re here if we need to update the node
            // Update the cost, estimate and connection
            endNodeRecord.costSoFar = endNodeCost;
            endNodeRecord.father = new NodeRecord(current);
            endNodeRecord.estimatedTotalCost = endNodeCost + endNodeHeuristic;

            // And add it to the open list
            if(openMap.count(endNode.id) < 1){
                open.push(endNodeRecord); 
                openMap[endNodeRecord.node.id] = endNodeRecord.costSoFar;

                //cout<<"+ "<<endNodeRecord.node.id<<" entra a open con est. "<<endNodeRecord.estimatedTotalCost<<endl;
            }

        }
        // We’ve finished looking at the connections for
        // the current node, so add it to the closed list
        // and remove it from the open list        
        closed[current.node.id] = current;
    }

    // We’re here if we’ve either found the goal, or
    // if we’ve no more nodes to search, find which.
    if (current.node.id == goal.id){ 
        // Compile the list of connections in the path
        // Work back along the path, accumulating
        // connections

        path.push_front(current.node.point);
        NodeRecord *father = current.father;

        while (father != NULL){              
            path.push_front(father->node.point);
            father = father->father;
        }
        // Reverse the path, and return it
    }
    
    return path;
}

#endif