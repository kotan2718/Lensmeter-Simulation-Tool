
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


// SRTLM.h : SRTLM Application's main header file.
//

#if !defined(AFX_SRTLM_H__856265B9_C462_4623_9EC9_A6755D3F35E2__INCLUDED_)
#define AFX_SRTLM_H__856265B9_C462_4623_9EC9_A6755D3F35E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"        // Main Symbol

#include  <stdio.h>
#include  <math.h>
#include  <stdlib.h>

/////////////////////////////////////////////////////////////////////////////
// CSRTLMApp:
// For the definition of this class's behavior, please refer to the SRTLM.cpp file.
//

class CSRTLMApp : public CWinApp
{
public:
    CSRTLMApp();

// Override
    // ClassWizard generates virtual function overrides.
    //{{AFX_VIRTUAL(CSRTLMApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CSRTLMApp)
        // Note - ClassWizard adds or removes member functions at this location.
        //        Do not edit the code generated at this location.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ inserts additional declarations immediately before the preceding line.

#endif // !defined(AFX_SRTLM_H__856265B9_C462_4623_9EC9_A6755D3F35E2__INCLUDED_)
