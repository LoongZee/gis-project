
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// sunflower.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

CConOperation Operation;
SeqStack<GeoPoint> s_point;
SeqStack<GeoLine> s_line;
SeqStack<GeoCircle> s_Circle;
SeqStack<GeoNote> s_note;
SeqStack<GeoLayer> s_layer;
CRect rect_point;
CRect rect_note;
CPoint m_startp,m_lastp;
GeoPoint selectpoint,m_pointMouse;
GeoLine selectline,m_lineMouse;
GeoCircle selectcircle,m_circleMouse;
GeoNote selectnote,m_noteMouse;
GeoLayer importlayer;
bool Isselectpoint;
bool Isselectline;
bool Isselectcircle;
bool Isselectnote;
bool m_delete;
bool m_bLBtnDown;
int  tag,tag_linecut=1,tag_Dlinetopoint=1;
int  list;
int  editlayer=-1;


