
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

BOOL CDpNumCtrl::DpSetData3(double dValue, int type)
{
    //* Rounded to the second decimal place
    m_dNumValue = _wtof(str_cvt(dValue * 100.0, 0)) / 100.0;
    m_iType = type;
    //
    switch(m_iType) {
    case 0:    //* Lens Position, Tilt
        m_iIntMaxPlus = 45;
        m_iIntMaxMinus = 45;
        break;
    }

    if (m_dNumValue > 0.0) {
        m_strSign = "+";
        if (m_dNumValue > double(m_iIntMaxPlus))
            m_dNumValue = double(m_iIntMaxPlus);
    }
    else {
        m_strSign = "-";
        if (m_dNumValue < -double(m_iIntMaxMinus))
            m_dNumValue = -double(m_iIntMaxMinus);
    }
    double dDmy = fabs(m_dNumValue);
    m_iIntSecond = int(floor(dDmy / 10.0));
    m_iIntFirst = int(floor(dDmy - m_iIntSecond * 10.0));
    dDmy = (dDmy - floor(dDmy)) * 100.0;
    m_iFracFirst = int(floor(dDmy / 10.0));

    int iIntTmp = m_iIntSecond * 10 + m_iIntFirst;

    if (m_iFracFirst > 9) {
        m_iFracFirst = 0;
        m_iIntFirst++;
        if (m_iIntFirst > 9) {
            m_iIntFirst = 0;
            m_iIntSecond++;
        }
        if(m_dNumValue >= 0.0) {
            if (iIntTmp > m_iIntMaxPlus) {
                //* m_iIntMaxPlus = 45
                m_iIntSecond = int(floor(double(m_iIntMaxPlus) / 10.0));
                m_iIntFirst = m_iIntMaxPlus - m_iIntSecond;
            }
        }
        else {
            if (iIntTmp > m_iIntMaxMinus) {
                //* m_iIntMaxMinus = 45
                m_iIntSecond = int(floor(double(m_iIntMaxMinus) / 10.0));
                m_iIntFirst = m_iIntMaxMinus - m_iIntSecond;
            }
        }
    }
    //
    //
    return TRUE;
}

