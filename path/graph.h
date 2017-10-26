#include <map>
#include <iostream>
#include <fstream>

class Node;
class Connection;

class Node{ 
public:
    vector<Connection> connections;
    int id;
    vec3 position;
    vec3 triangle[3];

    Node(){}

    /*
    Copia el array que contiene los vertices del triangulo
    Con los vertices del triangulo, calcula el baricentro y lo almacena en position
    */
    Node(int i,vec3 t[]) : id(i){
        for(int i =0; i<3; i++){ triangle[i] = t[i]; }
        position = {(triangle[0].x+triangle[1].x+triangle[2].x)/3
                    ,0 
                    ,(triangle[0].z+triangle[1].z+triangle[2].z)/3 };
    }

    void printPosition(){        
        cout<< position.x<<","<<position.y<<","<<position.z<<endl;
    }

    //vector<Connection> getConnections(){ return connections;}
};

class Connection{
protected:
    float cost;
    Node fromNode;
    Node toNode;

public:
    Connection(float c, Node &fn, Node &tn) : cost(c),fromNode(fn),toNode(tn) {}

    float getCost(){ return cost; }
    Node getFromNode(){ return fromNode; }
    Node getToNode(){ return toNode; }
};

class Graph{ 
protected: 
    map<int,Node> nodes;
  
public:
    float sign (vec3 p1, vec3 p2, vec3 p3)
    {
        return (p1.x - p3.x) * (p2.z - p3.z) - (p2.x - p3.x) * (p1.z - p3.z);
    }

    /*
    Busca si el punto dado se encuentra dentro del 
    triangulo correspondiente al nodo
    */
    bool pointInTriangle (vec3 pt, Node node)
    {
        vec3 v1 = node.triangle[0];
        vec3 v2 = node.triangle[1];
        vec3 v3 = node.triangle[2];
        bool b1, b2, b3;

        b1 = sign(pt, v1, v2) < 0.0f;
        b2 = sign(pt, v2, v3) < 0.0f;
        b3 = sign(pt, v3, v1) < 0.0f;

        return ((b1 == b2) && (b2 == b3));
    }

    /*
    Obtiene el nodo del grafo dada una position en el mapa
    */
    bool getNode(vec3 pt, Node &node){
        for (map<int,Node>::iterator it = nodes.begin(); it != nodes.end(); ++it ){
            cout<<"buscando triangulo en nodo "<<(*it).second.id<<endl;
            if( pointInTriangle(pt,(*it).second) ) {
                cout<<"-> encontrado "<<endl;
                node = (*it).second;
                return true;
            }
        }
    }

    void drawTriangles()
    {
        glColor3f(1,0,0);
        for (map<int,Node>::iterator it = nodes.begin(); it != nodes.end(); ++it ){
            glBegin(GL_LINE_LOOP);
                for (int i=0; i < 3;i++){
                    glVertex3f( (*it).second.triangle[i].x,
                                (*it).second.triangle[i].y,
                                (*it).second.triangle[i].z);
                }
            glEnd();
        }
    }

    /*
        Hay que completar los triangulos e incluir los adyacentes
    */
    void createGameGraph()
    {
        nodes[1] = Node(1, new vec3[3]{vec3(5,0,25),vec3(14,0,25),vec3(5,0,34)} );
        nodes[2] = Node(2, new vec3[3]{vec3(5,0,34),vec3(14,0,34),vec3(14,0,25)} );
        nodes[3] = Node(3, new vec3[3]{vec3(14,0,33),vec3(14,0,26),vec3(16,0,26)} );
        nodes[4] = Node(4, new vec3[3]{vec3(14,0,33),vec3(16,0,26),vec3(16,0,33)} );
        nodes[5] = Node(5, new vec3[3]{vec3(16,0,34),vec3(21,0,34),vec3(16,0,25)} );
        nodes[6] = Node(6, new vec3[3]{vec3(21,0,25),vec3(21,0,34),vec3(16,0,25)} );
        nodes[7] = Node(7, new vec3[3]{vec3(21,0,33),vec3(23,0,33),vec3(21,0,30)} );
        nodes[8] = Node(8, new vec3[3]{vec3(23,0,30),vec3(23,0,33),vec3(21,0,30)} );
        nodes[9] = Node(9, new vec3[3]{vec3(21,0,30),vec3(21,0,23),vec3(24,0,23)} );
        nodes[10] = Node(10, new vec3[3]{vec3(21,0,30),vec3(24,0,30),vec3(24,0,23)} );

        /*
        PRUEBA
        Node node;
        if (getNode(vec3(15,0,28), node)){
            cout<<node.id<<endl;
            node.printPosition();
        }
        */
    }
};