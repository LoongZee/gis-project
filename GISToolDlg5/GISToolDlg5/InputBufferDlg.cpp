// InputBufferDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GISToolDlg5.h"
#include "InputBufferDlg.h"
#include "afxdialogex.h"


// CInputBufferDlg 对话框

IMPLEMENT_DYNAMIC(CInputBufferDlg, CDialog)

CInputBufferDlg::CInputBufferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputBufferDlg::IDD, pParent)
{

	m_rad = 0;
	m_r = 0;
	m_g = 0;
	m_b = 0;
}

CInputBufferDlg::~CInputBufferDlg()
{
}

void CInputBufferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_rad);
	DDX_Text(pDX, IDC_EDIT2, m_r);
	DDX_Text(pDX, IDC_EDIT3, m_g);
	DDX_Text(pDX, IDC_EDIT4, m_b);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(CInputBufferDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CInputBufferDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CInputBufferDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInputBufferDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CInputBufferDlg 消息处理程序
CInputBufferDlg dlg;
int  mrad;
int mmark=0;
COLORREF mcolor=RGB(0,0,0);

extern "C" __declspec(dllexport) BOOL WINAPI InputBufferDlg(int &mark,int &rad,COLORREF &color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(dlg.DoModal()==IDOK)
	{
		rad=mrad;
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




void CInputBufferDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg1;
	COLORREF color;
	CString text;
	dlg.m_Edit.GetWindowText(text);
	m_rad=_ttoi(text);
	if (dlg1.DoModal())
	{
		color=dlg1.GetColor();
		m_r=GetRValue(color);
		m_g=GetGValue(color);
		m_b=GetBValue(color);
		UpdateData(false);
	}
}


void CInputBufferDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	dlg.m_Edit.GetWindowText(text);
	mrad=_ttoi(text);
	if(dlg.m_r!=0||dlg.m_g!=0||dlg.m_b!=0)
		mcolor=RGB(dlg.m_r,dlg.m_g,dlg.m_b);
	CDialog::OnOK();
}


void CInputBufferDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
    mmark=1;
	CDialog::OnCancel();
}
