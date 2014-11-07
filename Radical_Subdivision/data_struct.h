#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>

struct VERTEX
{
	float x,y,z;
};
struct FACE
{
	int index[3];
	VERTEX noraml;//������
};

struct ASE_OBJECT
{
	int vertex_num;
	VERTEX* vertex_list;
	int face_num;
	FACE* face_list;
	ASE_OBJECT* next;
};

struct ASE_OBJECT_HEAD
{
	int object_number;
	ASE_OBJECT* head;
};

struct PLY_OBJECT
{
	int vertex_num;
	VERTEX* vertex_list;

	int face_num;
	FACE* face_list;
};

//////////////////////////////////////////////////////////////////	
//					subdivision data struct						//
//																//

enum EVENORODD{UNKNOWN,ODD,EVEN};

class LOD_VERTEX
{
public:
	int index;		//��������ԭʼ����0��������
	VERTEX point;	//��������
	VERTEX normal;	//������
	int	valence;	//��.
	EVENORODD even;	//�Ƿ�Ϊż����.-1: δ����, 1: ���, 2:ż��. ż��������һlevel�н���������

	int adj[20];//�ڽӶ������������˳ʱ������(������������ĴָΪ����).

	inline LOD_VERTEX& operator =(const LOD_VERTEX& a)
	{
		this->index = a.index;
		this->point = a.point;
		this->normal = a.normal;
		this->valence = a.valence;
		this->even = a.even;

		for (int i = 0; i<20; i++)
			this->adj[i] = a.adj[i];
		return *this;
	}
};

class LOD_FACE
{
public:
	int vertIndex[3];//��������
	VERTEX normal;	//������

	int faceVertexID; // new face vertex

	inline LOD_FACE& operator =(const LOD_FACE& a)
	{
		for (int i =0; i<3; i++)
			this->vertIndex[i] = a.vertIndex[i];		
	//	memcpy(b.vertIndex,a.vertIndex,sizeof(int)*3);
		this->normal = a.normal;
		this->faceVertexID = a.faceVertexID;
		return *this;
	}
};


/////////////////////////////////////////////////////////////////////////
//
//				error vertex
//
class LOD_ERROR
{
public:
	int vertexIndex;				// original vertex index
	VERTEX point;

	float errXYZ[3];				// error 
	int faceVertex[3];				// three vertex around the error vertex
};
/////////////////////////////////////////////////////////////////////////
#include <math.h>
static void minus(VERTEX &a, VERTEX b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
}
static void normalize(VERTEX &p)
{ // adjust p vector to unit length		
	double sizeSq = p.x * p.x + p.y * p.y + p.z * p.z;
	if(sizeSq < 0.0000001)
	{
		//cerr << "\nnormalize() sees vector (0,0,0)!";
		return; // does nothing to zero vectors;
	}
	float scaleFactor = (float)(1.0/sqrt(sizeSq));
	p.x *= scaleFactor; p.y *= scaleFactor; p.z *= scaleFactor;
}

static VERTEX cross(VERTEX a, VERTEX b)
{ // return a cross b
	VERTEX ans;
	ans.x = a.y*b.z - a.z*b.y;
	ans.y = a.z*b.x - a.x*b.z;
	ans.z = a.x*b.y - a.y*b.x;
	return ans;
}

static float dot(VERTEX a, VERTEX b)
{ // return a dotted with b
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static VERTEX createVector(VERTEX a, VERTEX b)
{ // create a vector from a to b
	VERTEX ans;
	ans.x = b.x - a.x;
	ans.y = b.y - a.y;
	ans.z = b.z - a.z;
	return ans;
}

static VERTEX createVector(float ax, float ay, float az,
	float bx, float by, float bz)
{ // create a vector from a to b
	VERTEX ans;
	ans.x = bx - ax;
	ans.y = by - ay;
	ans.z = bz - az;
	return ans;
}

static VERTEX createVector(VERTEX a){
	// create a vector from 0 to a
	VERTEX ans;
	ans.x = a.x;
	ans.y = a.y;
	ans.z = a.z;
	return ans;
}

static void product(VERTEX &a, float m)
{ // multiple a vector by m
	a.x *= m;
	a.y *= m;
	a.z *= m;
}

//////////////////////////////////////////////////////////////////
//
//  half edge struct
///////////////////////////////////////////////////////////
struct Vertex{

	struct HalfEdge *startEdge;
	VERTEX coord;
	int id;
};

struct Face{

	struct HalfEdge *firstEdge;
	struct Vertex *ver;
	int faceVertexId;
	int nPolygon;
};

struct HalfEdge{
	
	struct Vertex *head;
	struct Face *leftf;
	struct HalfEdge *sym;
	struct HalfEdge *next;
};



#ifndef PI
#define PI 3.14159265359
#endif

#endif