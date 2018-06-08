#include "StdAfx.h"
#include "MyOpenGL.h"
#include <cmath>
#include <iostream>
#define POINTNUM 200
#define CIRCLENUM 20
#define PI 3.1415926

CVector966 tracePointPos[POINTNUM];//姓名轨迹点
CVector966 refCircle[CIRCLENUM];//参考圆轨迹点
CVector966 allPointPos[POINTNUM*CIRCLENUM];//计算轨迹点位置结果
int iCurIndex;//运动小人当前参考轨迹点下标
GLfloat (*vert)[3] = 0, (*norm)[3] = 0;
int nVert=0;
GLuint texture1[1]={0};
GLuint texture2[1]={0};

CMyOpenGL::CMyOpenGL(void)
{
} 


CMyOpenGL::~CMyOpenGL(void)
{
}


/**
* \brief 初始化
*/
void CMyOpenGL::PostInit(void)
{
	//glShadeModel(GL_FLAT);
	//glFrontFace(GL_CW);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_BACK,GL_LINE);
	////定义了一个 圆的路径
	//for(int i = 0; i < CIRCLENUM; i++)
	//{
	//	float angle = i*2*3.14/(CIRCLENUM-1);
	//	refCircle[i].x = 0;
	//	refCircle[i].y = 1*cos(angle);
	//	refCircle[i].z = 1*sin(angle);
	//}
	////渲染点位构成名字 刘昊

	////刘 中 文的一点，3点
	//for(int i = 0; i < 3; i++){
	//	tracePointPos[i][0] = 0.3 * i - 18;
	//	tracePointPos[i][1] = 10 - i;
	//	tracePointPos[i][2] = 0;
	//}

	////刘 中 文的一横，15点
	//for(int i = 0; i < 15; i++){
	//	tracePointPos[i + 3][0] = -i - 9;
	//	tracePointPos[i + 3][1] = 7;	
	//	tracePointPos[i + 3][2] = 0;
	//}

	////刘 中 文的一撇，11点
	//for(int i = 0; i < 11; i++){
	//	tracePointPos[i + 18][0] = -i - 12;
	//	tracePointPos[i + 18][1] = -1.68 * i + 5;	
	//	tracePointPos[i + 18][2] = 0;
	//}

	////刘 中 文的一捺，9点
	//for(int i = 0; i < 9; i++){
	//	tracePointPos[i + 29][0] = -i - 13;
	//	tracePointPos[i + 29][1] = 1.6 * i - 9;	
	//	tracePointPos[i + 29][2] = 0;
	//}

	////刘 中 立刀的一竖，8点
	//for(int i = 0; i < 8;i++){
	//	tracePointPos[i + 38][0] = -9;
	//	tracePointPos[i + 38][1] = -i + 4;
	//	tracePointPos[i + 38][2] = 0;
	//}

	////刘 中 立刀的大竖，22点
	//for(int i = 0; i < 22;i++){
	//	tracePointPos[i + 46][0] = -5;
	//	tracePointPos[i + 46][1] = -i + 10;
	//	tracePointPos[i + 46][2] = 0;
	//}

	////昊 中 日的一竖，6点
	//for(int i = 0; i < 6; i++)
	//{
	//	tracePointPos[i + 68][0] = 5;
	//	tracePointPos[i + 68][1] = i + 4;
	//	tracePointPos[i + 68][2] = 0;
	//}

	////昊 中 日的一竖，6点
	//for(int i = 0; i < 6; i++)
	//{
	//	tracePointPos[i + 74][0] = 14;
	//	tracePointPos[i + 74][1] = i + 4;
	//	tracePointPos[i + 74][2] = 0;
	//}

	////昊 中 日的一横，10点
	//for(int i = 0; i < 10; i++)
	//{
	//	tracePointPos[i + 80][0] = i + 5;
	//	tracePointPos[i + 80][1] = 10;
	//	tracePointPos[i + 80][2] = 0;
	//}

	////昊 中 日的一横，10点
	//for(int i = 0; i < 10; i++)
	//{
	//	tracePointPos[i + 90][0] = i + 5;
	//	tracePointPos[i + 90][1] = 7;
	//	tracePointPos[i + 90][2] = 0;
	//}

	////昊 中 日的一横，10点
	//for(int i = 0; i < 10; i++)
	//{
	//	tracePointPos[i + 100][0] = i + 5;
	//	tracePointPos[i + 100][1] = 4;
	//	tracePointPos[i + 100][2] = 0;
	//}

	////昊 中 天的一横，12点
	//for(int i = 0; i < 12; i++)
	//{
	//	tracePointPos[i + 110][0] = i + 4;
	//	tracePointPos[i + 110][1] = 1;
	//	tracePointPos[i + 110][2] = 0;
	//}

	////昊 中 天的一横，14点
	//for(int i = 0; i < 14; i++)
	//{
	//	tracePointPos[i + 122][0] = i + 3;
	//	tracePointPos[i + 122][1] = -2;
	//	tracePointPos[i + 122][2] = 0;
	//}

	////昊 中 天的一撇中的一小竖，3点
	//for(int i = 0; i < 3; i++)
	//{
	//	tracePointPos[i + 136][0] = 9.5;
	//	tracePointPos[i + 136][1] = -i + 1;
	//	tracePointPos[i + 136][2] = 0;
	//}

	////昊 中 天的一撇中的一小撇，7点
	//for(int i = 0; i < 7; i++)
	//{
	//	tracePointPos[i + 139][0] = -i + 9.5;
	//	tracePointPos[i + 139][1] = -1.6 * i - 2;
	//	tracePointPos[i + 139][2] = 0;
	//}

	////昊 中 天的一捺
	//for(int i = 0; i < 7; i++)
	//{
	//	tracePointPos[i + 146][0] = -i + 16;
	//	tracePointPos[i + 146][1] = 1.6 * i - 12;
	//	tracePointPos[i + 146][2] = 0;
	//}

	//CMatrix966 mat;
	//for(int i=0; i<POINTNUM; i++)
	//{
	//	CVector966 dir;
	//	float rotang = 0;
	//	if(i != POINTNUM - 1)
	//	{
	//		dir = tracePointPos[ (i + 1) % POINTNUM] - tracePointPos[i];				
	//	}
	//	else
	//	{
	//		dir = tracePointPos[i] - tracePointPos[(i + POINTNUM - 1) % POINTNUM];				
	//	}
	//	dir.Normalize();//方向
	//	rotang = acos(dir.x);
	//	if(dir.y < 0)
	//	{
	//		rotang = -rotang;
	//	}
	//	rotang = rotang * 180 / acosf(-1);
	//	CVector966 axis;
	//	axis.z = 1;
	//	mat.SetRotate(rotang, axis);//设置为旋转矩阵。
	//	mat.Translate(tracePointPos[i]);
	//	for(int j=0;j<CIRCLENUM;j++)
	//	{
	//		int index = i*CIRCLENUM+j;
	//		allPointPos[index] = mat.MulPosition(refCircle[j]); 
	//	}
	//}

	//glEnable(GL_LIGHTING);
	////0号光源-太阳光
	//GLfloat light0Ambient[] = {0.2, 0.2, 0.2, 1.0};
	//GLfloat light0Diffuse[] = {1.0, 1.0, 1.0, 1.0};
	//GLfloat light0Specular[] = {0.5, 0.5, 0.5, 1.0};
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
	//glEnable(GL_LIGHT0);

	////1号光源-聚光灯
	//GLfloat light1Diffuse[] = {0.5, 0.5, 0.5, 1.0};
	//GLfloat light1Specular[] = {0.5, 0.5, 0.5, 1.0};
	//GLfloat light1SpotCutoff = 45.0;
	//GLfloat light1SpotExponent = 2.0;
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
 //   glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1SpotCutoff);
	//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, light1SpotExponent);
	//glEnable(GL_LIGHT1);


	////指定顶点颜色为材质颜色
	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	//pModal->cvModCurPos = tracePointPos[0];
	//pModal->cvModCurDir = tracePointPos[1] - tracePointPos[0];
	//pModal->cvModPrevDir = pModal->cvModCurDir;
	//pModal->cvModCurDir.Normalize();
	//glEnable(GL_DEPTH_TEST);
	//glPushMatrix();
	//glLoadIdentity();
	//glTranslatef(0, 0, -25);
	//glMultMatrixf(pCamera->cmEyeMat);
	//glGetFloatv(GL_MODELVIEW_MATRIX, pCamera->cmEyeMat);
	//glPopMatrix();
	//GetTexture();
	//pCamera->cvMovVec.z = 25;
	//pCamera->ShowView();
}


