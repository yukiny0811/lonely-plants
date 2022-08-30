

#include "ofApp.h"
#include <regex>
#include <iostream>

void ofApp::setup(){
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofBackground(0);
    
    fluid = Fluid();
    fluid.setup();
    
    V[0] = "f";
    V[1] = "+";
    V[2] = "-";
    V[3] = "[";
    V[4] = "]";
    V[5] = "f";
    V[6] = "f";
    V[7] = "f";
    
    Pkey[0] = "f";
    
    PValue[0] = "f[-ff]f[++f]f";
    
    for (int i = 0; i < 3; i++) {
        for (int i = 0; i < 1; i++) {
            W = regex_replace(W, regex(Pkey[i]), PValue[i]);
            std::cout << W << std::endl;
        }
    }
    
    backColor = ofColor(0, 0, 0);
    
    fluid.mainDensityColor = ofColor(155, 155, 85);
    fluid.subDensityColor = ofColor(255, 80, 120);
    backColor = ofColor(120, 120, 100);
    
}

void ofApp::update() {
    fluid.update();
    
    float inputSize = 2;
    
    int x = 50;
    int y = 98;
    
    for (int ty = -inputSize; ty < inputSize; ty++) {
        for (int tx = -inputSize; tx < inputSize; tx++) {
            if (!(x + tx > 100 || x + tx < 0)) {
                if (!(y + ty > 100 || y + ty < 0)) {
                    fluid.density[fluid.getPos(x + tx, y + ty)] = 1;
                }
            }
        }
    }
    
    timeCount += 1;
    
    if (timeCount > 600) {
        fluid.velocityDiffusion = 0.001;
        fluid.densityDiffusion = 0.001;
        gravityOn = true;
        fluid.lock = false;
        backColor = ofColor(0, 0, 0);
    }
    
    if (timeCount > 900) {
        
        fluid.velocityDiffusion = 0.5;
        fluid.densityDiffusion = 0.0000000000000000000001;
        gravityOn = false;
        fluid.lock = true;
        
        while (1) {
            bool canGenerate = false;
            PValue[0] = "";
            W = "f";
            for (int i = 0; i < 15; i++) {
                PValue[0] += V[int(floor(ofRandom(6.999999)))];
            }
            
            std:cout << PValue[0] << std::endl;
            
            int pushCounter = 0;
            for (int i = 0; i < PValue[0].size(); i++) {
                if (PValue[0][i] == '[') {
                    pushCounter += 1;
                }
                if (PValue[0][i] == ']') {
                    pushCounter -= 1;
                }
                if (pushCounter < 0) {
                    canGenerate = false;
                    break;
                }
            }
            if (pushCounter == 0) {
                canGenerate = true;
            }
            if (canGenerate) {
                PValue[0] = "f" + PValue[0];
                for (int i = 0; i < 3; i++) {
                    for (int i = 0; i < 1; i++) {
                        W = regex_replace(W, regex(Pkey[i]), PValue[i]);
                        std::cout << W << std::endl;
                    }
                }
                break;
            }
        }
        
        fluid.mainDensityColor = ofColor(80 + ofRandom(80), 80 + ofRandom(80), 80 + ofRandom(80));
        fluid.subDensityColor = ofColor(ofRandom(200), ofRandom(200), ofRandom(200));
        
        backColor = ofColor(80 + ofRandom(40), 80 + ofRandom(40), 80 + ofRandom(40));
        
        
        timeCount = 0;
    }
    
}

void ofApp::draw(){
    ofSetColor(backColor);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    fluid.drawDensity();
    
    if (gravityOn) {
        for (int i = 1; i < 101; i++) {
            for (int j = 1; j < 101; j++) {
                if (ofRandom(100) < 20) {
                    fluid.velocity[fluid.getPos(i, j)] = ofVec2f(ofRandom(-0.5, 0.5), 1);
                }
            }
        }
        fluid.drawVelocity();
    } else {
        ofMatrix4x4 master = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);

        ofMatrix4x4 m;

        ofPushMatrix();

        ofSetColor(255, 0, 0);
        ofTranslate(500, 1000);
        ofSetLineWidth(5);
        for (int i = 0; i < W.size(); i++) {
            if(W[i] == 'f') {

                m = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);

                ofPoint p(0, 0);
                ofMatrix4x4 translatationMatrix;

                float* fm = m.getPtr();
                float* fmaster = master.getPtr();

                for (int i = 0; i < 16; i++) {
                    fm[i] -= fmaster[i];
                }
                translatationMatrix.set(fm);
                translatationMatrix._mat[3][3] = 1;
                p = p * translatationMatrix;
                
                if (showBone) {
                    ofDrawLine(0, 0, 0, -30);
                }

                ofTranslate(0, -30);

                ofPoint p2(0, 0);

                m = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);

                fm = m.getPtr();

                for (int i = 0; i < 16; i++) {
                    fm[i] -= fmaster[i];
                }
                translatationMatrix.set(fm);
                translatationMatrix._mat[3][3] = 1;
                p2 = p2 * translatationMatrix;
                
                if (p.x > 10 && p.x < 990 && p.y > 10 && p.y < 990 && p2.x > 10 && p2.x < 990 && p2.y > 10 && p2.y < 990) {
                    fluid.velocity[fluid.getPos(int(p.x / 10), int(p.y / 10))] = ofVec2f((p2.x - p.x) / 3, (p2.y - p.y) / 3);
                }
                
            } else if (W[i] == '[') {
                ofPushMatrix();
            } else if (W[i] == ']') {
                ofPopMatrix();
            } else if (W[i] == '-') {
                ofRotateDeg(-30);
            } else if (W[i] == '+') {
                ofRotateDeg(30);
            }
        }
        ofPopMatrix();
    }

    ofSetColor(150, 150, 150);
    ofDrawRectangle(0, 950, 1000, 50);
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("LONELY PLANTS", 30, 30);
    ofDrawBitmapString("PRESS B TO TOGGLE BONES", 30, 50);
    
}

void ofApp::keyPressed(int key){
    if (key == 'b') {
        showBone = !showBone;
    }
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){
    
}

void ofApp::mouseReleased(int x, int y, int button){
    fluid.isMousePressed = false;
}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}
 
void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
