
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
        switch (pWnd->GetDlgCtrlID())
        {
        case IDC_EDIT_SPH:
            pDC->SetBkColor(m_IjiruyoiColor); // change the background color
            // pDC->SetTextColor(m_textcolor); // change the text color
            hbr = (HBRUSH) m_IjiruyoiBrush; //  apply the brush
            break;
        case IDC_EDIT_CYL:
            pDC->SetBkColor(m_IjiruyoiColor); // change the background color
            hbr = (HBRUSH) m_IjiruyoiBrush; //  apply the brush
            break;
        case IDC_EDIT_N:
            pDC->SetBkColor(m_IjiruyoiColor); // change the background color
            hbr = (HBRUSH) m_IjiruyoiBrush; //  apply the brush
            break;
        case IDC_EDIT_T:
            pDC->SetBkColor(m_IjiruyoiColor); // change the background color
            hbr = (HBRUSH) m_IjiruyoiBrush; //  apply the brush
            break;
        case IDC_EDIT_CURVE:
            pDC->SetBkColor(m_IjiruyoiColor); // change the background color
            hbr = (HBRUSH) m_IjiruyoiBrush; //  apply the brush
            break;
        case IDC_EDIT_AX2:
            pDC->SetBkColor(m_IjiruyoiColor); // change the background color
            // pDC->SetTextColor(m_textcolor); // change the text color
            hbr = (HBRUSH) m_IjiruyoiBrush; //  apply the brush
            break;

        case IDC_EDIT_TARGET_DPT:
            pDC->SetBkColor(m_IjirunaColor); // change the background color
            // pDC->SetTextColor(m_textcolor); // change the text color
            hbr = (HBRUSH) m_IjirunaBrush; //  apply the brush
            break;
        case IDC_EDIT_LP_X:
            pDC->SetBkColor(m_IjirunaColor); // change the background color
            hbr = (HBRUSH) m_IjirunaBrush; //  apply the brush
            break;
        case IDC_EDIT_LP_Y:
            pDC->SetBkColor(m_IjirunaColor); // change the background color
            hbr = (HBRUSH) m_IjirunaBrush; //  apply the brush
            break;
        case IDC_EDIT_L_TILT_X:
            pDC->SetBkColor(m_IjirunaColor); // change the background color
            hbr = (HBRUSH) m_IjirunaBrush; //  apply the brush
            break;
        case IDC_EDIT_L_TILT_Y:
            pDC->SetBkColor(m_IjirunaColor); // change the background color
            hbr = (HBRUSH) m_IjirunaBrush; //  apply the brush
            break;
        case IDC_EDIT_PG_DEG:
            pDC->SetBkColor(m_IjirunaColor); // change the background color
            hbr = (HBRUSH) m_IjirunaBrush; //  apply the brush
            break;
        case IDC_EDIT_AX:
            pDC->SetBkColor(m_IjirunaColor); // change the background color
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

