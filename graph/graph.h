/* 
    Andrea Centeno
    sep-dic 2017
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>

class Node{ 
public:
    int id;
    glm::vec3 point;
    glm::vec3 triangle[3];
    set<int> adjacent;

    Node(){}

    Node(int i,glm::vec3 t[], bool addNext = true) : id(i){
        for(int i =0; i<3; i++){ triangle[i] = t[i]; }
        setPoint();
        if(addNext) adjacent.insert(i+1);
    }

    Node(int i,glm::vec3 t[], set<int> a) : id(i), adjacent(a){
        for(int i =0; i<3; i++){ triangle[i] = t[i]; }
        setPoint();
    }

    void setPoint(){
        point = {(triangle[0].x+triangle[1].x+triangle[2].x)/3
                ,0 
                ,(triangle[0].z+triangle[1].z+triangle[2].z)/3 };
    }

    void printNodeInfo(){
        cout<<"-- NODO "<<id<<" --"<<endl;
        cout<<"   Punto "<< point.x<<","<<point.y<<","<<point.z<<endl;
        cout<<"   Adyacentes ";
        for(set<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it){ 
            cout<<(*it)<<" ";
        }
        cout <<endl;
    }

    void drawAdjLine(map<int,Node> nodes){
        glColor3f(1,1,1);
        for (set<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it ){
            if ((*it) < id) continue;
            glm::vec3 p;
            glBegin(GL_LINES);
                p = nodes[(*it)].point;
                glVertex3f( p.x,p.y,p.z);
                glVertex3f( point.x,point.y,point.z);
            glEnd();
        }
    }
};

class Heuristic{ 
public:
    //Stores the goal node that this heuristic is estimating for
    Node goalNode;

    Heuristic(Node g) : goalNode(g){}

    /*
    Generates an estimated cost to reach the 
    stored goal from the given node
    */
    float estimate(Node node){
        return glm::distance(node.point,goalNode.point);
    }
};


class Graph{ 
public:
    map<int,Node> nodes;
    map<pair<int,int>, float> distances;
    map<pair<int,int>, int> weight;
  
    float sign (glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
    {
        return (p1.x - p3.x) * (p2.z - p3.z) - (p2.x - p3.x) * (p1.z - p3.z);
    }

    /*
    Busca si el punto dado se encuentra dentro del triangulo correspondiente al nodo
    */
    bool pointInTriangle (glm::vec3 pt, Node node)
    {
        glm::vec3 v1 = node.triangle[0];
        glm::vec3 v2 = node.triangle[1];
        glm::vec3 v3 = node.triangle[2];
        bool b1, b2, b3;

        b1 = sign(pt, v1, v2) < 0.0f;
        b2 = sign(pt, v2, v3) < 0.0f;
        b3 = sign(pt, v3, v1) < 0.0f;

        return ((b1 == b2) && (b2 == b3));
    }

    /*
    Obtiene el nodo del grafo dada una point en el mapa
    */
    bool getNode(glm::vec3 pt, Node &node){
        //cout<<"Buscar punto "<< pt.x<<","<<pt.y<<","<<pt.z<<endl;
        for (map<int,Node>::iterator it = nodes.begin(); it != nodes.end(); ++it ){
            //cout<<"buscando triangulo en nodo "<<(*it).second.id<<endl;
            if( pointInTriangle(pt,(*it).second) ) {
                node = (*it).second;
                //cout<<"-> encontrado "<<endl;
                //node.printNodeInfo();
                return true;
            }
        }
    }

    /*
    Aumenta el peso de un camino
    */
    bool changeWeight(std::list<int> nodesID, int weight){   
        int i,j;

        std::list<int>::iterator it = nodesID.begin();
        i = (*it);

        ++it;

        while (it != nodesID.end()){
            j = (*it);

            this->weight[make_pair(i,j)] += weight;
            i = j;
            ++it;
        }
    }

    /*
    Itera sobre los nodos y calcula las distancias entre los adyacentes
    */
    void setDistances(){
        float dist;
        Node node;
        for (map<int,Node>::iterator itNode = nodes.begin(); itNode != nodes.end(); ++itNode ){
            node = (*itNode).second;
            for (set<int>::iterator it = node.adjacent.begin(); it != node.adjacent.end(); ++it ){
                if ((*it) < node.id) continue;
                dist = glm::distance(node.point,nodes[(*it)].point);
                this->distances[make_pair(node.id,(*it))] = dist;
                this->distances[make_pair((*it),node.id)] = dist;

                //costo
                this->weight[make_pair(node.id,(*it))] = 1;
                this->weight[make_pair((*it),node.id)] = 1;

                //inserto el nodo actual entre los adyacentes del otro
                nodes[(*it)].adjacent.insert(node.id);
            }
            
        }
    }

    /*
    Dibuja los triagulos asociados a los nodos
    */
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

            (*it).second.drawAdjLine(nodes);
            glColor3f(1,0,0);
        }
    }

     /*
    Imprime todos los nodos
    */
    void printGraph(){
        cout<<"----------------PESOS ---------------"<<endl;
        for (map<pair<int,int>, int>::iterator it = weight.begin(); it != weight.end(); ++it ){
            if ((*it).second > 1)
                cout<<(*it).first.first<<","<<(*it).first.second<<" "<<(*it).second<<endl;
        }
    }

    /* Crea el grafo del juego */
    void createGameGraphNew();
};

#endif