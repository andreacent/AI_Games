#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "graph.h"
#include "pathfindAStar.h"

#include <set>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

void Graph::createGameGraph()
{
    int i = 0;
    nodes[0] = Node(i++, new vec3[3]{vec3(16,0,16),vec3(12,0,18),vec3(5,0,17)}, set<int>{1,90} ); // conect 90
    nodes[1] = Node(i++, new vec3[3]{vec3(5,0,17),vec3(5,0,25),vec3(12,0,18)}, set<int>{2} );
    nodes[2] = Node(i++, new vec3[3]{vec3(12,0,23),vec3(5,0,25),vec3(12,0,18)}, set<int>{3,52} );
    nodes[3] = Node(i++, new vec3[3]{vec3(5,0,34),vec3(5,0,25),vec3(12,0,23)}, set<int>{4} );
    nodes[4] = Node(i++, new vec3[3]{vec3(5,0,34),vec3(16,0,25),vec3(12,0,23)} );
    nodes[5] = Node(i++, new vec3[3]{vec3(5,0,34),vec3(16,0,25),vec3(10,0,34)} , set<int>{6,7});
    nodes[6] = Node(i++, new vec3[3]{vec3(14,0,28),vec3(14,0,34),vec3(10,0,34)}, set<int>{7} );
    nodes[7] = Node(i++, new vec3[3]{vec3(14,0,28),vec3(14,0,33),vec3(16,0,25)} );
    nodes[8] = Node(i++, new vec3[3]{vec3(16,0,33),vec3(14,0,33),vec3(16,0,25)} );
    nodes[9] = Node(i++, new vec3[3]{vec3(16,0,34),vec3(21,0,25),vec3(16,0,25)} );
    nodes[10] = Node(i++, new vec3[3]{vec3(16,0,34),vec3(21,0,25),vec3(21,0,34)}, set<int>{11} );
    nodes[11] = Node(i++, new vec3[3]{vec3(21,0,33),vec3(23,0,23),vec3(21,0,25)} );
    nodes[12] = Node(i++, new vec3[3]{vec3(21,0,33),vec3(23,0,23),vec3(25,0,33)} );
    nodes[13] = Node(i++, new vec3[3]{vec3(25,0,23),vec3(23,0,23),vec3(25,0,33)} );
    nodes[14] = Node(i++, new vec3[3]{vec3(25,0,24),vec3(25,0,34),vec3(30,0,24)}, set<int>{15,18} );
    nodes[15] = Node(i++, new vec3[3]{vec3(27,0,30),vec3(27,0,34),vec3(25,0,34)} );
    nodes[16] = Node(i++, new vec3[3]{vec3(27,0,30),vec3(27,0,33),vec3(31,0,33)} );
    nodes[17] = Node(i++, new vec3[3]{vec3(31,0,30),vec3(27,0,30),vec3(31,0,33)}, set<int>{18,19,20,21} );
    nodes[18] = Node(i++, new vec3[3]{vec3(30,0,24),vec3(30,0,30),vec3(27,0,30)} );
    nodes[19] = Node(i++, new vec3[3]{vec3(30,0,30),vec3(30,0,23),vec3(32,0,23)} );
    nodes[20] = Node(i++, new vec3[3]{vec3(30,0,30),vec3(34,0,25),vec3(32,0,23)} );
    nodes[21] = Node(i++, new vec3[3]{vec3(30,0,30),vec3(34,0,25),vec3(34,0,30)}, set<int>{22,24} );
    nodes[22] = Node(i++, new vec3[3]{vec3(31,0,30),vec3(31,0,34),vec3(34,0,30)} );
    nodes[23] = Node(i++, new vec3[3]{vec3(36,0,34),vec3(31,0,34),vec3(34,0,30)}, set<int>{25}  );
    nodes[24] = Node(i++, new vec3[3]{vec3(36,0,25),vec3(34,0,25),vec3(34,0,30)} );
    nodes[25] = Node(i++, new vec3[3]{vec3(34,0,30),vec3(36,0,25),vec3(36,0,34)} );
    nodes[26] = Node(i++, new vec3[3]{vec3(36,0,25),vec3(38,0,33),vec3(36,0,33)} );
    nodes[27] = Node(i++, new vec3[3]{vec3(36,0,25),vec3(38,0,33),vec3(38,0,25)} );
    nodes[28] = Node(i++, new vec3[3]{vec3(38,0,25),vec3(38,0,34),vec3(44,0,25)}, set<int>{29,32}  );
    nodes[29] = Node(i++, new vec3[3]{vec3(43,0,33),vec3(38,0,34),vec3(44,0,25)}, set<int>{30,31} );
    nodes[30] = Node(i++, new vec3[3]{vec3(43,0,33),vec3(43,0,34),vec3(38,0,34)}, false);
    nodes[31] = Node(i++, new vec3[3]{vec3(43,0,33),vec3(44,0,25),vec3(45,0,33)}, false);
    nodes[32] = Node(i++, new vec3[3]{vec3(37,0,25),vec3(44,0,25),vec3(41,0,23)} );
    nodes[33] = Node(i++, new vec3[3]{vec3(48,0,19),vec3(44,0,25),vec3(41,0,23)}, set<int>{34} );
    nodes[34] = Node(i++, new vec3[3]{vec3(48,0,19),vec3(48,0,12),vec3(41,0,23)}, set<int>{35} );
    nodes[35] = Node(i++, new vec3[3]{vec3(41,0,12),vec3(48,0,12),vec3(41,0,23)}, set<int>{36,53,55,59} );
    //centro
    nodes[36] = Node(i++, new vec3[3]{vec3(41,0,20),vec3(41,0,22),vec3(37,0,18)} );
    nodes[37] = Node(i++, new vec3[3]{vec3(41,0,22),vec3(37,0,24),vec3(37,0,18)} );
    nodes[38] = Node(i++, new vec3[3]{vec3(35,0,24),vec3(37,0,24),vec3(37,0,18)} );
    nodes[39] = Node(i++, new vec3[3]{vec3(35,0,24),vec3(35,0,18),vec3(37,0,18)} );
    nodes[40] = Node(i++, new vec3[3]{vec3(35,0,24),vec3(35,0,19),vec3(33,0,22)} );
    nodes[41] = Node(i++, new vec3[3]{vec3(30,0,19),vec3(35,0,19),vec3(33,0,22)} );
    nodes[42] = Node(i++, new vec3[3]{vec3(29,0,18),vec3(29,0,22),vec3(33,0,22)} );
    nodes[43] = Node(i++, new vec3[3]{vec3(29,0,24),vec3(29,0,18),vec3(26,0,24)} );
    nodes[44] = Node(i++, new vec3[3]{vec3(26,0,18),vec3(29,0,18),vec3(26,0,24)} );
    nodes[45] = Node(i++, new vec3[3]{vec3(22,0,22),vec3(26,0,22),vec3(26,0,18)} );
    nodes[46] = Node(i++, new vec3[3]{vec3(22,0,22),vec3(19,0,19),vec3(25,0,19)} );
    nodes[47] = Node(i++, new vec3[3]{vec3(22,0,22),vec3(19,0,19),vec3(20,0,24)} );
    nodes[48] = Node(i++, new vec3[3]{vec3(19,0,24),vec3(19,0,19),vec3(20,0,24)} );
    nodes[49] = Node(i++, new vec3[3]{vec3(19,0,18),vec3(16,0,24),vec3(19,0,24)} );
    nodes[50] = Node(i++, new vec3[3]{vec3(19,0,18),vec3(16,0,24),vec3(16,0,18)} );
    nodes[51] = Node(i++, new vec3[3]{vec3(12,0,22),vec3(16,0,24),vec3(16,0,18)} );
    nodes[52] = Node(i++, new vec3[3]{vec3(12,0,22),vec3(12,0,20),vec3(16,0,18)}, false );

    //abajo
    nodes[53] = Node(i++, new vec3[3]{vec3(47,0,12),vec3(45,0,12),vec3(47,0,7)} );
    nodes[54] = Node(i++, new vec3[3]{vec3(45,0,7),vec3(45,0,12),vec3(47,0,7)} );
    nodes[55] = Node(i++, new vec3[3]{vec3(41,0,12),vec3(45,0,12),vec3(45,0,8)} );
    nodes[56] = Node(i++, new vec3[3]{vec3(41,0,12),vec3(43,0,8),vec3(45,0,8)} );
    nodes[57] = Node(i++, new vec3[3]{vec3(41,0,12),vec3(43,0,8),vec3(32,0,7)}, set<int>{58,60} );
    nodes[58] = Node(i++, new vec3[3]{vec3(43,0,7),vec3(43,0,8),vec3(32,0,7)},false );
    nodes[59] = Node(i++, new vec3[3]{vec3(41,0,12),vec3(41,0,16),vec3(33,0,16)} );
    nodes[60] = Node(i++, new vec3[3]{vec3(33,0,16),vec3(32,0,7),vec3(41,0,12)});

    
    /* --------- SERGIO --------- */
    nodes[61] = Node(i++, new vec3[3]{vec3(30,0,16),vec3(32,0, 7),vec3(33,0,16)}, set<int>{64,62});
    nodes[62] = Node(i++, new vec3[3]{vec3(30,0,16),vec3(33,0,16),vec3(30,0,17)}, set<int>{63});
    nodes[63] = Node(i++, new vec3[3]{vec3(33,0,17),vec3(33,0,16),vec3(30,0,17)}, false);
    nodes[64] = Node(i++, new vec3[3]{vec3(30,0,16),vec3(29,0,11),vec3(32,0, 7)}, set<int>{65,66});
    nodes[65] = Node(i++, new vec3[3]{vec3(30,0,16),vec3(29,0,11),vec3(27,0,14)}, set<int>{69,70});
    nodes[66] = Node(i++, new vec3[3]{vec3(32,0, 7),vec3(29,0,11),vec3(27,0, 8)}, set<int>{67,68});
    nodes[67] = Node(i++, new vec3[3]{vec3(32,0, 7),vec3(27,0, 7),vec3(27,0, 8)}, false);
    nodes[68] = Node(i++, new vec3[3]{vec3(29,0,11),vec3(25,0,11),vec3(27,0, 8)}, set<int>{66,69,76} );
    nodes[69] = Node(i++, new vec3[3]{vec3(29,0,11),vec3(25,0,11),vec3(27,0,14)}, set<int>{65,72,68} );
    nodes[70] = Node(i++, new vec3[3]{vec3(30,0,16),vec3(24,0,16),vec3(27,0,14)}, set<int>{65,71} );
    nodes[71] = Node(i++, new vec3[3]{vec3(22,0,14),vec3(24,0,16),vec3(27,0,14)}, set<int>{77,72,70} );
    nodes[72] = Node(i++, new vec3[3]{vec3(22,0,14),vec3(25,0,11),vec3(27,0,14)}, set<int>{69,71,73} );
    nodes[73] = Node(i++, new vec3[3]{vec3(22,0,14),vec3(25,0,11),vec3(25,0, 8)}, set<int>{74,72,76} );
    nodes[74] = Node(i++, new vec3[3]{vec3(22,0,14),vec3(20,0, 7),vec3(25,0, 8)}, set<int>{75,79} );
    nodes[75] = Node(i++, new vec3[3]{vec3(25,0, 7),vec3(20,0, 7),vec3(25,0, 8)} );
    nodes[76] = Node(i++, new vec3[3]{vec3(27,0, 8),vec3(25,0,11),vec3(25,0, 8)}, set<int>{73,68} );
    nodes[77] = Node(i++, new vec3[3]{vec3(20,0,16),vec3(22,0,14),vec3(24,0,16)}, set<int>{71,74,78} );
    nodes[78] = Node(i++, new vec3[3]{vec3(20,0,16),vec3(22,0,14),vec3(16,0,16)});
    nodes[79] = Node(i++, new vec3[3]{vec3(20,0, 7),vec3(22,0,14),vec3(16,0,16)});
    nodes[80] = Node(i++, new vec3[3]{vec3(20,0, 7),vec3(16,0, 7),vec3(16,0,16)});
    nodes[81] = Node(i++, new vec3[3]{vec3(16,0,15),vec3(16,0, 8),vec3(14,0,15)});
    nodes[82] = Node(i++, new vec3[3]{vec3(10,0,12),vec3(16,0, 8),vec3(14,0,15)}, set<int>{81,84,85} );
    nodes[83] = Node(i++, new vec3[3]{vec3(14,0,15),vec3( 8,0,16),vec3(14,0,16)}, set<int>{81,85,90} ); //conect 90
    nodes[84] = Node(i++, new vec3[3]{vec3(10,0,12),vec3(16,0, 8),vec3( 7,0, 8)}, set<int>{82,87} );
    nodes[85] = Node(i++, new vec3[3]{vec3(10,0,12),vec3( 8,0,16),vec3(14,0,15)}) ;
    nodes[86] = Node(i++, new vec3[3]{vec3(10,0,12),vec3( 8,0,16),vec3( 5,0,12)}, set<int>{85,89,87} );
    nodes[87] = Node(i++, new vec3[3]{vec3(10,0,12),vec3( 7,0, 8),vec3( 5,0,12)});
    nodes[88] = Node(i++, new vec3[3]{vec3( 7,0, 8),vec3( 5,0, 8),vec3( 5,0,12)}, false);
    nodes[89] = Node(i++, new vec3[3]{vec3( 5,0,17),vec3( 8,0,16),vec3( 5,0,12)}, set<int>{90} ); // conect 90
    nodes[90] = Node(i++, new vec3[3]{vec3( 5,0,17),vec3( 8,0,16),vec3(16,0,16)} );
    /*
    */

    setDistances();
}

