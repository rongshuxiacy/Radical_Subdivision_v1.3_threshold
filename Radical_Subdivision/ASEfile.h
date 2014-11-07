#pragma once

#ifndef __ASE_FILE_H__
#define __ASE_FILE_H__

#include "data_struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

class ASEfile
{
public:
	ASEfile(void);
	bool loadfile(const char* filename);
	ASE_OBJECT_HEAD* getase_head(){return head;}	//�����ļ�ͷ��ָ��
	void render();									//����aseģ��
	void print();									//���ase�ļ���Ϣ
	~ASEfile(void);
private:
	void centralize();	//���Ļ���ʹ��ȡase�ļ��Ķ��������ƶ����е�

private:	
	ASE_OBJECT_HEAD* head;
};

#endif