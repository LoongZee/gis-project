// GISToolDlg2.h : GISToolDlg2 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGISToolDlg2App
// �йش���ʵ�ֵ���Ϣ������� GISToolDlg2.cpp
//

class CGISToolDlg2App : public CWinApp
{
public:
	CGISToolDlg2App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