void Graph::createGameGraphSquare()
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
    nodes[70] = Node(70, new vec3[3]{vec3(12,0,16),vec3(14,0,7),vec3(12,0,7)} );
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
}

void Graph::createGameGraphNew()
{
    int it = 0;
    // ZONA MORADA(EN EL CROQUIS)
        vec3 a_0 = {12,0,16};
        vec3 b_0 = { 5,0,17};
        vec3 c_0 = { 0,0,17};
        vec3 d_0 = { 3,0,18};
        vec3 e_0 = {12,0,18};
        vec3 f_0 = { 6,0,21};
        vec3 g_0 = { 0,0,22};
        vec3 h_0 = { 0,0,25};
        vec3 i_0 = { 5,0,25};
        vec3 j_0 = {12,0,23};
        vec3 k_0 = {12,0,25};
        vec3 l_0 = {6,0,39};

        vec3 m_0 = { 1,0,26};
        vec3 n_0 = { 4,0,26};

        vec3 o_0 = { 5,0,29};
        vec3 p_0 = { 4,0,29};

        vec3 q_0 = { 4,0,32};
        vec3 r_0 = { 5,0,32};

        vec3 s_0 = { 1,0,39};
        vec3 t_0 = { 4,0,37};
        vec3 u_0 = { 5,0,37};
        vec3 v_0 = { 5,0,39};
        
        vec3 w_0 = {10,0,34};
        vec3 x_0 = {13,0,34};

        vec3 y_0 = {10,0,37};
        vec3 z_0 = { 6,0,37};
        
        vec3 a0 = { 5,0,34};
        vec3 b0 = {13,0,39};


        nodes[0]  = Node(0, new vec3[3]{a_0, b_0, e_0} , set<int>{1,124} );
        nodes[1]  = Node(1, new vec3[3]{b_0, d_0, e_0} , set<int>{2,5} );
        nodes[2]  = Node(2, new vec3[3]{b_0, d_0, c_0} );
        nodes[3]  = Node(3, new vec3[3]{g_0, d_0, c_0} );
        nodes[4]  = Node(4, new vec3[3]{g_0, d_0, f_0} , set<int>{5,8} );
        nodes[5]  = Node(5, new vec3[3]{e_0, d_0, f_0} );
        nodes[6]  = Node(6, new vec3[3]{e_0, j_0, f_0} );
        nodes[7]  = Node(7, new vec3[3]{i_0, j_0, f_0} , set<int>{8,10} );
        nodes[8]  = Node(8, new vec3[3]{i_0, g_0, f_0} );
        nodes[9]  = Node(9, new vec3[3]{i_0, g_0, h_0} ,false );

        nodes[10]  = Node(10, new vec3[3]{i_0, j_0, k_0} );
        nodes[11]  = Node(11, new vec3[3]{i_0, r_0, k_0} , set<int>{12,13} );
        nodes[12]  = Node(12, new vec3[3]{r_0, w_0, k_0} , set<int>{20,21} );
        nodes[13]  = Node(13, new vec3[3]{p_0, o_0, r_0} );
        nodes[14]  = Node(14, new vec3[3]{q_0, r_0, p_0} );
        nodes[15]  = Node(15, new vec3[3]{p_0, t_0, s_0} , set<int>{16,18} );
        nodes[16]  = Node(16, new vec3[3]{s_0, p_0, m_0} );
        nodes[17]  = Node(17, new vec3[3]{m_0, p_0, n_0} , false);
        nodes[18]  = Node(18, new vec3[3]{s_0, t_0, v_0} );
        nodes[19]  = Node(19, new vec3[3]{u_0, v_0, t_0} ,false );

        nodes[20]  = Node(20, new vec3[3]{ a0, w_0, r_0} ,false );
        nodes[21]  = Node(21, new vec3[3]{k_0, x_0, w_0} , set<int>{22,26} );
        nodes[22]  = Node(22, new vec3[3]{w_0, x_0, y_0} );
        nodes[23]  = Node(23, new vec3[3]{ b0, y_0, x_0} );
        nodes[24]  = Node(24, new vec3[3]{ b0, l_0, y_0} );
        nodes[25]  = Node(25, new vec3[3]{z_0, l_0, y_0} , false );

    // ZONA VERDE(EN EL CROQUIS)
        vec3 a_1 = {14,0,26};
        vec3 b_1 = {14,0,33};

        vec3 c_1 = {16,0,26};
        vec3 d_1 = {16,0,33};
        
        vec3 e_1 = {17,0,34};
        vec3 f_1 = {17,0,39};
        
        vec3 g_1 = {20,0,29};
        vec3 h_1 = {20,0,34};
        vec3 i_1 = {20,0,37};
        
        vec3 j_1 = {21,0,25};
        vec3 k_1 = {21,0,33};
        
        vec3 l_1 = { 25,0,35}; // inutil
        vec3 m_1 = { 25,0,37};
        vec3 n_1 = { 25,0,39};
        
        vec3 o_1 = {26,0,25};
        vec3 p_1 = {26,0,33};
        
        vec3 q_1 = {27,0,37};
        vec3 r_1 = {27,0,39};
        
        vec3 s_1 = {30,0,25}; // inutil
        
        vec3 t_1 = {32,0,29};
        vec3 u_1 = {32,0,33};
        vec3 v_1 = {32,0,37};
        
        vec3 w_1 = {33,0,25};
        
        vec3 x_1 = {35,0,34};
        vec3 y_1 = {35,0,39};
        
        vec3 z_1 = {36,0,26};
        vec3 a1  = {36,0,33};

        nodes[26]  = Node(26, new vec3[3]{k_0, x_0, a_1} );
        nodes[27]  = Node(27, new vec3[3]{x_0,a_1,b_1} );
        nodes[28]  = Node(28, new vec3[3]{a_1,b_1,c_1} );
        nodes[29]  = Node(29, new vec3[3]{c_1,b_1,g_1} , set<int>{30,38} );

        nodes[30]  = Node(30, new vec3[3]{g_1,b_1,p_1} , set<int>{31,37} );
        nodes[31]  = Node(31, new vec3[3]{d_1,h_1,k_1} );
        nodes[32]  = Node(32, new vec3[3]{d_1,e_1,h_1} );
        nodes[33]  = Node(33, new vec3[3]{e_1,i_1,h_1} );
        nodes[34]  = Node(34, new vec3[3]{e_1,i_1,f_1} );
        nodes[35]  = Node(35, new vec3[3]{f_1,n_1,i_1} );
        nodes[36]  = Node(36, new vec3[3]{i_1,m_1,n_1} , false );
        nodes[37]  = Node(37, new vec3[3]{g_1,p_1,t_1} , set<int>{40,42} );
        nodes[38]  = Node(38, new vec3[3]{c_1,g_1,o_1} , set<int>{39,40} );
        nodes[39]  = Node(39, new vec3[3]{c_1,o_1,j_1} , false );

        nodes[40]  = Node(40, new vec3[3]{g_1,t_1,o_1} );
        nodes[41]  = Node(41, new vec3[3]{o_1,w_1,t_1} , set<int>{43} );
        nodes[42]  = Node(42, new vec3[3]{p_1,t_1,u_1} , set<int>{45} );
        nodes[43]  = Node(43, new vec3[3]{t_1,w_1,z_1} );
        nodes[44]  = Node(44, new vec3[3]{t_1,z_1,x_1} , set<int>{45,49} );
        nodes[45]  = Node(45, new vec3[3]{t_1,x_1,v_1} );
        nodes[46]  = Node(46, new vec3[3]{x_1,v_1,y_1} );
        nodes[47]  = Node(47, new vec3[3]{v_1,y_1,r_1} );
        nodes[48]  = Node(48, new vec3[3]{q_1,r_1,v_1} , false );
        nodes[49]  = Node(49, new vec3[3]{z_1,x_1,a1 } );

    // ZONA ROSA(EN EL CROQUIS)
        vec3 a_2 = {36,0,37};
        vec3 b_2 = {36,0,39};

        vec3 c_2 = {38,0,26};
        vec3 d_2 = {38,0,33};
        
        vec3 e_2 = {39,0,37};

        vec3 f_2 = {41,0,18};
        vec3 g_2 = {41,0,23};
        vec3 h_2 = {41,0,25};

        vec3 i_2 = {42,0,39};
        
        vec3 j_2 = {43,0,33};

        vec3 k_2 = {45,0,37};
        vec3 l_2 = {45,0,39};

        vec3 m_2 = {48,0,17};
        vec3 n_2 = {48,0,25};
        vec3 o_2 = {48,0,31};

        vec3 p_2 = {49,0,21};
        vec3 q_2 = {49,0,33};

        vec3 r_2 = {50,0,26};
        vec3 s_2 = {50,0,31};
        vec3 t_2 = {50,0,33};
        vec3 u_2 = {50,0,37};

        vec3 v_2 = {53,0,26};
        vec3 w_2 = {53,0,33};
        vec3 x_2 = {53,0,39};
        
        vec3 y_2 = {54,0,17};
        vec3 z_2 = {54,0,25};
        
        vec3 a2 = {39,0,33};
        vec3 b2 = {42,0,34};
        vec3 c2 = {53,0,31};

        nodes[50]  = Node(50, new vec3[3]{ a1,d_2,z_1} );
        nodes[51]  = Node(51, new vec3[3]{z_1,d_2,c_2} );
        nodes[52]  = Node(52, new vec3[3]{c_2,h_2,d_2} );
        nodes[53]  = Node(53, new vec3[3]{h_2,j_2,d_2} , set<int>{54,58} );
        nodes[54]  = Node(54, new vec3[3]{ a2,j_2,e_2} );
        nodes[55]  = Node(55, new vec3[3]{e_2,i_2, b2} );
        nodes[56]  = Node(56, new vec3[3]{e_2,i_2,b_2} );
        nodes[57]  = Node(57, new vec3[3]{a_2,b_2,e_2} , false );
        nodes[58]  = Node(58, new vec3[3]{j_2,o_2,h_2} , set<int>{59,67} );
        nodes[59]  = Node(59, new vec3[3]{j_2,w_2,o_2} , set<int>{60,63} );

        nodes[60]  = Node(60, new vec3[3]{o_2, c2,w_2} );
        nodes[61]  = Node(61, new vec3[3]{s_2, c2,v_2} );
        nodes[62]  = Node(62, new vec3[3]{s_2,v_2,r_2} , false );
        nodes[63]  = Node(63, new vec3[3]{t_2,w_2,u_2} );
        nodes[64]  = Node(64, new vec3[3]{u_2,x_2,w_2} );
        nodes[65]  = Node(65, new vec3[3]{u_2,x_2,l_2} );
        nodes[66]  = Node(66, new vec3[3]{l_2,k_2,u_2} , false );
        nodes[67]  = Node(67, new vec3[3]{o_2,n_2,h_2} );
        nodes[68]  = Node(68, new vec3[3]{h_2,n_2,g_2} );
        nodes[69]  = Node(69, new vec3[3]{g_2,n_2,p_2} , set<int>{70,71} );

        nodes[70]  = Node(70, new vec3[3]{g_2,p_2,f_2} , set<int>{74} );
        nodes[71]  = Node(71, new vec3[3]{n_2,z_2,p_2} );
        nodes[72]  = Node(72, new vec3[3]{y_2,z_2,p_2} );
        nodes[73]  = Node(73, new vec3[3]{p_2,m_2,y_2} );
        nodes[74]  = Node(74, new vec3[3]{p_2,f_2,m_2} );

    // ZONA AZUL(EN EL CROQUIS)
        vec3 a_3 = {27,0, 1};
        vec3 b_3 = {27,0, 4};

        vec3 c_3 = {32,0, 1};
        vec3 d_3 = {32,0, 4};
        vec3 e_3 = {32,0, 7};

        vec3 f_3 = {33,0,16};

        vec3 g_3 = {35,0, 1};
        vec3 h_3 = {35,0, 7};

        vec3 i_3 = {36,0, 1};
        vec3 j_3 = {36,0, 4};

        vec3 k_3 = {37,0,15};

        vec3 l_3 = {39,0, 4};
        vec3 m_3 = {39,0, 7};
        vec3 n_3 = {39,0,15};

        vec3 o_3 = {41,0,16};

        vec3 p_3 = {42,0, 1};
        vec3 q_3 = {42,0, 7};

        vec3 r_3 = {43,0, 8};

        vec3 s_3 = {45,0, 1};
        vec3 t_3 = {45,0, 4};

        vec3 u_3 = {48,0,12};

        vec3 v_3 = {49,0, 8};
        vec3 w_3 = {49,0,12};
        vec3 x_3 = {49,0,14};
        
        vec3 y_3 = {50,0, 1};
        vec3 z_3 = {50,0, 8};
        
        vec3 a3 = {53,0, 1};
        vec3 b3 = {53,0,12};
        vec3 c3 = {53,0,14};
        vec3 d3 = {50,0, 4};

        nodes[75]  = Node(75, new vec3[3]{f_2,m_2,o_3} );
        nodes[76]  = Node(76, new vec3[3]{m_2,o_3,u_3} );
        nodes[77]  = Node(77, new vec3[3]{n_3,o_3,u_3} );
        nodes[78]  = Node(78, new vec3[3]{n_3,r_3,u_3} , set<int>{79,87} );
        nodes[79]  = Node(79, new vec3[3]{r_3,u_3,z_3} );

        nodes[80]  = Node(80, new vec3[3]{u_3,z_3, b3} , set<int>{81,83} );
        nodes[81]  = Node(81, new vec3[3]{w_3,x_3, b3} );
        nodes[82]  = Node(82, new vec3[3]{x_3, b3, c3} , false );
        nodes[83]  = Node(83, new vec3[3]{z_3, a3, b3} );
        nodes[84]  = Node(84, new vec3[3]{y_3,z_3, a3} );
        nodes[85]  = Node(85, new vec3[3]{t_3,y_3, d3} );
        nodes[86]  = Node(86, new vec3[3]{s_3,t_3,y_3} , false );
        nodes[87]  = Node(87, new vec3[3]{m_3,n_3,r_3} , set<int>{88,92} );
        nodes[88]  = Node(88, new vec3[3]{l_3,m_3,r_3} );
        nodes[89]  = Node(89, new vec3[3]{l_3,p_3,q_3} );

        nodes[90]  = Node(90, new vec3[3]{i_3,l_3,p_3} );
        nodes[91]  = Node(91, new vec3[3]{i_3,j_3,l_3} , false );
        nodes[92]  = Node(92, new vec3[3]{h_3,m_3,n_3} );
        nodes[93]  = Node(93, new vec3[3]{k_3,n_3,h_3} );
        nodes[94]  = Node(94, new vec3[3]{f_3,k_3,h_3} );
        nodes[95]  = Node(95, new vec3[3]{e_3,f_3,h_3} , set<int>{96,100} );
        nodes[96]  = Node(96, new vec3[3]{e_3,g_3,h_3} );
        nodes[97]  = Node(97, new vec3[3]{c_3,e_3,g_3} );
        nodes[98]  = Node(98, new vec3[3]{b_3,c_3,d_3} );
        nodes[99]  = Node(99, new vec3[3]{a_3,b_3,c_3} , false );

    // ZONA ROJO(EN EL CROQUIS)
        vec3 a_4 = { 1,0, 1};
        vec3 b_4 = { 1,0, 5};
        vec3 c_4 = { 1,0, 8};
        vec3 d_4 = { 1,0,12};
        vec3 e_4 = { 1,0,14};
        
        vec3 f_4 = { 4,0,12};
        vec3 g_4 = { 4,0,14};
        
        vec3 h_4 = { 5,0,12};
        
        vec3 i_4 = {10,0, 5};
        vec3 j_4 = {10,0, 8};
        
        vec3 k_4 = {13,0, 1};
        vec3 l_4 = {13,0, 7};
        
        vec3 m_4 = {14,0, 8};
        vec3 n_4 = {14,0,15};
        
        vec3 o_4 = {16,0, 8};
        vec3 p_4 = {16,0,15};
        
        vec3 q_4 = {17,0, 1};
        vec3 r_4 = {17,0, 7};
        
        vec3 s_4 = {20,0, 4};
        vec3 t_4 = {20,0, 7};
        
        vec3 u_4 = {21,0,16};
        
        vec3 v_4 = {25,0,16};
        
        vec3 w_4 = {25,0, 1};
        vec3 x_4 = {25,0, 4};
        vec3 y_4 = {25,0, 8};
        
        vec3 z_4 = {27,0, 8};

        nodes[100]  = Node(100, new vec3[3]{e_3,f_3,z_4} );
        nodes[101]  = Node(101, new vec3[3]{z_4,f_3,v_4} );
        nodes[102]  = Node(102, new vec3[3]{y_4,z_4,v_4} );
        nodes[103]  = Node(103, new vec3[3]{u_4,v_4,y_4} );
        nodes[104]  = Node(104, new vec3[3]{u_4,t_4,y_4} );
        nodes[105]  = Node(105, new vec3[3]{p_4,u_4,t_4} );
        nodes[106]  = Node(106, new vec3[3]{o_4,t_4,p_4} , set<int>{107,111} );
        nodes[107]  = Node(107, new vec3[3]{o_4,t_4,s_4} );
        nodes[108]  = Node(108, new vec3[3]{r_4,s_4,q_4} );
        nodes[109]  = Node(109, new vec3[3]{s_4,x_4,q_4} );

        nodes[110]  = Node(110, new vec3[3]{x_4,w_4,q_4} , false );
        nodes[111]  = Node(111, new vec3[3]{p_4,n_4,o_4} );
        nodes[112]  = Node(112, new vec3[3]{n_4,j_4,o_4} , set<int>{113,118} );
        nodes[113]  = Node(113, new vec3[3]{j_4,m_4,l_4} );
        nodes[114]  = Node(114, new vec3[3]{j_4,i_4,l_4} );
        nodes[115]  = Node(115, new vec3[3]{i_4,l_4,k_4} );
        nodes[116]  = Node(116, new vec3[3]{i_4,k_4,a_4} );
        nodes[117]  = Node(117, new vec3[3]{a_4,b_4,i_4} , false );
        nodes[118]  = Node(118, new vec3[3]{n_4,h_4,j_4} , set<int>{119,123} );
        nodes[119]  = Node(119, new vec3[3]{c_4,h_4,j_4} );

        nodes[120]  = Node(120, new vec3[3]{d_4,c_4,h_4} );
        nodes[121]  = Node(121, new vec3[3]{d_4,f_4,g_4} );
        nodes[122]  = Node(122, new vec3[3]{e_4,d_4,g_4} , false );
        nodes[123]  = Node(123, new vec3[3]{n_4,h_4,a_0} );
        nodes[124]  = Node(124, new vec3[3]{a_0,b_0,h_4} );

    setDistances();
}

#endif