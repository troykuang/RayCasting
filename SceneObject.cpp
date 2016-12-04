#include "SceneObject.h"


using namespace std;

SceneObject::SceneObject(){
	type = 1;	//default if they dont set a type
	selected = false;	//after being created it is selected automatically
	intersected = false;
	size = 1;

	//to use for the normals


	assignFaces(); 	//to hold the faces and the right drawing order
	

	//default scale is 1 unit
	scale[0] = 1;
	scale[1] = 1;
	scale[2] = 1;

	//set at the origin
	position[0] = 5;
	position[1] = scale[1]/2;
	position[2] = 5;

	//default is original orientation (no rotation)
	orientation[0] = 0;
	orientation[1] = 0;
	orientation[2] = 0;

	updateBounds();
	calcNorms();
}

// bool SceneObject::operator== (const SceneObject& p1, const SceneObject& p2)
//     {
//         return 
//             (p1.type() == p2.type()) && 
//             (p1.selected() == p2.selected()) &&
//             (p1.intersected() == p2.intersected());
//     }


SceneObject::~SceneObject(){

}

int SceneObject::getType(){		//returns the type 
	return type;
}

	
void SceneObject::setType(int i){
	// 1 is cube
	// 2 is sphere
	// 3 is cone
	// 4 is teapot
	type = i;
	if(i == 3){
		position[2] = 0.0;
	}
	updateBounds();
}

string SceneObject::getPos(){
	cout<<"x: "<<position[0]<<endl;
	cout<<"y: "<<position[1]<<endl;
	cout<<"z: "<<position[2]<<endl;
}


void SceneObject::updateBounds(){
	//everytime it is rendered, it will update the bounds first in order to make sure it is correct
/*	double boundingVertices [8][3];
	int boundingFaces [6][4];
	double xMin, xMax, yMin, yMax, zMin, zMax;*/
	xMin = position[0]-scale[0]/2;
	xMax = position[0]+scale[0]/2;
	yMin = position[1]-scale[1]/2;
	yMax = position[1]+scale[1]/2;
	zMin = position[2]-scale[2]/2;
	zMax = position[2]+scale[2]/2;

	boundingVertices[0][0] = xMin;
	boundingVertices[0][1] = yMin;
	boundingVertices[0][2] = zMax;

	boundingVertices[1][0] = xMin;
	boundingVertices[1][1] = yMax;
	boundingVertices[1][2] = zMax;

	boundingVertices[2][0] = xMax;
	boundingVertices[2][1] = yMax;
	boundingVertices[2][2] = zMax;

	boundingVertices[3][0] = xMax;
	boundingVertices[3][1] = yMin;
	boundingVertices[3][2] = zMax;

	boundingVertices[4][0] = xMin;
	boundingVertices[4][1] = yMin;
	boundingVertices[4][2] = zMin;

	boundingVertices[5][0] = xMin;
	boundingVertices[5][1] = yMax;
	boundingVertices[5][2] = zMin;

	boundingVertices[6][0] = xMax;
	boundingVertices[6][1] = yMax;
	boundingVertices[6][2] = zMin;

	boundingVertices[7][0] = xMax;
	boundingVertices[7][1] = yMin;
	boundingVertices[7][2] = zMin;


}

void SceneObject::computeNorm(float v1[3], float v2[3]){
	float vx = v1[1]*v2[2]-v1[2]*v2[1];
	float vy = v1[2]*v2[0]-v1[0]*v2[2];
	float vz = v1[0]*v2[1]-v1[1]*v2[0];
	float l = sqrt(vx*vx+vy*vy+vz*vz);

	nvx = vx/l;
	nvy = vy/l;
	nvz = vz/l;
}

