#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto flag = true;
	for (int x = -300; x <= 300; x += 200) {

		for (int y = -300; y <= 300; y += 200) {

			ofMesh mesh;
			auto param = 50;
			auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

			int angle_x = ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.003), 0, 1, -360, 360);
			auto rotation_x = glm::rotate(glm::mat4(), angle_x * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));

			int angle_y = ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.003), 0, 1, -360, 360);
			auto rotation_y = glm::rotate(glm::mat4(), angle_y * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));

			int angle_z = ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * 0.003), 0, 1, -360, 360);
			auto rotation_z = glm::rotate(glm::mat4(), angle_y * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec4(param, param, param, 0) * rotation_z * rotation_y * rotation_z);
			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec4(param, -param, -param, 0) * rotation_z * rotation_y * rotation_z);
			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec4(-param, param, -param, 0) * rotation_z * rotation_y * rotation_z);
			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec4(-param, -param, param, 0) * rotation_z * rotation_y * rotation_z);

			mesh.addIndex(0); mesh.addIndex(1); mesh.addIndex(2);
			mesh.addIndex(0); mesh.addIndex(1); mesh.addIndex(3);
			mesh.addIndex(0); mesh.addIndex(2); mesh.addIndex(3);
			mesh.addIndex(1); mesh.addIndex(2); mesh.addIndex(3);

			if (flag = !flag) {
			
				ofSetColor(239);
				mesh.drawFaces();
			}

			ofSetColor(39);
			mesh.drawWireframe();

			for (auto& vertex : mesh.getVertices()) {

				ofDrawSphere(vertex, 5);

			}
		}

		flag = !flag;
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}