// CGISToolDlg5.h : CGISToolDlg5 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGISToolDlg5App
// �йش���ʵ�ֵ���Ϣ������� CGISToolDlg5.cpp
//

class CGISToolDlg5App : public CWinApp
{
public:
	CGISToolDlg5App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
