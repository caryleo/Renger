#include "StdAfx.h"
#include "MyOpenGL.h"

#include <cmath>
#include <iostream>
#define POINTNUM 200
#define CIRCLENUM 20
#define PI 3.1415926
#define BMP_Header_Length 54  //ͼ���������ڴ���е�ƫ����  
CModelLoader m_loader_car;
CModelLoader m_loader_lupai;
CModelLoader m_loader_yuaubao;
CModelLoader m_loader_hulan;
CModelLoader m_loader_fangwu;
CModelLoader m_loader_fangwu2;
CModelLoader m_loader_luren;
CModelLoader m_loader_lupai4;
CModelLoader m_loader_shu;
GLuint texRoad;//��·����
double start,stop;//��ʼʱ�䣬����ʱ��
struct Hulan
{
	double x,z,rotate;
}hulan[100];
int hulanCnt=0;

CMyOpenGL::CMyOpenGL(void)
{
} 


CMyOpenGL::~CMyOpenGL(void)
{
}


/**
* \brief ��ʼ��
*/
void CMyOpenGL::PostInit(void)
{
	start=time(NULL);
	texRoad = load_texture("Data/road.bmp");
	m_loader_lupai.Init(3);//·��
	m_loader_car.Init(2);//����
	m_loader_lupai4.Init(4);//·��4
	m_loader_luren.Init(5);//·��
	m_loader_yuaubao.Init(11);//Ԫ��
	m_loader_hulan.Init(10);//����
	m_loader_fangwu.Init(9);//����
	m_loader_fangwu2.Init(8);//����2
	m_loader_shu.Init(1);//��
	pCar->init(Point_AABB(0,0,500,4,4,8,0,0,-1),0);//��ʼ��������
	pCar->setGothicTrans_car(
		0, 0 , 400,   
		0.00003 , 0.00003 , 0.00003 ,      
		0 , 0 , 0 , 0);

	pCar->addWall(50,-20,450,50,380,350);
	pCar->addWall(50,-20,350,450,380,350);
	pCar->addWall(450,-20,350,450,380,-200);
	pCar->addWall(450,-20,-200,250,380,-200);
	pCar->addWall(250,-20,-200,250,380,-450);
	pCar->addWall(250,-20,-450,-350,380,-450);
	pCar->addWall(-350,-20,-450,-350,380,100);
	pCar->addWall(-350,-20,100,-250,380,100);
	pCar->addWall(-250,-20,100,-250,380,450);
	pCar->addWall(-250,-20,450,50,380,450);

	pCar->addWall(-50,-20,350,-50,380,250);
	pCar->addWall(-50,-20,250,350,380,250);
	pCar->addWall(350,-20,250,350,380,-100);
	pCar->addWall(350,-20,-100,150,380,-100);
	pCar->addWall(150,-20,-100,150,380,-350);
	pCar->addWall(150,-20,-350,-250,380,-350);
	pCar->addWall(-250,-20,-350,-250,380,0);
	pCar->addWall(-250,-20,0,-150,380,0);
	pCar->addWall(-150,-20,0,-150,380,350);
	pCar->addWall(-150,-20,350,-50,380,350);

	pCar->addYuanbao(0,300);
	pCar->addYuanbao(150,300);
	pCar->addYuanbao(400,300);
	pCar->addYuanbao(400,50);
	pCar->addYuanbao(300,-150);
	pCar->addYuanbao(-300,-250);
	pCar->addYuanbao(-200,50);
	pCar->addYuanbao(-200,400);

	pCamera->SetGameMode(1);
}


