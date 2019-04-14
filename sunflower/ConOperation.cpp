#include "StdAfx.h"
#include "ConOperation.h"


CConOperation::CConOperation(void)
{
	
}

void CConOperation::Connectiondb()
{
	con.Initial("DESKTOP-FSHJEDI\\SQLEXPRESS01","sunflower_gis","sa","123456");
}

void CConOperation::DisConnectiondb()
{
	//if (con.m_pRecordset != NULL)
	//	con.m_pRecordset->Close();
	//如果正在连接数据库，则断开
	//if(con.m_pConnection->State)
	//{
	//	con.m_pConnection->Close();
	//	con.m_pConnection.Release();
	//}
	//con.m_pConnection=NULL;
	//con.m_pRecordset=NULL;
	//::CoUninitialize(); 
}

CConOperation::~CConOperation(void)
{
}

int CConOperation::addPoint(GeoPoint &point)
{
	CString sql;
	sql.Format(_T("insert into Point(point_id,point_x,point_y,point_colorr,point_colorg,point_colorb,point_type,point_layer) values ('%d','%f','%f','%d','%d','%d','%d','%d');"),-1,float(point.mpoint.x),float(point.mpoint.y),GetRValue(point.color),GetGValue(point.color),GetBValue(point.color),point.type,point.layer);
	con.ExecuteSQL(sql.GetBuffer(0));
	sql="select MAX(point_id)+1 as point_id from Point;";
	pRec=con.Query(sql.GetBuffer(0));
	_variant_t t_ID;
	t_ID = pRec->GetCollect("point_id");
	sql.Format(_T("UPDATE Point set point_id='%d' where point_id=-1;"),int(t_ID));
	con.ExecuteSQL(sql.GetBuffer(0));
	return t_ID;
}


void CConOperation::modifyPoint(GeoPoint &point)
{
	CString sql;
	sql.Format(_T("select * from Point where point_id='%d';"),int(point.id));
	pRec=con.Query(sql.GetBuffer(0));
	pRec->PutCollect("point_colorr",GetRValue(point.color));
	pRec->PutCollect("point_colorg",GetGValue(point.color));
	pRec->PutCollect("point_colorb",GetBValue(point.color));
	pRec->PutCollect("point_x",point.mpoint.x);
	pRec->PutCollect("point_y",point.mpoint.y);
	pRec->PutCollect("point_type",point.type);
	pRec->PutCollect("point_layer",point.layer);
	pRec->Update();
}
void CConOperation::deletePoint(GeoPoint &point)
{
	CString sql;
	sql.Format(_T("delete from Point where point_id='%d';"),point.id);
	con.ExecuteSQL(sql.GetBuffer(0));
}


int CConOperation::addlayer(GeoLayer &layer)
{
	CString sql;
	sql.Format(_T("insert into layer(layer_id,layer_name,layer_type) values ('%d','%s','%d');"),-1,layer.Layername,layer.mtype);
	con.ExecuteSQL(sql.GetBuffer(0));
	sql="select MAX(layer_id)+1 as layer_id from layer;";
	pRec=con.Query(sql.GetBuffer(0));
	_variant_t t_ID;
	t_ID = pRec->GetCollect("layer_id");
	sql.Format(_T("UPDATE layer set layer_id='%d' where layer_id=-1;"),int(t_ID));
	con.ExecuteSQL(sql.GetBuffer(0));
	return t_ID;
}


void CConOperation::deletelayer(GeoLayer &layer)
{
	CString sql;
	sql.Format(_T("delete from layer where layer_id='%d';"),layer.id);
	con.ExecuteSQL(sql.GetBuffer(0));
}


