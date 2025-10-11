
//*  DpNumCtrl class
//*  Original Author: Masakazu Irie
//*  Modified by: Kazuo Kawamura (for SRTLM project)
//*
//*  Please see the LICENSE file for detailed license terms of this code.


// CDpNumCtrl.cpp : インプリメンテーション ファイル
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
// CDpNumCtrl メッセージ ハンドラ

BOOL CDpNumCtrl::DpSetData0(double dValue1, double dValue2, int type)
{
    // バグあり（修正:2000/9/23）
    // 川村拝借 2002/05/13
    // 小数第３位以下四捨五入
    m_dNumValue = _wtof(str_cvt(dValue1 * 1000.0, 0)) / 1000.0;
//    kko.Format(_T("%f"), m_dNumValue);AfxMessageBox( kko);
    m_iType = type;
    //
    switch(m_iType)
    {
    case 0:    // 屈折力
        // dValue2 はダミー
        m_iIntMaxPlus = 15;
        m_iIntMaxMinus = 25;
        break;
    case 1:    // 球面屈折力
        // dValue2 は現在の円柱レンズの度数
        // 小数第３位以下四捨五入
        dValue2 = _wtof(str_cvt(dValue2 * 1000.0, 0)) / 1000.0;
        if(dValue2 <= 0.0) {
            m_iIntMaxPlus = 15;
            m_iIntMaxMinus = 25 + int(dValue2);
        }
        else {
            m_iIntMaxPlus = 15 - int(dValue2);
            m_iIntMaxMinus = 25;
        }
//        kko.Format(_T("%.22f"), dValue2);AfxMessageBox( kko);
        break;
    case 2:    // 円柱屈折力
        // dValue2 は現在の円柱レンズの度数
        // 小数第３位以下四捨五入
        dValue2 = _wtof(str_cvt(dValue2 * 1000.0, 0)) / 1000.0;
        if(dValue2 <= 0.0) {
            m_iIntMaxPlus = 15;
            m_iIntMaxMinus = 25 + int(dValue2);
        }
        else {
            m_iIntMaxPlus = 15 - int(dValue2);
            m_iIntMaxMinus = 25;
        }
        break;
    case 3:    // レンズカーブ
        // dValue2 はダミー
        m_iIntMaxPlus = 15;
        m_iIntMaxMinus = 15;
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
    m_iFracSecond = int(floor(dDmy - m_iFracFirst * 10.0));

    int iIntTmp = m_iIntSecond * 10 + m_iIntFirst;

    if (m_iFracSecond > 9) {
        m_iFracSecond = 0;
        m_iFracFirst++;
        if (m_iFracFirst > 9) {
            m_iFracFirst = 0;
            m_iIntFirst++;
        }
        if (m_iIntFirst > 9) {
            m_iIntFirst = 0;
            m_iIntSecond++;
        }
        if(m_dNumValue >= 0.0) {
            if (iIntTmp > m_iIntMaxPlus) {
                // m_iIntMaxPlus = 15
                m_iIntSecond = int(floor(double(m_iIntMaxPlus) / 10.0));
                m_iIntFirst = m_iIntMaxPlus - m_iIntSecond;
            }
        }
        else {
            if (iIntTmp > m_iIntMaxMinus) {
                // m_iIntMaxMinus = 25
                m_iIntSecond = int(floor(double(m_iIntMaxMinus) / 10.0));
                m_iIntFirst = m_iIntMaxMinus - m_iIntSecond;
            }
        }
    }
    //
    //
    return TRUE;
}

// ///////////////////////////////////////
// キャラクタチェック
void CDpNumCtrl::DpCharacterCheck0(UINT nChar)
// ///////////////////////////////////////
{
    int iIntTmp = m_iIntSecond * 10 + m_iIntFirst;
    int iFracTmp = m_iFracFirst * 10 + m_iFracSecond;

    int tmpnum = 0;
    double ftmpnum = 0.0;
    _TCHAR str[2];
    switch (m_SelStart)
    {
    case SIGN_FIELD_START:
        //
        if ((nChar != ' ') && (nChar != '+') && (nChar != '-')) {
            return;
        }
        if (m_iType == 0) {
            if ((nChar == ' ') || (nChar == '+')) {
                m_strSign = "+";
            }
            else if ((nChar == '-')) {
                m_strSign = "-";
            }
        }
        else {
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
        if ((nChar < 48) || (nChar > 51)) return;   // 10の位がとれる値は 0,1,2
        str[0] = (char) nChar;
        str[1] = '\0';
        tmpnum = _wtoi(str);
        //
        if(m_strSign == "+") {
            if ((tmpnum * 10 + m_iIntFirst) * 100 + iFracTmp <= m_iIntMaxPlus * 100) {
                m_iIntSecond = tmpnum;

                m_SelStart = INT_FIRST_FIELD_START;
                m_SelStop = INT_FIRST_FIELD_STOP;
            }
        }
        if(m_strSign == "-") {
            if ((tmpnum * 10 + m_iIntFirst) * 100 + iFracTmp <= m_iIntMaxMinus * 100) {
                m_iIntSecond = tmpnum;

                m_SelStart = INT_FIRST_FIELD_START;
                m_SelStop = INT_FIRST_FIELD_STOP;
            }
        }
        break;
    case INT_FIRST_FIELD_START:
        //
        if ((nChar < 48) || (nChar > 57)) return;
        str[0] = (char) nChar;
        str[1] = '\0';
        tmpnum = _wtoi(str);
        //
        if(m_strSign == "+") {
            if ((m_iIntSecond * 10 + tmpnum) * 100 + iFracTmp <= m_iIntMaxPlus * 100) {
                m_iIntFirst = tmpnum;

                m_SelStart = FRAC_FIRST_FIELD_START;
                m_SelStop = FRAC_FIRST_FIELD_STOP;
            }
        }
        if(m_strSign == "-") {
            if ((m_iIntSecond * 10 + tmpnum) * 100 + iFracTmp <= m_iIntMaxMinus * 100) {
                m_iIntFirst = tmpnum;

                m_SelStart = FRAC_FIRST_FIELD_START;
                m_SelStop = FRAC_FIRST_FIELD_STOP;
            }
        }
        break;
    case FRAC_FIRST_FIELD_START:
        //
        if ((nChar < 48) || (nChar > 57))
            return;
        str[0] = (char) nChar;
        str[1] = '\0';
        tmpnum = _wtoi(str);
        //
        if(m_strSign == "+") {
            if (iIntTmp * 100 + tmpnum * 10 + m_iFracSecond <= m_iIntMaxPlus * 100) {
                m_iFracFirst = tmpnum;

                m_SelStart = FRAC_SECOND_FIELD_START;
                m_SelStop = FRAC_SECOND_FIELD_STOP;
            }
        }
        if(m_strSign == "-") {
            if (iIntTmp * 100 + tmpnum * 10 + m_iFracSecond <= m_iIntMaxMinus * 100) {
                m_iFracFirst = tmpnum;

                m_SelStart = FRAC_SECOND_FIELD_START;
                m_SelStop = FRAC_SECOND_FIELD_STOP;
            }
        }
        break;
    case FRAC_SECOND_FIELD_START:
        //
        if ((nChar < 48) || (nChar > 57)) return;
        str[0] = (char) nChar;
        str[1] = '\0';
        tmpnum = _wtoi(str);
        //
        if(m_strSign == "+") {
            if (iIntTmp * 100 + m_iFracFirst * 10 + tmpnum <= m_iIntMaxPlus * 100) {
                m_iFracSecond = tmpnum;
            }
        }
        if(m_strSign == "-") {
            if (iIntTmp * 100 + m_iFracFirst * 10 + tmpnum <= m_iIntMaxMinus * 100) {
                m_iFracSecond = tmpnum;

            }
        }
        break;
    }
    //
}
// ///////////////////////////////////////////
// キーフェッチ
void CDpNumCtrl::DpKeyFetch0(UINT nChar)
// ///////////////////////////////////////////
{
//    switch(m_iType)
//    {
//    case 0:    // 屈折力
//        m_iIntMaxPlus = 15;
//        m_iIntMaxMinus = 25;
//        break;
//    case 3:    // レンズカーブ
//        m_iIntMaxPlus = 15;
//        m_iIntMaxMinus = 15;
//        break;
//    }
    int numtmp;
    int iIntTmp = m_iIntSecond * 10 + m_iIntFirst;
    int iFracTmp = m_iFracFirst * 10 + m_iFracSecond;


    switch (nChar)
    {
    case VK_RETURN:
        return;    // 小数点は何もしない
        break;
    case VK_HOME:
        // 現在位置のフィールドをクリア
        OnClearField();
        break;
    case VK_DECIMAL:
        return;    // 小数点は何もしない
        break;
    case VK_BACK:
        switch (m_SelStart)
        {
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
        case FRAC_SECOND_FIELD_START:
            m_iFracSecond = 0;
            break;
        }
        break;
    case VK_UP:
//        kko.Format(_T("%d"), m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp);AfxMessageBox( kko);
        switch (m_SelStart)
        {
        case SIGN_FIELD_START:
            if((m_strSign == "+") && (iIntTmp * 100 + iFracTmp < m_iIntMaxMinus * 100)) {
                m_strSign = "-";
            }
            else if((m_strSign == "-") && (iIntTmp * 100 + iFracTmp < m_iIntMaxPlus * 100)) {
                m_strSign = "+";
            }
            break;
        case INT_SECOND_FIELD_START:
            if(m_strSign == "+") {
                m_iIntSecond++;
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp > m_iIntMaxPlus * 100) {
                    m_iIntSecond--;
                }
            }
            else {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp > 0) {
                    m_iIntSecond--;
                    if(m_iIntSecond < 0)                 {
                        m_strSign = "+";
                        double dDmy = 1000.0 - double(iIntTmp * 100 + iFracTmp);
                        m_iIntSecond = 0;
                        m_iIntFirst = int(floor(dDmy / 100.0));
                        dDmy = dDmy - double(m_iIntFirst) * 100.0;
                        m_iFracFirst = int(floor(dDmy / 10.0));
                        m_iFracSecond = int(floor(dDmy - m_iFracFirst * 10.0));
                    }
                }
            }
            break;
        case INT_FIRST_FIELD_START:
            if(m_strSign == "+") {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp < m_iIntMaxPlus * 100) {
                    m_iIntFirst++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp > m_iIntMaxPlus * 100) {
                        m_iIntFirst--;
                    }
                }
                if(m_iIntFirst > 9) {
                    numtmp = m_iIntFirst;
                    m_iIntFirst = 0;
                    m_iIntSecond++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp > m_iIntMaxPlus * 100) {
                        m_iIntFirst = numtmp - 1;
                        m_iIntSecond--;
                    }
                }
            }
            else {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp > 0) {
                    m_iIntFirst--;
                    if(m_iIntFirst < 0) {
                        m_iIntFirst = 9;
                        m_iIntSecond--;
                        if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp <= 0) {
                            m_strSign = "+";
                            m_iIntFirst = 0;
                            m_iIntSecond++;
                            double dDmy = 100.0 - double(iFracTmp);
                            m_iFracFirst = int(floor(dDmy / 10.0));
                            m_iFracSecond = int(floor(dDmy - m_iFracFirst * 10.0));
                        }
                    }
                }
            }
            break;
        case FRAC_FIRST_FIELD_START:
            if (m_strSign == "+")  {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond < m_iIntMaxPlus * 100) {
                    m_iFracFirst++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxPlus * 100) {
                        m_iFracFirst--;
                    }
                }
                if(m_iFracFirst > 9) {
                    numtmp = m_iFracFirst;
                    m_iFracFirst = 0;
                    m_iIntFirst++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxPlus * 100) {
                        m_iFracFirst = numtmp - 1;
                        m_iIntFirst--;
                    }
                }
                if(m_iIntFirst > 9) {
                    numtmp = m_iIntFirst;
                    m_iIntFirst = 0;
                    m_iIntSecond++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxPlus * 100) {
                        m_iIntFirst = numtmp - 1;
                        m_iIntSecond--;
                    }
                }
            }
            else {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > 0) {
                    m_iFracFirst--;
                    if(m_iFracFirst < 0) {
                        m_iFracFirst = 9;
                        m_iIntFirst--;
                        if(m_iIntFirst < 0) {
                            m_iIntFirst = 9;
                            m_iIntSecond--;
                            if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond <= 0) {
                                m_strSign = "+";
                                m_iIntFirst = 0;
                                m_iIntSecond++;
                                m_iFracFirst =0;
                                double dDmy = 10.0 - double(m_iFracSecond);
                                m_iFracSecond = int(dDmy);
                            }
                        }
                    }
                }
            }
            break;
        case FRAC_SECOND_FIELD_START:
            if (m_strSign == "+")  {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond < m_iIntMaxPlus * 100) {
                    m_iFracSecond++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxPlus * 100) {
                        m_iFracSecond--;
                    }
                }
                if(m_iFracSecond > 9) {
                    numtmp = m_iFracSecond;
                    m_iFracSecond = 0;
                    m_iFracFirst++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxPlus * 100) {
                        m_iFracSecond = numtmp - 1;
                        m_iFracFirst--;
                    }
                }
                if(m_iFracFirst > 9) {
                    numtmp = m_iFracFirst;
                    m_iFracFirst = 0;
                    m_iIntFirst++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxPlus * 100) {
                        m_iFracFirst = numtmp - 1;
                        m_iIntFirst--;
                    }
                }
                if(m_iIntFirst > 9) {
                    numtmp = m_iIntFirst;
                    m_iIntFirst = 0;
                    m_iIntSecond++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxPlus * 100) {
                        m_iIntFirst = numtmp - 1;
                        m_iIntSecond--;
                    }
                }
            }
            else {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > 0) {
                    m_iFracSecond--;
                    if(m_iFracSecond < 0) {
                        m_iFracSecond = 9;
                        m_iFracFirst--;
                        if(m_iFracFirst < 0) {
                            m_iFracFirst = 9;
                            m_iIntFirst--;
                            if(m_iIntFirst < 0) {
                                m_iIntFirst = 9;
                                m_iIntSecond--;
                                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond <= 0) {
                                    m_strSign = "+";
                                    m_iIntFirst = 0;
                                    m_iIntSecond = 0;
                                    m_iFracFirst =0;
                                    m_iFracSecond = 0;
                                }
                            }
                        }
                    }
                }
            }
            //break;
        }
        break;
    case VK_DOWN:
        switch (m_SelStart)
        {
        case SIGN_FIELD_START:
            if((m_strSign == "+") && (iIntTmp * 100 + iFracTmp < m_iIntMaxMinus * 100)) {
                m_strSign = "-";
            }
            else if((m_strSign == "-") && (iIntTmp * 100 + iFracTmp < m_iIntMaxPlus * 100)) {
                m_strSign = "+";
            }
            break;
        case INT_SECOND_FIELD_START:
            if(m_strSign == "+") {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp > 0) {
                    m_iIntSecond--;
                    if(m_iIntSecond < 0) {
                        m_strSign = "-";
                        double dDmy = 1000.0 - double(iIntTmp * 100 + iFracTmp);
                        m_iIntSecond = 0;
                        m_iIntFirst = int(floor(dDmy / 100.0));
                        dDmy = dDmy - double(m_iIntFirst) * 100.0;
                        m_iFracFirst = int(floor(dDmy / 10.0));
                        m_iFracSecond = int(floor(dDmy - m_iFracFirst * 10.0));
                    }
                }
                else if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp == 0) {
                    m_strSign = "-";
                    m_iIntSecond = 1;
                }
            }
            else {
                m_iIntSecond++;
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp > m_iIntMaxMinus * 100) {
                    m_iIntSecond--;
                }
            }
            break;
        case INT_FIRST_FIELD_START:
            if(m_strSign == "+") {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp > 0) {
                    m_iIntFirst--;
                    if(m_iIntFirst < 0) {
                        m_iIntFirst = 9;
                        m_iIntSecond--;
                        if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp <= 0) {
                            m_strSign = "-";
                            m_iIntFirst = 0;
                            m_iIntSecond++;
                            double dDmy = 100.0 - double(iFracTmp);
                            m_iFracFirst = int(floor(dDmy / 10.0));
                            m_iFracSecond = int(floor(dDmy - m_iFracFirst * 10.0));
                        }
                    }
                }
                else if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp == 0) {
                    m_strSign = "-";
                    m_iIntFirst = 1;
                }
            }
            else {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp < m_iIntMaxMinus * 100) {
                    m_iIntFirst++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp > m_iIntMaxMinus * 100) {
                        m_iIntFirst--;
                    }
                }
                if(m_iIntFirst > 9) {
                    numtmp = m_iIntFirst;
                    m_iIntFirst = 0;
                    m_iIntSecond++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + iFracTmp > m_iIntMaxMinus * 100) {
                        m_iIntFirst = numtmp - 1;
                        m_iIntSecond--;
                    }
                }
            }
            break;
        case FRAC_FIRST_FIELD_START:
            if (m_strSign == "+")  {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > 0) {
                    m_iFracFirst--;
                    if(m_iFracFirst < 0) {
                        m_iFracFirst = 9;
                        m_iIntFirst--;
                        if(m_iIntFirst < 0) {
                            m_iIntFirst = 9;
                            m_iIntSecond--;
                            if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond <= 0) {
                                m_strSign = "-";
                                m_iIntFirst = 0;
                                m_iIntSecond++;
                                m_iFracFirst =0;
                                double dDmy = 10.0 - double(m_iFracSecond);
                                m_iFracSecond = int(dDmy);
                            }
                        }
                    }
                }
                else if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond == 0) {
                    m_strSign = "-";
                    m_iFracFirst = 1;
                }
            }
            else {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond < m_iIntMaxMinus * 100) {
                    m_iFracFirst++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxMinus * 100) {
                        m_iFracFirst--;
                    }
                }
                if(m_iFracFirst > 9) {
                    numtmp = m_iFracFirst;
                    m_iFracFirst = 0;
                    m_iIntFirst++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxMinus * 100) {
                        m_iFracFirst = numtmp - 1;
                        m_iIntFirst--;
                    }
                }
                if(m_iIntFirst > 9) {
                    numtmp = m_iIntFirst;
                    m_iIntFirst = 0;
                    m_iIntSecond++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxMinus * 100) {
                        m_iIntFirst = numtmp - 1;
                        m_iIntSecond--;
                    }
                }
            }
            break;
        case FRAC_SECOND_FIELD_START:
            if (m_strSign == "+")  {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > 0) {
                    m_iFracSecond--;
                    if(m_iFracSecond < 0) {
                        m_iFracSecond = 9;
                        m_iFracFirst--;
                        if(m_iFracFirst < 0) {
                            m_iFracFirst = 9;
                            m_iIntFirst--;
                            if(m_iIntFirst < 0) {
                                m_iIntFirst = 9;
                                m_iIntSecond--;
                                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond <= 0) {
                                    m_strSign = "-";
                                    m_iIntFirst = 0;
                                    m_iIntSecond = 0;
                                    m_iFracFirst =0;
                                    m_iFracSecond = 0;
                                }
                            }
                        }
                    }
                }
                else if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond == 0) {
                    m_strSign = "-";
                    m_iFracSecond = 1;
                }
            }
            else {
                if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond < m_iIntMaxMinus * 100) {
                    m_iFracSecond++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxMinus * 100) {
                        m_iFracSecond--;
                    }
                }
                if(m_iFracSecond > 9) {
                    numtmp = m_iFracSecond;
                    m_iFracSecond = 0;
                    m_iFracFirst++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxMinus * 100) {
                        m_iFracSecond = numtmp - 1;
                        m_iFracFirst--;
                    }
                }
                if(m_iFracFirst > 9) {
                    numtmp = m_iFracFirst;
                    m_iFracFirst = 0;
                    m_iIntFirst++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxMinus * 100) {
                        m_iFracFirst = numtmp - 1;
                        m_iIntFirst--;
                    }
                }
                if(m_iIntFirst > 9) {
                    numtmp = m_iIntFirst;
                    m_iIntFirst = 0;
                    m_iIntSecond++;
                    if (m_iIntSecond * 1000 + m_iIntFirst * 100 + m_iFracFirst * 10 + m_iFracSecond > m_iIntMaxMinus * 100) {
                        m_iIntFirst = numtmp - 1;
                        m_iIntSecond--;
                    }
                }
            }
            //break;
        }
        break;
    case VK_RIGHT:
        switch (m_SelStart)
        {
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
            m_SelStart = FRAC_SECOND_FIELD_START;
            break;
        case FRAC_SECOND_FIELD_START:
            m_SelStart = SIGN_FIELD_START;
            break;
        }
        switch (m_SelStop)
        {
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
            m_SelStop = FRAC_SECOND_FIELD_STOP;
            break;
        case FRAC_SECOND_FIELD_STOP:
            m_SelStop = SIGN_FIELD_STOP;
            break;
        }
        break;
    case VK_LEFT:
        switch (m_SelStart)
        {
        case SIGN_FIELD_START:
            m_SelStart = FRAC_SECOND_FIELD_START;
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
        case FRAC_SECOND_FIELD_START:
            m_SelStart = FRAC_FIRST_FIELD_START;
            break;
        }
        switch (m_SelStop)
        {
        case SIGN_FIELD_STOP:
            m_SelStop = FRAC_SECOND_FIELD_STOP;
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
        case FRAC_SECOND_FIELD_STOP:
            m_SelStop = FRAC_FIRST_FIELD_STOP;
            break;
        }
        break;
    }
}

