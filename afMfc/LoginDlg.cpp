// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"

#include "LoginDlg.h"
//#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{

	m_strName = _T("");
	m_strValue = _T("");
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_Password, m_strValue);
	DDX_Control(pDX, IDC_STATIC_PIC, m_Pic);
	DDX_Control(pDX, IDC_CHECK_SHOW, m_chkSave);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(theApp.OpenAccess()==false) return TRUE;

	m_Pic.SetPictureID(IDB_LOGIN_ICON);
	SetDlgItemText(IDC_EDIT_NAME,"User");
	SetDlgItemText(IDC_EDIT_Password,"123");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);
	if(theApp.OpenAccess()==false)
	{
		theApp.CloseAccess();
		::MessageBox(m_hWnd,"用户数据打开失败！","提示信息",MB_OK|MB_ICONWARNING);
		return;
	}

	char szSql[_MAX_PATH]="";
	sprintf(szSql,"select [Password],[Type] from UserData where [UserName]=\'%s\'",m_strName);
	_RecordsetPtr pRs = theApp.GetRecordset(szSql);
	if(pRs==NULL||pRs->GetRecordCount()==0)
	{
		theApp.CloseAccess();
		::MessageBox(m_hWnd,"用户不存在！","提示信息",MB_OK|MB_ICONWARNING);
		return;
	}

	pRs->MoveFirst();
	
	_variant_t varPd = pRs->GetCollect("Password"); 

	if(strcmp(m_strValue,(TCHAR*)(_bstr_t)varPd)!=0)
	{
		theApp.CloseAccess();
		::MessageBox(m_hWnd,"密码错误！","提示信息",MB_OK|MB_ICONWARNING);
		return;
	}
	
	_variant_t varTy = pRs->GetCollect("Type"); 
	switch(atoi((TCHAR*)(_bstr_t)varTy))
	{
	case 0:
		m_iUserType = UT_User;
		break;
	case 1:
		m_iUserType = UT_UserAdmin;
		break;
	case 2:
		m_iUserType = UT_DataAdmin;
		break;
	}
	theApp.CloseAccess();

	CDialog::OnOK();
}


void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
