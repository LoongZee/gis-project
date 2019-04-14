// AddLayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GISToolDlg4.h"
#include "AddLayerDlg.h"
#include "afxdialogex.h"


// CAddLayerDlg �Ի���

IMPLEMENT_DYNAMIC(CAddLayerDlg, CDialog)

CAddLayerDlg::CAddLayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddLayerDlg::IDD, pParent)
{

	m_name = _T("");
}

CAddLayerDlg::~CAddLayerDlg()
{
}

void CAddLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_COMBO1, m_type);
	DDX_Control(pDX, IDC_EDIT1, m_n);
}


BEGIN_MESSAGE_MAP(CAddLayerDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddLayerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAddLayerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAddLayerDlg ��Ϣ�������
CAddLayerDlg dlg;
CString mname;
int mtype=0;
int mmark=0;

extern "C" __declspec(dllexport) BOOL WINAPI AddLayerDlg(int &mark,int &type,CString &name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(dlg.DoModal()==IDOK)
	{
		type=mtype;
		mark=mmark;
		name=mname;
		return(1);
	}
	else
	{
		return(0);
	}
}


void CAddLayerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString  strTemp;
	dlg.m_type.GetWindowText(strTemp);
	if(strTemp=="��ͼ��")
		mtype=0;
	else if(strTemp=="��ͼ��")
		mtype=1;
	else if(strTemp=="��ͼ��")
		mtype=2;
	else if(strTemp=="ע��ͼ��")
		mtype=3;

	CString text;
	dlg.m_n.GetWindowText(text);
	mname=text;
	UpdateData(false);
	CDialog::OnOK();
}


void CAddLayerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mmark=1;
	CDialog::OnCancel();
}


BOOL CAddLayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_type.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
