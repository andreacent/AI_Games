#include <queue>
#include <map>
#include <set>
#include "graph.h"

float estimate(Node node,Node goal){
    return distance(node.position,goal.position);
}

std::vector<Node> pathfindAStar(Node start, Node end, Node goal){ //Graph graph, 
        
    //This structure is used to keep track of the information we need for each node
    struct NodeRecord{
        NodeRecord* parent;
        Node node;
        Connection* connection;
        float costSoFar;
        float estimatedTotalCost;
    };

    class CompareNodes {
    public:
        bool operator()(NodeRecord &n1, NodeRecord &n2) {
            if (n1.estimatedTotalCost  < n2.estimatedTotalCost ) return true;
            return false;
        }
    };


    // Initialize the record for the start node
    NodeRecord startRecord;
    startRecord.node = start;
    startRecord.costSoFar = 0;
    startRecord.estimatedTotalCost = estimate(start,goal);//heuristic.estimate(start,goal);

    // Initialize the open and closed lists
    std::priority_queue<NodeRecord, std::vector<NodeRecord>, CompareNodes> open; //open = PathfindingList(); 
    std::map<int,float> openMap; //almaceno el id del nodo y el costSoFar minimo
    std::vector<NodeRecord> closed; //closed = PathfindingList();
    std::set<int> closedSet; //alamceno el id de los nodos cerrados

    NodeRecord current = startRecord;

    open.push(startRecord);//open += startRecord;    

    // Iterate through processing each node
    while (!open.empty()){
        // Find the smallest element in the open list (using the estimatedTotalCost)
        //current = open.smallestElement();
        current = open.top();        
        open.pop();
        openMap.erase(current.node.id);
        
        // If it is the goal node, then terminate
        if (current.node.id == goal.id) break;

        // Otherwise get its outgoing connections
        //std::vector<Connection> connections = current.node.connections;

        // Loop through each connection in turn
        for (vector<Connection>::iterator iter = current.node.connections.begin(); 
                iter != current.node.connections.end(); 
                ++iter ){//for (connection in connections){
            // Get the cost estimate for the end node
            Connection connection = (*iter);
            Node endNode = connection.getToNode();
            float endNodeCost = current.costSoFar + connection.getCost();
            float endNodeHeuristic;
            NodeRecord endNodeRecord;

            // If the node is closed we may have to skip, or remove it from the closed list.
            if(closedSet.count(endNode.id) > 0){// (closed.contains(endNode)){                
                vector<NodeRecord>::iterator endNodeRecordIter;

                for (vector<NodeRecord>::iterator it = closed.begin(); it != closed.end(); ++it ){
                    if ((*it).node.id == endNode.id) {
                        // Here we find the record in the closed list corresponding to the endNode.
                        endNodeRecord = (*it);
                        endNodeRecordIter = it;
                        break;
                    }
                }               

                // If we didn’t find a shorter route, skip
                if (endNodeRecord.costSoFar <= endNodeCost) continue;

                // Otherwise remove it from the closed list
                closed.erase(endNodeRecordIter);
                closedSet.erase(endNode.id);

                // We can use the node’s old cost values
                // to calculate its heuristic without calling
                // the possibly expensive heuristic function
                endNodeHeuristic = endNodeCost - endNodeRecord.costSoFar;
            }
            // Skip if the node is open and we’ve not found a better route
            else if (openMap.count(endNode.id) > 0 && openMap[endNode.id] > endNodeCost){ //(open.contains(endNode)){
                // Here we find the record in the open list corresponding to the endNode.
                // If our route is no better, then skip 
                //if (endNodeRecord.costSoFar <= endNodeCost) continue;

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
                endNodeHeuristic = endNodeCost - endNodeRecord.costSoFar;
            }
            // Otherwise we know we’ve got an unvisited node, so make a record for it
            else{
                endNodeRecord.node = endNode;

                // We’ll need to calculate the heuristic value
                // using the function, since we don’t have an
                // existing record to use
                endNodeHeuristic = estimate(endNode,goal);//heuristic.estimate(endNode,goal);
            }

            // We’re here if we need to update the node
            // Update the cost, estimate and connection
            endNodeRecord.costSoFar = endNodeCost;
            endNodeRecord.parent = &current;
            endNodeRecord.connection = &connection;
            endNodeRecord.estimatedTotalCost = endNodeCost + endNodeHeuristic;

            // And add it to the open list
            if(openMap.count(endNode.id) < 1){
                open.push(endNodeRecord); 
                openMap[endNodeRecord.node.id] = endNodeRecord.costSoFar;
            }

        }
        // We’ve finished looking at the connections for
        // the current node, so add it to the closed list
        // and remove it from the open list        
        closed.push_back(current);
        closedSet.insert(current.node.id);
    }

    std::vector<Node> path;
    // We’re here if we’ve either found the goal, or
    // if we’ve no more nodes to search, find which.
    if (current.node.id != goal.id){
        // We’ve run out of nodes without finding the
        // goal, so there’s no solution
        return path;
    }
    else{ // Compile the list of connections in the path
        // Work back along the path, accumulating
        // connections
        while (current.node.id != start.id){            
            path.push_back(current.node);//path += current.connection;
            current = *current.parent;
        }
        // Reverse the path, and return it
        return path;
    }
}