/**
* \brief 绘制主控
*/
void CMyOpenGL::InDraw(void)
{
	scene.Render();
	//glPushAttrib(GL_ENABLE_BIT);
	//glFrontFace(GL_CCW);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
	//glColor3f(0.3,0.5,0.3);
	//glDisable(GL_CULL_FACE);
	//glutSolidSphere(500, 1000, 1000);
	//glPopAttrib();
	//DrawAxes();
	//glPushMatrix();
	//GLfloat light0Position[] = {0.0, 0.0, 10000.0, 1.0};
	//glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
	//pModal->cmModPrev = pModal->cmModCur;
	//GLfloat light1Position[] = {pModal->cvModCurPos.x, pModal->cvModCurPos.y, pModal->cvModCurPos.z, 1.0};
	//glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
	//
	//if (pCamera->GetSlerp())
	//{
	//	CVector966 tmp;
	//	tmp.Z(-1);
	//	CVector966 dir = pModal->cmModCur.MulVector(tmp);
	//	GLfloat light1SpotDirection[] = {dir.x, dir.y, dir.z, 1.0};
	//	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1SpotDirection);
	//	pModal->cmModCur = pCamera->GetSlerpQua().ToMatrix();
	//	pModal->cmModCur.Translate(pModal->cvModPrevPos);
	//	glMultMatrixf(pModal->cmModCur);
	//	DrawRobot();
	//	
	//}
	//else
	//{
	//	if (pModal->iModelMode == 0)
	//	{
	//		CVector966 tmp;
	//		tmp.Z(-1);
	//		CVector966 dir = pModal->cmModCur.MulVector(tmp);
	//		GLfloat light1SpotDirection[] = {dir.x, dir.y, dir.z, 1.0};
	//		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1SpotDirection);
	//		pModal->cmModCur = pModal->cvModCurDir.ToMatrix();
	//		pModal->cmModCur.Translate(pModal->cvModCurPos);
	//		glMultMatrixf(pModal->cmModCur);
	//		DrawRobot();
	//	}
	//	else
	//	{
	//		CVector966 tmp;
	//		tmp.Z(-1);
	//		CVector966 dir = pModal->cmModCur.MulVector(tmp);
	//		GLfloat light1SpotDirection[] = {dir.x, dir.y, dir.z, 1.0};
	//		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1SpotDirection);
	//		pModal->cmModCur.Translate(pModal->cvModCurPos);
	//		glMultMatrixf(pModal->cmModCur);
	//		DrawUfo();
	//	}
	//	
	//}       
	//
	//
	//glPopMatrix();
	////glPushAttrib(GL_ENABLE_BIT);
	////glDisable(GL_LIGHTING);
	//if (pModal->iTraceMode == 0)
	//{
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//	glColor3f(0.5, 0.4, 0.1);	
	//	for(int i = 0; i < POINTNUM; i++)
	//	{
	//		CVector966 dir;
	//		float rotang = 0;
	//		dir = tracePointPos[(i + 1) % POINTNUM] - tracePointPos[i];		
	//		dir.Normalize();//方向
	//		rotang = acos(dir.x) * 180 / 3.14;
	//		if(dir.y<0)
	//		{
	//			rotang = -rotang;
	//		}
	//		glPushMatrix();
	//		glTranslatef(tracePointPos[i].x, tracePointPos[i].y, tracePointPos[i].z);
	//		glRotatef(rotang, 0, 0, 1);
	//		glBegin(GL_LINE_STRIP);		
	//		for(int j = 0; j < CIRCLENUM; j++)
	//		{
	//			glVertex3fv(refCircle[j]);
	//		}
	//		glEnd();
	//		glPopMatrix();
	//	}
	//}
	//else
	//{
	//	CMatrix966 mat;
	//	float lastrotang = 0;
	//	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//	glBegin(GL_TRIANGLE_STRIP);
	//	for(int i=0;i<POINTNUM-1;i++)
	//	{
	//		if (i == 2 || i == 17 || i == 28 || i == 37 || i == 45 || i == 67 || i == 73 || i == 79 || i == 89 || i == 99 || i ==
	//			109 || i == 121 || i == 135 || i == 138 || i == 145) //笔画连接处为黑色
	//		{
	//			glEnd();
	//			glColor4f(0.1,0.1,0.1,0.5);
	//			glBegin(GL_TRIANGLE_STRIP);				
	//		}
	//		else
	//		{
	//			glColor3f(0.5,0.4,0.1);
	//		}
	//		for(int j=0;j<CIRCLENUM;j++)
	//		{
	//			int index1 = i*CIRCLENUM+j;
	//			int index2 = index1+CIRCLENUM;
	//			glVertex3fv(allPointPos[index1]);
	//			glVertex3fv(allPointPos[index2]);
	//		}			
	//	}
	//	glEnd();
	//}
	//glPopAttrib();
}


