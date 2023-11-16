
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



//base
inline void base(GLint m, GLint n) {

	glPushMatrix();
	glTranslated(0., -0.01, 0.);
	glRotated(-90, 1, 0, 0);

	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			glVertex2d(i * x_step + x_start, j * y_step + y_start);
			glVertex2d(i * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, j * y_step + y_start);
		}
	}
	glEnd();

	glPopMatrix();
}

//sand
inline void sandBase(GLint m, GLint n) {

	glColor3f(211 / 255.0, 211 / 255.0, 211.0 / 255.0);
	glPushMatrix();
	glTranslated(0., -0.01, 0.);
	glRotated(-90, 1, 0, 0);

	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			glVertex2d(i * x_step + x_start, j * y_step + y_start);
			glVertex2d(i * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, j * y_step + y_start);
		}
	}
	glEnd();

	glPopMatrix();
}

//lake
inline void lake(GLint m, GLint n) {

	glColor3f(123.0 / 255.0, 167.0 / 255.0, 201.0 / 255.0);

	glPushMatrix();
	glTranslated(0., -0.01, 0.);
	glRotated(-90, 1, 0, 0);

	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			glVertex2d(i * x_step + x_start, j * y_step + y_start);
			glVertex2d(i * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, j * y_step + y_start);
		}
	}
	glEnd();
	glPopMatrix();
}


inline void garden(GLint m, GLint n) {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);


	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;

	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);


	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			GLfloat x0 = i * x_step + x_start;
			GLfloat y0 = j * y_step + y_start;
			GLfloat x1 = (i + 1) * x_step + x_start;
			GLfloat y1 = (j + 1) * y_step + y_start;

			GLfloat height = 0;


			if (i == 0 || j == 0 || i == 6 || j == 6) {
				glColor3f(0.3, 0.3, 0.3);

			}
			else {
				glColor3f(117.0 / 255.0, 148.0 / 255.0, 101.0 / 255.0);

			}

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x0, -y1, 0);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, height);
			glVertex3f(x1, -y0, height);
			glVertex3f(x1, -y1, height);
			glVertex3f(x0, -y1, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x0, -y1, 0);
			glVertex3f(x0, -y1, height);
			glVertex3f(x0, -y0, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x1, -y1, height);
			glVertex3f(x1, -y0, height);
			glEnd();

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
	}
	glPopMatrix();

}

inline void parkingLot(GLint m, GLint n) {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;

	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);


	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			GLfloat x0 = i * x_step + x_start;
			GLfloat y0 = j * y_step + y_start;
			GLfloat x1 = (i + 1) * x_step + x_start;
			GLfloat y1 = (j + 1) * y_step + y_start;

			GLfloat height = 0;

			if (i == 0 || j == 0 || i == 6 || ((j == 6) && (i != 3 && i != 2))) {

				height = 0.03;
				glColor3f(0.5, 0.5, 0.5);
			}
			else {
				height = 0;
				glColor3f(0.3, 0.3, 0.3);

			}
			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x0, -y1, 0);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, height);
			glVertex3f(x1, -y0, height);
			glVertex3f(x1, -y1, height);
			glVertex3f(x0, -y1, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x0, -y1, 0);
			glVertex3f(x0, -y1, height);
			glVertex3f(x0, -y0, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x1, -y1, height);
			glVertex3f(x1, -y0, height);
			glEnd();

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
	}
	glPopMatrix();
}

//park
inline void park(GLint m, GLint n) {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;

	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);


	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			GLfloat x0 = i * x_step + x_start;
			GLfloat y0 = j * y_step + y_start;
			GLfloat x1 = (i + 1) * x_step + x_start;
			GLfloat y1 = (j + 1) * y_step + y_start;

			GLfloat height = 0;


			if (i == 0 || j == 0 || i == 6 || j == 6) {
				glColor3f(117.0 / 255.0, 148.0 / 255.0, 101.0 / 255.0);

			}
			else {
				glColor3f(123.0 / 255.0, 167.0 / 255.0, 201.0 / 255.0);

			}
			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x0, -y1, 0);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, height);
			glVertex3f(x1, -y0, height);
			glVertex3f(x1, -y1, height);
			glVertex3f(x0, -y1, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x0, -y1, 0);
			glVertex3f(x0, -y1, height);
			glVertex3f(x0, -y0, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x1, -y1, height);
			glVertex3f(x1, -y0, height);
			glEnd();

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
	}
	glPopMatrix();
}

inline void building(GLint m, GLint n) {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;

	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);


	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			GLfloat x0 = i * x_step + x_start;
			GLfloat y0 = j * y_step + y_start;
			GLfloat x1 = (i + 1) * x_step + x_start;
			GLfloat y1 = (j + 1) * y_step + y_start;

			GLfloat height = 0;

			// building 1
			if ((i == 1 || i == 2) && (j == 1 || j == 2 || j == 3 || j == 4 || j == 5)) {

				height = 1.0;
				glColor3f(0.9, 0.9, 0.89);
			}

			else if ((j == 1 || j == 2) && (i == 3 || i == 4 || i == 5)) {

				height = 0.01;
				glColor3f(117.0 / 255.0, 148.0 / 255.0, 101.0 / 255.0);
			}

			// building 2
			else if ((i == 4 || i == 5) && (j == 4 || j == 5)) {

				height = 0.5;
				glColor3f(0.74, 0.73, 0.75);
			}

			else {
				height = 0.03;
				glColor3f(0.6, 0.6, 0.6);
			}

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x0, -y1, 0);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, height);
			glVertex3f(x1, -y0, height);
			glVertex3f(x1, -y1, height);
			glVertex3f(x0, -y1, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x0, -y1, 0);
			glVertex3f(x0, -y1, height);
			glVertex3f(x0, -y0, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x1, -y1, height);
			glVertex3f(x1, -y0, height);
			glEnd();

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
	}
	glPopMatrix();

}