// ///////////////////////////////////////////
// マウス左ボタン（フィールド指定）
void CDpNumCtrl::DpLButtonDown0(int pos)
// ///////////////////////////////////////////
{
    if (pos <= (SIGN_FIELD_STOP)) {
        //AfxMessageBox("Dpt Hi!");
        m_SelStart = SIGN_FIELD_START;
        m_SelStop = SIGN_FIELD_STOP;
    }
    else if ((pos >= INT_SECOND_FIELD_START) && (pos <= INT_SECOND_FIELD_STOP)) {
        m_SelStart = INT_SECOND_FIELD_START;
        m_SelStop = INT_SECOND_FIELD_STOP;
    }
    else if ((pos >= INT_FIRST_FIELD_START) && (pos <= INT_FIRST_FIELD_STOP)) {
        m_SelStart = INT_FIRST_FIELD_START;
        m_SelStop = INT_FIRST_FIELD_STOP;
    }
    else if ((pos >= FRAC_FIRST_FIELD_START) && (pos <= FRAC_FIRST_FIELD_STOP)) {
        m_SelStart = FRAC_FIRST_FIELD_START;
        m_SelStop = FRAC_FIRST_FIELD_STOP;
    }
    else if ((pos >= FRAC_SECOND_FIELD_START) && (pos <= FRAC_SECOND_FIELD_STOP)) {
        m_SelStart = FRAC_SECOND_FIELD_START;
        m_SelStop = FRAC_SECOND_FIELD_STOP;
    }
}