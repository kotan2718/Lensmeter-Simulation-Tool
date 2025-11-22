
//*  DpNumCtrl class
//*  Original Author: Masakazu Irie
//*  Modified by: Kazuo Kawamura (for SRTLM project)
//*
//*  Please see the LICENSE file for detailed license terms of this code.


// CDpNumCtrl.cpp : implementation file
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
/////////////////////////////////////////////////////////////////////////////
// CDpNumCtrl message handlers

BOOL CDpNumCtrl::DpSetData2(double dValue, int type)
{
    //* Round to the fourth decimal place
    m_dNumValue = _wtof(str_cvt(dValue * 1000.0, 0)) / 1000.0;
    m_dNumValue = dValue;
    m_iType = type;
    //
    switch(m_iType) {
        case 0:    //* Refractive Index
            m_iMax = 2500;
            m_iMin = 1000;
            break;
        }
    double dDmy = m_dNumValue;
    //* 1.523
    //* 1
    m_iIntFirst = int(floor(dDmy));

    //* 15.23 - 10.00 => 5.23
    dDmy = (dDmy - double(m_iIntFirst)) * 10.0;
    //* 5
    m_iFracFirst = int(floor(dDmy));
    //* 52.3 - 50.0 => 2.3
    dDmy = (dDmy - double(m_iFracFirst)) * 10.0;
    //* 2
    m_iFracSecond = int(floor(dDmy));
    //* 23.0 - 20.0 => 3.0
    dDmy = (dDmy - double(m_iFracSecond)) * 10.0;
    //* 3
    m_iFracThird = int(floor(dDmy));

    if (m_iFracThird > 9) {
        m_iFracThird = 0;
        m_iFracSecond++;
        if (m_iFracSecond > 9) {
            m_iFracSecond = 0;
            m_iFracFirst++;
        }
        if (m_iFracFirst > 9) {
            m_iFracFirst = 0;
            m_iIntFirst++;
        }
        if (m_iIntFirst > 2) {
            m_iIntFirst = 2;
        }
    }
    //
    //
    return TRUE;
}

/////////////////////////////////////////
//* Character Check
/////////////////////////////////////////
void CDpNumCtrl::DpCharacterCheck2(UINT nChar)
{
    int tmpnum = 0;
    int numSum = 0;
    _TCHAR str[2];
    switch (m_SelStart) {
        case INT_FIRST_FIELD_START:
            //
            if ((nChar < 49) || (nChar > 51)) { //* The values ​​that can take the ones digit are 1,2.
                return;
            }
            str[0] = (char) nChar;
            str[1] = '\0';
            tmpnum = _wtoi(str);
            //
            numSum = tmpnum * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
            if (numSum >= m_iMin && numSum <= m_iMax) {
                m_iIntFirst = tmpnum;

                m_SelStart = FRAC_FIRST_FIELD_START;
                m_SelStop = FRAC_FIRST_FIELD_STOP;
            }
            break;
        case FRAC_FIRST_FIELD_START:
            //
            if ((nChar < 48) || (nChar > 57)) {
                return;
            }
            str[0] = (char) nChar;
            str[1] = '\0';
            tmpnum = _wtoi(str);
            //
            numSum = m_iIntFirst * 1000 + tmpnum * 100 + m_iFracSecond * 10 + m_iFracThird;
            if (numSum >= m_iMin && numSum <= m_iMax) {
                m_iFracFirst = tmpnum;

                m_SelStart = FRAC_SECOND_FIELD_START;
                m_SelStop = FRAC_SECOND_FIELD_STOP;
            }
            break;
        case FRAC_SECOND_FIELD_START:
            //
            if ((nChar < 48) || (nChar > 57)) {
                return;
            }
            str[0] = (char) nChar;
            str[1] = '\0';
            tmpnum = _wtoi(str);
            //
            numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + tmpnum * 10 + m_iFracThird;
            if (numSum >= m_iMin && numSum <= m_iMax) {
                m_iFracSecond = tmpnum;

                m_SelStart = FRAC_THIRD_FIELD_START;
                m_SelStop = FRAC_THIRD_FIELD_STOP;
            }
            break;
        case FRAC_THIRD_FIELD_START:
            //
            if ((nChar < 48) || (nChar > 57)) {
                return;
            }
            str[0] = (char) nChar;
            str[1] = '\0';
            tmpnum = _wtoi(str);
            //
            numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + tmpnum;
            if (numSum >= m_iMin && numSum <= m_iMax) {
                m_iFracThird = tmpnum;

            }
            break;
    }
}

