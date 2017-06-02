#pragma once




// CLoginDlg 对话框
#include "PngPicture.h"
#include "afMfc.h"
class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_Login };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
