#pragma once


// InputNoteDlg �Ի���

class InputNoteDlg : public CDialog
{
	DECLARE_DYNAMIC(InputNoteDlg)

public:
	InputNoteDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InputNoteDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
