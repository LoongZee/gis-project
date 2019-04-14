#pragma once
class CConnection
{
public:
	CConnection(void);
	virtual ~CConnection(void);
	int ExecuteSQL(wchar_t * strSQL);//执行sql语句
	_RecordsetPtr Query(wchar_t * strSQL);//查询sql并返回查询结果
	int Initial(char *servername,char *db,char *username,char *password);//初始化
	bool IsConnection();
public:
	char 		m_username[100];	//用户名
	char 		m_password[100];	//密码
	char		m_servername[50];	//服务器名
	char		m_database[100];	//连接数据库
	_bstr_t				m_strConnect;		//连接字符串
	char				m_strCon[200];
	_RecordsetPtr		m_pRecordset;
	_ConnectionPtr		m_pConnection;
};

