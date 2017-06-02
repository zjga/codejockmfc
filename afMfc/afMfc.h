// afMfc.h : main header file for the afMfc application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CafMfcApp:
// See afMfc.cpp for the implementation of this class
//
enum USETTYPE
{
	UT_UserAdmin = 0x0001,
	UT_DataAdmin = 0x0002,
	UT_User = 0x0004
};

class CafMfcApp : public CWinApp
{
public:
	CafMfcApp();

	char m_szUserName[_MAX_PATH];
	USETTYPE  m_iUserType;
	char m_szDataPath[_MAX_PATH];
	std::vector<std::string> m_StartPaths;
	bool m_bReStart;
	// Overrides
public:
	virtual BOOL InitInstance();

	// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	bool OpenAccess(void);

private:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
public:
	bool CloseAccess(void);
	_RecordsetPtr GetRecordset(const char* szSql);
};

extern CafMfcApp theApp;