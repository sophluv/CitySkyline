
#ifndef EXTRA_H
#define EXTRA_H

#include "ofMain.h"

//screen width
inline float gw() {
	return ofGetWidth();
}

//screen height
inline float gh() {
	return ofGetHeight();
}

//ModelView matrix
inline void coutModelviewMatrix() {
	
	GLfloat Matriz[4][4];
	cout << endl << "Modelview Matrix" << endl;
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << Matriz[j][i] << " ";
		}
		cout << endl;
	}
}

//Projection matrix
inline void coutProjectionMatrix() {

	GLfloat Matriz[4][4];
	cout << endl << "Projection Matrix" << endl;
	glGetFloatv(GL_PROJECTION_MATRIX, &Matriz[0][0]);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << Matriz[j][i] << " ";
		}
		cout << endl;
	}
}

//ModelView Matrix position
inline ofVec3f getModelViewMatrixPos() {
	GLfloat Matriz[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);
	ofVec3f aux;
	aux.x = Matriz[3][0];
	aux.y = Matriz[3][1];
	aux.z = Matriz[3][2];
	return aux;
}


inline void printMatrix(GLfloat m[][4]) {
	cout << endl << "Matrix 4x4" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << m[j][i] << " ";
		}
		cout << endl;
	}
	cout << endl << "matrix" << endl;
}

inline ofVec3f cross(ofVec3f A, ofVec3f B) {
	ofVec3f aux;
	aux.x = A.y * B.z - A.z * B.y;
	aux.y = A.z * B.x - A.x * B.z; 
	aux.z = A.x * B.y - A.y * B.x;

	return aux;
}


//prespective view
inline void perspective(GLfloat theta, GLfloat alpha, GLfloat beta, bool invertX = false, bool invertY = false) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat tan = tanf(theta * 0.5 * PI / 180.0);
	GLfloat d = (gh() / 2.0) / tan;
	GLfloat nearClip = d / alpha;
	GLfloat farClip = d * beta;
	GLfloat ymax = nearClip * tan;
	GLfloat xmax = (gw() / gh()) * ymax;
	if (invertX) {
		xmax = -xmax;
	}
	if (invertY) {
		ymax = -ymax;
	}
	glFrustum(-xmax, xmax, -ymax, ymax, nearClip, farClip);
}

//lookAt
inline void lookat(
	GLfloat camX,
	GLfloat camY,
	GLfloat camZ,
	GLfloat targetX,
	GLfloat targetY,
	GLfloat targetZ,
	GLfloat upX,
	GLfloat upY,
	GLfloat upZ)
{
	ofVec3f cam = ofVec3f(camX, camY, camZ);
	ofVec3f target = ofVec3f(targetX, targetY, targetZ);
	ofVec3f up = ofVec3f(upX, upY, upZ);


	ofVec3f N = cam - target;
	N = N.normalized();
	ofVec3f U = cross(up, N);
	U = U.normalized();
	ofVec3f V = cross(N, U);
	V = V.normalized();

	GLfloat camTransformMatrix[4][4] = {
		{U.x, V.x, N.x, 0},
		{U.y, V.y, N.y, 0},
		{U.z, V.z, N.z, 0},
		{-U.dot(cam), -V.dot(cam), -N.dot(cam), 1}
	};


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(&camTransformMatrix[0][0]);

}

inline void lookat(ofVec3f cam, ofVec3f look, ofVec3f up) {
	lookat(cam.x, cam.y, cam.z, look.x, look.y, look.z, up.x, up.y, up.z);
}




void drawBase(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat height) {



	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, 0);
	glVertex3f(x1, -y0, 0);
	glVertex3f(x1, -y1, 0);
	glVertex3f(x0, -y1, 0);
	glEnd();


	//top
	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, height);
	glVertex3f(x1, -y0, height);
	glVertex3f(x1, -y1, height);
	glVertex3f(x0, -y1, height);
	glEnd();

	//left side
	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, 0);
	glVertex3f(x0, -y1, 0);
	glVertex3f(x0, -y1, height);
	glVertex3f(x0, -y0, height);
	glEnd();

	//back side
	glBegin(GL_QUADS);
	glVertex3f(x1, -y0, 0);
	glVertex3f(x1, -y1, 0);
	glVertex3f(x1, -y1, height);
	glVertex3f(x1, -y0, height);
	glEnd();

	//right side
	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, 0);
	glVertex3f(x1, -y0, 0);
	glVertex3f(x1, -y0, height);
	glVertex3f(x0, -y0, height);
	glEnd();


	glBegin(GL_QUADS);
	glVertex3f(x0, -y1, 0);
	glVertex3f(x1, -y1, 0);
	glVertex3f(x1, -y1, height);
	glVertex3f(x0, -y1, height);
	glEnd();



}






