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

	ofDisableArbTex();

	ofBackground(200, 200, 200);

	glShadeModel(GL_SMOOTH);




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
	carDepth = 0.03;
	carHeight = 0.1;  
	 
	carPos.x = -0.4; 
	carPos.y = 0.01; 
	carPos.z = -0.4;
	 
	carRotation.set(0, 0, 0);  
	carState = 0; 

	//sliding door parameters 
	doorWidth = 0.05; 
	doorDepth = 0.104; 
	doorHeight = 0.05;
	 
	doorRightPos.x = -3.9;
	doorRightPos.y = 0.65;
	doorRightPos.z = -1.4;

	doorLeftPos.x = -3.9;
	doorLeftPos.y = 0.65;
	doorLeftPos.z = 1.4;

	//aux for sliding door
	count = 0;
	open = 0;

	//7x7 quarters
	n = 7;
	m = 7; 


	ambientOn = true;
	dirOn = false;
	pointOn = false;
	spotOn = false;



	ambientDirOn = true;
	difuseDirOn = true;
	specularDirOn = true;
	
	ambientPointOn = true;
	difusePointOn = true;
	specularPointOn = true;

	ambientSpotOn = true;
	difuseSpotOn = true;
	specularSpotOn = true;




	if (img1.load("building1.jpg")) {
		cout << "Image loaded successfully." << endl;
	}
	else {
		cout << "Failed to load image." << endl;
	}   

	if (img2.load("building2.jpg")) {
		cout << "Image loaded successfully." << endl;
	}
	else {
		cout << "Failed to load image." << endl;
	}
	if (img3.load("building3.jpg")) {
		cout << "Image loaded successfully." << endl;
	}
	else {
		cout << "Failed to load image." << endl;
	}
	if (img4.load("building4.jpg")) {
		cout << "Image loaded successfully." << endl;
	}
	else {
		cout << "Failed to load image." << endl;
	}
	if (img5.load("building5.jpg")) {
		cout << "Image loaded successfully." << endl;
	}
	else {
		cout << "Failed to load image." << endl;
	}

	if (img6.load("building6.jpg")) {
		cout << "Image loaded successfully." << endl;
	}
	else {
		cout << "Failed to load image." << endl;
	}

	if (img7.load("building7.jpg")) {
		cout << "Image loaded successfully." << endl;
	}
	else {
		cout << "Failed to load image." << endl;
	}



	if (pav1.load("paving1.jpg")) {
		cout << "Image loaded successfully." << endl;
	}
	else {
		cout << "Failed to load image." << endl;
	}

	if (parking1.load("parkinglot.jpg")) {
		cout << "Image loaded successfully." << endl;
	}
	else {
		cout << "Failed to load image." << endl;
	}



	for (int i = 0; i < 10; i++) {
		freqs[i] = 0.25 + 0.25 * i * 5;
		amps[i] = 1. / (i * 0.25 + 1);
		cout << endl << amps[i];
	}


	phaseX = 0.;
	phaseY = 0.;

	px = 128;
	py = 128;
	sky.allocate(px, py, OF_IMAGE_COLOR);
	skyPixels = new unsigned char[px * py * 3];


	nightSky.allocate(gw(), gh(), GL_RGBA);


	nightSky.begin();//inicia o desenho no frame buffer
	ofClear(0, 0, 0, 255);//limpa
	nightSky.end();//finaliza o desenho no buffer
	nightSkyImg.allocate(gw(), gh(), OF_IMAGE_COLOR_ALPHA);




	//materials


	customMatCoef = 1;



	//concrete
	concreteAmb[0] = 0.26;//R
	concreteAmb[1] = 0.26;//G
	concreteAmb[2] = 0.26;//B
	concreteAmb[3] = 1.;

	concreteDif[0] = 0.26;//R
	concreteDif[1] = 0.26;//G
	concreteDif[2] = 0.26;//B
	concreteDif[3] = 1.;

	concreteSpec[0] = 0.1;//R
	concreteSpec[1] = 0.1;//G
	concreteSpec[2] = 0.1;//B
	concreteSpec[3] = 1.;

	GLfloat concreteCoef = 1;


	//grass
	grassAmb[0] = 0.46;//R
	grassAmb[1] = 0.58;//G
	grassAmb[2] = 0.39;//B
	grassAmb[3] = 1.;

	grassDif[0] = 0.46;//R
	grassDif[1] = 0.58;//G
	grassDif[2] = 0.39;//B
	grassDif[3] = 1.;

	grassSpec[0] = 0.46;//R
	grassSpec[1] = 0.58;//G
	grassSpec[2] = 0.39;//B
	grassSpec[3] = 1.;

	GLfloat grassCoef = 1;


	//sand
	sandAmb[0] = 0.827;//R
	sandAmb[1] = 0.827;//G
	sandAmb[2] = 0.678;//B
	sandAmb[3] = 1.0;

	sandDif[0] = 0.827;//R
	sandDif[1] = 0.827;//G
	sandDif[2] = 0.678;//B
	sandDif[3] = 1.0;

	sandSpec[0] = 0.827;//R
	sandSpec[1] = 0.827;//G
	sandSpec[2] = 0.678;//B
	sandSpec[3] = 1.0;

	GLfloat sandCoef = 1;

	//water
	waterAmb[0] = 0.57; //R
	waterAmb[1] = 0.69; //G
	waterAmb[2] = 0.74; //B
	waterAmb[3] = 1.0;

	waterDif[0] = 0.57; //R
	waterDif[1] = 0.69; //G
	waterDif[2] = 0.74; //B
	waterDif[3] = 1.0;

	waterSpec[0] = 0.67;//R
	waterSpec[1] = 0.70;//G
	waterSpec[2] = 0.88;//B
	waterSpec[3] = 1.0;

	GLfloat waterCoef = 50;

	//building
	buildingAmb[0] = 1;//R
	buildingAmb[1] = 1;//G
	buildingAmb[2] = 1;//B
	buildingAmb[3] = 1;

	buildingDif[0] = 1;//R
	buildingDif[1] = 1;//G
	buildingDif[2] = 1;//B
	buildingDif[3] = 1;

	buildingSpec[0] = 1;//R
	buildingSpec[1] = 1;//G
	buildingSpec[2] = 1;//B
	buildingSpec[3] = 1;;	
	
	GLfloat buildingCoef = 1;

	//glass
	glassAmb[0] = 0.82;//R
	glassAmb[1] = 0.9;//G
	glassAmb[2] = 1;//B
	glassAmb[3] = 1;

	glassDif[0] = 0.82;//R
	glassDif[1] = 0.9;//G
	glassDif[2] = 1;//B
	glassDif[3] = 1;

	glassSpec[0] = 1;//R
	glassSpec[1] = 1;//G
	glassSpec[2] = 1;//B
	glassSpec[3] = 1;;

	GLfloat glassCoef = 100;

	//car1
	car1Amb[0] = 0.2;//R
	car1Amb[1] = 0.2;//G
	car1Amb[2] = 0.2;//B
	car1Amb[3] = 1;

	car1Dif[0] = 0.2;//R
	car1Dif[1] = 0.2;//G
	car1Dif[2] = 0.2;//B
	car1Dif[3] = 1;

	car1Spec[0] = 1;//R
	car1Spec[1] = 1;//G
	car1Spec[2] = 1;//B
	car1Spec[3] = 1;

	GLfloat car1Coef = 100;

	//car2
	car2Amb[0] = 0.70;//R
	car2Amb[1] = 0.76;//G
	car2Amb[2] = 0.88;//B
	car2Amb[3] = 1;

	car2Dif[0] = 0.70;//R
	car2Dif[1] = 0.76;//G
	car2Dif[2] = 0.88;//B
	car2Dif[3] = 1;

	car2Spec[0] = 1;//R
	car2Spec[1] = 1;//G
	car2Spec[2] = 1;//B
	car2Spec[3] = 1;

	GLfloat car2Coef = 100;

}