bool CMyOpenGL::OnKey(unsigned char nChar, bool bDown)
{
	return false;
}

/**
* \brief 更新主控
*/
void CMyOpenGL::Update()
{
	//if (!pCamera->GetSlerp())
	//{
	//	pModal->cvModPrevPos = pModal->cvModCurPos;

	//	if (pModal->iModelMode == 0)
	//	{
	//		if (pModal->bModelChange)
	//		{
	//			pModal->bModelChange = false;
	//			int tmpIndex = iCurIndex;
	//			float dis = (tracePointPos[tmpIndex] - pModal->cvModCurPos).len();
	//			for (int i = 0; i < POINTNUM; i++)
	//			{
	//				float tmpDis = (tracePointPos[i] - pModal->cvModCurPos).len();
	//				if (tmpDis < dis)
	//				{
	//					tmpIndex = i;
	//					dis = tmpDis;
	//				}
	//			}
	//			iCurIndex = tmpIndex;
	//			pModal->cvModCurDir = tracePointPos[tmpIndex] - pModal->cvModCurPos;
	//			if (pModal->fSpeed <= 0)
	//			{
	//				iCurIndex = (iCurIndex + 1) % POINTNUM;;
	//			}
	//			else
	//			{
	//				iCurIndex = (iCurIndex - 1 + POINTNUM) % POINTNUM;
	//			}
	//		}
	//		else
	//		{
	//			pModal->cvModPrevDir = pModal->cvModCurDir;
	//			//便于后面的分析工作，将速度绝对值取出来
	//			float len = fabs(pModal->fSpeed);
	//			while(true)
	//			{
	//				int nextindex;
	//				//确认方向
	//				if(pModal->fSpeed > 0)
	//				{
	//					nextindex = (iCurIndex + 1) % POINTNUM;
	//				}
	//				else
	//				{
	//					nextindex = (iCurIndex - 1 + POINTNUM) % POINTNUM;
	//				}
	//				//小球到下一个基准点的距离
	//				float leftlen = (tracePointPos[nextindex] - pModal->cvModCurPos).len();
	//				//每次进入update都要更新一次方向 这正是我的问题所在
	//				pModal->cvModCurDir = tracePointPos[nextindex] - pModal->cvModCurPos;
	//				pModal->cvModCurDir.Normalize();
	//				pModal->cvUfoDir = pModal->cvModCurDir;
	//				if(leftlen > len)//小球速度不会跨过当前点，向前走就好了
	//				{
	//					pModal->cvModCurPos = pModal->cvModCurPos + pModal->cvModCurDir * len;
	//					break;
	//				}
	//				else	//小球会跨点，那就走到下一个点继续寻找
	//				{				
	//					pModal->cvModCurPos = tracePointPos[nextindex];
	//					len -= leftlen;
	//					iCurIndex = nextindex;
	//				}
	//			}
	//		}
	//		float tmp = pModal->cvModPrevDir.dotMul(pModal->cvModCurDir) / (pModal->cvModCurDir.len() * pModal->cvModPrevDir.len());
	//		tmp = (tmp > 1) ? 1 : ((tmp < -1) ? -1 : tmp);
	//		float angle = acosf(tmp);
	//		angle = angle * 180 / acosf(-1);
	//		if (angle > 10)
	//		{
	//			pCamera->CalSlerp(angle);
	//		}
	//		else
	//		{
	//			pCamera->SetSlerp(false);
	//		}
	//	}
	//	else
	//	{
	//		pModal->cvModPrevDir = pModal->cvUfoDir;
	//		float len = pModal->fSpeed;
	//		if (pModal->bSpeed)
	//		{
	//			pModal->cvModCurPos = pModal->cvModCurPos + pModal->cvUfoDir * len;
	//		}
	//		else
	//		{
	//			pModal->cvModCurPos = pModal->cvModCurPos + pModal->cvUfoDir * -len;
	//		}
	//		
	//	}
	//}
	//pCamera->ChkSlerp();
}

