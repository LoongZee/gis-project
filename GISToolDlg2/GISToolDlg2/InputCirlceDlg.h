#pragma once


// CInputCirlceDlg �Ի���

class CInputCirlceDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputCirlceDlg)

public:
	CInputCirlceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputCirlceDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_r;
	int m_g;
	int m_b;
	CComboBox m_type;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
