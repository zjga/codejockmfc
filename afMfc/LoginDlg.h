#pragma once




// CLoginDlg �Ի���
#include "PngPicture.h"
#include "afMfc.h"
class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Login };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	CString m_strName;
	CString m_strValue;
	USETTYPE m_iUserType;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CPngPicture m_Pic;
	//CStatic m_Pic;
	CButton m_chkSave;

	afx_msg void OnBnClickedOk();
};
