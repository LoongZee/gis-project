#pragma once


// CInputLayerDlg �Ի���

class CInputLayerDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputLayerDlg)

public:
	CInputLayerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputLayerDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_type;
	CEdit m_edit;
	CComboBox m_select;
	vector<GeoLayer> layers;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
};
