#ifndef _Graph_
	#define _Graph_
	#include "graph.h"
#endif

#include "pathfindAStar.h"

void Graph::createGameGraph()
{
    nodes[0] = Node(0, new vec3[3]{vec3(0,0,25),vec3(12,0,25),vec3(0,0,17)}, list<int>{1} );
    nodes[1] = Node(1, new vec3[3]{vec3(5,0,25),vec3(14,0,25),vec3(5,0,34)} );
    nodes[2] = Node(2, new vec3[3]{vec3(5,0,34),vec3(14,0,34),vec3(14,0,25)} );
    nodes[3] = Node(3, new vec3[3]{vec3(14,0,33),vec3(14,0,26),vec3(16,0,26)} );
    nodes[4] = Node(4, new vec3[3]{vec3(14,0,33),vec3(16,0,26),vec3(16,0,33)} );
    nodes[5] = Node(5, new vec3[3]{vec3(16,0,34),vec3(21,0,34),vec3(16,0,25)} );
    nodes[6] = Node(6, new vec3[3]{vec3(21,0,25),vec3(21,0,34),vec3(16,0,25)} );
    nodes[7] = Node(7, new vec3[3]{vec3(21,0,33),vec3(23,0,25),vec3(21,0,25)}, list<int>{6,8,10} );
    nodes[8] = Node(8, new vec3[3]{vec3(21,0,33),vec3(23,0,25),vec3(23,0,33)}, list<int>{7} ); //11
    nodes[9] = Node(9, new vec3[3]{vec3(21,0,23),vec3(24,0,23),vec3(21,0,25)}, list<int>{10} );
    nodes[10] = Node(10, new vec3[3]{vec3(24,0,25),vec3(24,0,23),vec3(21,0,25)}, list<int>{7} );//11

    setDistances();
    /*
    for (map<int,Node>::iterator it = nodes.begin(); it != nodes.end(); ++it ){
        (*it).second.printNodeInfo();
    }
    */
}
