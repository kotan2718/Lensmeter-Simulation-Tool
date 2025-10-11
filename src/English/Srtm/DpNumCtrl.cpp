
//*  DpNumCtrl class
//*  Original Author: Masakazu Irie
//*  Modified by: Kazuo Kawamura (for SRTLM project)
//*
//*  Please see the LICENSE file for detailed license terms of this code.


// DpNumCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DpNumCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDpNumCtrl

CDpNumCtrl::CDpNumCtrl()
{
    //* Refractive Power
    m_strSign =   "+";
    m_iIntThird =   0;
    m_iIntSecond =  0;
    m_iIntFirst =   0;
    m_iFracFirst =  0;
    m_iFracSecond = 0;
    m_iFracThird =  0;

    m_SelStart =   -1;
    m_SelStop =    -1;
}

CDpNumCtrl::~CDpNumCtrl()
{
}


BEGIN_MESSAGE_MAP(CDpNumCtrl, CEdit)
    ON_COMMAND(MN_CLEAR_LATITUDE,OnClearLatitude)
    ON_COMMAND(MN_CLEAR_FIELD,OnClearField)
    //{{AFX_MSG_MAP(CDpNumCtrl)
    ON_WM_SETFOCUS()
    ON_WM_CHAR()
    ON_WM_KEYDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_NCPAINT()
    ON_WM_RBUTTONUP()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDpNumCtrl message handlers


void CDpNumCtrl::OnSetFocus(CWnd* pOldWnd)
{
    //
    CEdit::OnSetFocus(pOldWnd);
    //
    m_SelStart = SIGN_FIELD_START;
    m_SelStop = SIGN_FIELD_STOP;
    SetSel(m_SelStart,m_SelStop);
    HideCaret();
}



BOOL CDpNumCtrl::SetData(double dValue1, double dValue2, int iEditType, int iType)
{
    m_iNumDispType = iEditType;
    //
    m_dValue1 = dValue1;
    m_dValue2 = dValue2;
    m_iType = iType;
    switch(m_iNumDispType)
    {
    case 0:    //* Refractive Power
        DpSetData0(m_dValue1, m_dValue2, m_iType);
        break;
    case 1:    //* Axis Direction of Lens
        DpSetData1(m_dValue1, m_iType);
        break;
    case 2:    //* Refractive Index
        DpSetData2(m_dValue1, m_iType);
        break;
    case 3:    //* Lens Position, Tilt
        DpSetData3(m_dValue1, m_iType);
        break;
    case 4:    //* Lens Thickness
        DpSetData4(m_dValue1, m_iType);
        break;
    case 5:    //* Lens Curve
        DpSetData5(m_dValue1, m_dValue2, m_iType);
        break;
    }

    FormatAndDisplay();
    return TRUE;
}

double CDpNumCtrl::GetData()
{
    int iIntTmp = m_iIntThird * 100 + m_iIntSecond * 10 + m_iIntFirst;
    int iFracTmp = m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;

    double result = double(iIntTmp);
    if (iFracTmp > 0.0) {
        result += double(iFracTmp) / 1000.0;
    }
    if (m_strSign == "-") {
        result = -result;
    }

    return result;
}



///////////////////////////////////////////
//* Format display routine
void CDpNumCtrl::FormatAndDisplay()
///////////////////////////////////////////
{
    CString cStrBuf;

    switch(m_iNumDispType)
    {
    case 0:    //* Refractive Power
        {
            //* Key fetch conversion from “-0.00 => +0.00” for “VK_UP”.
            //* Conversion from “ + 0.00 = > -0.00” for “VK_DOWN” is described in OnKeyDown().
            if(m_iIntSecond == 0 && m_iIntFirst == 0 && m_iFracFirst == 0 && m_iFracSecond == 0) {
                m_strSign = "+";
            }
            cStrBuf.Format(_T("%s %01d%01d.%01d%01d"), m_strSign, m_iIntSecond, m_iIntFirst, m_iFracFirst, m_iFracSecond);
            break;
        }
    case 1:    //* Axis Direction of Lens
        {
            int iIntThird = m_iIntThird;
            int iIntSecond = m_iIntSecond;
            int iIntFirst = m_iIntFirst;
            int iFrac = m_iFracFirst;
            if(iIntThird == 0 && iIntSecond == 0 && iIntFirst == 0 && iFrac == 0) {
                iIntThird = 1;
                iIntSecond = 8;
                iIntFirst = 0;
                iFrac = 0;
            }
            cStrBuf.Format(_T(" %01d%01d%01d.%01d"), iIntThird, iIntSecond, iIntFirst, iFrac);
            break;
        }
    case 2:    //* Refractive Index
        {
            cStrBuf.Format(_T("   %01d.%01d%01d%01d"), m_iIntFirst, m_iFracFirst, m_iFracSecond, m_iFracThird);
            break;
        }
    case 3:    //* Lens Position, Tilt
        {
        //* Key fetch conversion from “-0.00 => +0.00” for “VK_UP”.
        //* Conversion from “ + 0.00 = > -0.00” for “VK_DOWN” is described in OnKeyDown().
        if(m_iIntSecond == 0 && m_iIntFirst == 0 && m_iFracFirst == 0 ) {
                m_strSign = "+";
            }
            cStrBuf.Format(_T("%s %01d%01d.%01d"), m_strSign, m_iIntSecond, m_iIntFirst, m_iFracFirst);
            break;
        }
    case 4:    //* Lens Thickness
        {
            cStrBuf.Format(_T("  %01d%01d.%01d%01d"), m_iIntSecond, m_iIntFirst, m_iFracFirst, m_iFracSecond);
            break;
        }
    case 5:    //* Lens Curve
        {
            cStrBuf.Format(_T("%s %01d%01d.%01d%01d"), m_strSign, m_iIntSecond, m_iIntFirst, m_iFracFirst, m_iFracSecond);
            break;
        }
    }

    SetWindowText(cStrBuf);
    UpdateData(FALSE);
    SetSel(m_SelStart,m_SelStop);

}