/**
 * \brief 绘制坐标轴
 */
void CMyOpenGL::DrawAxes()
{
	//glPushAttrib(GL_ENABLE_BIT);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_TEXTURE_2D);
	//glPushMatrix();
	//glBegin(GL_LINES);
	//glColor3f(1,0,0);
	//glVertex3f(0,0,0);
	//glVertex3f(30,0,0);
	//glColor3f(0,1,0);
	//glVertex3f(0,0,0);
	//glVertex3f(0,30,0);
	//glColor3f(0,0,1);
	//glVertex3f(0,0,0);
	//glVertex3f(0,0,30);
	//glEnd();
	//glPopMatrix();
	//glPopAttrib();
}

/**
 * \brief 画一个球
 * \param radius 半径
 * \param lon 经向分割
 * \param lat 纬向分割
 */
void CMyOpenGL::DrawBall(GLfloat radius,int lon,int lat)
{
	//glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	//glEnable(GL_TEXTURE_2D);
	//glFrontFace(GL_CW);
	//if (pModal->iModelMode == 0)
	//{
	//	glBindTexture(GL_TEXTURE_2D, texture1[0]);
	//}
	//else
	//{
	//	glBindTexture(GL_TEXTURE_2D, texture2[0]);
	//}
	//glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);			//正面用填充方式绘制。
	//glBegin(GL_TRIANGLES);
	//GLfloat picLon, picLat;
	//GLfloat refLon = 1.0 / lon, refLat = 1.0 / lat;
	//GLfloat lonCur, lonNext, lonStep = 2 * PI / lon;
	//GLfloat latCur, latNext, latStep = PI / lat;
	//GLfloat v1[3], v2[3], v3[3], v4[3], normal[3];
	//int i, j;
	//for(lonCur = 0, i = 0; i < lon; lonCur += lonStep, i++)	//经度
	//{

	//	lonNext = lonCur+lonStep;
	//	picLon = refLon * i;
	//	if(i==lon-1)
	//	{
	//		lonNext = 0;	//边界约束，经度要转360°连接

	//	}
	//		
	//	for(latCur=-PI/2,j=0;j<lat;latCur+=latStep,j++)	//维度
	//	{
	//		latNext = latCur+latStep;
	//		picLat = refLat * j;
	//		if(j==lat-1)
	//		{
	//			latNext=PI/2;	//边界约束，纬度约束到90°
	//		}
	//		
	//		
	//		//第一个点
	//		v1[2]=radius*cos(latCur)*sin(lonCur);
	//		v1[0]=radius*cos(latCur)*cos(lonCur);
	//		v1[1]=radius*sin(latCur);

	//		//第二个点
	//		v2[2]=radius*cos(latCur)*sin(lonNext);
	//		v2[0]=radius*cos(latCur)*cos(lonNext);
	//		v2[1]=radius*sin(latCur);

	//		//第三个点
	//		v3[2]=radius*cos(latNext)*sin(lonNext);
	//		v3[0]=radius*cos(latNext)*cos(lonNext);
	//		v3[1]=radius*sin(latNext);

	//		//第四个点
	//		v4[2]=radius*cos(latNext)*sin(lonCur);
	//		v4[0]=radius*cos(latNext)*cos(lonCur);
	//		v4[1]=radius*sin(latNext);
	//		
	//		//第一个三角形
	//		CalculateNormal(v1,v2,v3,normal);
	//		Normalize(normal);
	//		glNormal3fv(normal);
	//		glTexCoord2f(picLon, picLat);
	//		glVertex3fv(v1);
	//		glTexCoord2f(picLon + refLon, picLat);
	//		glVertex3fv(v2);
	//		glTexCoord2f(picLon + refLon, picLat + refLat);
	//		glVertex3fv(v3);
	//		//第二个三角形
	//		CalculateNormal(v3,v4,v1,normal);
	//		Normalize(normal);
	//		glNormal3fv(normal);
	//		glVertex3fv(v3);
	//		glTexCoord2f(picLon, picLat + refLat);
	//		glVertex3fv(v4);
	//		glVertex3fv(v1);
	//	}
	//}
	//glEnd();
	//glPopAttrib();
}