/**
* \brief ��������
*/
void CMyOpenGL::changeGothicTrans(float trans[],double x,double y,double z,double a,double b,double c,double r,double _x,double _y,double _z)
{
	trans[0]=x;trans[1]=y;trans[2]=z;
	trans[3]=a;trans[4]=b;trans[5]=c;
	trans[6]=r;trans[7]=_x;trans[8]=_y;trans[9]=_z;
}
void CMyOpenGL::hulanInit()
{
	hulanCnt=0;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=50;hulan[hulanCnt++].z=400;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=100;hulan[hulanCnt++].z=350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=200;hulan[hulanCnt++].z=350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=300;hulan[hulanCnt++].z=350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=400;hulan[hulanCnt++].z=350;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=300;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=200;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=0;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=-100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=450;hulan[hulanCnt++].z=-200;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=400;hulan[hulanCnt++].z=-200;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=300;hulan[hulanCnt++].z=-200;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=250;hulan[hulanCnt++].z=-250;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=250;hulan[hulanCnt++].z=-350;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=250;hulan[hulanCnt++].z=-450;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=200;hulan[hulanCnt++].z=-450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=100;hulan[hulanCnt++].z=-450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=0;hulan[hulanCnt++].z=-450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-100;hulan[hulanCnt++].z=-450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-200;hulan[hulanCnt++].z=-450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-300;hulan[hulanCnt++].z=-450;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=-400;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=-300;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=-200;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=-100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=0;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-350;hulan[hulanCnt++].z=50;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-300;hulan[hulanCnt++].z=100;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=150;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=250;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=350;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=450;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-200;hulan[hulanCnt++].z=450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-100;hulan[hulanCnt++].z=450;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=0;hulan[hulanCnt++].z=450;

	/*********************************************************/
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-50;hulan[hulanCnt++].z=300;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=0;hulan[hulanCnt++].z=250;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=100;hulan[hulanCnt++].z=250;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=200;hulan[hulanCnt++].z=250;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=300;hulan[hulanCnt++].z=250;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=350;hulan[hulanCnt++].z=200;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=350;hulan[hulanCnt++].z=100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=350;hulan[hulanCnt++].z=0;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=350;hulan[hulanCnt++].z=-50;


	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=300;hulan[hulanCnt++].z=-100;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=200;hulan[hulanCnt++].z=-100;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=150;hulan[hulanCnt++].z=-150;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=150;hulan[hulanCnt++].z=-250;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=150;hulan[hulanCnt++].z=-300;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=100;hulan[hulanCnt++].z=-350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=0;hulan[hulanCnt++].z=-350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-100;hulan[hulanCnt++].z=-350;
	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-200;hulan[hulanCnt++].z=-350;


	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=-300;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=-200;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=-100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=-100;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-250;hulan[hulanCnt++].z=-50;


	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-200;hulan[hulanCnt++].z=0;

	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-150;hulan[hulanCnt++].z=50;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-150;hulan[hulanCnt++].z=150;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-150;hulan[hulanCnt++].z=250;
	hulan[hulanCnt].rotate=90;hulan[hulanCnt].x=-150;hulan[hulanCnt++].z=300;

	hulan[hulanCnt].rotate=0;hulan[hulanCnt].x=-100;hulan[hulanCnt++].z=350;

}
void CMyOpenGL::drawHulan()
{
	hulanInit();
	float gothicTrans_hulan[10];
	for(int i=0;i<hulanCnt;i++)
	{
		changeGothicTrans(gothicTrans_hulan,
			hulan[i].x,-20, hulan[i].z , //��ʾ����������λ��  
			0.18, 0.18, 0.18 ,      //��ʾxyz�Ŵ���  
			hulan[i].rotate, 0 , 1 , 0  //��ʾ��ת  
			);
		m_loader_hulan.DrawModel(gothicTrans_hulan);
	}
}

