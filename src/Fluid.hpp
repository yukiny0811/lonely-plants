

#ifndef Fluid_hpp
#define Fluid_hpp

#include <stdio.h>

#endif

#include <ofMain.h>

#define NUM 102*102

class Fluid {
private:
    
    float dt = 0.01;
    
    float cellSize = 10;
    
    float inputSize = 5.0;
    
    void addSourceFloat(float* current, float* prev, float dt);
    void addSourceVec(ofVec2f* current, ofVec2f* prev, float dt);
    
    void diffuseFloat(float* current, float* prev, float diffusionAmount, float dt);
    void diffuseVec(ofVec2f* current, ofVec2f* prev, float diffusionAmount, float dt);
    
    void advect(float* currentDensity, float* prevDensity, ofVec2f* currentVelocity, float dt);
    void advectVel(ofVec2f* currentVelocity, ofVec2f* prevVelocity, float dt);
    
    void setBoundaryFloat(float* current, int side);
    void setBoundaryVec(ofVec2f* current, int side);
    
    void project(ofVec2f* currentVelocity, ofVec2f* prevVelocity);
    
    void densityStep();
    
    void velocityStep();
    
public:
    
    //マウスの入力判定
    bool isMousePressed = false;
    bool isLeftButton = true;
    
    //初期化
    void setup();
    
    //更新
    void update();
    
    //密度を描画
    void drawDensity();
    
    //速度を描画
    void drawVelocity();
    
    int getPos(int x, int y);
    
    ofVec2f prev_velocity[NUM];
    ofVec2f velocity[NUM];
    
    float density[NUM];
    float prev_density[NUM];
        
    float velocityDiffusion = 0.5;
    float densityDiffusion = 0.0000000000000000000001;
    
    bool lock = true;
    ofColor mainDensityColor;
    ofColor subDensityColor;
};