//-------------------------------------------------------------- 
void ofApp::update() {  


	if (view == 4) {
		camPos.x = W * cos(orbitAngle);
		camPos.z = W * sin(orbitAngle);
		camPos.y = H; 
		orbitAngle += PI*0.005;
	}

	//forward
	if (carState == 0) { 
		pointPos1[0] = carPos.x * 768 - 10;
		pointPos2[0] = carPos.x * 768 + 10;
		carPos.z += vel; 
		pointPos1[2] = carPos.z * 768 - 1500;
		pointPos2[2] = carPos.z * 768 - 1500;
		if (carPos.z >= 3.5) {
			carState = 1;
			carRotation.y = 90;  
		}
	}
	//right
	else if (carState == 1) {
		pointPos1[2] = carPos.z * 768 - 1540 - 10;
		pointPos2[2] = carPos.z * 768 - 1540 + 10;
		carPos.x += vel;  
		pointPos1[0] = carPos.x * 768 + 37;
		pointPos2[0] = carPos.x * 768 + 37;
		if (carPos.x >= 0.4) {
			carState = 2;  
			carRotation.y = 180; 
		}
	}
	//backward
	else if (carState == 2) {
		pointPos1[0] = carPos.x * 768 - 10;
		pointPos2[0] = carPos.x * 768 + 10;
		carPos.z -= vel;
		pointPos1[2] = carPos.z * 768 - 1575;
		pointPos2[2] = carPos.z * 768 - 1575;
		if (carPos.z <= -0.4) {
			carState = 3; 
			carRotation.y = 270;  
		}
	}
	//left
	else if (carState == 3) {
		pointPos1[2] = carPos.z * 768 - 1575 - 10;
		pointPos2[2] = carPos.z * 768 - 1575 + 10;
		carPos.x -= vel;
		pointPos1[0] = carPos.x * 768 - 25;
		pointPos2[0] = carPos.x * 768 - 25;
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glShadeModel(GL_SMOOTH);

	//prespective camera
	glViewport(0, 0, gw(), gh());
	 

	//#################################################
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE); 
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer);

	//################################################# AMBIENT LIGHT

	if (ambientOn) {
		ambientLight[0] = 0.6;//R
		ambientLight[1] = 0.6;//G
		ambientLight[2] = 0.6;//B
		ambientLight[3] = 1;//useless


		//skybox day
		//#################################################
		glEnable(GL_COLOR_MATERIAL);

		skyPixels = sky.getPixels().getData();

		ofColor A(137, 207, 240);
		ofColor B(255, 255, 255);

		for (int j = 0; j < py; j++) {
			for (int i = 0; i < px; i++) {
				int index = 3 * (j * px + i);
				float noise = getMultiNoise(0.01 * (i)+phaseX, 0.01 * (j)+phaseY, freqs, amps, 10);
				ofColor auxColor = A.getLerped(B, noise);
				skyPixels[index] = auxColor.r;
				skyPixels[index + 1] = auxColor.g;
				skyPixels[index + 2] = auxColor.b;
			}
		}
		sky.setFromPixels(skyPixels, px, py, OF_IMAGE_COLOR);
		sky.update();

		glEnable(GL_TEXTURE);
		sky.bind();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glColor3f(1, 1, 1);
		glPushMatrix();
		glRotatef(0, 1, 0, 0);
		glRotatef(0, 0, 1, 0);
		glRotatef(0, 0, 0, 1);
		glScalef(5 * gw(), 5 * gw(), 5 * gw());
		sphereSkyBox(64);
		glPopMatrix();

		sky.unbind();
		glDisable(GL_TEXTURE);

		ofFill();

		rx += 0.01;
		ry += 0.2;
		rz += 0.015;
		glDisable(GL_COLOR_MATERIAL);

		//#################################################

	}
	else {
		ambientLight[0] = 0.;
		ambientLight[1] = 0.;
		ambientLight[2] = 0.;
		ambientLight[3] = 1;


	//skybox night
	//#################################################
		glEnable(GL_COLOR_MATERIAL);

		skyPixels = sky.getPixels().getData();

		phaseX += 0.005 * cos(dirVecTheta * 0.001);
		phaseY -= 0.006 * cos(dirVecTheta * 0.0001);

		ofColor A(255, 225, 102);
		ofColor B(255, 255, 255);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		nightSky.begin();

		glColor4f(0, 0, 0, 0.05);
		ofDrawRectangle(0, 0, gw(), gh());

		glPushMatrix();
		glTranslatef(0, 0, 1.);
		float x = ofRandom(0, gw());
		float y = ofRandom(0, gh());

		ofSetColor(255, 255, 255, 255);
		ofDrawCircle(x, y, 1);
		ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255), ofRandom(20, 255));
		ofRect(ofRandom(0, gw() * 0.5), ofRandom(0, gh()), 2, 2);

		glPopMatrix();
		nightSky.end();
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		ofDisableAlphaBlending();

		nightSky.readToPixels(nightSkyImg.getPixelsRef());
		nightSkyImg.update();

		glEnable(GL_TEXTURE);
		nightSkyImg.bind();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glColor3f(1, 1, 1);
		glPushMatrix();
		glRotatef(0, 1, 0, 0);
		glRotatef(0, 0, 1, 0);
		glRotatef(0, 0, 0, 1);
		glScalef(5 * gw(), 5 * gw(), 5 * gw());
		sphereSkyBox(64);
		glPopMatrix();

		nightSkyImg.unbind();
		glDisable(GL_TEXTURE);

		ofFill();

		rx += 0.01;
		ry += 0.2;
		rz += 0.015;
		glDisable(GL_COLOR_MATERIAL);

	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	//#################################################


	//################################################# DIRECIONAL LIGHT

	//direction
	dirVec[0] = 100;//x
	dirVec[1] = 100;//y
	dirVec[2] = 100;//z
	dirVec[3] = 0;//vector


	if (ambientDirOn) {
		dirAmb[0] = 0.2;//R
		dirAmb[1] = 0.2;//G
		dirAmb[2] = 0.15;//B
		dirAmb[3] = 1.;//constante
	}
	else {
		dirAmb[0] = 0;//R
		dirAmb[1] = 0;//G
		dirAmb[2] = 0;//B
		dirAmb[3] = 1.;//constante
	}


	if (difuseDirOn) {
		dirDif[0] = 0.1;//R
		dirDif[1] = 0.1;//G
		dirDif[2] = 0.1;//B
		dirDif[3] = 1.;//constante
	}
	else {
		dirDif[0] = 0;//R
		dirDif[1] = 0;//G
		dirDif[2] = 0;//B
		dirDif[3] = 1.;//constante
	}

	if (specularDirOn) {
		dirSpec[0] = 0.1;//R
		dirSpec[1] = 0.1;//G
		dirSpec[2] = 0.1;//B
		dirSpec[3] = 1.;//constante
	}
	else {
		dirSpec[0] = 0;//R
		dirSpec[1] = 0;//G
		dirSpec[2] = 0;//B
		dirSpec[3] = 1.;//constante
	}


	glLightfv(GL_LIGHT0, GL_POSITION, dirVec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, dirAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dirDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, dirSpec);

	if (dirOn) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}


	//################################################# POINT LIGHT 

	//position
	pointPos1[1] = 6;//y
	pointPos1[3] = 1;//

	pointPos2[1] = 6;//y
	pointPos2[3] = 1;//


	if (ambientPointOn) {

		pointAmb[0] = 0.1;//R
		pointAmb[1] = 0.1;//G
		pointAmb[2] = 0.1;//B
		pointAmb[3] = 1.;//constante
	}
	else {

		pointAmb[0] = 0;//R
		pointAmb[1] = 0;//G
		pointAmb[2] = 0;//B
		pointAmb[3] = 1.;//constante
	}

	if (difusePointOn) {
		pointDif[0] = 1;//R 
		pointDif[1] = 1;//G
		pointDif[2] = 1;//B 
		pointDif[3] = 1.;//constante
	}
	else {
		pointDif[0] = 0;//R 
		pointDif[1] = 0;//G
		pointDif[2] = 0;//B 
		pointDif[3] = 1.;//constante
	}

	if (specularPointOn) {
		pointSpec[0] = 0.9;//R
		pointSpec[1] = 0.9;//G
		pointSpec[2] = 0.9;//B
		pointSpec[3] = 1.;//constante
	}
	else {
		pointSpec[0] = 0;//R
		pointSpec[1] = 0;//G
		pointSpec[2] = 0;//B
		pointSpec[3] = 1.;//constante
	}


	glLightfv(GL_LIGHT1, GL_POSITION, pointPos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, pointAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, pointDif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpec);

	glLightfv(GL_LIGHT2, GL_POSITION, pointPos2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, pointAmb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, pointDif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, pointSpec);


	//atenuação
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.9);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0001);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.00001);

	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.9);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0001);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.00001);

	if (pointOn) {
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
	}
	else {
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);

	}


	//################################################# SPOT LIGHT

	//position
	spotPos[0] = -208 ;
	spotPos[1] = gh() * 0.2;//y
	spotPos[2] = -190;
	spotPos[3] = 1;

	//direction
	spotDir[0] = -220;  
	spotDir[1] = 0;
	spotDir[2] = -190;
	spotDir[3] = 0;

	if (ambientSpotOn) {
		spotAmb[0] = 0.05;//R
		spotAmb[1] = 0.05;//G
		spotAmb[2] = 0.05;//B
		spotAmb[3] = 1;//constante
	}
	else {
		spotAmb[0] = 0;//R
		spotAmb[1] = 0;//G
		spotAmb[2] = 0;//B
		spotAmb[3] = 1;//constante
	}

	if (difuseSpotOn) {
		spotDif[0] = 0.8;//R
		spotDif[1] = 0.8;//G
		spotDif[2] = 0.8;//B
		spotDif[3] = 1.;//constante
	}
	else {
		spotDif[0] = 0;//R
		spotDif[1] = 0;//G
		spotDif[2] = 0;//B
		spotDif[3] = 1.;//constante
	}

	if (specularSpotOn) {
		spotSpecular[0] = 0.3;//R
		spotSpecular[1] = 0.3;//G
		spotSpecular[2] = 0.3;//B
		spotSpecular[3] = 1;//constante
	}
	else {
		spotSpecular[0] = 0;//R
		spotSpecular[1] = 0;//G
		spotSpecular[2] = 0;//B
		spotSpecular[3] = 1;//constante

	}

	//concentracao
	spotExponent = 10;//0 - 128

	////angulo
	spotCutoff = 180;//0 - 180

	glLightfv(GL_LIGHT3, GL_POSITION, spotPos);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDir);

	glLightfv(GL_LIGHT3, GL_AMBIENT, spotAmb);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, spotDif);
	glLightfv(GL_LIGHT3, GL_SPECULAR, spotSpecular);

	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spotExponent); 
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spotCutoff);

	//atenuação
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0001);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.00001);
	if (spotOn) {
		glEnable(GL_LIGHT3);
	}
	else {
		glDisable(GL_LIGHT3);
	}

	//#################################################

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
	 
	//#################################################

	glDisable(GL_LIGHTING);

	//#################################################

	if (pointOn) {  
		glColor3f(1, 1, 1);

		glPushMatrix(); 
		glTranslatef(pointPos1[0], pointPos1[1], pointPos1[2]);    
		glScalef(0.7, 0.7, 0.7);  
		ofDrawSphere(10.);  
		glPopMatrix();

		glPushMatrix();
		glTranslatef(pointPos2[0], pointPos2[1], pointPos2[2]);
		glScalef(0.7, 0.7, 0.7);
		ofDrawSphere(10.);
		glPopMatrix();

	}
	if (spotOn) {
		glColor3f(1, 1, 1); 
		glPushMatrix();
		glTranslatef(spotPos[0], spotPos[1], spotPos[2]); 
		glScalef(1.3, 0.7, 0.7); 
		ofDrawSphere(10.);
		glPopMatrix(); 
	}

	glPopMatrix();

}
 