void drawBuilding(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat height, ofImage img) {

	glEnable(GL_TEXTURE);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	img.bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, 0);
	glVertex3f(x1, -y0, 0);
	glVertex3f(x1, -y1, 0);
	glVertex3f(x0, -y1, 0);
	glEnd();


	//top
	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, height);
	glVertex3f(x1, -y0, height);
	glVertex3f(x1, -y1, height);
	glVertex3f(x0, -y1, height);
	glEnd();

	//left side
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);  
	glVertex3f(x0, -y0, 0);
	glTexCoord2f(1, 1);  
	glVertex3f(x0, -y1, 0);
	glTexCoord2f(1, 0);  
	glVertex3f(x0, -y1, height);
	glTexCoord2f(0, 0); 
	glVertex3f(x0, -y0, height);
	glEnd();


	//back side
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); 
	glVertex3f(x1, -y0, 0);
	glTexCoord2f(1, 1);  
	glVertex3f(x1, -y1, 0);
	glTexCoord2f(1, 0);  
	glVertex3f(x1, -y1, height);
	glTexCoord2f(0, 0);  
	glVertex3f(x1, -y0, height);
	glEnd();

	//right side
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);  
	glVertex3f(x0, -y0, 0);
	glTexCoord2f(1, 1);  
	glVertex3f(x1, -y0, 0);
	glTexCoord2f(1, 0);  
	glVertex3f(x1, -y0, height);
	glTexCoord2f(0, 0);  
	glVertex3f(x0, -y0, height);
	glEnd();

	//bottom side
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);  
	glVertex3f(x0, -y1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(x1, -y1, 0);
	glTexCoord2f(1, 0);  
	glVertex3f(x1, -y1, height);
	glTexCoord2f(0, 0);  
	glVertex3f(x0, -y1, height);
	glEnd();


	img.unbind();
	glDisable(GL_TEXTURE);
}


void drawWalkway(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat height, ofImage img) {

	glEnable(GL_TEXTURE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	img.bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, 0);
	glVertex3f(x1, -y0, 0);
	glVertex3f(x1, -y1, 0);
	glVertex3f(x0, -y1, 0);
	glEnd();


	//top
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(x0, -y0, height);
	glTexCoord2f(1, 0);
	glVertex3f(x1, -y0, height);
	glTexCoord2f(1, 1);
	glVertex3f(x1, -y1, height);
	glTexCoord2f(0, 1);
	glVertex3f(x0, -y1, height);
	glEnd();

	//left side
	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, 0);
	glVertex3f(x0, -y1, 0);
	glVertex3f(x0, -y1, height);
	glVertex3f(x0, -y0, height);
	glEnd();

	//back side
	glBegin(GL_QUADS);
	glVertex3f(x1, -y0, 0);
	glVertex3f(x1, -y1, 0);
	glVertex3f(x1, -y1, height);
	glVertex3f(x1, -y0, height);
	glEnd();

	//right side
	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, 0);
	glVertex3f(x1, -y0, 0);
	glVertex3f(x1, -y0, height);
	glVertex3f(x0, -y0, height);
	glEnd();


	glBegin(GL_QUADS);
	glVertex3f(x0, -y1, 0);
	glVertex3f(x1, -y1, 0);
	glVertex3f(x1, -y1, height);
	glVertex3f(x0, -y1, height);
	glEnd();

	img.unbind();
	glDisable(GL_TEXTURE);

}


//base
inline void base() {


	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	GLfloat x0 = -0.5;
	GLfloat y0 = -0.5;
	GLfloat x1 = 0.5;
	GLfloat y1 = 0.5;

	GLfloat height = -0.001;
	drawBase(x0, y0, x1, y1, height);

	glPopMatrix();
}


inline void parkingLot() {


	glPushMatrix();
	glRotated(-90, 1, 0, 0);


	GLfloat height = 0.001;

	GLfloat x0 = -0.35;
	GLfloat y0 = -0.45;
	GLfloat x1 = 0.35;
	GLfloat y1 = -0.47;

	drawBase(x0, y0, x1, y1, height);

	x0 = -0.35;
	y0 = -0.45;
	x1 = -0.33; 
	y1 = 0.35;

	drawBase(x0, y0, x1, y1, height);

	x0 = 0.35;
	y0 = -0.45;
	x1 = 0.33;
	y1 = 0.35;

	drawBase(x0, y0, x1, y1, height);

	glPopMatrix();

} 


