#pragma once
#include "Connection.h"
class CConOperation
{
public:
	CConOperation(void);
    virtual ~CConOperation(void);
	void Connectiondb();
	void DisConnectiondb();
	//�����
	int addPoint(GeoPoint &point);
	void modifyPoint(GeoPoint &point);
    void deletePoint(GeoPoint &point);
	//�߲���
	int addLine(GeoLine &line);
	void modifyLine(GeoLine &line);
    void deleteLine(GeoLine &line);

	//�����
	int addCircle(GeoCircle &circle);
	void modifyCircle(GeoCircle &circle);
    void deleteCircle(GeoCircle &circle);

	//ע�ǲ���
	int addNote(GeoNote &note);
	void modifyNote(GeoNote &note);
    void deleteNote(GeoNote &note);

	//ͼ�����
	int addlayer(GeoLayer &layer);
	void deletelayer(GeoLayer &layer);
	vector<GeoLayer> selectlayer();
	void importlayer(GeoLayer &layer);

private:
	CConnection con;
	_RecordsetPtr pRec;
};