/**
 * \brief 计算法向量
 * \param v1 第一个点
 * \param v2 第二个点
 * \param v3 第三个点
 * \param normal 法向量
 */
void CMyOpenGL::CalculateNormal(GLfloat v1[],GLfloat v2[],GLfloat v3[],GLfloat normal[])
{
	//GLfloat dirv2_v1[3],dirv2_v3[3];
	//for(int i=0;i<3;i++)
	//{
	//	dirv2_v1[i]=v1[i]-v2[i];
	//	dirv2_v3[i]=v3[i]-v2[i];
	//}
	////叉乘计算法线方向
	//normal[0]=dirv2_v1[1]*dirv2_v3[2]-dirv2_v1[2]*dirv2_v3[1];
	//normal[1]=dirv2_v1[2]*dirv2_v3[0]-dirv2_v1[0]*dirv2_v3[2];
	//normal[2]=dirv2_v1[0]*dirv2_v3[1]-dirv2_v1[1]*dirv2_v3[0];
}

/**
 * \brief 法向量规范化
 * \param v 法向量
 */
void CMyOpenGL::Normalize(GLfloat *v)
{
	//GLfloat dis = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	//if(dis>0)
	//{
	//	v[0]/=dis;
	//	v[1]/=dis;
	//	v[2]/=dis;
	//}
}

