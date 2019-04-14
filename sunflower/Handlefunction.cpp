#include "StdAfx.h"
#include "Handlefunction.h"

double PointToPoint(double x1,double y1,double x2,double y2) //�õ������ľ���
{
return sqrt(pow((x1-x2),2)+pow((y1-y2),2));
}


//��P���߶ε���̾����߶����˵�ֱ�ΪA(x1,y1)��B(x2,y2)
double PointToLine(CPoint point,double x1,double y1,double x2,double y2)
{
	double a,b,c,ang_A,ang_B;
	a=PointToPoint(point.x,point.y,x1,y1);    //PA�ĳ���
	b=PointToPoint(point.x,point.y,x2,y2);    //PB�ĳ���
	c=PointToPoint(x1,y1,x2,y2);              //AB�ĳ���
	ang_A=(pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c);  //��A��cosֵ
	ang_B=(pow(a,2)+pow(c,2)-pow(b,2))/(2*a*c);  //��B��cosֵ
	if (int(c)==int(a+b))                       //��P��AB��
		return 0.0;
	else 
	{
		if (ang_A<=0||ang_B<=0)                 //���P��AB�ļн�Ϊ��ǻ�P��AB�ӳ����ϣ�ȡab�н�С��
			return 100.0;
		else                                   //���P��AB�ļн�Ϊ�۽�ȡP��AB�Ĵ��ߵĳ���
			return b*sqrt(1-pow(ang_B,2));
	}
}


bool OnMouseSelectLine(CPoint point, GeoLine &line)
{
	for (int i=0;i<line.getSize()-1;i++)
	{
		if (PointToLine(point,line.data[i].x,line.data[i].y,line.data[i+1].x,line.data[i+1].y)<5.0)
		{
			return true;
		}	
	}	
		return false;
}


//����������
double GetQuadrantAngle(double x1,double y1, double x2,double y2)//�����������޽�
{
	double x = x2 - x1;
	double y = y2 - y1;
	double theta = atan(y/x);
	if (x > 0 && y < 0) return -theta;
	if (x > 0 && y > 0) return PI * 2 - theta;
	if (x < 0 && y < 0) return -theta + PI;
	if (x < 0 && y > 0) return -theta + PI;
	return theta;
}


CPoint * GetPolygon(double x1, double y1, double x2, double y2,int r)//���ĸ����������
{
	CPoint *temp = new CPoint[4];
	double theta = GetQuadrantAngle(x1, y1, x2, y2) ;
	if (theta<PI/2){
		temp[0].x =long( x2 + r*sin(theta));
		temp[0].y =long( y2 + r*cos(theta));
		temp[1].x =long( x2 - r*sin(theta));
		temp[1].y =long( y2 - r*cos(theta));
		temp[2].x =long( x1 - r*sin(theta));
		temp[2].y =long( y1 - r*cos(theta));
		temp[3].x =long( x1 + r*sin(theta));
		temp[3].y =long( y1 + r*cos(theta));
	}
	else if (PI / 2 < theta && theta < PI){
		temp[0].x = long(x2 + r*sin(PI - theta));
		temp[0].y =long( y2 - r*cos(PI-theta));
		temp[1].x =long( x1 + r*sin(PI-theta));
		temp[1].y =long( y1 - r*cos(PI-theta));
		temp[2].x =long( x1 - r*sin(PI-theta));
		temp[2].y =long( y1 + r*cos(PI-theta));
		temp[3].x =long( x2 - r*sin(PI-theta));
		temp[3].y =long( y2 + r*cos(PI-theta));
	}
	else if (1.5*PI < theta && theta< 2*PI){
		temp[0].x =long( x1 + r*sin(2*PI-theta));
		temp[0].y =long( y1 - r*cos(2*PI-theta));
		temp[1].x = long(x1 - r*sin(2 * PI - theta));
		temp[1].y = long(y1 + r*cos(2 * PI - theta));
		temp[2].x = long(x2 - r*sin(2 * PI - theta));
		temp[2].y = long(y2 + r*cos(2 * PI - theta));
		temp[3].x = long(x2 + r*sin(2 * PI - theta));
		temp[3].y = long(y2 - r*cos(2 * PI - theta));
	}
	else if (PI < theta && theta < 1.5*PI){
		temp[0].x = long(x2 + r*sin(theta - PI));
		temp[0].y =long( y2 + r*cos(theta-PI));
		temp[1].x =long( x1 + r*sin(theta-PI));
		temp[1].y =long( y1 + r*cos(theta-PI));
		temp[2].x = long(x1 - r*sin(theta - PI));
		temp[2].y =long( y1 - r*cos(theta-PI));
		temp[3].x = long(x2 - r*sin(theta - PI));
		temp[3].y =long( y2 - r*cos(theta-PI));
	}
	return  temp;
}

bool OnMouseSelectcircle01(long x1,long y1,long x2,long y2,long x3,long y3)
{
	long x=(x1-x2)*(x1-x3);
	long y=(y1-y2)*(y1-y3);
	if(x<=0&&y<=0)
	{
		return true;
	}
	else return false;
}


bool OnMouseDelete(long x1,long y1,long x2,long y2,long x3,long y3)
{
	long x=(x1-x2)*(x1-x3);
	long y=(y1-y2)*(y1-y3);
	if(x<=0&&y<=0)
	{
		return false;
	}
	else return true;
}

int OnMouseSelectcircle2(long nvert,GeoCircle &circle ,long testx,long testy)
{
    int i, j, c = 0;
    for(i=0,j=nvert-1;i<nvert;j=i++) {
		if (((circle.data[i].y>testy)!=(circle.data[j].y>testy))&&(testx<(circle.data[j].x-circle.data[i].x)*(testy-circle.data[i].y)/(circle.data[j].y-circle.data[i].y)+circle.data[i].x))
            c = !c;
    }
    return c;
}

CPoint GetOtherPoint(CRect &rt,CPoint &point)  
{  
	long x = 0;  
	long y = 0;  
	if (rt.left == point.x)  
	{  
		x = rt.right;  
	}  
	else  
	{  
		x = rt.left;  
	}  
	if (rt.top == point.y)  
	{  
		y = rt.bottom ;  
	}  
	else  
	{  
		y = rt.top;  
	}  
	return CPoint(x,y);  
}  
