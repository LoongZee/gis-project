// InputLayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sunflower.h"
#include "InputLayerDlg.h"
#include "afxdialogex.h"


// CInputLayerDlg �Ի���

IMPLEMENT_DYNAMIC(CInputLayerDlg, CDialog)

CInputLayerDlg::CInputLayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputLayerDlg::IDD, pParent)
{

	m_type = _T("");
}

CInputLayerDlg::~CInputLayerDlg()
{
}

void CInputLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_type);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_COMBO1, m_select);
}


BEGIN_MESSAGE_MAP(CInputLayerDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CInputLayerDlg::OnSelchangeCombo1)
END_MESSAGE_MAP()


// CInputLayerDlg ��Ϣ�������


BOOL CInputLayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	layers.clear();
	Operation.Connectiondb();
	layers=Operation.selectlayer();
	int a=layers.size();
	if(layers.size()!=0)
	{
		for(unsigned int i=0;i<layers.size();i++)
		{
			bool t=true;
			for(int j=0;j<s_layer.getSize();j++)
			{
				if(layers[i].id==s_layer.elements[j].id)
				{
					t=false;
					break;
				}
			}
			if(t)
				m_select.AddString(layers[i].Layername);
	}

	m_select.SetCurSel(0);
	OnSelchangeCombo1();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CInputLayerDlg::OnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(layers.size()!=0)
	{
		CString str;   
		int nSel;   
		// ��ȡ��Ͽ�ؼ����б����ѡ���������   
		nSel = m_select.GetCurSel();   
		// ����ѡ����������ȡ�����ַ���   
		m_select.GetLBText(nSel, str); 
		for(unsigned int i=0;i<layers.size();i++)
		{
			if(str==layers[i].Layername)
			{
				importlayer.Layername=layers[i].Layername;
				importlayer.id=layers[i].id;
				importlayer.mtype=layers[i].mtype;
				importlayer.isedit=false;
				importlayer.isshow=false;
				if(layers[i].mtype==0)
					SetDlgItemText(IDC_EDIT1, _T("��ͼ��")); 
				else if(layers[i].mtype==1)
					SetDlgItemText(IDC_EDIT1, _T("��ͼ��")); 
				else if(layers[i].mtype==2)
					SetDlgItemText(IDC_EDIT1, _T("��ͼ��")); 
				else if(layers[i].mtype==3)
					SetDlgItemText(IDC_EDIT1, _T("ע��ͼ��")); 
			}
		}  
	}
}
