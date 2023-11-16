#include "ofApp.h"


#define W 1024 
#define H 768

GLfloat cp[4][9] = {
		{-W, W / 3, 0, 0, W / 3, 0, 0, 1, 0}, //front
		{0, W*1.1, 0, 0, 0, 0, 0, 0, -1}, //top 
		{-W*0.5, -W / 3, W*0.5, 0, W / 3, 0, 0, 1, 0}, //bottom
		{W*0.5, W / 3, -W*0.5, 0, W / 3, 0, 0, 1, 0} //extra 
};

ofColor colors[3][3] = {
{ofColor(138, 137, 136), ofColor(194, 191, 190), ofColor(165, 160, 160)},
{ofColor(200, 200, 200), ofColor(160, 161, 157), ofColor(194, 191, 190)},
{ofColor(132, 128, 129), ofColor(212, 220, 220), ofColor(102, 108, 105)}
};


//--------------------------------------------------------------  
void ofApp::setup() {

	ofSetFrameRate(60);
	glEnable(GL_DEPTH_TEST);

	ofEnableLighting();

	glPointSize(200);
	glLineWidth(3);
	
	lensAngle = 50;
	alpha = 10;
	beta = 1000;
	
	view = 0;
	orbitAngle = 0;
	lookatPos = ofVec3f(0, 0, 0);
	camUp = ofVec3f(0, 1, 0);

	vel = 0.01;

	//floor parameters
	resX = 10;
	resY = 10;
	floorX = 1;
	floorY = 1;
	floorWidth = gw();
	floorHeight = gw();
	floorHeightPos = 0.;

	//car parameters
	carWidth = 0.05;
	carDepth = 0.05;
	carHeight = 0.1;

	carPos.x = -0.4;
	carPos.y = 0.01;
	carPos.z = -0.4;

	carRotation.set(0, 0, 0);
	carState = 0; 

	//sliding door parameters
	doorWidth = 0.05;
	doorDepth = 0.18;
	doorHeight = 0.05;

	doorRightPos.x = -4.1;
	doorRightPos.y = 0.65;
	doorRightPos.z = -1.4;

	doorLeftPos.x = -4.1;
	doorLeftPos.y = 0.65;
	doorLeftPos.z = 1.4;

	//aux for sliding door
	count = 0;
	open = 0;

	//7x7 quarters
	n = 7;
	m = 7; 


	minHeight = 0.3;
	maxHeight = 0.8;

	nBuildings = 3;

	for (int i = 0; i < nBuildings; i++) {
		for (int j = 0; j < nBuildings; j++) {
			tallHeights[i][j] = minHeight + static_cast<GLfloat>(rand()) / (RAND_MAX + 1.0) * (maxHeight - minHeight); 
		}
	}
	 
	minHeight = 0.15;
	maxHeight = 0.3;

	for (int i = 0; i < nBuildings; i++) {
		for (int j = 0; j < nBuildings; j++) {
			midHeights[i][j] = minHeight + static_cast<GLfloat>(rand()) / (RAND_MAX + 1.0) * (maxHeight - minHeight); 
		}
	}

	minHeight = -0.1;
	maxHeight = 0.15;

	for (int i = 0; i < nBuildings; i++) {
		for (int j = 0; j < nBuildings; j++) {
			shortHeights[i][j] = minHeight + static_cast<GLfloat>(rand()) / (RAND_MAX + 1.0) * (maxHeight - minHeight);
		}
	}


	ambientLight.setAmbientColor(ofFloatColor(0.7, 0.7, 0.7, 1.0)); 
	ambientLight.enable();

	light.setPosition(0, 0, 0); 
	light.setDiffuseColor(ofFloatColor(1.0, 1.0, 0.7, 1.0)); 
	light.enable();

	ambientLightEnabled = true; 

	ofBackground(ofColor(211, 240, 246));

}