int CConOperation::addLine(GeoLine &line)
{
	CString sql;
	sql.Format(_T("insert into Line(line_id,line_type,line_width,line_layer,line_colorr,line_colorg,line_colorb) values ('%d','%d','%d','%d','%d','%d','%d');"),-1,line.type,line.width,line.layer,GetRValue(line.color),GetGValue(line.color),GetBValue(line.color));
	con.ExecuteSQL(sql.GetBuffer(0));
	sql="select MAX(line_id)+1 as line_id from Line;";
	pRec=con.Query(sql.GetBuffer(0));
	_variant_t t_ID;
	t_ID = pRec->GetCollect("line_id");
	sql.Format(_T("UPDATE Line set line_id='%d' where line_id=-1;"),int(t_ID));
	con.ExecuteSQL(sql.GetBuffer(0));
	sql.Format(_T("SELECT * FROM Line where line_id='%d';"),int(t_ID));
	pRec=con.Query(sql.GetBuffer(0));
	try
	{
		CMemFile memFile;
		CArchive ar(&memFile, CArchive::store);
		for(int i=0;i<line.getSize();i++)
		{
			ar.Write(&line.data[i],sizeof(CPoint));
		}
		ar.Close(); 
		
		DWORD dwSize = DWORD(memFile.GetLength());
		LPBYTE lpInfo = memFile.Detach();
 
		VARIANT varBLOB;
		SAFEARRAY *psa;
		SAFEARRAYBOUND rgsabound[1];
 
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = dwSize;
 
		psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
		for(long i = 0; i < (long)dwSize; i++)
		{
			SafeArrayPutElement (psa, &i, lpInfo++);
		}
		varBLOB.vt = VT_ARRAY | VT_UI1;
		varBLOB.parray = psa;
		pRec->GetFields()->GetItem("line_data")->AppendChunk(varBLOB);
		pRec->Update();

	}
	catch(_com_error &e)
	{
		CString str=e.Description();
		AfxMessageBox(str);
		return -1;
	}
	return t_ID;
}
void CConOperation::modifyLine(GeoLine &line)
{
	CString sql;
	sql.Format(_T("select * from Line where line_id='%d';"),int(line.id));
	pRec=con.Query(sql.GetBuffer(0));
		try
	{
		CMemFile memFile;
		CArchive ar(&memFile, CArchive::store);
		for(int i=0;i<line.getSize();i++)
		{
			ar.Write(&line.data[i],sizeof(CPoint));
		}
		ar.Close(); 
		
		DWORD dwSize = DWORD(memFile.GetLength());
		LPBYTE lpInfo = memFile.Detach();
 
		VARIANT varBLOB;
		SAFEARRAY *psa;
		SAFEARRAYBOUND rgsabound[1];
 
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = dwSize;
 
		psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
		for(long i = 0; i < (long)dwSize; i++)
		{
			SafeArrayPutElement (psa, &i, lpInfo++);
		}
		varBLOB.vt = VT_ARRAY | VT_UI1;
		varBLOB.parray = psa;
		pRec->GetFields()->GetItem("line_data")->AppendChunk(varBLOB);
		pRec->PutCollect("line_colorr",GetRValue(line.color));
		pRec->PutCollect("line_colorg",GetGValue(line.color));
		pRec->PutCollect("line_colorb",GetBValue(line.color));
		pRec->PutCollect("line_type",line.type);
		pRec->PutCollect("line_width",line.width);
		pRec->PutCollect("line_layer",line.layer);
		pRec->Update();
	}
	catch(_com_error &e)
	{
		CString str=e.Description();
		AfxMessageBox(str);
		return ;
	}
}
void CConOperation::deleteLine(GeoLine &line)
{
	CString sql;
	sql.Format(_T("delete from Line where line_id='%d';"),line.id);
	con.ExecuteSQL(sql.GetBuffer(0));
}

int CConOperation::addCircle(GeoCircle &circle)
{
	CString sql;
	sql.Format(_T("insert into Circle(circle_id,circle_type,circle_layer,circle_colorr,circle_colorg,circle_colorb) values ('%d','%d','%d','%d','%d','%d');"),-1,circle.type,circle.layer,GetRValue(circle.color),GetGValue(circle.color),GetBValue(circle.color));
	con.ExecuteSQL(sql.GetBuffer(0));
	sql="select MAX(circle_id)+1 as circle_id from Circle;";
	pRec=con.Query(sql.GetBuffer(0));
	_variant_t t_ID;
	t_ID = pRec->GetCollect("circle_id");
	sql.Format(_T("UPDATE Circle set circle_id='%d' where circle_id=-1;"),int(t_ID));
	con.ExecuteSQL(sql.GetBuffer(0));
	sql.Format(_T("SELECT * FROM Circle where circle_id='%d';"),int(t_ID));
	pRec=con.Query(sql.GetBuffer(0));
	try
	{
		CMemFile memFile;
		CArchive ar(&memFile, CArchive::store);
		for(int i=0;i<circle.getSize();i++)
		{
			ar.Write(&circle.data[i],sizeof(CPoint));
		}
		ar.Close(); 
		
		DWORD dwSize = DWORD(memFile.GetLength());
		LPBYTE lpInfo = memFile.Detach();
 
		VARIANT varBLOB;
		SAFEARRAY *psa;
		SAFEARRAYBOUND rgsabound[1];
 
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = dwSize;
 
		psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
		for(long i = 0; i < (long)dwSize; i++)
		{
			SafeArrayPutElement (psa, &i, lpInfo++);
		}
		varBLOB.vt = VT_ARRAY | VT_UI1;
		varBLOB.parray = psa;
		pRec->GetFields()->GetItem("circle_data")->AppendChunk(varBLOB);
		pRec->Update();
	}
	catch(_com_error &e)
	{
		CString str=e.Description();
		AfxMessageBox(str);
		return -1;
	}
	return t_ID;
}
void CConOperation::modifyCircle(GeoCircle &circle)
{
	CString sql;
	sql.Format(_T("select * from Circle where circle_id='%d';"),int(circle.id));
	pRec=con.Query(sql.GetBuffer(0));
		try
	{
		CMemFile memFile;
		CArchive ar(&memFile, CArchive::store);
		for(int i=0;i<circle.getSize();i++)
		{
			ar.Write(&circle.data[i],sizeof(CPoint));
		}
		ar.Close(); 
		
		DWORD dwSize = DWORD(memFile.GetLength());
		LPBYTE lpInfo = memFile.Detach();
 
		VARIANT varBLOB;
		SAFEARRAY *psa;
		SAFEARRAYBOUND rgsabound[1];
 
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = dwSize;
 
		psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
		for(long i = 0; i < (long)dwSize; i++)
		{
			SafeArrayPutElement (psa, &i, lpInfo++);
		}
		varBLOB.vt = VT_ARRAY | VT_UI1;
		varBLOB.parray = psa;
		pRec->GetFields()->GetItem("circle_data")->AppendChunk(varBLOB);
		pRec->PutCollect("circle_colorr",GetRValue(circle.color));
		pRec->PutCollect("circle_colorg",GetGValue(circle.color));
		pRec->PutCollect("circle_colorb",GetBValue(circle.color));
		pRec->PutCollect("circle_type",circle.type);
		pRec->PutCollect("circle_layer",circle.layer);
		pRec->Update();
	}
	catch(_com_error &e)
	{
		CString str=e.Description();
		AfxMessageBox(str);
		return ;
	}
}
void CConOperation::deleteCircle(GeoCircle &circle)
{
	CString sql;
	sql.Format(_T("delete from Circle where circle_id='%d';"),circle.id);
	con.ExecuteSQL(sql.GetBuffer(0));
}


