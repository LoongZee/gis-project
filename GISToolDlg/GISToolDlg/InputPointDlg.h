#pragma once


// CInputPointDlg �Ի���

class CInputPointDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputPointDlg)

public:
	CInputPointDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputPointDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	int m_r;
	int m_g;
	int m_b;
	CComboBox m_type;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
};