/////////////////////////////////////////
//* Character Check
void CDpNumCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
/////////////////////////////////////////
{
    m_nChar = nChar;
    switch(m_iNumDispType)
    {
    case 0:    //* Refractive Power
        DpCharacterCheck0(m_nChar);
        break;
    case 1:    //* Axis Direction of Lens
        DpCharacterCheck1(m_nChar);
        break;
    case 2:    //* Refractive Index
        DpCharacterCheck2(m_nChar);
        break;
    case 3:    //* Lens Position, Tilt
        DpCharacterCheck3(m_nChar);
        break;
    case 4:    //* Lens Thickness
        DpCharacterCheck4(m_nChar);
        break;
    case 5:    //* Lens Curve
        DpCharacterCheck5(m_nChar);
        break;
    }
    //
    FormatAndDisplay();
}
////////////////////////////////////////////
//* Key Fetch
void CDpNumCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
////////////////////////////////////////////
{
    m_nChar = nChar;
    switch(m_iNumDispType)
    {
    case 0:    //* Refractive Power
        DpKeyFetch0(m_nChar);
        break;
    case 1:    //* Axis Direction of Lens
        DpKeyFetch1(m_nChar);
        break;
    case 2:    //* Refractive Index
        DpKeyFetch2(m_nChar);
        break;
    case 3:    //* Lens Position, Tilt
        DpKeyFetch3(m_nChar);
        break;
    case 4:    //* Lens Thickness
        DpKeyFetch4(m_nChar);
        break;
    case 5:    //* Lens Curve
        DpKeyFetch5(m_nChar);
        break;
    }

    FormatAndDisplay();
}
/////////////////////////////////////
//* Left mouse button (field specification)
void CDpNumCtrl::OnLButtonDown(UINT nFlags, CPoint point)
/////////////////////////////////////
{
    //* Standard routine
    CEdit::OnLButtonDown(nFlags, point);
    m_pos = this->CharFromPos(point);
    switch(m_iNumDispType)
    {
    case 0:    //* Refractive Power
        DpLButtonDown0(m_pos);
        break;
    case 1:    //* Axis Direction of Lens
        DpLButtonDown1(m_pos);
        break;
    case 2:    //* Refractive Index
        DpLButtonDown2(m_pos);
        break;
    case 3:    //* Lens Position, Tilt
        DpLButtonDown3(m_pos);
        break;
    case 4:    //* Lens Thickness
        DpLButtonDown4(m_pos);
        break;
    case 5:    //* Lens Curve
        DpLButtonDown5(m_pos);
        break;
    }
    //
    CEdit::SetSel(m_SelStart,m_SelStop);
    HideCaret();
}

void CDpNumCtrl::OnNcPaint()
{
    FormatAndDisplay();
    CEdit::OnNcPaint();
    HideCaret();
}

void CDpNumCtrl::OnClearLatitude()
{
    m_iIntThird = 0;
    m_iIntSecond = 0;
    m_iIntFirst = 0;
    m_iFracFirst = 0;
    m_iFracSecond = 0;
    m_iFracThird = 0;
    FormatAndDisplay();
}
///////////////////////////////////////////
//* Current field clear routine
void CDpNumCtrl::OnClearField()
///////////////////////////////////////////
{
    switch (m_SelStart)
    {
    case INT_THIRD_FIELD_START:
        m_iIntThird = 0;
        break;
    case INT_SECOND_FIELD_START:
        m_iIntSecond = 0;
        break;
    case INT_FIRST_FIELD_START:
        m_iIntFirst = 0;
        break;
    case FRAC_FIRST_FIELD_START:
        m_iFracFirst = 0;
        break;
    case FRAC_SECOND_FIELD_START:
        m_iFracSecond = 0;
        break;
    case FRAC_THIRD_FIELD_START:
        m_iFracThird = 0;
        break;
    }
    FormatAndDisplay();
}
//
/////////////////////////////////////////////////////
//
//* Cancel routine for standard operation
//
/////////////////////////////////////////////////////
//
//////////////////////////////////////////////
//* To disable drag and drop
void CDpNumCtrl::OnMouseMove(UINT nFlags, CPoint point)
//////////////////////////////////////////////
{
}
//////////////////////////////////////////////
//* To disable of double-click
void CDpNumCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
//////////////////////////////////////////////
{
}
//////////////////////////////////////////////
//*A no-action handler to prevent displaying CEdit's standard track menu
void CDpNumCtrl::OnRButtonUp(UINT nFlags, CPoint point)
//////////////////////////////////////////////
{
}

