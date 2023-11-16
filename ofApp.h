#pragma once

#include "ofMain.h"
#include "extra.h"
#include <cmath>


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void drawGeometry();

		int view;
		GLfloat lensAngle;
		GLfloat alpha, beta;

		ofLight light;
		ofLight ambientLight;

		ofVec3f camPos;
		ofVec3f lookatPos;
		ofVec3f camUp;
		GLfloat orbitAngle;

		float vel;

		GLint resX ;
		GLint resY ;
		GLint floorX;
		GLint floorY;
		GLint floorWidth;
		GLint floorHeight;
		GLint floorHeightPos;

		GLint m;
		GLint n;

		GLint nBuildings;

		GLfloat minHeight;
		GLfloat maxHeight;

		GLfloat tallHeights[3][3];
		GLfloat midHeights[3][3];
		GLfloat shortHeights[3][3];

		//car
		GLfloat carWidth, carHeight, carDepth;
		ofVec3f carPos;
		ofVec3f carRotation;
		int carState;

		//sliding door
		GLfloat doorWidth, doorHeight, doorDepth;
		ofVec3f doorRightPos;
		ofVec3f doorLeftPos;

		int count;
		int open;

		bool ambientLightEnabled;

};