bool CMyOpenGL::GetTexture()
{
	//AUX_RGBImageRec *img1 = auxDIBImageLoad("lib/dumb1.bmp");
	//glGenTextures(1, &texture1[0]);
	//glBindTexture(GL_TEXTURE_2D, texture1[0]);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, img1->sizeX, img1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, img1->data);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
	//free(img1->data);
	//free(img1);
	//AUX_RGBImageRec *img2 = auxDIBImageLoad("lib/plane1.bmp");
	//glGenTextures(1, &texture2[0]);
	//glBindTexture(GL_TEXTURE_2D, texture2[0]);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, img2->sizeX, img2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, img2->data);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
	//free(img2->data);
	//free(img2);
	return true;
}

void CMyOpenGL::DrawBox(float size)
{
	//glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture1[0]);
	//glColor3f(1,1,1);
	//glBegin(GL_QUADS);
	//// Back Face
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f * size, -1.0f * size, -1.0f * size);	// Bottom Right Of The Texture and Quad
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f * size,  1.0f * size, -1.0f * size);	// Top Right Of The Texture and Quad
	//glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f * size,  1.0f * size, -1.0f * size);	// Top Left Of The Texture and Quad
	//glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f * size, -1.0f * size, -1.0f * size);	// Bottom Left Of The Texture and Quad
	//// Front Face
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f * size, -1.0f * size,  1.0f * size);	// Bottom Left Of The Texture and Quad
	//glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f * size, -1.0f * size,  1.0f * size);	// Bottom Right Of The Texture and Quad
	//glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f * size,  1.0f * size,  1.0f * size);	// Top Right Of The Texture and Quad
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f * size,  1.0f * size,  1.0f * size);	// Top Left Of The Texture and Quad
	//// Top Face
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f * size,  1.0f * size, -1.0f * size);	// Top Left Of The Texture and Quad
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f * size,  1.0f * size,  1.0f * size);	// Bottom Left Of The Texture and Quad
	//glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f * size,  1.0f * size,  1.0f * size);	// Bottom Right Of The Texture and Quad
	//glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f * size,  1.0f * size, -1.0f * size);	// Top Right Of The Texture and Quad
	//// Bottom Face
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f * size, -1.0f * size, -1.0f * size);	// Top Right Of The Texture and Quad
	//glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f * size, -1.0f * size, -1.0f * size);	// Top Left Of The Texture and Quad
	//glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f * size, -1.0f * size,  1.0f * size);	// Bottom Left Of The Texture and Quad
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f * size, -1.0f * size,  1.0f * size);	// Bottom Right Of The Texture and Quad
	//// Right face
	//glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f * size, -1.0f * size, -1.0f * size);	// Bottom Right Of The Texture and Quad
	//glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f * size,  1.0f * size, -1.0f * size);	// Top Right Of The Texture and Quad
	//glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f * size,  1.0f * size,  1.0f * size);	// Top Left Of The Texture and Quad
	//glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f * size, -1.0f * size,  1.0f * size);	// Bottom Left Of The Texture and Quad
	//// Left Face
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f * size, -1.0f * size, -1.0f * size);	// Bottom Left Of The Texture and Quad
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f * size, -1.0f * size,  1.0f * size);	// Bottom Right Of The Texture and Quad
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f * size,  1.0f * size,  1.0f * size);	// Top Right Of The Texture and Quad
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f * size,  1.0f * size, -1.0f * size);	// Top Left Of The Texture and Quad
	//glEnd();
	//glPopAttrib();
}