void SceneObject::calcNorms(){
	//Front 12 10
	U[0] = boundingVertices[1][0] - boundingVertices[2][0];
	U[1] = boundingVertices[1][1] - boundingVertices[2][1];
	U[2] = boundingVertices[1][2] - boundingVertices[2][2];
	//printf("the U are:%f,%f,%f\n",U[0],U[1],U[2]);

	V[0] = boundingVertices[1][0] - boundingVertices[0][0];
	V[1] = boundingVertices[1][1] - boundingVertices[0][1];
	V[2] = boundingVertices[1][2] - boundingVertices[0][2];
	//printf("the V are:%f,%f,%f\n",V[0],V[1],V[2]);

	computeNorm(U,V);
	norms[0][0]= nvx;
	norms[0][1]= nvy;
	norms[0][2]= nvz;
	printf("the norms0 are:%f,%f,%f\n",nvx,nvy,nvz);


	//Back 65 67
	U[0] = boundingVertices[6][0] - boundingVertices[5][0];
	U[1] = boundingVertices[6][1] - boundingVertices[5][1];
	U[2] = boundingVertices[6][2] - boundingVertices[5][2];
	//printf("the U are:%f,%f,%f\n",U[0],U[1],U[2]);

	V[0] = boundingVertices[6][0] - boundingVertices[7][0];
	V[1] = boundingVertices[6][1] - boundingVertices[7][1];
	V[2] = boundingVertices[6][2] - boundingVertices[7][2];
	//printf("the V are:%f,%f,%f\n",V[0],V[1],V[2]);

	computeNorm(U,V);
	norms[1][0]= nvx;
	norms[1][1]= nvy;
	norms[1][2]= nvz;
	printf("the norms1 are:%f,%f,%f\n",nvx,nvy,nvz);


	//Left 51 54
	U[0] = boundingVertices[5][0] - boundingVertices[1][0];
	U[1] = boundingVertices[5][1] - boundingVertices[1][1];
	U[2] = boundingVertices[5][2] - boundingVertices[1][2];
	//printf("the U are:%f,%f,%f\n",U[0],U[1],U[2]);

	V[0] = boundingVertices[5][0] - boundingVertices[4][0];
	V[1] = boundingVertices[5][1] - boundingVertices[4][1];
	V[2] = boundingVertices[5][2] - boundingVertices[4][2];
	//printf("the V are:%f,%f,%f\n",V[0],V[1],V[2]);

	computeNorm(U,V);
	norms[2][0]= nvx;
	norms[2][1]= nvy;
	norms[2][2]= nvz;
	printf("the norms2 are:%f,%f,%f\n",nvx,nvy,nvz);


	//Right 26 23
	U[0] = boundingVertices[2][0] - boundingVertices[6][0];
	U[1] = boundingVertices[2][1] - boundingVertices[6][1];
	U[2] = boundingVertices[2][2] - boundingVertices[6][2];
	//printf("the U are:%f,%f,%f\n",U[0],U[1],U[2]);

	V[0] = boundingVertices[2][0] - boundingVertices[3][0];
	V[1] = boundingVertices[2][1] - boundingVertices[3][1];
	V[2] = boundingVertices[2][2] - boundingVertices[3][2];
	//printf("the V are:%f,%f,%f\n",V[0],V[1],V[2]);

	computeNorm(U,V);
	norms[3][0]= nvx;
	norms[3][1]= nvy;
	norms[3][2]= nvz;
	printf("the norms3 are:%f,%f,%f\n",nvx,nvy,nvz);


	//Top 56 51
	U[0] = boundingVertices[5][0] - boundingVertices[6][0];
	U[1] = boundingVertices[5][1] - boundingVertices[6][1];
	U[2] = boundingVertices[5][2] - boundingVertices[6][2];
	//printf("the U are:%f,%f,%f\n",U[0],U[1],U[2]);

	V[0] = boundingVertices[5][0] - boundingVertices[1][0];
	V[1] = boundingVertices[5][1] - boundingVertices[1][1];
	V[2] = boundingVertices[5][2] - boundingVertices[1][2];
	//printf("the V are:%f,%f,%f\n",V[0],V[1],V[2]);

	computeNorm(U,V);
	norms[4][0]= nvx;
	norms[4][1]= nvy;
	norms[4][2]= nvz;
	printf("the norms4 are:%f,%f,%f\n",nvx,nvy,nvz);


	//Btm 74 73
	U[0] = boundingVertices[7][0] - boundingVertices[4][0];
	U[1] = boundingVertices[7][1] - boundingVertices[4][1];
	U[2] = boundingVertices[7][2] - boundingVertices[4][2];
	//printf("the U are:%f,%f,%f\n",U[0],U[1],U[2]);

	V[0] = boundingVertices[7][0] - boundingVertices[3][0];
	V[1] = boundingVertices[7][1] - boundingVertices[3][1];
	V[2] = boundingVertices[7][2] - boundingVertices[3][2];
	//printf("the V are:%f,%f,%f\n",V[0],V[1],V[2]);

	computeNorm(U,V);
	norms[5][0]= nvx;
	norms[5][1]= nvy;
	norms[5][2]= nvz;
	printf("the norms5 are:%f,%f,%f\n",nvx,nvy,nvz);
	



}


void SceneObject::assignFaces(){
	boundingFaces[0][0] = 0;	//front face
	boundingFaces[0][1] = 3;
	boundingFaces[0][2] = 2;
	boundingFaces[0][3] = 1;

	boundingFaces[1][0] = 4;	//back face
	boundingFaces[1][1] = 5;
	boundingFaces[1][2] = 6;
	boundingFaces[1][3] = 7;

	boundingFaces[2][0] = 7;	//right side
	boundingFaces[2][1] = 6;
	boundingFaces[2][2] = 2;
	boundingFaces[2][3] = 3;

	boundingFaces[3][0] = 0;	//left side
	boundingFaces[3][1] = 1;
	boundingFaces[3][2] = 5;
	boundingFaces[3][3] = 4;

	boundingFaces[4][0] = 2;	//top
	boundingFaces[4][1] = 6;
	boundingFaces[4][2] = 5;
	boundingFaces[4][3] = 1;

	boundingFaces[5][0] = 0;	//bottom
	boundingFaces[5][1] = 4;
	boundingFaces[5][2] = 7;
	boundingFaces[5][3] = 3;




}



/*int main(){
	SceneObject * s = new SceneObject("natasha",0,3,4);
	s -> getType();
	s -> getPos();
	s -> addAmbient(2,3,4);
	s -> addDiffuse(1,2,3);
	s -> addSpecular(0,0,2);
	s -> addShiny(3);

	return 1;
}


*/