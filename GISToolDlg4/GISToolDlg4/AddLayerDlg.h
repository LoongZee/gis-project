#pragma once


// CAddLayerDlg 对话框

class CAddLayerDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddLayerDlg)

public:
	CAddLayerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddLayerDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	afx_msg void OnBnClickedOk();
	CComboBox m_type;
	CEdit m_n;
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
