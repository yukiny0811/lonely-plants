
//
// Lonely Plants
// 2021 Yuki Kuwashima
//
// 流体アニメーションはJos StamさんのStable Fluidsのアルゴリズムを使っています。
// 植物の成長シミュレーションのアルゴリズムはL-Systemを使っています。
//


#pragma once

#include "ofMain.h"
#include "Fluid.hpp"

class ofApp : public ofBaseApp{
    
private:
    
    ofColor backColor;
    
    bool gravityOn = false;
    
    int timeCount = 0;
    
    Fluid fluid;
    string V[8];
    string W = "f";
    string Pkey[1];
    string PValue[1];
    
    bool showBone = false;

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
		
};
