// GISToolDlg.h : GISToolDlg DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGISToolDlgApp
// �йش���ʵ�ֵ���Ϣ������� GISToolDlg.cpp
//

class CGISToolDlgApp : public CWinApp
{
public:
	CGISToolDlgApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