/////////////////////////////////////////
//* Character Check
/////////////////////////////////////////
void CDpNumCtrl::DpCharacterCheck3(UINT nChar)
{
    switch(m_iType) {
        case 0:    //* Lens Position, Tilt
            m_iIntMaxPlus = 45;
            m_iIntMaxMinus = 45;
            break;
    }
    int iIntTmp = m_iIntSecond * 10 + m_iIntFirst;

    int tmpnum = 0;
    double ftmpnum = 0.0;
    _TCHAR str[2];
    switch (m_SelStart) {
        case SIGN_FIELD_START:
            //
            if (
                (nChar != ' ') && (nChar != '+') && (nChar != '-')
                )
                return;
            if (m_iType == 0) {
                if ((nChar == ' ') || (nChar == '+')) {
                    m_strSign = "+";
                } else if ((nChar == '-')) {
                    m_strSign = "-";
                }
            } else {
                if ((nChar == ' ') || (nChar == '+')) {
                    m_strSign = "+";
                }
                else if ((nChar == '-')) {
                    m_strSign = "-";
                }
            }
            m_SelStart = INT_SECOND_FIELD_START;
            m_SelStop = INT_SECOND_FIELD_STOP;
            break;
        case INT_SECOND_FIELD_START:
            //
            if ((nChar < 48) || (nChar > 53)) { //* The values that can be used in the tens place are 0,1,2,3,4.
                return;
            }
            str[0] = (char) nChar;
            str[1] = '\0';
            tmpnum = _wtoi(str);
            //
            if(m_strSign == "+") {
                if (tmpnum * 100 + m_iIntFirst * 10 + m_iFracFirst <= m_iIntMaxPlus * 10) {
                    m_iIntSecond = tmpnum;

                    m_SelStart = INT_FIRST_FIELD_START;
                    m_SelStop = INT_FIRST_FIELD_STOP;
                }
            }
            if(m_strSign == "-") {
                if (tmpnum * 100 + m_iIntFirst * 10 + m_iFracFirst <= m_iIntMaxMinus * 10) {
                    m_iIntSecond = tmpnum;

                    m_SelStart = INT_FIRST_FIELD_START;
                    m_SelStop = INT_FIRST_FIELD_STOP;
                }
            }
            break;
        case INT_FIRST_FIELD_START:
            //
            if ((nChar < 48) || (nChar > 57)) {
                return;
            }
            str[0] = (char) nChar;
            str[1] = '\0';
            tmpnum = _wtoi(str);
            //
            if(m_strSign == "+") {
                if (m_iIntSecond * 100 + tmpnum * 10 + m_iFracFirst <= m_iIntMaxPlus * 10) {
                    m_iIntFirst = tmpnum;

                    m_SelStart = FRAC_FIRST_FIELD_START;
                    m_SelStop = FRAC_FIRST_FIELD_STOP;
                }
            }
            if(m_strSign == "-") {
                if (m_iIntSecond * 100 + tmpnum * 10 + m_iFracFirst <= m_iIntMaxMinus * 10) {
                    m_iIntFirst = tmpnum;

                    m_SelStart = FRAC_FIRST_FIELD_START;
                    m_SelStop = FRAC_FIRST_FIELD_STOP;
                }
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
            if(m_strSign == "+") {
                if (iIntTmp * 10 + tmpnum <= m_iIntMaxPlus * 10) {
                    m_iFracFirst = tmpnum;
                }
            }
            if(m_strSign == "-") {
                if (iIntTmp * 10 + tmpnum  <= m_iIntMaxMinus * 10) {
                    m_iFracFirst = tmpnum;
                }
            }
            break;
    }
    //
}
/////////////////////////////////////////////
//* Key Fetch
/////////////////////////////////////////////
void CDpNumCtrl::DpKeyFetch3(UINT nChar)
{
    switch(m_iType) {
        case 0:    //* Lens Position, Tilt
            m_iIntMaxPlus = 45;
            m_iIntMaxMinus = 45;
            break;
    }
    int iIntTmp = m_iIntSecond * 10 + m_iIntFirst;

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
                case SIGN_FIELD_START:
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
            }
            break;
        case VK_UP:
            switch (m_SelStart) {
                case SIGN_FIELD_START:
                    if (m_iType == 0) {
                        if (m_strSign == "+") {
                            m_strSign = "-";
                        } else {
                            m_strSign = "+";
                        }
                    } else {
                        if (m_strSign == "+") {
                            m_strSign = "-";
                        } else {
                            m_strSign = "+";
                        }
                    }
                    break;
                case INT_SECOND_FIELD_START:
                    if(m_strSign == "+") {
                        m_iIntSecond++;
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > m_iIntMaxPlus * 10) {
                            m_iIntSecond--;
                        }
                    } else {
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > 0) {
                            m_iIntSecond--;
                            if(m_iIntSecond < 0) {
                                m_strSign = "+";
                                m_iIntSecond = 0;
                                double dDmy = 100.0 - double(m_iIntFirst * 10.0 + m_iFracFirst);
                                m_iIntFirst = int(floor(dDmy / 10.0));
                                dDmy = dDmy - double(m_iIntFirst) * 10.0;
                                m_iFracFirst = int(floor(dDmy));
                            }
                        }
                    }
                    break;
                case INT_FIRST_FIELD_START:
                    if(m_strSign == "+") {
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst < m_iIntMaxPlus * 10) {
                            m_iIntFirst++;
                        }
                        if(m_iIntFirst > 9) {
                            m_iIntFirst = 0;
                            m_iIntSecond++;
                        }
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > m_iIntMaxPlus * 10) {
                            m_iIntFirst--;
                        }
                    } else {
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > 0) {
                            m_iIntFirst--;
                            if(m_iIntFirst < 0) {
                                m_iIntFirst = 9;
                                m_iIntSecond--;
                                if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst <= 0) {
                                    m_strSign = "+";
                                    m_iIntFirst = 0;
                                    m_iIntSecond++;
                                    double dDmy = 10.0 - double(m_iFracFirst);
                                    m_iFracFirst = int(floor(dDmy));
                                }
                            }
                        }
                    }
                    break;
                case FRAC_FIRST_FIELD_START:
                    if (m_strSign == "+") {
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst < m_iIntMaxPlus * 10) {
                            m_iFracFirst++;
                        }
                        if(m_iFracFirst > 9) {
                            m_iFracFirst = 0;
                            m_iIntFirst++;
                            if(m_iIntFirst > 9) {
                                m_iIntFirst = 0;
                                m_iIntSecond++;
                            }
                            if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > m_iIntMaxPlus * 10) {
                                m_iIntFirst--;
                                m_iFracFirst = 9;
                            }
                        }
                    } else {
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > 0) {
                            m_iFracFirst--;
                            if(m_iFracFirst < 0) {
                                m_iFracFirst = 9;
                                m_iIntFirst--;
                                if(m_iIntFirst < 0) {
                                    m_iIntFirst = 9;
                                    m_iIntSecond--;
                                    if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst <= 0) {
                                        m_strSign = "+";
                                        m_iIntFirst = 0;
                                        m_iIntSecond++;
                                        m_iFracFirst =0;
                                    }
                                }
                            }
                        }
                    }
                    break;
            }
            break;
        case VK_DOWN:
            switch (m_SelStart) {
                case SIGN_FIELD_START:
                    if (m_iType == 0) {
                        if (m_strSign == "+") {
                            m_strSign = "-";
                        } else {
                            m_strSign = "+";
                        }
                    } else {
                        if (m_strSign == "+") {
                            m_strSign = "-";
                        }
                        else {
                            m_strSign = "+";
                        }
                    }
                    break;
                case INT_SECOND_FIELD_START:
                    //* This is processed in the same format as m_iInfFirst and m_iFracFirst.
                    if(m_strSign == "+") {
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > 0) {
                            m_iIntSecond--;
                            if(m_iIntSecond < 0) {
                                m_strSign = "-";
                                m_iIntSecond = 0;
                                double dDmy = 100.0 - double(m_iIntFirst * 10.0 + m_iFracFirst);
                                m_iIntFirst = int(floor(dDmy / 10.0));
                                dDmy = dDmy - double(m_iIntFirst) * 10.0;
                                m_iFracFirst = int(floor(dDmy));
                            }
                        } else if(m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst == 0) {
                            m_strSign = "-";
                            m_iIntSecond = 1;
                        }
                    } else {
                        m_iIntSecond++;
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > m_iIntMaxMinus * 10) {
                            m_iIntSecond--;
                        }
                    }
                    break;
                case INT_FIRST_FIELD_START:
                    if(m_strSign == "+") {
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > 0) {
                            m_iIntFirst--;
                            if(m_iIntFirst < 0) {
                                m_iIntFirst = 9;
                                m_iIntSecond--;
                                if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst <= 0) {
                                    m_strSign = "-";
                                    m_iIntFirst = 0;
                                    m_iIntSecond++;
                                    double dDmy = 10.0 - double(m_iFracFirst);
                                    m_iFracFirst = int(floor(dDmy));
                                }
                            }
                        }
                        else if(m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst == 0) {
                            m_strSign = "-";
                            m_iIntFirst = 1;
                        }
                    } else {
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst < m_iIntMaxMinus * 10) {
                            m_iIntFirst++;
                        }
                        if(m_iIntFirst > 9) {
                            m_iIntFirst = 0;
                            m_iIntSecond++;
                        }
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > m_iIntMaxMinus * 10) {
                            m_iIntFirst--;
                        }
                    }
                    break;
                case FRAC_FIRST_FIELD_START:
                    if (m_strSign == "+")  {
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > 0) {
                            m_iFracFirst--;
                            if(m_iFracFirst < 0) {
                                m_iFracFirst = 9;
                                m_iIntFirst--;
                                if(m_iIntFirst < 0) {
                                    m_iIntFirst = 9;
                                    m_iIntSecond--;
                                    if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst <= 0) {
                                        m_strSign = "-";
                                        m_iIntFirst = 0;
                                        m_iIntSecond++;
                                        m_iFracFirst =0;
                                    }
                                }
                            }
                        } else if(m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst == 0) {
                            m_strSign = "-";
                            m_iFracFirst = 1;
                        }
                    } else {
                        if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst < m_iIntMaxMinus * 10) {
                            m_iFracFirst++;
                        }
                        if(m_iFracFirst > 9) {
                            m_iFracFirst = 0;
                            m_iIntFirst++;
                            if(m_iIntFirst > 9) {
                                m_iIntFirst = 0;
                                m_iIntSecond++;
                            }
                            if (m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst > m_iIntMaxMinus * 10) {
                                m_iIntFirst--;
                                m_iFracFirst = 9;
                            }
                        }
                    }
                    break;
            }
            break;
        case VK_RIGHT:
            switch (m_SelStart) {
                case SIGN_FIELD_START:
                    m_SelStart = INT_SECOND_FIELD_START;
                    break;
                case INT_SECOND_FIELD_START:
                    m_SelStart = INT_FIRST_FIELD_START;
                    break;
                case INT_FIRST_FIELD_START:
                    m_SelStart = FRAC_FIRST_FIELD_START;
                    break;
                case FRAC_FIRST_FIELD_START:
                    m_SelStart = SIGN_FIELD_START;
                    break;
            }
            switch (m_SelStop) {
                case SIGN_FIELD_STOP:
                    m_SelStop = INT_SECOND_FIELD_STOP;
                    break;
                case INT_SECOND_FIELD_STOP:
                    m_SelStop = INT_FIRST_FIELD_STOP;
                    break;
                case INT_FIRST_FIELD_STOP:
                    m_SelStop = FRAC_FIRST_FIELD_STOP;
                    break;
                case FRAC_FIRST_FIELD_STOP:
                    m_SelStop = SIGN_FIELD_STOP;
                    break;
            }
            break;
        case VK_LEFT:
            switch (m_SelStart) {
                case SIGN_FIELD_START:
                    m_SelStart = FRAC_FIRST_FIELD_START;
                    break;
                case INT_SECOND_FIELD_START:
                    m_SelStart = SIGN_FIELD_START;
                    break;
                case INT_FIRST_FIELD_START:
                    m_SelStart = INT_SECOND_FIELD_START;
                    break;
                case FRAC_FIRST_FIELD_START:
                    m_SelStart = INT_FIRST_FIELD_START;
                    break;
            }
            switch (m_SelStop) {
                case SIGN_FIELD_STOP:
                    m_SelStop = FRAC_FIRST_FIELD_STOP;
                    break;
                case INT_SECOND_FIELD_STOP:
                    m_SelStop = SIGN_FIELD_STOP;
                    break;
                case INT_FIRST_FIELD_STOP:
                    m_SelStop = INT_SECOND_FIELD_STOP;
                    break;
                case FRAC_FIRST_FIELD_STOP:
                    m_SelStop = INT_FIRST_FIELD_STOP;
                    break;
            }
            break;
    }
}

/////////////////////////////////////////////
//* Left mouse button (field specification)
/////////////////////////////////////////////
void CDpNumCtrl::DpLButtonDown3(int pos)
{
    if (pos <= (SIGN_FIELD_STOP)) {
        //* AfxMessageBox("Pos Hi!");
        m_SelStart = SIGN_FIELD_START;
        m_SelStop = SIGN_FIELD_STOP;
    } else if ((pos >= INT_SECOND_FIELD_START) && (pos <= INT_SECOND_FIELD_STOP)) {
        m_SelStart = INT_SECOND_FIELD_START;
        m_SelStop = INT_SECOND_FIELD_STOP;
    } else if ((pos >= INT_FIRST_FIELD_START) && (pos <= INT_FIRST_FIELD_STOP)) {
        m_SelStart = INT_FIRST_FIELD_START;
        m_SelStop = INT_FIRST_FIELD_STOP;
    } else if ((pos >= FRAC_FIRST_FIELD_START) && (pos <= FRAC_FIRST_FIELD_STOP)) {
        m_SelStart = FRAC_FIRST_FIELD_START;
        m_SelStop = FRAC_FIRST_FIELD_STOP;
    }
}