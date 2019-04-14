

#pragma once
#include <vector>
using namespace std;


struct GeoPoint
{
    CPoint mpoint;
    int type;
	COLORREF color;//ÑÕÉ«
	int layer;
	int id;
};

struct GeoLine
{
	int getSize()const{
		return data.size();
	}
	void Push(const CPoint &x){
	data.push_back(x); 
	};
	int id;
	vector<CPoint> data;
	int type;
	int width;
	COLORREF color;
	int layer;
};

struct GeoCircle
{
    int getSize()const{
		return data.size();
	}
	void Push(const CPoint &x){
	data.push_back(x); 
	};
	int id;
	vector<CPoint> data;
	int type;
	COLORREF color;//ÑÕÉ«
	int layer;
};

struct GeoNote
{
	int id;
    CString mnote;
	CPoint mpoint;
	COLORREF color;//ÑÕÉ«
	int layer;
};



struct GeoLayer
{
    CString Layername;
	int id;
	int mtype;
	BOOL isshow;
	BOOL isedit;
};
