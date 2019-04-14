#pragma once


// CInputLayerDlg 对话框

class CInputLayerDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputLayerDlg)

public:
	CInputLayerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputLayerDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_type;
	CEdit m_edit;
	CComboBox m_select;
	vector<GeoLayer> layers;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
};