/**
* \brief 绘制小机器人
*/
void CMyOpenGL::DrawRobot()
{
	//glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
	//glFrontFace(GL_CCW);
	//static int type = 0, curFrame = 0;
	//curFrame++;
	//if(curFrame % 10 == 0)
	//{
	//	type = (type + 1) % 8;
	//}
	//const float size=1;
	//glPushMatrix();
	//glTranslatef(0, size * 1.2, 0);

	////头
	//glPushMatrix();
	//glColor3f(0.4, 1, 0);
	////glutSolidSphere(size * 0.3, 100, 100);
	//DrawBall(size * 0.3, 100, 100);
	////DrawBox(size * 0.3);
	//glPopMatrix();

	////身子    
	//glColor3f(0.2, 0.2, 0);
	//glPushMatrix();
	//glTranslatef(0, -size * 0.3, 0);
	//glRotatef(90, 1, 0, 0);
	//glutSolidCone(size * 0.7, size * 1.5, 100, 100);
	//glPopMatrix();

	////胳膊
	//glColor3f(0.4, 0.1, 0);
	//glPushMatrix();
	//glTranslatef(-size * 0.5, -size * 0.7, 0);
	//glRotatef(-8, 0, 0, 1);
	//if(type == 0)
	//{
	//	glRotatef(-40, 1, 0, 0);
	//}
	//else if(type == 1)
	//{
	//	glRotatef(-20, 1, 0, 0);
	//}
	//else if (type == 2)
	//{
	//	glRotatef(0, 1, 0, 0);
	//}
	//else if(type == 3)
	//{
	//	glRotatef(20, 1, 0, 0);
	//}
	//else if (type == 4)
	//{
	//	glRotatef(40, 1, 0, 0);
	//}
	//else if (type == 5)
	//{
	//	glRotatef(20, 1, 0, 0);
	//}
	//else if (type == 6)
	//{
	//	glRotatef(0, 1, 0, 0);
	//}
	//else
	//{
	//	glRotatef(-20, 1, 0, 0);
	//}
	//glTranslatef(0, -size * 0.5, 0);
	//glScalef(0.2, 1, 0.2);
	//glutSolidCube(size);
	//glPopMatrix();

	////胳膊
	//glColor3f(0.4, 0.1 ,0);
	//glPushMatrix();
	//glTranslatef(size * 0.5, -size * 0.7, 0);
	//glRotatef(8, 0, 0, 1);
	//if(type == 0)
	//{
	//	glRotatef(40, 1, 0, 0);
	//}
	//else if(type == 1)
	//{
	//	glRotatef(20, 1, 0, 0);
	//}
	//else if (type == 2)
	//{
	//	glRotatef(0, 1, 0, 0);
	//}
	//else if(type == 3)
	//{
	//	glRotatef(-20, 1, 0, 0);
	//}
	//else if (type == 4)
	//{
	//	glRotatef(-40, 1, 0, 0);
	//}
	//else if (type == 5)
	//{
	//	glRotatef(-20, 1, 0, 0);
	//}
	//else if (type == 6)
	//{
	//	glRotatef(0, 1, 0, 0);
	//}
	//else
	//{
	//	glRotatef(20, 1, 0, 0);
	//}
	//glTranslatef(0, -size * 0.5, 0);
	//glScalef(0.2, 1, 0.2);
	//glutSolidCube(size);
	//glPopMatrix();

	////腿
	//glColor3f(1, 0, 1);
	//glPushMatrix();
	//glTranslatef(-size * 0.2, -size * 1.5, 0);
	//if(type == 0)
	//{
	//	glRotatef(10, 1, 0, 0);
	//}
	//else if(type == 1)
	//{
	//	glRotatef(5, 1, 0, 0);
	//}
	//else if (type == 2)
	//{
	//	glRotatef(0, 1, 0, 0);
	//}
	//else if(type == 3)
	//{
	//	glRotatef(-5, 1, 0, 0);
	//}
	//else if (type == 4)
	//{
	//	glRotatef(-10, 1, 0, 0);
	//}
	//else if (type == 5)
	//{
	//	glRotatef(-5, 1, 0, 0);
	//}
	//else if (type == 6)
	//{
	//	glRotatef(0, 1, 0, 0);
	//}
	//else
	//{
	//	glRotatef(5, 1, 0, 0);
	//}
	//glTranslatef(0, -size * 0.5, 0);
	//glScalef(0.2, 1, 0.2);
	//glutSolidCube(size);
	//glPopMatrix();

	////腿
	//glColor3f(1, 0, 1);
	//glPushMatrix();
	//glTranslatef(size * 0.2, -size * 1.5, 0);
	//if(type == 0)
	//{
	//	glRotatef(-10, 1, 0, 0);
	//}
	//else if(type == 1)
	//{
	//	glRotatef(-5, 1, 0, 0);
	//}
	//else if (type == 2)
	//{
	//	glRotatef(0, 1, 0, 0);
	//}
	//else if(type == 3)
	//{
	//	glRotatef(5, 1, 0, 0);
	//}
	//else if (type == 4)
	//{
	//	glRotatef(10, 1, 0, 0);
	//}
	//else if (type == 5)
	//{
	//	glRotatef(5, 1, 0, 0);
	//}
	//else if (type == 6)
	//{
	//	glRotatef(0, 1, 0, 0);
	//}
	//else
	//{
	//	glRotatef(-5, 1, 0, 0);
	//}
	//glTranslatef(0, -size * 0.5, 0);
	//glScalef(0.2, 1, 0.2);
	//glutSolidCube(size);
	//glPopMatrix();
	//glPopMatrix();
	//glPopAttrib();
}

