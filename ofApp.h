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

		// camera
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


		//lights
		GLfloat ambientLight[4];
		bool ambientOn;
		bool dirOn;
		bool pointOn;
		bool autoMove;
		bool localViewer;


		bool ambientDirOn;
		bool difuseDirOn;
		bool specularDirOn;

		bool ambientPointOn;
		bool difusePointOn;
		bool specularPointOn;

		bool ambientSpotOn;
		bool difuseSpotOn;
		bool specularSpotOn;

		GLfloat dirVec[4];
		GLfloat dirAmb[4];
		GLfloat dirDif[4];
		GLfloat dirSpec[4];
		ofVec3f dirVec3f;
		GLfloat dirVecTheta;

		GLfloat pointPos1[4];
		GLfloat pointPos2[4];
		GLfloat pointAmb[4];
		GLfloat pointDif[4];
		GLfloat pointSpec[4];
		GLfloat pointZtheta;

		GLfloat spotPos[4];
		GLfloat spotDir[3];
		GLfloat spotAmb[4];
		GLfloat spotDif[4];
		GLfloat spotSpecular[4];
		GLfloat spotExponent;
		GLfloat spotCutoff;
		GLfloat spotTheta;
		bool spotOn;

		//materials
		int mat;
		bool customMat;
		GLint customMatCoef;

		GLfloat customMatAmb[4];
		GLfloat customMatDif[4];
		GLfloat customMatSpec[4];

		GLfloat  concreteAmb[4];
		GLfloat  concreteDif[4];
		GLfloat  concreteSpec[4];
		GLint    concreteCoef;

		GLfloat  grassAmb[4];
		GLfloat  grassDif[4];
		GLfloat  grassSpec[4];
		GLint    grassCoef;

		GLfloat  sandAmb[4];
		GLfloat  sandDif[4];
		GLfloat  sandSpec[4];
		GLint    sandCoef;

		GLfloat  waterAmb[4];
		GLfloat  waterDif[4];
		GLfloat  waterSpec[4];
		GLint    waterCoef;

		GLfloat  buildingAmb[4];
		GLfloat  buildingDif[4];
		GLfloat  buildingSpec[4];
		GLint    buildingCoef;

		GLfloat  glassAmb[4];
		GLfloat  glassDif[4];
		GLfloat  glassSpec[4];
		GLint    glassCoef;

		GLfloat  car1Amb[4];
		GLfloat  car1Dif[4];
		GLfloat  car1Spec[4];
		GLint    car1Coef;

		GLfloat  car2Amb[4];
		GLfloat  car2Dif[4];
		GLfloat  car2Spec[4];
		GLint    car2Coef;

		//texture
		ofImage img1;		
		ofImage img2;
		ofImage img3;
		ofImage img4;
		ofImage img5;
		ofImage img6;		
		ofImage img7;

		ofImage road1;
		ofImage pav1;
		ofImage parking1;

		
		GLfloat pointAtC, pointAtL, pointAtQ;


		ofImage waterTex;
		vector<ofVec3f> vertexes;
		vector<ofVec3f> normals;
		vector<ofVec2f> texCoords;


		//water
		float phaseX;
		float phaseY;
		float freqs[10];
		float amps[10];


		//skybox
		float rx, ry, rz;

		ofImage sky;
		ofFbo nightSky;
		ofImage nightSkyImg;
		unsigned char* skyPixels = NULL;
		int px, py, numPixels;


};