//--------------------------------------------------------------
void ofApp::update() { 

	if (view == 4) {
		camPos.x = W * cos(orbitAngle);
		camPos.z = W * sin(orbitAngle);
		camPos.y = H;
		orbitAngle += PI*0.005;
	}

	// forward
	if (carState == 0) {
		carPos.z += vel;
		if (carPos.z >= 3.5) {
			carState = 1;
			carRotation.y = 90; 
		}
	}
	// right
	else if (carState == 1) {
		carPos.x += vel;
		if (carPos.x >= 0.4) {
			carState = 2; 
			carRotation.y = 180; 
		}
	}
	//backward
	else if (carState == 2) {
		carPos.z -= vel;
		if (carPos.z <= -0.4) {
			carState = 3; 
			carRotation.y = 270;  
		}
	}
	//left
	else if (carState == 3) {
		carPos.x -= vel;
		if (carPos.x <= -0.4) {
			carState = 0; 
			carRotation.y = 0; 
		}
	}
	//open
	if (count >= 0 && count < 90) {
		doorRightPos.z += vel;
		doorLeftPos.z -= vel;
	}
	//close 
	else if (count >= 90 && count < 180) {
		doorRightPos.z -= vel;
		doorLeftPos.z += vel;
	}

	count++;

	if (count >= 180) {
		count = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofEnableLighting();

	//prespective camera
	glViewport(0, 0, gw(), gh());
	
	//projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective(lensAngle, alpha, beta);

	//lookat   
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	if (view < 4) {
		lookat(
			cp[view][0], cp[view][1], cp[view][2],
			cp[view][3], cp[view][4], cp[view][5],
			cp[view][6], cp[view][7], cp[view][8]
		);
	}
	else {
		lookat(camPos, lookatPos, camUp);
	}
	drawGeometry();
	glPopMatrix();

	//orthographic view
	glViewport(0, 0, gw() * 0.35, gh() * 0.35);

	//projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//projection orthographic
	glOrtho(-gw()*0.5, gw()*0.5, -gh()*0.5, gh()*0.5, -10000, 10000);

	//camera
	if (view < 4) {
		lookat(
			cp[view][0], cp[view][1], cp[view][2],
			cp[view][3], cp[view][4], cp[view][5],
			cp[view][6], cp[view][7], cp[view][8]
		);
	}
	else {
		lookat(camPos, lookatPos, camUp);
	}
	
	drawGeometry();

	ofDisableLighting();
}

void ofApp::drawGeometry() {

	//grass field
	glPushMatrix(); 
	glTranslatef(0, 0, 0);

	glScalef(gh() * 6.2, gh() * 6.2, gh() * 6.2); 
	glColor3f(117.0 / 255.0, 148.0 / 255.0, 101.0 / 255.0);

	base(resX, resY);
	glPopMatrix();  

	//sand
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(gh() * 6.5, gh() * 6.5, gh() * 6.5);
	glColor3f(211 / 255.0, 211 / 255.0, 211.0 / 255.0);  

	base(resX, resY);
	glPopMatrix(); // base pop  

	// sea
	glPushMatrix(); // lake push 
	glTranslatef(0, 0, 0); 
	glScalef(gh() * 30, gh() * 30, gh() * 30); 
	lake(resX, resY);
	glPopMatrix(); // lake pop 

	glPushMatrix();
	 
	// 0,0
	glTranslatef(0, 0, 0);
	glScalef(gh() * 1, gh() * 1, gh() * 1);
	bigBuilding(n, m);

	//sliding door right
	glColor3f(220.0 / 255.0, 245.0 / 255.0, 245.0 / 255.0);
	glPushMatrix();
	glScalef(doorWidth, doorDepth, doorHeight);
	glTranslatef(doorRightPos.x, doorRightPos.y, doorRightPos.z);
	figure();
	glPopMatrix();

	//sliding door left
	glColor3f(220.0/255.0, 245.0/255.0, 245.0/255.0);
	glPushMatrix();
	glScalef(doorWidth, doorDepth, doorHeight);
	glTranslatef(doorLeftPos.x, doorLeftPos.y, doorLeftPos.z);
	figure();
	glPopMatrix();

	//door
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glScalef(doorWidth, doorDepth, 0.1);
	glTranslatef(-4.0, 0.65, 0);
	figure();
	glPopMatrix();

	// 1,0
	glTranslatef(1, 0, 0);
	building2(n, m, tallHeights, colors);  //1

	// 2,0
	glTranslatef(1, 0, 0);
	building1(n, m, midHeights, colors);  //2 

	// 2,1
	glTranslatef(0, 0, 1);
	bigBuilding(n, m);

	// 1,1
	glTranslatef(-1, 0, 0);
	building(n, m);

	// 0,1
	glTranslatef(-1, 0, 0);
	bigBuilding(n, m);

	// -1,1
	glTranslatef(-1, 0, 0);
	building1(n, m, tallHeights, colors);  //1 

	// -2,1
	glTranslatef(-1, 0, 0);
	building1(n, m, shortHeights, colors);  //2

	// -2,0
	glTranslatef(0, 0, -1);
	bigBuilding(n, m);

	// -1,0
	glTranslatef(1, 0, 0); 
	parkingLot(n, m);

	//cars
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(-0.3, 0, -0.2);
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();

	glColor3f(0.90, 0.90, 0.95);
	glPushMatrix();
	glTranslatef(-0.3, 0, 0);
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();

	glColor3f(0, 0.3, 0.3);
	glPushMatrix();
	glTranslatef(0.3, 0, 0);
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();

	glColor3f(0.1, 0.1, 0.2);
	glPushMatrix();
	glTranslatef(0.1, 0, 0);
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();

	glColor3f(0.14, 0.14, 0.2);
	glPushMatrix();
	glTranslatef(0.3, 0, 0.2);
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();

	// -1,-1
	glTranslatef(0, 0, -1);
	park(n, m);

	// 0,-1
	glTranslatef(1, 0, 0);
	building1(n, m, tallHeights, colors);

	// 1,-1
	glTranslatef(1, 0, 0);
	building1(n, m, tallHeights, colors);

	// 2,-1
	glTranslatef(1, 0, 0);
	building(n, m);

	// 2,-2
	glTranslatef(0, 0, -1);
	building1(n, m, shortHeights, colors);

	// 1,-2
	glTranslatef(-1, 0, 0);
	building1(n, m, tallHeights, colors);

	// 0,-2
	glTranslatef(-1, 0, 0);
	garden(n, m);

	//moving car
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(carPos.x, carPos.y, carPos.z);
	glRotatef(carRotation.x, 1, 0, 0); 
	glRotatef(carRotation.y, 0, 1, 0); 
	glRotatef(carRotation.z, 0, 0, 1); 
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();

	// -1,-2
	glTranslatef(-1, 0, 0);
	building(n, m);

	// -2,-2
	glTranslatef(-1, 0, 0);
	building1(n, m, shortHeights, colors); 

	// -2,-1
	glTranslatef(0, 0, 1);
	garden(n, m);

	//moving car
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(carPos.x, carPos.y, carPos.z);
	glRotatef(carRotation.x, 1, 0, 0);
	glRotatef(carRotation.y, 0, 1, 0);
	glRotatef(carRotation.z, 0, 0, 1);
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();

	// -2,2
	glTranslatef(0, 0, 3); 
	building2(n, m, shortHeights, colors); 

	// -1,2
	glTranslatef(1, 0, 0);
	building1(n, m, shortHeights, colors);

	// 0,2
	glTranslatef(1, 0, 0);
	building1(n, m, midHeights, colors);

	// 1,2
	glTranslatef(1, 0, 0);
	building1(n, m, midHeights, colors);

	// 2,2 
	glTranslatef(1, 0, 0);
	garden(n, m);

	glPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {

	case 'g':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	//night mode
	case 'n':
		ambientLightEnabled = !ambientLightEnabled;
		if (ambientLightEnabled) {
			ambientLight.enable(); 
			ofBackground(ofColor(211, 240, 246));
		}
		else {
			ambientLight.disable(); 
			ofBackground(ofColor(37, 56, 64)); 
		}
		break;
	//move camera
	case OF_KEY_UP:
		lensAngle--;
		cout << endl << lensAngle;
		break;
	case OF_KEY_DOWN:
		lensAngle++;
		cout << endl << lensAngle;
		break;
	//change vision
	case ' ':
		view++;
		if (view > 4) {
			view = 0;
		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	setup(); 
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
