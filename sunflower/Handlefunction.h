#pragma once

#include "math.h"

const double PI=3.1415926;

//�����ߺ���
double PointToPoint(double x1,double y1,double x2,double y2);  //�õ������ľ���
double PointToLine(CPoint point,double x1,double y1,double x2,double y2);
bool OnMouseSelectLine(CPoint point, GeoLine &line);

//����������
double GetQuadrantAngle(double x1,double y1, double x2,double y2);//�����������޽�
CPoint * GetPolygon(double x1, double y1, double x2, double y2,int r);


bool OnMouseSelectcircle01(long x1,long y1,long x2,long y2,long x3,long y3);

int OnMouseSelectcircle2(long nvert,GeoCircle &circle ,long testx,long testy);

bool OnMouseDelete(long x1,long y1,long x2,long y2,long x3,long y3);


CPoint GetOtherPoint(CRect &rt,CPoint &point);
