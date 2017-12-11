/* 
    Andrea Centeno
    Sergio Teran
    sep-dic 2017
*/
#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "graph.h"
#include "pathfindAStar.h"

#include <set>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

void Graph::createGameGraphNew()
{
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

        nodes[1]  = Node(1, new vec3[3]{a_0, b_0, e_0} , set<int>{2,125} );
        nodes[2]  = Node(2, new vec3[3]{b_0, d_0, e_0} , set<int>{3,6} );
        nodes[3]  = Node(3, new vec3[3]{b_0, d_0, c_0} );
        nodes[4]  = Node(4, new vec3[3]{g_0, d_0, c_0} );
        nodes[5]  = Node(5, new vec3[3]{g_0, d_0, f_0} , set<int>{6,9} );
        nodes[6]  = Node(6, new vec3[3]{e_0, d_0, f_0} );
        nodes[7]  = Node(7, new vec3[3]{e_0, j_0, f_0} );
        nodes[8]  = Node(8, new vec3[3]{i_0, j_0, f_0} , set<int>{9,11,166} );
        nodes[9]  = Node(9, new vec3[3]{i_0, g_0, f_0} );
        nodes[10] = Node(10, new vec3[3]{i_0, g_0, h_0} ,false );

        nodes[11] = Node(11, new vec3[3]{i_0, j_0, k_0} );
        nodes[12] = Node(12, new vec3[3]{i_0, r_0, k_0} , set<int>{13,14} );
        nodes[13] = Node(13, new vec3[3]{r_0, w_0, k_0} , set<int>{21,22} );
        nodes[14] = Node(14, new vec3[3]{p_0, o_0, r_0} );
        nodes[15] = Node(15, new vec3[3]{q_0, r_0, p_0} );
        nodes[16] = Node(16, new vec3[3]{p_0, t_0, s_0} , set<int>{17,19} );
        nodes[17] = Node(17, new vec3[3]{s_0, p_0, m_0} );
        nodes[18] = Node(18, new vec3[3]{m_0, p_0, n_0} , false);
        nodes[19] = Node(19, new vec3[3]{s_0, t_0, v_0} );
        nodes[20] = Node(20, new vec3[3]{u_0, v_0, t_0} ,false );

        nodes[21] = Node(21, new vec3[3]{ a0, w_0, r_0} ,false );
        nodes[22] = Node(22, new vec3[3]{k_0, x_0, w_0} , set<int>{23,27} );
        nodes[23] = Node(23, new vec3[3]{w_0, x_0, y_0} );
        nodes[24] = Node(24, new vec3[3]{ b0, y_0, x_0} );
        nodes[25] = Node(25, new vec3[3]{ b0, l_0, y_0} );
        nodes[26] = Node(26, new vec3[3]{z_0, l_0, y_0} , false );

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
        vec3 l_1 = {25,0,35}; // inutil
        vec3 m_1 = {25,0,37};
        vec3 n_1 = {25,0,39};
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

        nodes[27] = Node(27, new vec3[3]{k_0, x_0, a_1}, set<int>{28,149}  );
        nodes[28] = Node(28, new vec3[3]{x_0,a_1,b_1} );
        nodes[29] = Node(29, new vec3[3]{a_1,b_1,c_1} );
        nodes[30] = Node(30, new vec3[3]{c_1,b_1,g_1} , set<int>{31,39} );

        nodes[31] = Node(31, new vec3[3]{g_1,b_1,p_1} , set<int>{32,38,148} );
        nodes[32] = Node(32, new vec3[3]{d_1,h_1,k_1} );
        nodes[33] = Node(33, new vec3[3]{d_1,e_1,h_1} );
        nodes[34] = Node(34, new vec3[3]{e_1,i_1,h_1} );
        nodes[35] = Node(35, new vec3[3]{e_1,i_1,f_1} );
        nodes[36] = Node(36, new vec3[3]{f_1,n_1,i_1} );
        nodes[37] = Node(37, new vec3[3]{i_1,m_1,n_1} , false );
        nodes[38] = Node(38, new vec3[3]{g_1,p_1,t_1} , set<int>{41,43} );
        nodes[39] = Node(39, new vec3[3]{c_1,g_1,o_1} , set<int>{40,41} );
        nodes[40] = Node(40, new vec3[3]{c_1,o_1,j_1} , set<int>{129,130} );

        nodes[41] = Node(41, new vec3[3]{g_1,t_1,o_1} );
        nodes[42] = Node(42, new vec3[3]{o_1,w_1,t_1} , set<int>{44,127} );
        nodes[43] = Node(43, new vec3[3]{p_1,t_1,u_1} , set<int>{46,146} );
        nodes[44] = Node(44, new vec3[3]{t_1,w_1,z_1}, set<int>{45,131} );
        nodes[45] = Node(45, new vec3[3]{t_1,z_1,x_1} , set<int>{46,50} );
        nodes[46] = Node(46, new vec3[3]{t_1,x_1,v_1} );
        nodes[47] = Node(47, new vec3[3]{x_1,v_1,y_1} );
        nodes[48] = Node(48, new vec3[3]{v_1,y_1,r_1} );
        nodes[49] = Node(49, new vec3[3]{q_1,r_1,v_1} , false );
        nodes[50] = Node(50, new vec3[3]{z_1,x_1,a1 } );

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

        nodes[51] = Node(51, new vec3[3]{ a1,d_2,z_1} );
        nodes[52] = Node(52, new vec3[3]{z_1,d_2,c_2} );
        nodes[53] = Node(53, new vec3[3]{c_2,h_2,d_2} , set<int>{54,132} );
        nodes[54] = Node(54, new vec3[3]{h_2,j_2,d_2} , set<int>{55,59} );
        nodes[55] = Node(55, new vec3[3]{ a2,j_2,e_2} );
        nodes[56] = Node(56, new vec3[3]{e_2,i_2, b2} );
        nodes[57] = Node(57, new vec3[3]{e_2,i_2,b_2} );
        nodes[58] = Node(58, new vec3[3]{a_2,b_2,e_2} , false );
        nodes[59] = Node(59, new vec3[3]{j_2,o_2,h_2} , set<int>{60,68} );
        nodes[60] = Node(60, new vec3[3]{j_2,w_2,o_2} , set<int>{61,64,144} );

        nodes[61] = Node(61, new vec3[3]{o_2, c2,w_2} );
        nodes[62] = Node(62, new vec3[3]{s_2, c2,v_2} );
        nodes[63] = Node(63, new vec3[3]{s_2,v_2,r_2} , false );
        nodes[64] = Node(64, new vec3[3]{t_2,w_2,u_2} );
        nodes[65] = Node(65, new vec3[3]{u_2,x_2,w_2} );
        nodes[66] = Node(66, new vec3[3]{u_2,x_2,l_2} );
        nodes[67] = Node(67, new vec3[3]{l_2,k_2,u_2} , false );
        nodes[68] = Node(68, new vec3[3]{o_2,n_2,h_2} );
        nodes[69] = Node(69, new vec3[3]{h_2,n_2,g_2} );
        nodes[70] = Node(70, new vec3[3]{g_2,n_2,p_2} , set<int>{71,72} );

        nodes[71] = Node(71, new vec3[3]{g_2,p_2,f_2} , set<int>{75,150} );
        nodes[72] = Node(72, new vec3[3]{n_2,z_2,p_2} );
        nodes[73] = Node(73, new vec3[3]{y_2,z_2,p_2} );
        nodes[74] = Node(74, new vec3[3]{p_2,m_2,y_2} );
        nodes[75] = Node(75, new vec3[3]{p_2,f_2,m_2} );

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

        nodes[76]  = Node(76, new vec3[3]{f_2,m_2,o_3} );
        nodes[77]  = Node(77, new vec3[3]{m_2,o_3,u_3} );
        nodes[78]  = Node(78, new vec3[3]{n_3,o_3,u_3}, set<int>{79,137} );
        nodes[79]  = Node(79, new vec3[3]{n_3,r_3,u_3} , set<int>{80,88} );
        nodes[80]  = Node(80, new vec3[3]{r_3,u_3,z_3} );

        nodes[81]  = Node(81, new vec3[3]{u_3,z_3, b3} , set<int>{82,84} );
        nodes[82]  = Node(82, new vec3[3]{w_3,x_3, b3} );
        nodes[83]  = Node(83, new vec3[3]{x_3, b3, c3} , false );
        nodes[84]  = Node(84, new vec3[3]{z_3, a3, b3} );
        nodes[85]  = Node(85, new vec3[3]{y_3,z_3, a3} );
        nodes[86]  = Node(86, new vec3[3]{t_3,y_3, d3} );
        nodes[87]  = Node(87, new vec3[3]{s_3,t_3,y_3} , false );
        nodes[88]  = Node(88, new vec3[3]{m_3,n_3,r_3} , set<int>{89,93} );
        nodes[89]  = Node(89, new vec3[3]{l_3,m_3,r_3} );
        nodes[90]  = Node(90, new vec3[3]{l_3,p_3,q_3} );

        nodes[91]  = Node(91, new vec3[3]{i_3,l_3,p_3} );
        nodes[92]  = Node(92, new vec3[3]{i_3,j_3,l_3} , false );
        nodes[93]  = Node(93, new vec3[3]{h_3,m_3,n_3} );
        nodes[94]  = Node(94, new vec3[3]{k_3,n_3,h_3} );
        nodes[95]  = Node(95, new vec3[3]{f_3,k_3,h_3} , set<int>{96,135});
        nodes[96]  = Node(96, new vec3[3]{e_3,f_3,h_3} , set<int>{97,101} );
        nodes[97]  = Node(97, new vec3[3]{e_3,g_3,h_3} );
        nodes[98]  = Node(98, new vec3[3]{c_3,e_3,g_3} );
        nodes[99]  = Node(99, new vec3[3]{b_3,c_3,d_3} );
        nodes[100] = Node(100, new vec3[3]{a_3,b_3,c_3} , false );

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

        nodes[101]  = Node(101, new vec3[3]{e_3,f_3,z_4}, set<int>{102,134}  );
        nodes[102]  = Node(102, new vec3[3]{z_4,f_3,v_4}, set<int>{103,140} );
        nodes[103]  = Node(103, new vec3[3]{y_4,z_4,v_4} );
        nodes[104]  = Node(104, new vec3[3]{u_4,v_4,y_4}, set<int>{105,141} );
        nodes[105]  = Node(105, new vec3[3]{u_4,t_4,y_4}, set<int>{106,133} );
        nodes[106]  = Node(106, new vec3[3]{p_4,u_4,t_4} , set<int>{107,136} );
        nodes[107]  = Node(107, new vec3[3]{o_4,t_4,p_4} , set<int>{108,112} );
        nodes[108]  = Node(108, new vec3[3]{o_4,t_4,s_4} );
        nodes[109]  = Node(109, new vec3[3]{r_4,s_4,q_4} );
        nodes[110]  = Node(110, new vec3[3]{s_4,x_4,q_4} );

        nodes[111]  = Node(111, new vec3[3]{x_4,w_4,q_4} , false );
        nodes[112]  = Node(112, new vec3[3]{p_4,n_4,o_4} );
        nodes[113]  = Node(113, new vec3[3]{n_4,j_4,o_4} , set<int>{114,119} );
        nodes[114]  = Node(114, new vec3[3]{j_4,m_4,l_4} );
        nodes[115]  = Node(115, new vec3[3]{j_4,i_4,l_4} );
        nodes[116]  = Node(116, new vec3[3]{i_4,l_4,k_4} );
        nodes[117]  = Node(117, new vec3[3]{i_4,k_4,a_4} );
        nodes[118]  = Node(118, new vec3[3]{a_4,b_4,i_4} , false );
        nodes[119]  = Node(119, new vec3[3]{n_4,h_4,j_4} , set<int>{120,124} );
        nodes[120]  = Node(120, new vec3[3]{c_4,h_4,j_4} );

        nodes[121]  = Node(121, new vec3[3]{d_4,c_4,h_4} );
        nodes[122]  = Node(122, new vec3[3]{d_4,f_4,g_4} );
        nodes[123]  = Node(123, new vec3[3]{e_4,d_4,g_4} , false );
        nodes[124]  = Node(124, new vec3[3]{n_4,h_4,a_0} , set<int>{125,138});
        nodes[125]  = Node(125, new vec3[3]{a_0,b_0,h_4} , false );


        //Nodos agregados por Andrea
        vec3 a_5 = { 30,0,25};
        vec3 b_5 = { 30,0,23};
        vec3 c_5 = { 33,0,23};
        nodes[126] = Node(126, new vec3[3]{a_5,b_5,c_5} );
        nodes[127] = Node(127, new vec3[3]{a_5,w_1,c_5},false );

        vec3 b_6 = { 24,0,23};
        vec3 c_6 = { 24,0,25};
        vec3 d_6 = { 21,0,23};
        nodes[128] = Node(128, new vec3[3]{j_1,b_6,d_6} );
        nodes[129] = Node(129, new vec3[3]{j_1,b_6,c_6}, false );

        vec3 d_7 = { 16,0,25};
        nodes[130] = Node(130, new vec3[3]{c_1,d_7,j_1}, false );

        vec3 a_7 = { 36,0,25};
        nodes[131] = Node(131, new vec3[3]{a_7,w_1,z_1} , false);

        vec3 a_8 = { 38,0,25};
        nodes[132] = Node(132, new vec3[3]{c_2,h_2,a_8} , false);

        vec3 a_9 = { 25,0, 7};
        nodes[133] = Node(133, new vec3[3]{a_9,t_4,y_4} , false);

        vec3 a_10 = { 27,0, 7};
        nodes[134]  = Node(134, new vec3[3]{a_10,e_3,z_4}, false );

        vec3 a_11 = { 37,0,16};
        nodes[135]  = Node(135, new vec3[3]{f_3,k_3,a_11}, false );

        vec3 a_12 = { 16,0,16};
        nodes[136]  = Node(136, new vec3[3]{p_4,u_4,a_12}, false );

        vec3 a_13 = { 39,0,16};
        nodes[137]  = Node(137, new vec3[3]{n_3,o_3,a_13}, false );

        vec3 a_14 = { 14,0,16};
        nodes[138]  = Node(138, new vec3[3]{n_4,a_0,a_14}, false );

        vec3 a_15 = { 33,0,17};
        vec3 b_15 = { 30,0,17};
        vec3 c_15 = { 30,0,16};
        nodes[139]  = Node(139, new vec3[3]{a_15,b_15,f_3} );
        nodes[140]  = Node(140, new vec3[3]{c_15,b_15,f_3}, false );


        vec3 a_16 = { 21,0,17};
        vec3 b_16 = { 24,0,17};
        vec3 c_16 = { 24,0,16};
        nodes[141]  = Node(141, new vec3[3]{c_16,b_16,u_4} );
        nodes[142]  = Node(142, new vec3[3]{a_16,b_16,u_4}, false );


        vec3 a_17 = { 45,0,34};
        vec3 b_17 = { 47,0,34};
        vec3 c_17 = { 45,0,33};
        vec3 d_17 = { 47,0,33};
        nodes[143]  = Node(143, new vec3[3]{a_17,b_17,c_17} );
        nodes[144]  = Node(144, new vec3[3]{b_17,c_17,d_17}, false );


        vec3 a_18 = { 27,0,34};
        vec3 b_18 = { 27,0,33};
        vec3 c_18 = { 29,0,33};
        vec3 d_18 = { 29,0,34};
        nodes[145]  = Node(145, new vec3[3]{a_18,d_18,c_18} );
        nodes[146]  = Node(146, new vec3[3]{a_18,b_18,c_18}, false );

        vec3 a_19 = { 23,0,34};
        vec3 b_19 = { 23,0,33};
        vec3 c_19 = { 25,0,33};
        vec3 d_19 = { 25,0,34};
        nodes[147]  = Node(147, new vec3[3]{a_19,b_19,c_19} );
        nodes[148]  = Node(148, new vec3[3]{a_19,d_19,c_19}, false );

        vec3 a_20 = { 14,0,25};
        nodes[149]  = Node(149, new vec3[3]{k_0, a_1,a_20}, false );

        //centro
        vec3 centro_2 = { 41,0,20};
        vec3 centro_3 = { 40,0,23};
        vec3 centro_4 = { 40,0,20};
        vec3 centro_5 = { 40,0,24};
        vec3 centro_6 = { 40,0,19};
        vec3 centro_7 = { 37,0,20};
        vec3 centro_8 = { 34,0,22};
        vec3 centro_9 = { 34,0,24};        

        nodes[150]  = Node(150, new vec3[3]{g_2, centro_2,centro_3} );
        nodes[151]  = Node(151, new vec3[3]{centro_4, centro_2,centro_3} );
        nodes[152]  = Node(152, new vec3[3]{centro_5, centro_6,centro_7},set<int>{153,157}  );
        nodes[153]  = Node(153, new vec3[3]{centro_5, centro_8,centro_7},set<int>{154,155} );
        nodes[154]  = Node(154, new vec3[3]{centro_5, centro_9,centro_8},false );

        vec3 centro_10 = { 34,0,20}; 
        vec3 centro_11 = { 34,0,19};  
        vec3 centro_12 = { 29,0,20}; 
        vec3 centro_13 = { 29,0,22}; 
        nodes[155]  = Node(155, new vec3[3]{centro_12, centro_7,centro_8},set<int>{156,158} );
        nodes[156]  = Node(156, new vec3[3]{centro_10, centro_7,centro_11} );
        nodes[157]  = Node(157, new vec3[3]{centro_6, centro_7,centro_11},false );
        nodes[158]  = Node(158, new vec3[3]{centro_12, centro_13,centro_8} );


        vec3 centro_14 = { 25,0,19}; 
        vec3 centro_15 = { 29,0,24}; 
        vec3 centro_16 = { 29,0,19}; 
        vec3 centro_17 = { 25,0,24}; 
        nodes[159]  = Node(159, new vec3[3]{centro_16, centro_15,centro_14} );
        nodes[160]  = Node(160, new vec3[3]{centro_17, centro_15,centro_14} );


        vec3 centro_18 = { 20,0,20}; 
        vec3 centro_19 = { 25,0,22}; 
        vec3 centro_20 = { 25,0,20}; 
        vec3 centro_21 = { 18,0,22}; 
        vec3 centro_22 = { 12,0,20}; 
        vec3 centro_23 = { 13,0,19}; 
        vec3 centro_24 = { 13,0,20}; 
        vec3 centro_25 = { 20,0,19}; 
        vec3 centro_26 = { 15,0,21}; 
        vec3 centro_27 = { 15,0,23}; 
        vec3 centro_28 = { 13,0,23}; 
        vec3 centro_29 = { 13,0,24}; 
        vec3 centro_30 = { 20,0,24}; 
        vec3 centro_31 = { 20,0,22}; 
        nodes[161]  = Node(161, new vec3[3]{centro_20, centro_19,centro_18} );
        nodes[162]  = Node(162, new vec3[3]{centro_21, centro_19,centro_18},set<int>{163,171} );
        nodes[163]  = Node(163, new vec3[3]{centro_21, centro_18,centro_22},set<int>{164,166,172} );
        nodes[164]  = Node(164, new vec3[3]{centro_24, centro_23,centro_18} );
        nodes[165]  = Node(165, new vec3[3]{centro_25, centro_18,centro_23},false );
        nodes[166]  = Node(166, new vec3[3]{centro_22, centro_26,j_0} );
        nodes[167]  = Node(167, new vec3[3]{centro_27, centro_26,j_0},set<int>{168,172} );
        nodes[168]  = Node(168, new vec3[3]{centro_27, centro_28,centro_29} );
        nodes[169]  = Node(169, new vec3[3]{centro_27, centro_29,centro_30} );
        nodes[170]  = Node(170, new vec3[3]{centro_27, centro_21,centro_30},set<int>{171,172} );
        nodes[171]  = Node(171, new vec3[3]{centro_31, centro_21,centro_30},false );
        nodes[172]  = Node(172, new vec3[3]{centro_26, centro_21,centro_27},false );

    setDistances();
}

#endif