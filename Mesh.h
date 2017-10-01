class Mesh{
protected:
	vec3 position;
	GLfloat height;
	vec3 color;
	char type; //W:wall, O:obstacle1, H:hole
	
public:	GLfloat width;

	Mesh(vec3 p, GLfloat h, GLfloat w, vec3 c,char t) 
		: position(p),height(h),width(w),color(c),type(t) {}


	void draw(){
		switch (type){       	
	        case 'W': 
	        case 'H':
	        case 'O':
	        	glColor3f(color.x,color.y,color.z);
				glPushMatrix();
					glTranslatef(position.x-(width/2), 0.0, position.z-(height/2));
					glBegin(GL_TRIANGLE_STRIP);
						glVertex3f(0, 1, 0);	// Front-top-left
						glVertex3f(width, 1, 0);// Front-top-right
						glVertex3f(0, 0, 0);	// Front-bottom-left
						glVertex3f(width, 0, 0);// Front-bottom-right
						glVertex3f(width, 0, height); 	// Back-bottom-right
						glVertex3f(width, 1, 0); 		// Front-top-right
						glVertex3f(width, 1, height); 	// Back-top-right
						glVertex3f(0, 1, 0); 			// Front-top-left
						glVertex3f(0, 1, height); 		// Back-top-left
						glVertex3f(0, 0, 0); 			// Front-bottom-left
						glVertex3f(0, 0, height);		// Back-bottom-left
						glVertex3f(width, 0, height);	// Back-bottom-right
						glVertex3f(0, 1, height);		// Back-top-left
						glVertex3f(width, 1, height);	// Back-top-right
					glEnd();
				glPopMatrix();
	        break;	
	        /* 	            
				glColor3f(color.x,color.y,color.z);
				glPushMatrix();
					glBegin(GL_QUADS);
						glVertex3f(position.x - width/2, position.y, position.z + height/2);
						glVertex3f(position.x + width/2, position.y, position.z + height/2);
						glVertex3f(position.x + width/2, position.y, position.z - height/2);
						glVertex3f(position.x - width/2, position.y, position.z - height/2);
					glEnd();
				glPopMatrix();
	        break;
	        */
	        default: break;
	    } 
	}

	vector<vec3> getTriangles(){
		vector<vec3> vertexes {
			vec3(0, 1, 0)
			,vec3(width, 1, 0)
			,vec3(0, 0, 0)
			,vec3(width, 0, 0)
			,vec3(width, 0, height)
			,vec3(width, 1, 0)
			,vec3(width, 1, height)
			,vec3(0, 1, 0)
			,vec3(0, 1, height)
			,vec3(0, 0, 0)
			,vec3(0, 0, height)
			,vec3(width, 0, height)
			,vec3(0, 1, height)
			,vec3(width, 1, height)
		};
		return vertexes;
	}
};