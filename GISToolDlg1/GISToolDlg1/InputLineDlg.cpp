// InputLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GISToolDlg1.h"
#include "InputLineDlg.h"
#include "afxdialogex.h"


// CInputLineDlg �Ի���

IMPLEMENT_DYNAMIC(CInputLineDlg, CDialog)

CInputLineDlg::CInputLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputLineDlg::IDD, pParent)
{

	m_r = 0;
	m_g = 0;
	m_b = 0;
	m_width = 1;
}

CInputLineDlg::~CInputLineDlg()
{
}

void CInputLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_r);
	DDX_Text(pDX, IDC_EDIT3, m_g);
	DDX_Text(pDX, IDC_EDIT4, m_b);
	DDX_Control(pDX, IDC_COMBO1, m_type);
	DDX_Text(pDX, IDC_EDIT1, m_width);
	DDV_MinMaxInt(pDX, m_width, 1, 100);
	DDX_Control(pDX, IDC_EDIT1, m_widthcontrol);
}


BEGIN_MESSAGE_MAP(CInputLineDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CInputLineDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CInputLineDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInputLineDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CInputLineDlg ��Ϣ�������
CInputLineDlg dlg;
int mtype=0;
int mmark=0;
int mwidth=1;
COLORREF mcolor=RGB(0,0,0);

extern "C" __declspec(dllexport) BOOL WINAPI InputLineDlg(int &mark,int &type,int &width,COLORREF &color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(dlg.DoModal()==IDOK)
	{
		type=mtype;
		color=mcolor;
		mark=mmark;
		width=mwidth;
		return(1);
	}
	else
	{
		return(0);
	}
	return(0);
}


void CInputLineDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog dlg1;
	COLORREF color;
	CString text;
	dlg.m_widthcontrol.GetWindowText(text);
	m_width=_ttoi(text);
	if (dlg1.DoModal()==IDOK)
	{
		color=dlg1.GetColor();
		m_r=GetRValue(color);
		m_g=GetGValue(color);
		m_b=GetBValue(color);
		UpdateData(false);
	}
}


void CInputLineDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString  strTemp;
	dlg.m_type.GetWindowText(strTemp);
	if(strTemp=="ʵ��")
		mtype=PS_SOLID;
	else if(strTemp=="����")
		mtype=PS_DASH;
	else if(strTemp=="����")
		mtype=PS_DOT;
	if(dlg.m_r!=0||dlg.m_g!=0||dlg.m_b!=0)
		mcolor=RGB(dlg.m_r,dlg.m_g,dlg.m_b);

	CString text;
	dlg.m_widthcontrol.GetWindowText(text);
	mwidth=_ttoi(text);
	UpdateData(false);
	CDialog::OnOK();

}


void CInputLineDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mmark=1;
	CDialog::OnCancel();
}


BOOL CInputLineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_type.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
