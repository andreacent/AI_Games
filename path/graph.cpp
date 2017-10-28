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
    nodes[8] = Node(8, new vec3[3]{vec3(21,0,33),vec3(23,0,25),vec3(23,0,33)}, list<int>{7,11} ); 
    nodes[9] = Node(9, new vec3[3]{vec3(21,0,23),vec3(24,0,23),vec3(21,0,25)}, list<int>{10} );
    nodes[10] = Node(10, new vec3[3]{vec3(24,0,25),vec3(24,0,23),vec3(21,0,25)}, list<int>{7,11} );
    nodes[11] = Node(11, new vec3[3]{vec3(23,0,25),vec3(23,0,34),vec3(25,0,25)}, list<int>{10,8,12} );
    nodes[12] = Node(12, new vec3[3]{vec3(25,0,34),vec3(23,0,34),vec3(25,0,25)} );
    nodes[13] = Node(13, new vec3[3]{vec3(25,0,25),vec3(27,0,25),vec3(25,0,33)} );
    nodes[14] = Node(14, new vec3[3]{vec3(27,0,33),vec3(27,0,25),vec3(25,0,33)} );
    nodes[15] = Node(15, new vec3[3]{vec3(27,0,25),vec3(27,0,34),vec3(29,0,25)} );
    nodes[16] = Node(16, new vec3[3]{vec3(29,0,34),vec3(27,0,34),vec3(29,0,25)} );
    nodes[17] = Node(17, new vec3[3]{vec3(29,0,25),vec3(31,0,25),vec3(29,0,33)}, list<int>{16,18,20} );
    nodes[18] = Node(18, new vec3[3]{vec3(31,0,25),vec3(29,0,33),vec3(31,0,33)}, list<int>{17,21} );
    nodes[19] = Node(19, new vec3[3]{vec3(30,0,23),vec3(33,0,23),vec3(30,0,25)}, list<int>{20} );
    nodes[20] = Node(20, new vec3[3]{vec3(33,0,23),vec3(33,0,25),vec3(30,0,25)}, list<int>{17,22} );
    nodes[21] = Node(21, new vec3[3]{vec3(31,0,25),vec3(31,0,34),vec3(36,0,34)}, list<int>{18,22} );
    nodes[22] = Node(22, new vec3[3]{vec3(36,0,25),vec3(31,0,25),vec3(36,0,34)}, list<int>{20,21,23} );
    nodes[23] = Node(23, new vec3[3]{vec3(36,0,26),vec3(36,0,33),vec3(38,0,26)} );
    nodes[24] = Node(24, new vec3[3]{vec3(38,0,33),vec3(36,0,33),vec3(38,0,26)}, list<int>{23,25,33} );
    nodes[25] = Node(25, new vec3[3]{vec3(38,0,30),vec3(38,0,34),vec3(43,0,30)}, list<int>{24,26,34} );
    nodes[26] = Node(26, new vec3[3]{vec3(43,0,34),vec3(38,0,34),vec3(43,0,30)} );
    nodes[27] = Node(27, new vec3[3]{vec3(43,0,33),vec3(43,0,30),vec3(45,0,33)} );
    nodes[28] = Node(28, new vec3[3]{vec3(45,0,30),vec3(43,0,30),vec3(45,0,33)}, list<int>{27,29,34} );
    nodes[29] = Node(29, new vec3[3]{vec3(45,0,30),vec3(45,0,34),vec3(47,0,30)}, list<int>{28,30,34} );
    nodes[30] = Node(30, new vec3[3]{vec3(47,0,34),vec3(45,0,34),vec3(47,0,30)} );
    nodes[31] = Node(31, new vec3[3]{vec3(47,0,30),vec3(47,0,33),vec3(49,0,30)}, list<int>{30,32,34} );
    nodes[32] = Node(32, new vec3[3]{vec3(49,0,33),vec3(47,0,33),vec3(49,0,30)}, list<int>{31} );
    nodes[33] = Node(33, new vec3[3]{vec3(38,0,25),vec3(38,0,30),vec3(48,0,25)}, list<int>{24,34} );
    nodes[34] = Node(34, new vec3[3]{vec3(48,0,30),vec3(38,0,30),vec3(48,0,25)}, list<int>{25,28,29,31} );

    setDistances();
    /*
    for (map<int,Node>::iterator it = nodes.begin(); it != nodes.end(); ++it ){
        (*it).second.printNodeInfo();
    }
    */
}


void drawPath(std::vector<Node> path){
    vec3 p1,p2;

    vector<Node>::iterator itPath = path.begin();
    p1 = (*itPath).point;

    ++itPath;

    glColor3f(0,1,1);
    while (itPath != path.end()){
        p2 = (*itPath).point;
        glBegin(GL_LINES);
            glVertex3f( p1.x,p1.y,p1.z);
            glVertex3f( p2.x,p2.y,p2.z);
        glEnd();

        p1 = p2;
        ++itPath;
    }
}