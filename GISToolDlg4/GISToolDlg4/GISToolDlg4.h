// GISToolDlg4.h : GISToolDlg4 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGISToolDlg4App
// �йش���ʵ�ֵ���Ϣ������� GISToolDlg4.cpp
//

class CGISToolDlg4App : public CWinApp
{
public:
	CGISToolDlg4App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
