#pragma once
class CConnection
{
public:
	CConnection(void);
	virtual ~CConnection(void);
	int ExecuteSQL(wchar_t * strSQL);//ִ��sql���
	_RecordsetPtr Query(wchar_t * strSQL);//��ѯsql�����ز�ѯ���
	int Initial(char *servername,char *db,char *username,char *password);//��ʼ��
	bool IsConnection();
public:
	char 		m_username[100];	//�û���
	char 		m_password[100];	//����
	char		m_servername[50];	//��������
	char		m_database[100];	//�������ݿ�
	_bstr_t				m_strConnect;		//�����ַ���
	char				m_strCon[200];
	_RecordsetPtr		m_pRecordset;
	_ConnectionPtr		m_pConnection;
};