void CMyOpenGL::InDraw(void)
{
	
	glPushMatrix();
	pScene->Render();
	glPopMatrix();
	DrawAxes(1000);
	
	glPushMatrix();
	float gothicTrans_fangwu[10] = { 
		100,-10, 200 , //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		180 , 0 , 1 , 0  //��ʾ��ת  
	};
	m_loader_fangwu.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		150,-10, 400 , //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		90 , 0 , 1 , 0  //��ʾ��ת  
		);
	m_loader_fangwu2.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		-300,-10, 250 , //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		-90 , 0 , 1 , 0  //��ʾ��ת  
		);
	m_loader_fangwu.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		-150,-10, -250 , //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		0 , 0 , 1 , 0  //��ʾ��ת  
		);
	m_loader_fangwu.DrawModel(gothicTrans_fangwu);
	changeGothicTrans(gothicTrans_fangwu,
		100,-10, -250 , //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		90 , 0 , 1 , 0  //��ʾ��ת  
		);

	m_loader_fangwu2.DrawModel(gothicTrans_fangwu);

	float gothicTransLupai4[10] = { 
		450,0 , -50, //��ʾ����������λ��  
		0.2, 0.1, 0.1 ,      //��ʾxyz�Ŵ���  
		0 , 0 , 1 , 0  //��ʾ��ת  
	};
	m_loader_lupai4.DrawModel(gothicTransLupai4);

	float gothicTransLuren[10] = { 
		-100,0 , 200, //��ʾ����������λ��  
		0.2, 0.2, 0.2 ,      //��ʾxyz�Ŵ���  
		0 , 0 , 1 , 0  //��ʾ��ת  
	};
	m_loader_luren.DrawModel(gothicTransLuren);

	float gothicTrans_shu[10]={
		-120, 0, 200,
		0.2, 0.2, 0.2,
		0, 0, 1 ,0
	};
	m_loader_shu.DrawModel(gothicTrans_shu);

	float gothicTrans_Lupai[10]={
		0,-5 , -50, //��ʾ����������λ��  
		0.08, 0.08, 0.8 ,      //��ʾxyz�Ŵ���  
		0 , 0 , 1 , 0  //��ʾ��ת  
	};
	m_loader_lupai.DrawModel(gothicTrans_Lupai);

    glPopMatrix();

	glPushMatrix();
	pCar->car_box.DrawAABBBoundingBox();//�������İ�Χ��
	glPushMatrix();
	CString tmp;
	tmp.Format("���С��ʱ��");
	CVector966 tmpPos(float(pCar->car_point.x), float(pCar->car_point.y) + 2, float(pCar->car_point.z));
	CString Score;
	Score.Format("��ǰ������ %d",pCar->score);
	pFont->Font2D(Score, CVector966(-0.9, 0.4, 0), 24, RGB(255, 255, 255), 0|8 , 0);
	stop=time(NULL);
	double durationTime = (double)difftime(stop, start);
	CString nowTime;
	nowTime.Format("��ǰʱ��: %.2f s",durationTime);
	pFont->Font2D(nowTime, CVector966(-0.9, 0.2, 0), 24, RGB(255, 255, 255), 0|8 , 0);
	CString pos;
	pos.Format("��ǰ��λ�ã���%.2lf��%.2lf��%.2lf��", pCar->car_point.x, pCar->car_point.y, pCar->car_point.z);
	pFont->Font2D(pos, CVector966(-0.9, 0.8, 0), 24, RGB(255, 255, 255), 0|8 , 0);
	CString dir;
	dir.Format("��ǰ��ͷ���򣺣�%.2lf��%.2lf��%.2lf��", pCar->car_point.dirx, pCar->car_point.diry, pCar->car_point.dirz);
	pFont->Font2D(dir, CVector966(-0.9, 0.6, 0), 24, RGB(255, 255, 255), 0|8 , 0);
	pFont->Font2D(tmp, tmpPos, 24, RGB(255,255,255), DT_CENTER | DT_BOTTOM, 1);
	m_loader_car.DrawModel(pCar->gothicTrans_car);
	glPopMatrix();

	for (int i=0;i<pCar->wall.size();i++)
	{
		pCar->wall[i].DrawAABBBoundingBox();
	}

	//��Ԫ��
	float gothicTrans_yuanbao[10];
	for (int i=0;i<pCar->yuanbao.size();i++)
	{
		if(pCar->yuanbaoFlag[i]!=1)
		{
			pCar->yuanbao[i].DrawAABBBoundingBox();
			changeGothicTrans(gothicTrans_yuanbao,
				(pCar->yuanbao[i].Xmax+pCar->yuanbao[i].Xmin)/2,0 ,(pCar->yuanbao[i].Zmax+pCar->yuanbao[i].Zmin)/2, 
				0.2,0.2, 0.2 ,      //��ʾxyz�Ŵ���  
				0 , 0 , 1 , 0  //��ʾ��ת  
				);
			m_loader_yuaubao.DrawModel(gothicTrans_yuanbao);
		}
	}
	
	//drawHulan();//������
	drawAllRoad();
	CString str;
	str.Format("fps: %.2f ֡ÿ��", fps);
	pFont->Font2D(str, CVector966(-0.9f, 0.9f, 0), 24, RGB(255, 255, 255), 0|8 , 0);
	CString sp;
	sp.Format("��ǰ�ٶȣ�%.2lf m/s", pCar->speed);
	pFont->Font2D(sp, CVector966(-0.9f, 0.7f, 0), 24, RGB(255, 255, 255), 0|8 , 0);
	glPopMatrix();
	
}


bool CMyOpenGL::OnKey(unsigned char nChar, bool bDown)
{
	return false;
}

/**
* \brief ��������
*/
void CMyOpenGL::Update()
{
	pCar->update();
}

/**
 * \brief ����������
 */
void CMyOpenGL::DrawAxes(int size)
{
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, size);
	glEnd();
	glPopMatrix();
	glPopAttrib();
}


//�������
// ����power_of_two�����ж�һ�������ǲ���2����������  
int CMyOpenGL::power_of_two(int n)  
{  
    if( n <= 0 )  
        return 0;  
    return (n & (n-1)) == 0;  
}  
  
