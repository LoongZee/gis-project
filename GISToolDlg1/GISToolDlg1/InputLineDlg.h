#pragma once


// CInputLineDlg �Ի���

class CInputLineDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputLineDlg)

public:
	CInputLineDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputLineDlg();

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
	int m_width;
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CEdit m_widthcontrol;
};
