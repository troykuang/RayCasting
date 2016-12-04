#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cmath>

using namespace std;


class SceneObject {

public:
	SceneObject();
	~SceneObject();
	void setType(int);
	int getType();
	string getPos();
	void assignFaces();
	void computeNorm(float[3],float[3]);
	void calcNorms();
	bool selected;
	bool intersected;
	float position [3];
	float orientation [3];
	float scale[3];

	int materialState;
	void changeMaterial(int);
	//for the bounding box
	void updateBounds();
	//bool operator==(const SceneObject& ,const SceneObject&);
	float boundingVertices [8][3];

	int boundingFaces [6][4];
	float boundingNorms [6][3];
	float xMin, xMax, yMin, yMax, zMin, zMax;
	//int size;

	float norms[6][3];
	float U [3];
	float V [3];
	float nvx,nvy,nvz;


private:
	int type;

};

#endif
