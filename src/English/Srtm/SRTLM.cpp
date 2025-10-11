
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


// SRTLM.cpp : Define classes for applications.
//

#include "stdafx.h"
#include "SRTLM.h"
#include "SRTLMDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSRTLMApp

BEGIN_MESSAGE_MAP(CSRTLMApp, CWinApp)
    //{{AFX_MSG_MAP(CSRTLMApp)
        // Note - ClassWizard adds or removes mapping macros at this location.
        //        Do not edit the code generated at this location.
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRTLMApp construction

CSRTLMApp::CSRTLMApp()
{
    // TODO: TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSRTLMApp object

CSRTLMApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSRTLMApp initialization

BOOL CSRTLMApp::InitInstance()
{
    AfxEnableControlContainer();

    // Standard Initialization Processes
    // If you do not use these features and wish to reduce the size of your executable,
    // remove any unnecessary specific initialization routines below.

#ifdef _AFXDLL
    // Enable3dControls();          // Call here when using MFC in a shared DLL.
#else
    Enable3dControlsStatic();    // Call here when linking statically with MFC.
#endif

    CSRTLMDlg dlg;
    m_pMainWnd = &dlg;
    int nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: Place code here to handle when the dialog is
        //       dismissed with OK
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: Place code here to handle when the dialog is
        //       dismissed with Cancel
    }

    // Instead of starting the application's message pump after the dialog is closed,
    // return FALSE to terminate the application.
    return FALSE;
}
