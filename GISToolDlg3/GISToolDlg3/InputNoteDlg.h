#pragma once


// InputNoteDlg 对话框

class InputNoteDlg : public CDialog
{
	DECLARE_DYNAMIC(InputNoteDlg)

public:
	InputNoteDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InputNoteDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_str;
	int m_r;
	int m_g;
	int m_b;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_Edit;
};