void drawBuilding(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat height) {

	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, 0);
	glVertex3f(x1, -y0, 0);
	glVertex3f(x1, -y1, 0);
	glVertex3f(x0, -y1, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, height);
	glVertex3f(x1, -y0, height);
	glVertex3f(x1, -y1, height);
	glVertex3f(x0, -y1, height);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(x0, -y0, 0);
	glVertex3f(x0, -y1, 0);
	glVertex3f(x0, -y1, height);
	glVertex3f(x0, -y0, height);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(x1, -y0, 0);
	glVertex3f(x1, -y1, 0);
	glVertex3f(x1, -y1, height);
	glVertex3f(x1, -y0, height);
	glEnd();

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

inline void bigBuilding(GLint m, GLint n) {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;

	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			GLfloat x0 = i * x_step + x_start;
			GLfloat y0 = j * y_step + y_start;
			GLfloat x1 = (i + 1) * x_step + x_start;
			GLfloat y1 = (j + 1) * y_step + y_start;

			GLfloat height = 1.1;
			glColor3f(0.7, 0.7, 0.7);

			//walkway
			if (i == 1 || i == 5 || j == 1 || j == 5) {
				height = 0.03;
				glColor3f(0.6, 0.6, 0.6);
			}
			//road
			if (i == 0 || i == 6 || j == 0 || j == 6) {
				height = 0;
				glColor3f(0.3, 0.3, 0.3);
			}

			//main building
			drawBuilding(x0, y0, x1, y1, height);

			//the top floor
			if (i == 3 && j == 3) {
				//smaller building
				GLfloat topHeight = 0.1;
				drawBuilding(x0, y0, x1, y1, height + topHeight);
			}
		}
	}
	glPopMatrix();
}

inline void building2(GLint m, GLint n, GLfloat randomHeights[3][3], ofColor colors[3][3]) {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;

	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);


	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			GLfloat x0 = i * x_step + x_start;
			GLfloat y0 = j * y_step + y_start;
			GLfloat x1 = (i + 1) * x_step + x_start;
			GLfloat y1 = (j + 1) * y_step + y_start;

			GLfloat height = randomHeights[i - 2][j - 2];

			GLubyte r = colors[i - 2][j - 2].r;
			GLubyte g = colors[i - 2][j - 2].g;
			GLubyte b = colors[i - 2][j - 2].b;
			glColor3ub(r, g, b);

			if (height <= 0) {
				height = 0;
				glColor3f(117.0 / 255.0, 148.0 / 255.0, 101.0 / 255.0);

			}
			//walkway
			if (i == 1 || i == 5 || j == 0 || j == 1 || j == 5) {
				height = 0.03;
				glColor3f(0.6, 0.6, 0.6);
			}
			//road
			if (i == 0 || i == 6 || j == 6) {
				height = 0;
				glColor3f(0.3, 0.3, 0.3);
			}

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x0, -y1, 0);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, height);
			glVertex3f(x1, -y0, height);
			glVertex3f(x1, -y1, height);
			glVertex3f(x0, -y1, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x0, -y1, 0);
			glVertex3f(x0, -y1, height);
			glVertex3f(x0, -y0, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x1, -y1, height);
			glVertex3f(x1, -y0, height);
			glEnd();

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
	}
	glPopMatrix();
}


inline void building1(GLint m, GLint n, GLfloat randomHeights[3][3], ofColor colors[3][3]) {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);

	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;

	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			GLfloat x0 = i * x_step + x_start;
			GLfloat y0 = j * y_step + y_start;
			GLfloat x1 = (i + 1) * x_step + x_start;
			GLfloat y1 = (j + 1) * y_step + y_start;


			GLfloat height = randomHeights[i - 2][j - 2];

			GLubyte r = colors[i - 2][j - 2].r;
			GLubyte g = colors[i - 2][j - 2].g;
			GLubyte b = colors[i - 2][j - 2].b;
			glColor3ub(r, g, b);

			if (height <= 0) {
				height = 0;
				glColor3f(117.0 / 255.0, 148.0 / 255.0, 101.0 / 255.0);

			}
			//walkway
			if (i == 1 || i == 5 || j == 1 || j == 5 || j == 6) {
				height = 0.03;
				glColor3f(0.6, 0.6, 0.6);
			}
			//road
			if (i == 0 || i == 6 || j == 0) {
				height = 0;
				glColor3f(0.3, 0.3, 0.3);
			}

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x0, -y1, 0);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, height);
			glVertex3f(x1, -y0, height);
			glVertex3f(x1, -y1, height);
			glVertex3f(x0, -y1, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x0, -y0, 0);
			glVertex3f(x0, -y1, 0);
			glVertex3f(x0, -y1, height);
			glVertex3f(x0, -y0, height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(x1, -y0, 0);
			glVertex3f(x1, -y1, 0);
			glVertex3f(x1, -y1, height);
			glVertex3f(x1, -y0, height);
			glEnd();

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
	}
	glPopMatrix();

}


inline void figure() {

	GLfloat p = 0.5;
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

}




#endif