int CConOperation::addNote(GeoNote &note)
{
    CString sql;
	sql.Format(_T("insert into Note(note_id,note_data,note_x,note_y,note_layer,note_colorr,note_colorg,note_colorb) values ('%d','%s','%f','%f','%d','%d','%d','%d');"),-1,note.mnote,float(note.mpoint.x),float(note.mpoint.y),note.layer,GetRValue(note.color),GetGValue(note.color),GetBValue(note.color));
	con.ExecuteSQL(sql.GetBuffer(0));
	sql="select MAX(note_id)+1 as note_id from Note;";
	pRec=con.Query(sql.GetBuffer(0));
	_variant_t t_ID;
	t_ID = pRec->GetCollect("note_id");
	sql.Format(_T("UPDATE Note set note_id='%d' where note_id=-1;"),int(t_ID));
	con.ExecuteSQL(sql.GetBuffer(0));
	return t_ID;
}
void CConOperation::modifyNote(GeoNote &note)
{
	CString sql;
	sql.Format(_T("select * from Note where note_id='%d';"),int(note.id));
	pRec=con.Query(sql.GetBuffer(0));
	pRec->PutCollect("note_colorr",GetRValue(note.color));
	pRec->PutCollect("note_colorg",GetGValue(note.color));
	pRec->PutCollect("note_colorb",GetBValue(note.color));
	pRec->PutCollect("note_x",float(note.mpoint.x));
	pRec->PutCollect("note_y",float(note.mpoint.y));
	pRec->PutCollect("note_layer",note.layer);
	pRec->PutCollect("note_data",_variant_t(note.mnote));
	pRec->Update();
}
void CConOperation::deleteNote(GeoNote &note)
{
	CString sql;
	sql.Format(_T("delete from Note where note_id='%d';"),note.id);
	con.ExecuteSQL(sql.GetBuffer(0));
}


vector<GeoLayer> CConOperation::selectlayer()
{
	CString sql;
	sql="select *  from layer;";
	pRec=con.Query(sql.GetBuffer(0));
	vector<GeoLayer> layers;
	while(!pRec->adoEOF)
	{
		GeoLayer temp_layer;
		temp_layer.id=pRec->GetCollect("layer_id");
		temp_layer.Layername=pRec->GetCollect("layer_name");
		temp_layer.mtype=pRec->GetCollect("layer_type");
		layers.push_back(temp_layer);
		pRec->MoveNext();
	}
	return layers;
}

