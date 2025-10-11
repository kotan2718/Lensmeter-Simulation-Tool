
//*  DpNumCtrl class
//*  Original Author: Masakazu Irie
//*  Modified by: Kazuo Kawamura (for SRTLM project)
//*
//*  Please see the LICENSE file for detailed license terms of this code.


#if !defined(AFX_DpNumCtrl_H__955A2301_C2C3_11D3_89EA_0040C7990626__INCLUDED_)
#define AFX_DpNumCtrl_H__955A2301_C2C3_11D3_89EA_0040C7990626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DpNumCtrl.h : Header file
//
//
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CDpNumCtrl Window

class CDpNumCtrl : public CEdit
{
// Construction
public:
    CDpNumCtrl();

// Attribute
public:

// Operation
public:

// Override
    // ClassWizard generates virtual function overrides.
    //{{AFX_VIRTUAL(CDpNumCtrl)
    //}}AFX_VIRTUAL

// Implementation
public:
    BOOL CDpNumCtrl::SetData(double dValue1, double dValue2, int iEditType, int iType);
    double GetData();
    virtual ~CDpNumCtrl();

    BOOL CDpNumCtrl::DpSetData0(double dValue1, double dValue2, int type);
    BOOL CDpNumCtrl::DpSetData1(double dValue1, int type);
    BOOL CDpNumCtrl::DpSetData2(double dValue1, int type);
    BOOL CDpNumCtrl::DpSetData3(double dValue1, int type);
    BOOL CDpNumCtrl::DpSetData4(double dValue1, int type);
    BOOL CDpNumCtrl::DpSetData5(double dValue1, double dValue2, int type);

    void CDpNumCtrl::DpCharacterCheck0(UINT nChar);
    void CDpNumCtrl::DpCharacterCheck1(UINT nChar);
    void CDpNumCtrl::DpCharacterCheck2(UINT nChar);
    void CDpNumCtrl::DpCharacterCheck3(UINT nChar);
    void CDpNumCtrl::DpCharacterCheck4(UINT nChar);
    void CDpNumCtrl::DpCharacterCheck5(UINT nChar);

    void CDpNumCtrl::DpKeyFetch0(UINT nChar);
    void CDpNumCtrl::DpKeyFetch1(UINT nChar);
    void CDpNumCtrl::DpKeyFetch2(UINT nChar);
    void CDpNumCtrl::DpKeyFetch3(UINT nChar);
    void CDpNumCtrl::DpKeyFetch4(UINT nChar);
    void CDpNumCtrl::DpKeyFetch5(UINT nChar);

    void CDpNumCtrl::DpLButtonDown0(int pos);
    void CDpNumCtrl::DpLButtonDown1(int pos);
    void CDpNumCtrl::DpLButtonDown2(int pos);
    void CDpNumCtrl::DpLButtonDown3(int pos);
    void CDpNumCtrl::DpLButtonDown4(int pos);
    void CDpNumCtrl::DpLButtonDown5(int pos);

    // Generated Message Map Function
protected:
    afx_msg void OnClearLatitude();
    afx_msg void OnClearField();
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnNcPaint();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
    char m_sSecondsString[7];
    enum {    MN_CLEAR_LATITUDE    =    1,
              MN_CLEAR_FIELD       =    2};

    int m_iType;
    double m_dValue1;
    double m_dValue2;
    int    m_nChar;
    int    m_pos;

    //* Display of refractive power
    int m_iIntMaxPlus;
    int m_iIntMaxMinus;

    int m_iMax;
    int m_iMin;

    void FormatAndDisplay();

    //* The following are used to mark the beginning and ending positions
    //* of the individual fields in the formatted display.

    enum {  //*                           [+,-] 0 0 0 . 0 0 0
            SIGN_FIELD_START        = 0,    //* +/- sign             start position.
            SIGN_FIELD_STOP         = 1,    //* +/- sign             stop position (+1).
            INT_THIRD_FIELD_START   = 1,    //* hundreds place       start position.
            INT_THIRD_FIELD_STOP    = 2,    //* hundreds place       stop position (+1).
            INT_SECOND_FIELD_START  = 2,    //* tens place           start position.
            INT_SECOND_FIELD_STOP   = 3,    //* tens place           stop position (+1).
            INT_FIRST_FIELD_START   = 3,    //* ones place           start position.
            INT_FIRST_FIELD_STOP    = 4,    //* ones place           stop position (+1).
            FRAC_FIRST_FIELD_START  = 5,    //* first decimal place  start position.
            FRAC_FIRST_FIELD_STOP   = 6,    //* first decimal place  stop position (+1).
            FRAC_SECOND_FIELD_START = 6,    //* second decimal place start position.
            FRAC_SECOND_FIELD_STOP  = 7,    //* second decimal place stop position (+1).
            FRAC_THIRD_FIELD_START  = 7,    //* third decimal place  start position.
            FRAC_THIRD_FIELD_STOP   = 8};   //* third decimal place  stop position (+1).

            //* Refractive power     [+,-]00.00
            //* Axis                     000.0
            //* Refractive index           0.000
            //* Lens position, tilt  [+,-]00.0
            //* Lens thickness            00.00


    //* The following two variables are used to mark the beginning and ending
    //* positions of the field we are currently on.  That is, the field currently
    //* highlighted.
    int m_SelStop;
    int m_SelStart;


//*    Numerical Data Structure
    //* Refractive power
    CString m_strSign;              //* The current sign setting.
    int m_iIntThird;                //* The current integer  hundreds place.
    int m_iIntSecond;               //* The current integer  tens place.
    int m_iIntFirst;                //* The current integer  ones place.
    int m_iFracFirst;               //* The current fraction first place.
    int m_iFracSecond;              //* The current fraction second place.
    int m_iFracThird;               //* The current fraction third place.

    double m_dNumValue;             //* The current numerical value.
    int m_iNumDispType;
public:
//    afx_msg void OnEditAx2();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ inserts additional declarations immediately before the preceding line.

#endif // !defined(AFX_DpNumCtrl_H__955A2301_C2C3_11D3_89EA_0040C7990626__INCLUDED_)