void ofApp::drawGeometry() {

	 
	//road field 
	glPushMatrix();
	glScalef(gh() * 6.1, gh() * 6.1, gh() * 6.1);	

	glMaterialfv(GL_FRONT, GL_AMBIENT, concreteAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, concreteDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, concreteSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, concreteCoef);

	base();
	glPopMatrix();

	//grass field 
	glTranslatef(0, -0.05, 0);
	glPushMatrix(); 
	glScalef(gh() * 6.5, gh() * 6.5, gh() * 6.5); 

	glMaterialfv(GL_FRONT, GL_AMBIENT, grassAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grassDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grassSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, grassCoef);
	base();
	glPopMatrix();   

	//sand
	glTranslatef(0, -0.05, 0);
	glPushMatrix();
	glScalef(gh() * 7, gh() * 7, gh() * 7);

	glMaterialfv(GL_FRONT, GL_AMBIENT, sandAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sandDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sandSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, sandCoef);
	base();
	glPopMatrix(); 

	// sea
	glTranslatef(0, -0.05, 0);
	glPushMatrix(); 
	glScalef(gh() * 30, gh() * 30, gh() * 30); 

	glMaterialfv(GL_FRONT, GL_AMBIENT, waterAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, waterDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, waterSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, waterCoef);
	base();
	glPopMatrix(); 


	glPushMatrix();
	glTranslatef(0, 0.15, 0);

	// 0,0
	glScalef(gh() * 1, gh() * 1, gh() * 1); 
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, buildingAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, buildingDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, buildingSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, buildingCoef);

	bigBuilding(img1, pav1); 
	glPopMatrix();

	lamp();

	glMaterialfv(GL_FRONT, GL_AMBIENT, glassAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glassDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, glassSpec); 
	glMaterialf(GL_FRONT, GL_SHININESS, glassCoef);

	//right sliding door
	glPushMatrix();

	glScalef(doorWidth, doorDepth, doorHeight); 
	glTranslatef(doorRightPos.x, doorRightPos.y, doorRightPos.z);

	figure();
	glPopMatrix();

	//left sliding door
	glPushMatrix();

	glScalef(doorWidth, doorDepth, doorHeight);
	glTranslatef(doorLeftPos.x, doorLeftPos.y, doorLeftPos.z);

	figure();
	glPopMatrix();
	 

	//door
	glPushMatrix();
	glScalef(doorWidth, doorDepth, 0.1);
	glTranslatef(-3.8, 0.64, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, concreteAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, concreteDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, concreteSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, concreteCoef);
	figure();
	glPopMatrix(); 

	glMaterialfv(GL_FRONT, GL_AMBIENT, buildingAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, buildingDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, buildingSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, buildingCoef);

	// 1,0
	glTranslatef(1, 0, 0);
	building1(img4, pav1);  

	// 2,0
	glTranslatef(1, 0, 0);
	building2(img1, pav1);   
	  
	// 2,1
	glTranslatef(0, 0, 1);
	bigBuilding(img1, pav1);

	// 1,1
	glTranslatef(-1, 0, 0);
	building(img2, img3, pav1);
	
	// 0,1
	glTranslatef(-1, 0, 0);
	bigBuilding(img1, pav1);

	// -1,1
	glTranslatef(-1, 0, 0);
	building2(img6, pav1);  

	// -2,1
	glTranslatef(-1, 0, 0);
	building2(img4, pav1);   

	// -2,0
	glTranslatef(0, 0, -1);
	bigBuilding(img1, pav1);

	// -1,0 
	glTranslatef(1, 0, 0); 
	parkingLot(); 
	 
	//cars
	glMaterialfv(GL_FRONT, GL_AMBIENT, car2Amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, car2Dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, car2Spec);
	glMaterialf(GL_FRONT, GL_SHININESS, car2Coef);

	glPushMatrix();
	glTranslatef(-0.13, 0.01, -0.311);
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0); 
	glTranslatef(-0.2 , 0.01, -0.246);
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, 0.01, -0.32);
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_AMBIENT, car1Amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, car1Dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, car1Spec);
	glMaterialf(GL_FRONT, GL_SHININESS, car1Coef);

	glPushMatrix();
	glTranslatef(0.09, 0.01, -0.33);	
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-0.01, 0.01, 0.25);
	glScalef(carWidth, carDepth, carHeight);
	figure();
	glPopMatrix();
	 
	// -1,-1

	glTranslatef(0, 0, -1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, grassAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grassDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grassSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, grassCoef);
	park();

	glMaterialfv(GL_FRONT, GL_AMBIENT, waterAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, waterDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, waterSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, waterCoef);
	pond();


	 
	glMaterialfv(GL_FRONT, GL_AMBIENT, buildingAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, buildingDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, buildingSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, buildingCoef);

	// 0,-1
	glTranslatef(1, 0, 0);
	building1(img5, pav1);
	 
	// 1,-1
	glTranslatef(1, 0, 0);
	building2(img6, pav1);

	// 2,-1
	glTranslatef(1, 0, 0);
	building(img2, img3, pav1);

	// 2,-2
	glTranslatef(0, 0, -1);
	building1(img4, pav1); 

	// 1,-2
	glTranslatef(-1, 0, 0);
	building2(img7, pav1);

	// 0,-2
	glTranslatef(-1, 0, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, grassAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grassDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grassSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, grassCoef);

	park();


	glMaterialfv(GL_FRONT, GL_AMBIENT, buildingAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, buildingDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, buildingSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, buildingCoef);

	//moving car
	glPushMatrix();
	glTranslatef(carPos.x, carPos.y, carPos.z);
	glRotatef(carRotation.x, 1, 0, 0); 
	glRotatef(carRotation.y, 0, 1, 0); 
	glRotatef(carRotation.z, 0, 0, 1); 

	glScalef(carWidth, carDepth, carHeight);

	glMaterialfv(GL_FRONT, GL_AMBIENT, car1Amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, car1Dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, car1Spec);
	glMaterialf(GL_FRONT, GL_SHININESS, car1Coef);

	figure();
	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_AMBIENT, buildingAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, buildingDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, buildingSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, buildingCoef);

	// -1,-2
	glTranslatef(-1, 0, 0);
	building(img2, img3, pav1);

	// -2,-2
	glTranslatef(-1, 0, 0);
	building1(img1, pav1);

	// -2,-1
	glTranslatef(0, 0, 1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, grassAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grassDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grassSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, grassCoef);

	park();


	//moving car
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(carPos.x, carPos.y, carPos.z);
	glRotatef(carRotation.x, 1, 0, 0);
	glRotatef(carRotation.y, 0, 1, 0);
	glRotatef(carRotation.z, 0, 0, 1);
	glScalef(carWidth, carDepth, carHeight);


	glMaterialfv(GL_FRONT, GL_AMBIENT, car1Amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, car1Dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, car1Spec);
	glMaterialf(GL_FRONT, GL_SHININESS, car1Coef);

	figure();
	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_AMBIENT, buildingAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, buildingDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, buildingSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, buildingCoef);

	// -2,2
	glTranslatef(0, 0, 3); 
	building2(img5, pav1);

	// -1,2  
	glTranslatef(1, 0, 0);
	building1(img4, pav1);

	// 0,2 
	glTranslatef(1, 0, 0); 
	building2(img3, pav1);

	// 1,2
	glTranslatef(1, 0, 0);
	building1(img6, pav1);

	// 2,2 
	glTranslatef(1, 0, 0);
	park();
	 

	glPopMatrix();

	 

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {


	case '1':
		ambientDirOn = !ambientDirOn;
		break;

	case '2':
		difuseDirOn = !difuseDirOn;
		break;

	case '3':
		specularDirOn = !specularDirOn;

	case '4':
		ambientPointOn = !ambientPointOn;
		break;

	case '5':
		difusePointOn = !difusePointOn;
		break;

	case '6':
		specularPointOn = !specularPointOn;
		break;

	case '7':
		ambientSpotOn = !ambientSpotOn;
		break;

	case '8':
		difuseSpotOn = !difuseSpotOn;
		break;

	case '9':
		specularSpotOn = !specularSpotOn;
		break;

	case 'g':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case 'a':
		ambientOn = !ambientOn;

		break;
	case 'd':
		dirOn = !dirOn;
		break;
	case 'p':
		pointOn = !pointOn;
		break;
	case 's':
		spotOn = !spotOn;
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
