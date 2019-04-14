#pragma once
#include "Connection.h"
class CConOperation
{
public:
	CConOperation(void);
    virtual ~CConOperation(void);
	void Connectiondb();
	void DisConnectiondb();
	//点操作
	int addPoint(GeoPoint &point);
	void modifyPoint(GeoPoint &point);
    void deletePoint(GeoPoint &point);
	//线操作
	int addLine(GeoLine &line);
	void modifyLine(GeoLine &line);
    void deleteLine(GeoLine &line);

	//面操作
	int addCircle(GeoCircle &circle);
	void modifyCircle(GeoCircle &circle);
    void deleteCircle(GeoCircle &circle);

	//注记操作
	int addNote(GeoNote &note);
	void modifyNote(GeoNote &note);
    void deleteNote(GeoNote &note);

	//图层操作
	int addlayer(GeoLayer &layer);
	void deletelayer(GeoLayer &layer);
	vector<GeoLayer> selectlayer();
	void importlayer(GeoLayer &layer);

private:
	CConnection con;
	_RecordsetPtr pRec;
};