/////////////////////////////////////////////
//* Key Fetch
/////////////////////////////////////////////
void CDpNumCtrl::DpKeyFetch2(UINT nChar)
{
    int numSum;
    switch (nChar) {
        case VK_HOME:
            //* Clear the current location field
            OnClearField();
            break;
        case VK_DECIMAL:
            return;    //* The decimal point does nothing
            break;
        case VK_BACK:
            switch (m_SelStart) {
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
            break;
        case VK_UP:
            switch (m_SelStart) {
                case INT_FIRST_FIELD_START:
                    m_iIntFirst++;
                    numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                    if (numSum > m_iMax) {
                        m_iIntFirst--;
                    }
                    break;
                case FRAC_FIRST_FIELD_START:
                    m_iFracFirst++;
                    numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                    if (numSum > m_iMax) {
                        m_iFracFirst--;
                    }
                    if(m_iFracFirst > 9) {
                        m_iFracFirst = 0;
                        m_iIntFirst++;
                        numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                        if (numSum > m_iMax) {
                            m_iFracFirst--;
                        }
                    }
                    break;
                case FRAC_SECOND_FIELD_START:
                    m_iFracSecond++;
                    numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                    if (numSum > m_iMax) {
                        m_iFracSecond--;
                    }
                    if(m_iFracSecond > 9) {
                        m_iFracSecond = 0;
                        m_iFracFirst++;
                        numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                        if (numSum > m_iMax) {
                            m_iFracSecond--;
                        }
                        if(m_iFracFirst > 9) {
                            m_iFracFirst = 0;
                            m_iIntFirst++;
                            numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                            if (numSum > m_iMax) {
                                m_iFracFirst--;
                            }
                        }
                    }
                    break;
                case FRAC_THIRD_FIELD_START:
                    m_iFracThird++;
                    numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                    if (numSum > m_iMax) {
                        m_iFracThird--;
                    }
                    if(m_iFracThird > 9) {
                        m_iFracThird = 0;
                        m_iFracSecond++;
                        numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                        if (numSum > m_iMax) {
                            m_iFracThird--;
                        }
                        if(m_iFracSecond > 9) {
                            m_iFracSecond = 0;
                            m_iFracFirst++;
                            numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                            if (numSum > m_iMax) {
                                m_iFracSecond--;
                            }
                            if(m_iFracFirst > 9) {
                                m_iFracFirst = 0;
                                m_iIntFirst++;
                                numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                                if (numSum > m_iMax) {
                                    m_iFracFirst--;
                                }
                            }
                        }
                    }
                    break;
            }
            break;
        case VK_DOWN:
            switch (m_SelStart) {
                case INT_FIRST_FIELD_START:
                    m_iIntFirst--;
                    numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                    if (numSum < m_iMin) {
                        m_iIntFirst++;
                    }
                    break;
                case FRAC_FIRST_FIELD_START:
                    m_iFracFirst--;
                    numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                    if (numSum < m_iMin) {
                        m_iFracFirst++;
                    }
                    if(m_iFracFirst < 0) {
                        m_iFracFirst = 9;
                        m_iIntFirst--;
                        numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                        if (numSum < m_iMin) {
                            m_iFracFirst = 0;
                            m_iIntFirst++;
                        }
                    }
                    break;
                case FRAC_SECOND_FIELD_START:
                    m_iFracSecond--;
                    numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                    if (numSum < m_iMin) {
                        m_iFracSecond++;
                    }
                    if(m_iFracSecond < 0) {
                        m_iFracSecond = 9;
                        m_iFracFirst--;
                        numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                        if (numSum < m_iMin) {
                            m_iFracSecond = 0;
                            m_iFracFirst++;
                        }
                        if(m_iFracFirst < 0) {
                            m_iFracFirst = 9;
                            m_iIntFirst--;
                            numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                            if (numSum < m_iMin) {
                                m_iFracFirst = 0;
                                m_iIntFirst++;
                            }
                        }
                    }
                    break;
                case FRAC_THIRD_FIELD_START:
                    m_iFracThird--;
                    numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                    if (numSum < m_iMin) {
                        m_iFracThird++;
                    }
                    if(m_iFracThird < 0) {
                        m_iFracThird = 9;
                        m_iFracSecond--;
                        numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                        if (numSum < m_iMin) {
                            m_iFracThird = 0;
                            m_iFracSecond++;
                        }
                        if(m_iFracSecond < 0) {
                            m_iFracSecond = 9;
                            m_iFracFirst--;
                            numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                            if (numSum < m_iMin) {
                                m_iFracSecond = 0;
                                m_iFracFirst++;
                            }
                            if(m_iFracFirst < 0) {
                                m_iFracFirst = 9;
                                m_iIntFirst--;
                                numSum = m_iIntFirst * 1000 + m_iFracFirst * 100 + m_iFracSecond * 10 + m_iFracThird;
                                if (numSum < m_iMin) {
                                    m_iFracFirst = 0;
                                    m_iIntFirst++;
                                }
                            }
                        }
                    }
                    break;
            }
            break;
        case VK_RIGHT:
            switch (m_SelStart) {
                case SIGN_FIELD_START:
                    m_SelStart = INT_FIRST_FIELD_START;
                    break;
                case INT_FIRST_FIELD_START:
                    m_SelStart = FRAC_FIRST_FIELD_START;
                    break;
                case FRAC_FIRST_FIELD_START:
                    m_SelStart = FRAC_SECOND_FIELD_START;
                    break;
                case FRAC_SECOND_FIELD_START:
                    m_SelStart = FRAC_THIRD_FIELD_START;
                    break;
                case FRAC_THIRD_FIELD_START:
                    m_SelStart = INT_FIRST_FIELD_START;
                    break;
            }
            switch (m_SelStop) {
                case SIGN_FIELD_STOP:
                    m_SelStop = INT_FIRST_FIELD_STOP;
                    break;
                case INT_FIRST_FIELD_STOP:
                    m_SelStop = FRAC_FIRST_FIELD_STOP;
                    break;
                case FRAC_FIRST_FIELD_STOP:
                    m_SelStop = FRAC_SECOND_FIELD_STOP;
                    break;
                case FRAC_SECOND_FIELD_STOP:
                    m_SelStop = FRAC_THIRD_FIELD_STOP;
                    break;
                case FRAC_THIRD_FIELD_STOP:
                    m_SelStop = INT_FIRST_FIELD_STOP;
                    break;
            }
            break;
        case VK_LEFT:
            switch (m_SelStart) {
                case INT_FIRST_FIELD_START:
                    m_SelStart = FRAC_THIRD_FIELD_START;
                    break;
                case FRAC_FIRST_FIELD_START:
                    m_SelStart = INT_FIRST_FIELD_START;
                    break;
                case FRAC_SECOND_FIELD_START:
                    m_SelStart = FRAC_FIRST_FIELD_START;
                    break;
                case FRAC_THIRD_FIELD_START:
                    m_SelStart = FRAC_SECOND_FIELD_START;
                    break;
            }
            switch (m_SelStop) {
                case INT_FIRST_FIELD_STOP:
                    m_SelStop = FRAC_THIRD_FIELD_STOP;
                    break;
                case FRAC_FIRST_FIELD_STOP:
                    m_SelStop = INT_FIRST_FIELD_STOP;
                    break;
                case FRAC_SECOND_FIELD_STOP:
                    m_SelStop = FRAC_FIRST_FIELD_STOP;
                    break;
                case FRAC_THIRD_FIELD_STOP:
                    m_SelStop = FRAC_SECOND_FIELD_STOP;
                    break;
            }
            break;
    }
}

/////////////////////////////////////////////
//* Left mouse button (field specification)
/////////////////////////////////////////////
void CDpNumCtrl::DpLButtonDown2(int pos)
{
    if (pos <= (INT_FIRST_FIELD_STOP)) {
        //* AfxMessageBox("Index Hi!");
        m_SelStart = INT_FIRST_FIELD_START;
        m_SelStop = INT_FIRST_FIELD_STOP;
    } else if ((pos >= FRAC_FIRST_FIELD_START) && (pos <= FRAC_FIRST_FIELD_STOP)) {
        m_SelStart = FRAC_FIRST_FIELD_START;
        m_SelStop = FRAC_FIRST_FIELD_STOP;
    } else if ((pos >= FRAC_SECOND_FIELD_START) && (pos <= FRAC_SECOND_FIELD_STOP)) {
        m_SelStart = FRAC_SECOND_FIELD_START;
        m_SelStop = FRAC_SECOND_FIELD_STOP;
    } else if ((pos >= FRAC_THIRD_FIELD_START) && (pos <= FRAC_THIRD_FIELD_STOP)) {
        m_SelStart = FRAC_THIRD_FIELD_START;
        m_SelStop = FRAC_THIRD_FIELD_STOP;
    }
}