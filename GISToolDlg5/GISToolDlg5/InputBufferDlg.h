#pragma once


// CInputBufferDlg 对话框

class CInputBufferDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputBufferDlg)

public:
	CInputBufferDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputBufferDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_rad;
	int m_r;
	int m_g;
	int m_b;
	afx_msg void OnBnClickedButton1();
	CEdit m_Edit;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
