// afMfc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afMfc.h"
#include "MainFrm.h"

#include "afMfcDoc.h"
#include "afMfcView.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CafMfcApp

BEGIN_MESSAGE_MAP(CafMfcApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CafMfcApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CafMfcApp construction

CafMfcApp::CafMfcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CafMfcApp object

CafMfcApp theApp;


// CafMfcApp initialization

BOOL CafMfcApp::InitInstance()
{

	if(!AfxOleInit())//这就是初始化COM库
	{
		AfxMessageBox("OLE初始化出错!");
		return FALSE;
	}

	//GFileSystem::DeleteFile(m_szDataPath,FOF_NO_UI);
	if(_access(m_szDataPath,0)!=0)
	{
		CreateDirectory(m_szDataPath,NULL);
		CString strFolder=m_szDataPath;
		strFolder+="Allotment";
		CreateDirectory(strFolder,NULL);
		CreateDirectory(strFolder+"\\Vector",NULL);
		CreateDirectory(strFolder+"\\Vector\\Test",NULL);
		CreateDirectory(strFolder+"\\AirLine",NULL);
		CreateDirectory(strFolder+"\\AirLine\\Test",NULL);
	}
	

	CLoginDlg loginDlg;
	if(loginDlg.DoModal() == IDOK)
	{
		strcpy(m_szUserName,loginDlg.m_strName);
		m_iUserType = loginDlg.m_iUserType;
	}
	else
		return FALSE;
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CafMfcDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CafMfcView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CafMfcApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CafMfcApp message handlers



bool CafMfcApp::OpenAccess(void)
{

	char szCommonPath[_MAX_PATH] = "";
	
	::SHGetSpecialFolderPath(NULL,szCommonPath,0x23,FALSE);
	
	sprintf(szCommonPath,"%s\\GeoBeans",szCommonPath);
	if(_access(szCommonPath,0)!=0)
	{
		CreateDirectory(szCommonPath,NULL);
	}
	
	char szAppPath[_MAX_PATH] = "";
	char szAppName[_MAX_FNAME] = "";
	::GetModuleFileName(NULL,szAppPath,_MAX_PATH);
	_splitpath(szAppPath,NULL,NULL,szAppName,NULL);
	sprintf(szCommonPath,"%s\\%s\\",szCommonPath,szAppName);
	if(_access(szCommonPath,0)!=0)
	{
		CreateDirectory(szCommonPath,NULL);
	}
	
	char szConnect[_MAX_PATH]="";
	char szDataPath[_MAX_PATH]="";
	sprintf(szDataPath,"%safMfc.dat",szCommonPath);
	sprintf(szConnect,"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;Jet OLEDB:Database Password=geobeans;",
		szDataPath);
	
	HRESULT hr;  //创建对象
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");    //创建Connection对象
		if (FAILED(hr)) return false;
		
		if(m_pConnection->State) return true;
		
		hr = m_pConnection->Open(szConnect,"","",adModeUnknown);  //连接数据库，注意DataSource路径的写法
		return SUCCEEDED(hr);
	}
	catch(_com_error e)
	{
		CString errorMsg;
		errorMsg.Format("连接数据库失败！\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errorMsg);
		return false;
	}
}


bool CafMfcApp::CloseAccess(void)
{
	if(m_pRecordset!=NULL&&m_pRecordset->GetState() == adStateOpen)
	{
		m_pRecordset->Close();
		m_pRecordset = NULL;
	}
	if (m_pConnection!=NULL&&m_pConnection->State)
	{
		m_pConnection->Close();
		m_pConnection = NULL;
	}
	return true;
}


_RecordsetPtr CafMfcApp::GetRecordset(const char* szSql)
{
	if(m_pConnection==NULL||m_pConnection->State==false||szSql==NULL||strlen(szSql)==0) 
		return NULL;

	HRESULT hr;
	try
	{
		hr = m_pRecordset.CreateInstance("ADODB.Recordset");
		if (FAILED(hr)) return NULL;
		//设置游标属性 不知道为什么要设置这个，但是不设置这个游标属性为3或者adUseClient的话返回的数据集数目为-1，获取不到记录
		m_pRecordset->CursorLocation = adUseClient;  
		//打开记录集
		m_pRecordset->Open(_variant_t(szSql),_variant_t((IDispatch *)m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
		return m_pRecordset;
	}
	catch(_com_error e)
	{
		CString errorMsg;
		errorMsg.Format("操作数据库失败！\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errorMsg);         //显示错误信息
		return NULL;
	}
}