/* ����load_texture 
* ��ȡһ��BMP�ļ���Ϊ���� 
* ���ʧ�ܣ�����0������ɹ������������� 
*/  
GLuint CMyOpenGL::load_texture(const char* file_name)  
{  
    GLint width, height, total_bytes;  
    GLubyte* pixels = 0;  
    GLuint last_texture_ID=0, texture_ID = 0;  
  
    // ���ļ������ʧ�ܣ�����  
    FILE* pFile = fopen(file_name, "rb");  
    if( pFile == 0 )  
        return 0;  
  
    // ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�  
    fseek(pFile, 0x0012, SEEK_SET);  
    fread(&width, 4, 1, pFile);  
    fread(&height, 4, 1, pFile);  
    fseek(pFile, BMP_Header_Length, SEEK_SET);  
  
    // ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���  
    {  
        GLint line_bytes = width * 3;  
        while( line_bytes % 4 != 0 )  
            ++line_bytes;  
        total_bytes = line_bytes * height;  
    }  
  
    // �����������ֽ��������ڴ�  
    pixels = (GLubyte*)malloc(total_bytes);  
    if( pixels == 0 )  
    {  
        fclose(pFile);  
        return 0;  
    }  
  
    // ��ȡ��������  
    if( fread(pixels, total_bytes, 1, pFile) <= 0 )  
    {  
        free(pixels);  
        fclose(pFile);  
        return 0;  
    }  
  
    // �Ծ;ɰ汾�ļ��ݣ����ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������  
    // ��ͼ���߳�����OpenGL�涨�����ֵ��Ҳ����  
    {  
        GLint max;  
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);  
        if( !power_of_two(width)  
            || !power_of_two(height)  
            || width > max  
            || height > max )  
        {  
            const GLint new_width = 256;  
            const GLint new_height = 256; // �涨���ź��µĴ�СΪ�߳���������  
            GLint new_line_bytes, new_total_bytes;  
            GLubyte* new_pixels = 0;  
  
            // ����ÿ����Ҫ���ֽ��������ֽ���  
            new_line_bytes = new_width * 3;  
            while( new_line_bytes % 4 != 0 )  
                ++new_line_bytes;  
            new_total_bytes = new_line_bytes * new_height;  
  
            // �����ڴ�  
            new_pixels = (GLubyte*)malloc(new_total_bytes);  
            if( new_pixels == 0 )  
            {  
                free(pixels);  
                fclose(pFile);  
                return 0;  
            }  
  
            // ������������  
            gluScaleImage(GL_RGB,  
                width, height, GL_UNSIGNED_BYTE, pixels,  
                new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);  
  
            // �ͷ�ԭ�����������ݣ���pixelsָ���µ��������ݣ�����������width��height  
            free(pixels);  
            pixels = new_pixels;  
            width = new_width;  
            height = new_height;  
        }  
    }  
  
    // ����һ���µ�������  
    glGenTextures(1, &texture_ID);  
    if( texture_ID == 0 )  
    {  
        free(pixels);  
        fclose(pFile);  
        return 0;  
    }  
  
    // ���µ������������������������  
    // �ڰ�ǰ���Ȼ��ԭ���󶨵������ţ��Ա��������лָ�  
    GLint lastTextureID=last_texture_ID;  
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);  
    glBindTexture(GL_TEXTURE_2D, texture_ID);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);  
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,  
        GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);  
    glBindTexture(GL_TEXTURE_2D, lastTextureID);  //�ָ�֮ǰ�������  
    free(pixels);  
    return texture_ID;  
}  

void CMyOpenGL::drawRoad(double x,double z)
{
	glBegin(GL_QUADS);  
    // ����  
    glTexCoord2f(0.0f, 1); glVertex3f(x,  -2, z-100);  // ������ı��ε�����  
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x,  -2,  z);  // ������ı��ε�����  
    glTexCoord2f(1, 0.0f); glVertex3f( x+100,  -2,  z);  // ������ı��ε�����  
    glTexCoord2f(1, 1); glVertex3f( x+100,  -2, z-100);  // ������ı��ε�����  
    glEnd();  
}
void CMyOpenGL::drawAllRoad()
{
	int xx[100]={0};
	int zz[100]={0};
	int tmpcnt=0;
	xx[tmpcnt]=-50;zz[tmpcnt++]=450;
	xx[tmpcnt]=-50;zz[tmpcnt++]=350;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texRoad);
	for(int i=0;i<tmpcnt;i++)
	{
		drawRoad(xx[i],zz[i]);
	}
	glDisable(GL_TEXTURE_2D);
}