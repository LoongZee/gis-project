// InputLayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "sunflower.h"
#include "InputLayerDlg.h"
#include "afxdialogex.h"


// CInputLayerDlg 对话框

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


// CInputLayerDlg 消息处理程序


BOOL CInputLayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	// 异常: OCX 属性页应返回 FALSE
}


void CInputLayerDlg::OnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(layers.size()!=0)
	{
		CString str;   
		int nSel;   
		// 获取组合框控件的列表框中选中项的索引   
		nSel = m_select.GetCurSel();   
		// 根据选中项索引获取该项字符串   
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
					SetDlgItemText(IDC_EDIT1, _T("点图层")); 
				else if(layers[i].mtype==1)
					SetDlgItemText(IDC_EDIT1, _T("线图层")); 
				else if(layers[i].mtype==2)
					SetDlgItemText(IDC_EDIT1, _T("面图层")); 
				else if(layers[i].mtype==3)
					SetDlgItemText(IDC_EDIT1, _T("注记图层")); 
			}
		}  
	}
}