//park
inline void pond() {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	GLfloat x0 = -0.28;
	GLfloat y0 = -0.28;
	GLfloat x1 = 0.28;
	GLfloat y1 = 0.28;

	GLfloat height = 0.013;

	drawBase(x0, y0, x1, y1, height);
	
	glPopMatrix();

}



//park
inline void park() {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	GLfloat x0 = -0.35;
	GLfloat y0 = -0.35;
	GLfloat x1 = 0.35;
	GLfloat y1 = 0.50;

	GLfloat height = 0.009;
	drawBase(x0, y0, x1, y1, height);

	glPopMatrix();

}

//lamp
inline void lamp() {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	GLfloat x0 = -0.25;
	GLfloat y0 = -0.25;
	GLfloat x1 = -0.242;
	GLfloat y1 = -0.242;

	GLfloat height = 0.2;
	drawBase(x0, y0, x1, y1, height);

	glTranslatef(0, 0, 0.2);

	x0 = -0.29;
	y0 = -0.252;
	x1 = -0.242;
	y1 = -0.24;

	height = 0.009;
	drawBase(x0, y0, x1, y1, height);
	glPopMatrix();

}

inline void building(ofImage img1, ofImage img2, ofImage img3){


	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	// building 1

	GLfloat x0 = -0.3;
	GLfloat y0 = -0.3;
	GLfloat x1 = 0;
	GLfloat y1 = 0;

	GLfloat height =0.7;
	drawBuilding(x0, y0, x1, y1, height, img1);


	// building 2

	 x0 = 0.1;
	 y0 = 0.1;
	 x1 = 0.32;
	 y1 = 0.32;

	height = 0.4;
	glColor3f(0.7, 0.7, 0.7);
	drawBuilding(x0, y0, x1, y1, height, img2);


	// walkway

	x0 = -0.35;
	y0 = -0.35;
	x1 = 0.35;
	y1 = 0.35;

	height = 0.03;
	glColor3f(0.6, 0.6, 0.6);
	drawWalkway(x0, y0, x1, y1, height, img3);

	glPopMatrix();

}


inline void bigBuilding(ofImage img1, ofImage img2) {
	glPushMatrix();

	glRotated(-90, 1, 0, 0);

	// main building

	GLfloat x0 = -0.2;
	GLfloat y0 = -0.2;
	GLfloat x1 = 0.2;
	GLfloat y1 = 0.2;

	GLfloat height = 1.1;
	glColor3f(0.7, 0.7, 0.7);
	drawBuilding(x0, y0, x1, y1, height, img1);


	// walkway

	 x0 = -0.35;
	 y0 = -0.35;
	 x1 = 0.35;
	 y1 = 0.35;

	height = 0.03;
	glColor3f(0.6, 0.6, 0.6);
	drawWalkway(x0, y0, x1, y1, height, img2);

	glPopMatrix();
}


inline void building2(ofImage img1, ofImage img2) {


	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	// main building

	GLfloat x0 = -0.2;
	GLfloat y0 = -0.2;
	GLfloat x1 = 0.2;
	GLfloat y1 = 0.2;

	GLfloat height = 0.6;
	glColor3f(0.7, 0.7, 0.7);
	drawBuilding(x0, y0, x1, y1, height, img1);


	// walkway

	x0 = -0.35;
	y0 = -0.35;
	x1 = 0.35;
	y1 = 0.5;

	height = 0.03;
	glColor3f(0.6, 0.6, 0.6);
	drawWalkway(x0, y0, x1, y1, height, img2);


	glPopMatrix();
}


inline void building1(ofImage img1, ofImage img2) {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	// main building

	GLfloat x0 = -0.2;
	GLfloat y0 = 0;
	GLfloat x1 = 0.2;
	GLfloat y1 = 0.3;

	GLfloat height = 0.75;
	glColor3f(0.7, 0.7, 0.7);
	drawBuilding(x0, y0, x1, y1, height, img1);

	 x0 = 0.2;
	 y0 = 0;
	 x1 = -0.2;
	 y1 = -0.3;

	 height = 0.75;
	glColor3f(0.7, 0.7, 0.7);
	drawBuilding(x0, y0, x1, y1, height, img1);

	// walkway

	x0 = -0.35;
	y0 = -0.5;
	x1 = 0.35;
	y1 = 0.35;

	height = 0.03;
	glColor3f(0.6, 0.6, 0.6);
	drawWalkway(x0, y0, x1, y1, height, img2);



	glPopMatrix();

}


