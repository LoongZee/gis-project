#pragma once


// CAddLayerDlg �Ի���

class CAddLayerDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddLayerDlg)

public:
	CAddLayerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddLayerDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	afx_msg void OnBnClickedOk();
	CComboBox m_type;
	CEdit m_n;
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
