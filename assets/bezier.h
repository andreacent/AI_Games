/* 
    Andrea Centeno
    carnet USB: 10-10138
    sep-dic 2017
*/
#ifndef BEZIER_H
#define BEZIER_H

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <list>

//https://users.cs.jmu.edu/bernstdh/web/common/lectures/summary_opengl-bezier-curves.php

int binomialCoeff(int n, int k){
    int result = 1;
    if (k > n - k) k = n - k;

    for (int i = 0; i < k; ++i)
    {
        result *= (n - i);
        result /= (i + 1);
    }

    return result;
}

class Bezier{
public:
    // Beziers size
    int size;
    // Beziers Points
    std::list<glm::vec3> points;  

    Bezier() { size = 0; }

    Bezier(std::list<glm::vec3> p) : points(p) {
        size = int(p.size());
    }

    glm::vec3 getPoint(GLfloat t) {
        glm::vec3 point = {0,0,0};
        int i = 0;
        for (glm::vec3 p : points) {
            point += p * (float)(binomialCoeff(size - 1, i) * pow(t, i) * pow(1 - t, size - 1 - i));
            i++;
        }
        return point;
    }

    float getParam(glm::vec3 position, int iterations = 20) {
        glm::vec3 point;
        float new_param = 0.5, param = 0.5, length, lower_length, upper_length; // Params starting from half the Bezier

        // Initial length value
        length = glm::length(getPoint(param) - position);

        for (int i = 0; i <= iterations; i++) {
            new_param = new_param / 2; // 0 < param < 1

            lower_length = glm::length(getPoint(param - new_param) - position); //lower bound comparation
            upper_length = glm::length(getPoint(param + new_param) - position); //upper bound comparation
            
            if (lower_length <= upper_length) {
                param -= new_param;
                length = lower_length;
            }
            else {
                param += new_param;
                length = upper_length;
            }
        }

        return param;
    }

    void draw() {
        glm::vec3 p1,p2;

        std::list<glm::vec3>::iterator itPath = points.begin();
        p1 = (*itPath);

        ++itPath;

        glColor3f(0,1,1);
        glBegin(GL_LINES);
            while (itPath != points.end()){
                p2 = (*itPath);
                glVertex3f(p1.x, p1.y, p1.z);
                glVertex3f(p2.x, p2.y, p2.z);
                p1 = p2;
                ++itPath;
            }
        glEnd();

        //Draw each segment of the curve. 
        //Make t increment in smaller amounts for a more detailed curve.
        p1 = points.front();
        glColor3f(1,0,1);
        glBegin(GL_LINES);
            for(float t = 0.0;t <= 1.0; t += 0.02)
            {
                p2 = getPoint(t);
                glVertex3f(p1.x, p1.y, p1.z);
                glVertex3f(p2.x, p2.y, p2.z);
                p1 = p2;
            }
        glEnd();
    }

};

#endif