// InputPointDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GISToolDlg.h"
#include "InputPointDlg.h"
#include "afxdialogex.h"

// CInputPointDlg �Ի���

IMPLEMENT_DYNAMIC(CInputPointDlg, CDialog)

CInputPointDlg::CInputPointDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputPointDlg::IDD, pParent)
{
	
	m_r = 0;
	m_g = 0;
	m_b = 0;
}

CInputPointDlg::~CInputPointDlg()
{
}

void CInputPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_r);
	DDX_Text(pDX, IDC_EDIT2, m_g);
	DDX_Text(pDX, IDC_EDIT3, m_b);
	DDX_Control(pDX, IDC_COMBO1, m_type);
}

BEGIN_MESSAGE_MAP(CInputPointDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CInputPointDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CInputPointDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInputPointDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CInputPointDlg ��Ϣ�������
CInputPointDlg dlg;
int mtype=0;
int mmark=0;
COLORREF mcolor=RGB(0,0,0);

extern "C" __declspec(dllexport) BOOL WINAPI InputPointDlg(int &mark,int &type,COLORREF &color)
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


void CInputPointDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


void CInputPointDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString  strTemp;
	dlg.m_type.GetWindowText(strTemp);
	if(strTemp=="���ε�")
		mtype=0;
	else if(strTemp=="���ǵ�")
		mtype=1;
	else if(strTemp=="���ĵ�")
		mtype=2;
	if(dlg.m_r!=0||dlg.m_g!=0||dlg.m_b!=0)
		mcolor=RGB(dlg.m_r,dlg.m_g,dlg.m_b);
	UpdateData(false);
	CDialog::OnOK();
}


BOOL CInputPointDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_type.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CInputPointDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mmark=1;
	CDialog::OnCancel();
}
