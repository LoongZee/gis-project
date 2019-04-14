#include "StdAfx.h"
#include "Connection.h"


CConnection::CConnection(void)
{
	::CoInitialize(NULL); 	
}


CConnection::~CConnection(void)
{
	//if (m_pRecordset != NULL)
	//	m_pRecordset->Close();
	////如果正在连接数据库，则断开
	//if(m_pConnection->State)
	//{
	//	m_pConnection->Close();
	//	m_pConnection.Release();
	//}
	//m_pConnection=NULL;
	//m_pRecordset=NULL;
	//::CoUninitialize(); 
}

int CConnection::ExecuteSQL(wchar_t * strSQL)
{
	int rtn;
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pConnection->Execute(strSQL,NULL,adCmdText);		
		rtn=0;
	}
	catch (_com_error e) 
	{
		AfxMessageBox(e.Description());
		rtn = -1;
	}
	return rtn;
};

_RecordsetPtr CConnection::Query(wchar_t * strSQL)//查询sql并返回查询结果
{
	m_pRecordset.CreateInstance("ADODB.Recordset");
	m_pRecordset->Open(strSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	return m_pRecordset;
}

int CConnection::Initial(char *servername,char *db,char *username,char *password)
{
	
	//服务器
	memset(m_servername,0,50);
	strcpy(m_servername,servername);
	//数据库
	memset(m_database,0,100);
	strcpy(m_database,db);
	//用户名
	memset(m_username,0,100);
	strcpy(m_username,username);
	//密码
	memset(m_password,0,100);
	strcpy(m_password,password);

	try
	{
		//创建Connection对象
		m_pConnection.CreateInstance("ADODB.Connection");
		sprintf(m_strCon,"Provider=SQLOLEDB;Server=%s;Database=%s;uid=%s;pwd=%s;",m_servername,m_database,m_username,m_password);
		m_strConnect =m_strCon;
		m_pConnection->Open(m_strConnect, "", "",adModeUnknown);
		if(m_pConnection==NULL)
			return -1;
		//创建记录集对象
		m_pRecordset.CreateInstance(__uuidof(Recordset));
	}
	catch (_com_error e) 
	{
		AfxMessageBox(e.Description());
		return -2;
	}
	return 0;
}

bool CConnection::IsConnection()
{
	if(m_pConnection == NULL)
		return false;
	else return true;
}