void CConOperation::importlayer(GeoLayer &layer)
{
	CString sql;
	if(layer.mtype==0)
	{
		sql.Format(_T("select *  from Point where point_layer='%d';"),layer.id);
		pRec=con.Query(sql.GetBuffer(0));
		while(!pRec->adoEOF)
		{
			GeoPoint temp_point;
			temp_point.id=pRec->GetCollect("point_id");
			temp_point.layer=pRec->GetCollect("point_layer");
			temp_point.type=pRec->GetCollect("point_type");
			temp_point.color=RGB(pRec->GetCollect("point_colorr"),pRec->GetCollect("point_colorg"),pRec->GetCollect("point_colorb"));
			temp_point.mpoint.x=pRec->GetCollect("point_x");
			temp_point.mpoint.y=pRec->GetCollect("point_y");
			s_point.Push(temp_point);
			pRec->MoveNext();
		}
	}
	if(layer.mtype==1)
	{
		sql.Format(_T("select *  from Line where line_layer='%d';"),layer.id);
		pRec=con.Query(sql.GetBuffer(0));
		while(!pRec->adoEOF)
		{
			GeoLine temp_line;
			temp_line.id=pRec->GetCollect("line_id");
			temp_line.type=pRec->GetCollect("line_type");
			temp_line.width=pRec->GetCollect("line_width");
			temp_line.layer=pRec->GetCollect("line_layer");
			temp_line.color=RGB(pRec->GetCollect("line_colorr"),pRec->GetCollect("line_colorg"),pRec->GetCollect("line_colorb"));

			long lDataSize = pRec->GetFields()->GetItem(_variant_t("line_data"))->ActualSize;
			if(lDataSize <= 0)return;
			_variant_t varBLOB;
			VariantInit (&varBLOB);
			varBLOB = pRec->GetFields()->GetItem(_variant_t("line_data"))->GetChunk(lDataSize);
			if(varBLOB.vt == (VT_ARRAY | VT_UI1))
			{
				BYTE *pBuf = new BYTE[lDataSize + 1];
				if(pBuf)
				{
					SafeArrayAccessData(varBLOB.parray,(void**)&pBuf);
					SafeArrayUnaccessData (varBLOB.parray);
					CMemFile memfile;
					memfile.Attach(pBuf,lDataSize);
					memfile.SeekToBegin();
					CArchive ar(&memfile, CArchive::load);
					for(int i=0;i<lDataSize/8;i++){
						CPoint p;
						ar.Read(&p,8);
						temp_line.data.push_back(p);
					}
					ar.Close();
					memfile.Detach();
					VariantClear (&varBLOB);
				} 
			}
			s_line.Push(temp_line);
			pRec->MoveNext();
		}
	}
	if(layer.mtype==2)
	{
		sql.Format(_T("select *  from Circle where circle_layer='%d';"),layer.id);
		pRec=con.Query(sql.GetBuffer(0));
		while(!pRec->adoEOF)
		{
			GeoCircle temp_circle;
			temp_circle.id=pRec->GetCollect("circle_id");
			temp_circle.type=pRec->GetCollect("circle_type");
			temp_circle.layer=pRec->GetCollect("circle_layer");
			temp_circle.color=RGB(pRec->GetCollect("circle_colorr"),pRec->GetCollect("circle_colorg"),pRec->GetCollect("circle_colorb"));

			long lDataSize = pRec->GetFields()->GetItem(_variant_t("circle_data"))->ActualSize;
			if(lDataSize <= 0)return;
			_variant_t varBLOB;
			VariantInit (&varBLOB);
			varBLOB = pRec->GetFields()->GetItem(_variant_t("circle_data"))->GetChunk(lDataSize);
			if(varBLOB.vt == (VT_ARRAY | VT_UI1))
			{
				BYTE *pBuf = new BYTE[lDataSize + 1];
				if(pBuf)
				{
					SafeArrayAccessData(varBLOB.parray,(void**)&pBuf);
					SafeArrayUnaccessData (varBLOB.parray);
					CMemFile memfile;
					memfile.Attach(pBuf,lDataSize);
					memfile.SeekToBegin();
					CArchive ar(&memfile, CArchive::load);
					for(int i=0;i<lDataSize/8;i++){
						CPoint p;
						ar.Read(&p,8);
						temp_circle.data.push_back(p);
					}
					ar.Close();
					memfile.Detach();
					VariantClear (&varBLOB);
				} 
			}
			s_Circle.Push(temp_circle);
			pRec->MoveNext();
		}
	}
	if(layer.mtype==3)
	{
		sql.Format(_T("select *  from Note where note_layer='%d';"),layer.id);
		pRec=con.Query(sql.GetBuffer(0));
		while(!pRec->adoEOF)
		{
			GeoNote temp_note;
			temp_note.id=pRec->GetCollect("note_id");
			temp_note.layer=pRec->GetCollect("note_layer");
			temp_note.mnote=pRec->GetCollect("note_data");
			temp_note.color=RGB(pRec->GetCollect("note_colorr"),pRec->GetCollect("note_colorg"),pRec->GetCollect("note_colorb"));
			temp_note.mpoint.x=pRec->GetCollect("note_x");
			temp_note.mpoint.y=pRec->GetCollect("note_y");
			s_note.Push(temp_note);
			pRec->MoveNext();
		}
	}
}