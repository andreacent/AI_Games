#ifndef _Graph_
	#define _Graph_
	#include "graph.h"
#endif

#include <set>
#include "pathfindAStar.h"

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

void Graph::createGameGraph()
{
    nodes[1] = Node(1, new vec3[3]{vec3(5,0,25),vec3(14,0,25),vec3(5,0,34)}, set<int>{2,78} );
    nodes[2] = Node(2, new vec3[3]{vec3(5,0,34),vec3(14,0,34),vec3(14,0,25)} );
    nodes[3] = Node(3, new vec3[3]{vec3(14,0,33),vec3(14,0,26),vec3(16,0,26)} );
    nodes[4] = Node(4, new vec3[3]{vec3(14,0,33),vec3(16,0,26),vec3(16,0,33)} );
    nodes[5] = Node(5, new vec3[3]{vec3(16,0,34),vec3(21,0,34),vec3(16,0,25)} );
    nodes[6] = Node(6, new vec3[3]{vec3(21,0,25),vec3(21,0,34),vec3(16,0,25)} );
    nodes[7] = Node(7, new vec3[3]{vec3(21,0,33),vec3(23,0,25),vec3(21,0,25)}, set<int>{8,10} );
    nodes[8] = Node(8, new vec3[3]{vec3(21,0,33),vec3(23,0,25),vec3(23,0,33)}, set<int>{11} ); 
    nodes[9] = Node(9, new vec3[3]{vec3(21,0,23),vec3(24,0,23),vec3(21,0,25)} );
    nodes[10] = Node(10, new vec3[3]{vec3(24,0,25),vec3(24,0,23),vec3(21,0,25)} );
    nodes[11] = Node(11, new vec3[3]{vec3(23,0,25),vec3(23,0,34),vec3(25,0,25)} );
    nodes[12] = Node(12, new vec3[3]{vec3(25,0,34),vec3(23,0,34),vec3(25,0,25)} );
    nodes[13] = Node(13, new vec3[3]{vec3(25,0,25),vec3(27,0,25),vec3(25,0,33)} );
    nodes[14] = Node(14, new vec3[3]{vec3(27,0,33),vec3(27,0,25),vec3(25,0,33)} );
    nodes[15] = Node(15, new vec3[3]{vec3(27,0,25),vec3(27,0,34),vec3(29,0,25)} );
    nodes[16] = Node(16, new vec3[3]{vec3(29,0,34),vec3(27,0,34),vec3(29,0,25)} );
    nodes[17] = Node(17, new vec3[3]{vec3(29,0,25),vec3(31,0,25),vec3(29,0,33)}, set<int>{18,20} );
    nodes[18] = Node(18, new vec3[3]{vec3(31,0,25),vec3(29,0,33),vec3(31,0,33)}, set<int>{21} );
    nodes[19] = Node(19, new vec3[3]{vec3(30,0,23),vec3(33,0,23),vec3(30,0,25)} );
    nodes[20] = Node(20, new vec3[3]{vec3(33,0,23),vec3(33,0,25),vec3(30,0,25)}, set<int>{22} );
    nodes[21] = Node(21, new vec3[3]{vec3(31,0,25),vec3(31,0,34),vec3(36,0,34)}, set<int>{18,22} );
    nodes[22] = Node(22, new vec3[3]{vec3(36,0,25),vec3(31,0,25),vec3(36,0,34)}, set<int>{20,21,23} );
    nodes[23] = Node(23, new vec3[3]{vec3(36,0,26),vec3(36,0,33),vec3(38,0,26)} );
    nodes[24] = Node(24, new vec3[3]{vec3(38,0,33),vec3(36,0,33),vec3(38,0,26)}, set<int>{25,34} );
    nodes[25] = Node(25, new vec3[3]{vec3(38,0,30),vec3(38,0,34),vec3(43,0,30)}, set<int>{26,33} );
    nodes[26] = Node(26, new vec3[3]{vec3(43,0,34),vec3(38,0,34),vec3(43,0,30)} );
    nodes[27] = Node(27, new vec3[3]{vec3(43,0,33),vec3(43,0,30),vec3(45,0,33)} );
    nodes[28] = Node(28, new vec3[3]{vec3(45,0,30),vec3(43,0,30),vec3(45,0,33)}, set<int>{29,32,33} );
    nodes[29] = Node(29, new vec3[3]{vec3(45,0,31),vec3(47,0,33),vec3(45,0,34)}, set<int>{30,80} );
    nodes[30] = Node(30, new vec3[3]{vec3(45,0,31),vec3(47,0,33),vec3(49,0,31)} );
    nodes[31] = Node(31, new vec3[3]{vec3(45,0,31),vec3(48,0,25),vec3(48,0,31)} );
    nodes[32] = Node(32, new vec3[3]{vec3(45,0,31),vec3(48,0,25),vec3(45,0,25)}, set<int>{33,35} );
    nodes[33] = Node(33, new vec3[3]{vec3(38,0,30),vec3(45,0,30),vec3(45,0,25)} );
    nodes[34] = Node(34, new vec3[3]{vec3(38,0,30),vec3(45,0,25),vec3(38,0,25)} );
    nodes[35] = Node(35, new vec3[3]{vec3(41,0,25),vec3(48,0,25),vec3(48,0,16)} );
    nodes[36] = Node(36, new vec3[3]{vec3(41,0,25),vec3(41,0,16),vec3(48,0,16)} );
    nodes[37] = Node(37, new vec3[3]{vec3(39,0,16),vec3(48,0,16),vec3(48,0,12)} );
    nodes[38] = Node(38, new vec3[3]{vec3(39,0,16),vec3(39,0,12),vec3(48,0,12)}, set<int>{39,41,43,45,47} );
    nodes[39] = Node(39, new vec3[3]{vec3(39,0,12),vec3(43,0,12),vec3(39,0,7)}, set<int>{40,47} );
    nodes[40] = Node(40, new vec3[3]{vec3(43,0,7),vec3(43,0,12),vec3(39,0,7)} );
    nodes[41] = Node(41, new vec3[3]{vec3(43,0,12),vec3(45,0,12),vec3(43,0,8)} );
    nodes[42] = Node(42, new vec3[3]{vec3(45,0,8),vec3(43,0,8),vec3(45,0,12)} );
    nodes[43] = Node(43, new vec3[3]{vec3(45,0,12),vec3(45,0,7),vec3(47,0,12)} );
    nodes[44] = Node(44, new vec3[3]{vec3(47,0,7),vec3(45,0,7),vec3(47,0,12)} );
    nodes[45] = Node(45, new vec3[3]{vec3(47,0,12),vec3(49,0,12),vec3(47,0,8)} );
    nodes[46] = Node(46, new vec3[3]{vec3(49,0,8),vec3(49,0,12),vec3(47,0,8)}, false );
    nodes[47] = Node(47, new vec3[3]{vec3(39,0,15),vec3(37,0,15),vec3(39,0,7)} );
    nodes[48] = Node(48, new vec3[3]{vec3(37,0,7),vec3(37,0,15),vec3(39,0,7)}, set<int>{49,53} );
    nodes[49] = Node(49, new vec3[3]{vec3(33,0,16),vec3(37,0,12),vec3(37,0,16)} );
    nodes[50] = Node(50, new vec3[3]{vec3(33,0,16),vec3(37,0,12),vec3(33,0,12)}, set<int>{51,53} );
    nodes[51] = Node(51, new vec3[3]{vec3(30,0,17),vec3(33,0,12),vec3(33,0,17)}, set<int>{52} );
    nodes[52] = Node(52, new vec3[3]{vec3(30,0,17),vec3(33,0,12),vec3(30,0,12)}, set<int>{53,55,61} );
    nodes[53] = Node(53, new vec3[3]{vec3(31,0,12),vec3(37,0,7),vec3(37,0,12)} );
    nodes[54] = Node(54, new vec3[3]{vec3(31,0,12),vec3(37,0,7),vec3(31,0,7)} );
    nodes[55] = Node(55, new vec3[3]{vec3(27,0,12),vec3(31,0,7),vec3(31,0,12)}, set<int>{56,62} );
    nodes[56] = Node(56, new vec3[3]{vec3(27,0,12),vec3(31,0,7),vec3(27,0,7)} );
    nodes[57] = Node(57, new vec3[3]{vec3(25,0,12),vec3(27,0,8),vec3(27,0,12)}, set<int>{58,62} );
    nodes[58] = Node(58, new vec3[3]{vec3(25,0,12),vec3(27,0,8),vec3(25,0,8)} );
    nodes[59] = Node(59, new vec3[3]{vec3(16,0,12),vec3(25,0,7),vec3(25,0,12)}, set<int>{60,62,64,66} );
    nodes[60] = Node(60, new vec3[3]{vec3(16,0,12),vec3(25,0,7),vec3(16,0,7)}, set<int>{67} );
    nodes[61] = Node(61, new vec3[3]{vec3(24,0,16),vec3(30,0,12),vec3(30,0,16)} );
    nodes[62] = Node(62, new vec3[3]{vec3(24,0,16),vec3(30,0,12),vec3(24,0,12)} );
    nodes[63] = Node(63, new vec3[3]{vec3(21,0,17),vec3(24,0,12),vec3(24,0,17)} );
    nodes[64] = Node(64, new vec3[3]{vec3(21,0,17),vec3(24,0,12),vec3(21,0,12)} );
    nodes[65] = Node(65, new vec3[3]{vec3(16,0,16),vec3(21,0,12),vec3(21,0,16)} );
    nodes[66] = Node(66, new vec3[3]{vec3(16,0,16),vec3(21,0,12),vec3(16,0,12)} );
    nodes[67] = Node(67, new vec3[3]{vec3(14,0,15),vec3(16,0,8),vec3(16,0,15)} );
    nodes[68] = Node(68, new vec3[3]{vec3(14,0,15),vec3(16,0,8),vec3(14,0,8)} );
    nodes[69] = Node(69, new vec3[3]{vec3(12,0,16),vec3(14,0,7),vec3(14,0,16)} );
    nodes[70] = Node(70, new vec3[3]{vec3(12,0,16),vec3(14,0,7),vec3(12,0,7)} );//set<int>{71,76} no creo que deba llegar a 76
    nodes[71] = Node(71, new vec3[3]{vec3(10,0,15),vec3(12,0,7),vec3(12,0,15)}, set<int>{72,75} );
    nodes[72] = Node(72, new vec3[3]{vec3(10,0,15),vec3(12,0,7),vec3(10,0,7)} );
    nodes[73] = Node(73, new vec3[3]{vec3(5,0,15),vec3(10,0,8),vec3(10,0,15)}, set<int>{74,75} );
    nodes[74] = Node(74, new vec3[3]{vec3(5,0,15),vec3(10,0,8),vec3(5,0,8)}, false );
    nodes[75] = Node(75, new vec3[3]{vec3(5,0,17),vec3(12,0,15),vec3(5,0,15)} );
    nodes[76] = Node(76, new vec3[3]{vec3(5,0,17),vec3(12,0,15),vec3(12,0,17)} );
    nodes[77] = Node(77, new vec3[3]{vec3(12,0,17),vec3(5,0,25),vec3(0,0,17)}, set<int>{78,79} );
    nodes[78] = Node(78, new vec3[3]{vec3(12,0,25),vec3(5,0,25),vec3(12,0,17)}, false );
    nodes[79] = Node(79, new vec3[3]{vec3(0,0,25),vec3(5,0,25),vec3(0,0,17)}, false );

    nodes[80] = Node(80, new vec3[3]{vec3(45,0,34),vec3(47,0,34),vec3(47,0,33)},false );//sobre 29


    setDistances();

    /*
    for (map<int,Node>::iterator it = nodes.begin(); it != nodes.end(); ++it ){
        (*it).second.printNodeInfo();
    }
    */
}