// GISToolDlg1.h : GISToolDlg1 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGISToolDlg1App
// �йش���ʵ�ֵ���Ϣ������� GISToolDlg1.cpp
//

class CGISToolDlg1App : public CWinApp
{
public:
	CGISToolDlg1App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
