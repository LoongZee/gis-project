
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")


#include "SeqStack.h"
#include "Gis_struct.h"
#include "ConOperation.h"
#include "Handlefunction.h"

extern CConOperation Operation;
extern SeqStack<GeoPoint> s_point;
extern SeqStack<GeoLine> s_line;
extern SeqStack<GeoCircle> s_Circle;
extern SeqStack<GeoNote> s_note;
extern SeqStack<GeoLayer> s_layer;
extern CRect rect_point;
extern CRect rect_note;
extern CPoint m_startp,m_lastp;
extern GeoPoint selectpoint,m_pointMouse;
extern GeoLine selectline,m_lineMouse;
extern GeoCircle selectcircle,m_circleMouse;
extern GeoNote selectnote,m_noteMouse;
extern GeoLayer importlayer;
extern bool Isselectpoint;
extern bool Isselectline;
extern bool Isselectcircle;
extern bool Isselectnote;
extern bool m_delete;
extern bool m_bLBtnDown;
extern int  tag,tag_linecut,tag_Dlinetopoint;
extern int  list;
extern int  editlayer;
