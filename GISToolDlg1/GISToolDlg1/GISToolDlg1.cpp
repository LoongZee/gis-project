// GISToolDlg1.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "GISToolDlg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CGISToolDlg1App

BEGIN_MESSAGE_MAP(CGISToolDlg1App, CWinApp)
END_MESSAGE_MAP()


// CGISToolDlg1App ����

CGISToolDlg1App::CGISToolDlg1App()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CGISToolDlg1App ����

CGISToolDlg1App theApp;


// CGISToolDlg1App ��ʼ��

BOOL CGISToolDlg1App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
