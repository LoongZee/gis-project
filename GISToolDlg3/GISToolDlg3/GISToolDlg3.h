// GISToolDlg3.h : GISToolDlg3 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGISToolDlg3App
// �йش���ʵ�ֵ���Ϣ������� GISToolDlg3.cpp
//

class CGISToolDlg3App : public CWinApp
{
public:
	CGISToolDlg3App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
