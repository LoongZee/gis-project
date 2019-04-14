#pragma once


// CInputLineDlg 对话框

class CInputLineDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputLineDlg)

public:
	CInputLineDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputLineDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_r;
	int m_g;
	int m_b;
	CComboBox m_type;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	int m_width;
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CEdit m_widthcontrol;
};