inline void figure() {

	glPushMatrix();

	GLfloat p = 0.5;
	glRotated(-90, 1, 0, 0);

	glBegin(GL_QUADS);

	glVertex3f(-p, -p, p);
	glVertex3f(-p, p, p);
	glVertex3f(p, p, p);
	glVertex3f(p, -p, p);

	glVertex3f(-p, -p, -p);
	glVertex3f(p, -p, -p);
	glVertex3f(p, p, -p);
	glVertex3f(-p, p, -p);

	glVertex3f(-p, -p, -p);
	glVertex3f(-p, -p, p);
	glVertex3f(p, -p, p);
	glVertex3f(p, -p, -p);

	glVertex3f(-p, p, p);
	glVertex3f(-p, p, -p);
	glVertex3f(p, p, -p);
	glVertex3f(p, p, p);

	glVertex3f(-p, -p, p);
	glVertex3f(-p, -p, -p);
	glVertex3f(-p, p, -p);
	glVertex3f(-p, p, p);

	glVertex3f(p, -p, p);
	glVertex3f(p, p, p);
	glVertex3f(p, p, -p);
	glVertex3f(p, -p, -p);

	glEnd();
	glPopMatrix();

}


inline void malha_unit_yup(GLint m, GLint n) {
	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			glVertex3f(i * x_step + x_start, j * y_step + y_start, 0);
			glVertex3f((i + 1) * x_step + x_start, j * y_step + y_start, 0);
			glVertex3f((i + 1) * x_step + x_start, (j + 1) * y_step + y_start, 0);
			glVertex3f(i * x_step + x_start, (j + 1) * y_step + y_start, 0);
		}
	}
	glEnd();
}






inline GLfloat getMultiNoise(float x, float y, float f[], float a[], int numBands) {

	float noise = 0;
	float maxAmp = 0.;

	for (int i = 0; i < numBands; i++) {
		noise += a[i] * ofNoise(f[i] * x, f[i] * y);
		maxAmp += a[i];
	}
	return noise / maxAmp;
}


inline void sphereSkyBox(int res) {

	glRotated(-90, 1, 0, 0);

	float dtheta = PI / float(res);
	float dphi = 2 * PI / float(res);



	for (int i = 0; i < res; i++) {
		for (int j = 0; j < res; j++) {
			glBegin(GL_QUADS);

			float x1 = sin(i * dtheta) * cos(j * dphi);
			float y1 = sin(i * dtheta) * sin(j * dphi);
			float z1 = cos(i * dtheta);
			float tx1 = i / float(res);
			float ty1 = j / float(res);
			ofVec3f n1 = ofVec3f(-x1, -y1, -z1);
			glTexCoord2f(ty1, tx1);
			glNormal3f(n1.x, n1.y, n1.z);
			glVertex3f(x1, y1, z1);

			float x2 = sin(i * dtheta) * cos((j + 1) * dphi);
			float y2 = sin(i * dtheta) * sin((j + 1) * dphi);
			float z2 = cos(i * dtheta);
			float tx2 = i / float(res);
			float ty2 = (j + 1) / float(res);
			ofVec3f n2 = ofVec3f(-x2, -y2, -z2);
			glTexCoord2f(ty2, tx2);
			glNormal3f(n2.x, n2.y, n2.z);
			glVertex3f(x2, y2, z2);

			float x3 = sin((i + 1) * dtheta) * cos((j + 1) * dphi);
			float y3 = sin((i + 1) * dtheta) * sin((j + 1) * dphi);
			float z3 = cos((i + 1) * dtheta);
			float tx3 = (i + 1) / float(res);
			float ty3 = (j + 1) / float(res);
			ofVec3f n3 = ofVec3f(-x3, -y3, -z3);
			glTexCoord2f(ty3, tx3);
			glNormal3f(n3.x, n3.y, n3.z);
			glVertex3f(x3, y3, z3);

			float x4 = sin((i + 1) * dtheta) * cos(j * dphi);
			float y4 = sin((i + 1) * dtheta) * sin(j * dphi);
			float z4 = cos((i + 1) * dtheta);
			float tx4 = (i + 1) / float(res);
			float ty4 = j / float(res);
			ofVec3f n4 = ofVec3f(-x4, -y4, -z4);
			glTexCoord2f(ty4, tx4);
			glNormal3f(n4.x, n4.y, n4.z);
			glVertex3f(x4, y4, z4);

			glEnd();
		}
	}
}

#endif