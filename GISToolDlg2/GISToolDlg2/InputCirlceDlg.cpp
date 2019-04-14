// InputCirlceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GISToolDlg2.h"
#include "InputCirlceDlg.h"
#include "afxdialogex.h"


// CInputCirlceDlg 对话框

IMPLEMENT_DYNAMIC(CInputCirlceDlg, CDialog)

CInputCirlceDlg::CInputCirlceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputCirlceDlg::IDD, pParent)
{

	m_r = 0;
	m_g = 0;
	m_b = 0;
}

CInputCirlceDlg::~CInputCirlceDlg()
{
}

void CInputCirlceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_r);
	DDX_Text(pDX, IDC_EDIT2, m_g);
	DDX_Text(pDX, IDC_EDIT3, m_b);
	DDX_Control(pDX, IDC_COMBO1, m_type);
}


BEGIN_MESSAGE_MAP(CInputCirlceDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CInputCirlceDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CInputCirlceDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputCirlceDlg 消息处理程序

CInputCirlceDlg dlg;
int mtype=0;
int mmark=0;
COLORREF mcolor=RGB(0,0,0);

extern "C" __declspec(dllexport) BOOL WINAPI InputCircleDlg(int &mark,int &type,COLORREF &color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(dlg.DoModal()==IDOK)
	{
		type=mtype;
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

void CInputCirlceDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;
	COLORREF color;
	if (dlg.DoModal())
	{
		color=dlg.GetColor();
		m_r=GetRValue(color);
		m_g=GetGValue(color);
		m_b=GetBValue(color);
		UpdateData(false);
	}

}


void CInputCirlceDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  strTemp;
	dlg.m_type.GetWindowText(strTemp);
	if(strTemp=="椭圆")
		mtype=0;
	else if(strTemp=="矩形")
		mtype=1;
	else if(strTemp=="自定义形状")
		mtype=2;
	if(dlg.m_r!=0||dlg.m_g!=0||dlg.m_b!=0)
		mcolor=RGB(dlg.m_r,dlg.m_g,dlg.m_b);
	UpdateData(false);
	CDialog::OnOK();
}


BOOL CInputCirlceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_type.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
