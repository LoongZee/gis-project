#pragma once


// CInputBufferDlg �Ի���

class CInputBufferDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputBufferDlg)

public:
	CInputBufferDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputBufferDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
