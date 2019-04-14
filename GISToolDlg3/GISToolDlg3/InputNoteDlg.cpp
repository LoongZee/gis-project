// InputNoteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GISToolDlg3.h"
#include "InputNoteDlg.h"
#include "afxdialogex.h"


// InputNoteDlg 对话框

IMPLEMENT_DYNAMIC(InputNoteDlg, CDialog)

InputNoteDlg::InputNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InputNoteDlg::IDD, pParent)
{

	m_str = _T("");
	m_r = 0;
	m_g = 0;
	m_b = 0;
}

InputNoteDlg::~InputNoteDlg()
{
}

void InputNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_str);
	DDX_Text(pDX, IDC_EDIT2, m_r);
	DDX_Text(pDX, IDC_EDIT3, m_g);
	DDX_Text(pDX, IDC_EDIT4, m_b);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(InputNoteDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &InputNoteDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &InputNoteDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &InputNoteDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// InputNoteDlg 消息处理程序
InputNoteDlg dlg;
CString mstr;
int mmark=0;
COLORREF mcolor=RGB(0,0,0);

extern "C" __declspec(dllexport) BOOL WINAPI InputnoteDlg(int &mark,CString &str,COLORREF &color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(dlg.DoModal()==IDOK)
	{
		str=mstr;
		color=mcolor;
		mark=mmark;
		return(1);
	}
	else
	{
		return(0);
	}
	return(0);
}

void InputNoteDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg1;
	COLORREF color;
	CString text;
	dlg.m_Edit.GetWindowText(text);
	m_str=text;
	if (dlg1.DoModal())
	{
		color=dlg1.GetColor();
		m_r=GetRValue(color);
		m_g=GetGValue(color);
		m_b=GetBValue(color);
		UpdateData(false);
	}
}


void InputNoteDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	dlg.m_Edit.GetWindowText(mstr);
	if(dlg.m_r!=0||dlg.m_g!=0||dlg.m_b!=0)
		mcolor=RGB(dlg.m_r,dlg.m_g,dlg.m_b);
	CDialog::OnOK();
}


void InputNoteDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	mmark=1;
	CDialog::OnCancel();
}
