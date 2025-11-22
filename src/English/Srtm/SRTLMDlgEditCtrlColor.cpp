
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




//* Background color of Edit Controls that users cannot change

HBRUSH CSRTLMDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr;

    switch (nCtlColor)
    {
    case CTLCOLOR_EDIT:
    case CTLCOLOR_MSGBOX:
    case CTLCOLOR_STATIC:       //* 20251029 (Ver.2.25.0) Added background color settings to Static Edit
        switch (pWnd->GetDlgCtrlID())
        {
        case IDC_EDIT_SPH:
        case IDC_EDIT_CYL:
        case IDC_EDIT_N:
        case IDC_EDIT_T:
        case IDC_EDIT_CURVE:
        case IDC_EDIT_AX2:
            pDC->SetBkColor(m_IjiruyoiColor); // change the background color
            // pDC->SetTextColor(m_textcolor); // change the text color
            hbr = (HBRUSH) m_IjiruyoiBrush; //  apply the brush
            break;

        case IDC_EDIT_TARGET_DPT:
        case IDC_EDIT_LP_X:
        case IDC_EDIT_LP_Y:
        case IDC_EDIT_L_TILT_X:
        case IDC_EDIT_L_TILT_Y:
        case IDC_EDIT_PG_DEG:
        case IDC_EDIT_AX:
        case IDC_EDIT_R1:       //* 20251029 (Ver.2.25.0) Changed to Static Text
        case IDC_EDIT_R2_MIN:   //* 20251029 (Ver.2.25.0) Changed to Static Text
        case IDC_EDIT_R2_MAX:   //* 20251029 (Ver.2.25.0) Changed to Static Text
            pDC->SetBkColor(m_IjirunaColor); // change the background color
            // pDC->SetTextColor(m_textcolor); // change the text color
            hbr = (HBRUSH) m_IjirunaBrush; //  apply the brush
            break;

        // otherwise do default handling of OnCtlColor
        default:
            hbr=CDialog::OnCtlColor(pDC,pWnd,nCtlColor);
            break;
        }
        break;

    // otherwise do default handling of OnCtlColor
    default:
        hbr=CDialog::OnCtlColor(pDC,pWnd,nCtlColor);
    }

    return hbr; // return brush
}