/**
* \brief 绘制小飞船
*/
void CMyOpenGL::DrawUfo()
{
	//glPushAttrib(GL_ENABLE_BIT|GL_POLYGON_BIT);
	//glFrontFace(GL_CCW);
	//glEnable(GL_CULL_FACE);
	//int size = 1;
	//glPushMatrix();
	//glColor3f(1, 1, 1);
	//glScalef(0.4f, 0.5f, 1.5f);
	////glutSolidSphere(1.0f * size, 100, 100);
	//DrawBall(1.0 * size, 100, 100);
	////DrawBox(1.0 * size);
	//glPopMatrix();
	//glPushMatrix();
	//glScalef(2.2f, 0.08f, 0.2f);
	//glutSolidCube(1 * size);
	//glPopMatrix();
	//glColor3f(1, 0, 0);
	//glPushMatrix();
	//glTranslatef(1.1f * size, 0, 0);
	//glScalef(0.4f, 0.5f, 1.5f);
	//glutSolidSphere(0.2f * size, 100, 100);
	//glPopMatrix();
	//glColor3f(0, 1, 0);
	//glPushMatrix();
	//glTranslatef(-1.1f * size, 0, 0);
	//glScalef(0.4f, 0.5f, 1.5f);
	//glutSolidSphere(0.2f * size, 100, 100);
	//glPopMatrix();
	//glColor3f(0.5, 1.5, 0);
	//glPushMatrix();
	//glTranslatef(0, 0, 1.5f * size);
	//glScalef(1.1f, 0.04f, 0.1f);
	//glutSolidCube(1 * size);
	//glPopMatrix();
	//glColor3f(1.5, 0.5, 0);
	//glPushMatrix();
	//glTranslatef(0, 0, 1.5f * size);
	//glRotatef(90, 0, 0, 1);
	//glScalef(1.1f, 0.04f, 0.1f);
	//glutSolidCube(1 * size);
	//glPopMatrix();
	//glPopAttrib();
}
