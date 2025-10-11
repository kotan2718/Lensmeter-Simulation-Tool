
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

//BOOL CDpNumCtrl::DpSetData6(double dValue, int type)
//{
//    // バグあり（修正:2000/9/23）
//    // 川村拝借 2002/05/13
//    // 小数第2位以下四捨五入
//    m_dNumValue = _wtof(str_cvt(dValue * 100.0, 0)) / 100.0;
//    m_iType = type;
//    //
//    switch(m_iType)
//    {
//    case 0:    // 角度
//        m_iMax = 1799;
//        break;
//    }
//
//    if (m_dNumValue > 179.9)
//        m_dNumValue = 0.0;
//
//    double dDmy = fabs(m_dNumValue);
//    m_iIntThird = int(floor(dDmy / 100.0));
//    m_iIntSecond = int(floor((dDmy - double(m_iIntThird) * 100.0) / 10.0));
//    m_iIntFirst = int(floor(dDmy - double(m_iIntThird) * 100.0
//                        - double(m_iIntSecond) * 10.0));
//    m_iFracFirst = int((dDmy - floor(dDmy)) * 10.0);
//    int tmpnum = m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst;
//
//    if(m_iFracFirst > 9) {
//        m_iFracFirst = 0;
//        m_iIntFirst++;
//        if(m_iIntFirst > 9) {
//            m_iIntFirst = 0;
//            m_iIntSecond++;
//        }
//        if(m_iIntSecond > 9) {
//            m_iIntSecond = 0;
//            m_iIntThird++;
//        }
//
//        if (tmpnum > m_iMax) {
//            m_iIntThird = 0;
//            m_iIntSecond = 0;
//            m_iIntFirst = 0;
//            m_iFracFirst = 0;
//        }
//    }
//    //
//    //
//    return TRUE;
//}

// ///////////////////////////////////////
// キャラクタチェック
//void CDpNumCtrl::DpCharacterCheck6(UINT nChar)
// ///////////////////////////////////////
//{
//    int tmpnum = 0;
//    double ftmpnum = 0.0;
//    _TCHAR str[2];
//    switch (m_SelStart)
//    {
//        case INT_THIRD_FIELD_START:
//            if ((nChar < 48) || (nChar > 50)) { // 100の位がとれる値は 0,1
//                return;
//            }
//            str[0] = (char) nChar;
//            str[1] = '\0';
//            tmpnum = _wtoi(str);
//            //
//            if (tmpnum * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst <= m_iMax) {
//                m_iIntThird = tmpnum;
//
//                m_SelStart = INT_SECOND_FIELD_START;
//                m_SelStop = INT_SECOND_FIELD_STOP;
//            }
//            break;
//        case INT_SECOND_FIELD_START:
//            if ((nChar < 48) || (nChar > 57)) {
//                return;
//            }
//            str[0] = (char) nChar;
//            str[1] = '\0';
//            tmpnum = _wtoi(str);
//            //
//            if(m_iIntThird * 1000 + tmpnum * 100 + m_iIntFirst * 10 + m_iFracFirst <= m_iMax) {
//                m_iIntSecond = tmpnum;
//
//                m_SelStart = INT_FIRST_FIELD_START;
//                m_SelStop = INT_FIRST_FIELD_STOP;
//            }
//            break;
//        case INT_FIRST_FIELD_START:
//            if ((nChar < 48) || (nChar > 57)) {
//                return;
//            }
//            str[0] = (char) nChar;
//            str[1] = '\0';
//            tmpnum = _wtoi(str);
//            //
//            if(m_iIntThird * 1000 + m_iIntSecond * 100 + tmpnum * 10 + m_iFracFirst <= m_iMax) {
//                m_iIntFirst = tmpnum;
//
//                m_SelStart = FRAC_FIRST_FIELD_START;
//                m_SelStop = FRAC_FIRST_FIELD_STOP;
//            }
//            break;
//        case FRAC_FIRST_FIELD_START:
//            if ((nChar < 48) || (nChar > 57)) {
//                return;
//            }
//            str[0] = (char) nChar;
//            str[1] = '\0';
//            tmpnum = _wtoi(str);
//            //
//            if(m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + tmpnum <= m_iMax) {
//                m_iFracFirst = tmpnum;
//            }
//            break;
//    }
//    //
//}

// ///////////////////////////////////////////
// キーフェッチ
//void CDpNumCtrl::DpKeyFetch6(UINT nChar)
// ///////////////////////////////////////////
//{
//    switch (nChar) {
//        case VK_HOME:
//            // 現在位置のフィールドをクリア
//            OnClearField();
//            break;
//        case VK_DECIMAL:
//            return;    // 小数点は何もしない
//            break;
//        case VK_BACK:
//            switch (m_SelStart) {
//                case INT_THIRD_FIELD_START:
//                    m_iIntThird = 0;
//                    break;
//                case INT_SECOND_FIELD_START:
//                    m_iIntSecond = 0;
//                    break;
//                case INT_FIRST_FIELD_START:
//                    m_iIntFirst = 0;
//                    break;
//                case FRAC_FIRST_FIELD_START:
//                    m_iFracFirst = 0;
//                    break;
//            }
//            break;
//        case VK_UP:
//            switch (m_SelStart) {
//                case INT_THIRD_FIELD_START:
//                    if (m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst    <= m_iMax) {
//                        m_iIntThird++;
//                    }
//                    if(m_iIntThird > 1) {
//                        m_iIntThird = 0;
//                    }
//                    break;
//                case INT_SECOND_FIELD_START:
//                    if (m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst <= m_iMax) {
//                        m_iIntSecond++;
//                    }
//                    if(m_iIntSecond > 9) {
//                        m_iIntSecond = 0;
//                        m_iIntThird++;
//                    }
//                    if (m_iIntThird * 10 + m_iIntSecond > 17) {
//                        m_iIntSecond = 0;
//                        m_iIntThird = 0;
//                    }
//                    break;
//                case INT_FIRST_FIELD_START:
//                    if (m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst <= m_iMax) {
//                        m_iIntFirst++;
//                    }
//                    if(m_iIntFirst > 9) {
//                        m_iIntFirst = 0;
//                        m_iIntSecond++;
//                    }
//                    if(m_iIntSecond > 9) {
//                        m_iIntSecond = 0;
//                        m_iIntThird++;
//                    }
//                    if (m_iIntThird * 100 + m_iIntSecond * 10 + m_iIntFirst > 179) {
//                        m_iIntFirst = 0;
//                        m_iIntSecond = 0;
//                        m_iIntThird = 0;
//                    }
//                    break;
//                case FRAC_FIRST_FIELD_START:
//                    if (m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst <= m_iMax) {
//                        m_iFracFirst++;
//                    }
//                    if(m_iFracFirst > 9) {
//                        m_iFracFirst = 0;
//                        m_iIntFirst++;
//                    }
//                    if(m_iIntFirst > 9) {
//                        m_iIntFirst = 0;
//                        m_iIntSecond++;
//                    }
//                    if(m_iIntSecond > 9) {
//                        m_iIntSecond = 0;
//                        m_iIntThird++;
//                    }
//                    if (m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst    > m_iMax) {
//                        m_iFracFirst = 0;
//                        m_iIntFirst = 0;
//                        m_iIntSecond = 0;
//                        m_iIntThird = 0;
//                    }
//                    break;
//                }
//                break;
//        case VK_DOWN:
//            switch (m_SelStart) {
//                case INT_THIRD_FIELD_START:
//                    if (m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst    >= 0) {
//                        m_iIntThird--;
//                    }
//                    if(m_iIntThird < 0) {
//                        m_iIntThird = 1;
//                    }
//                    break;
//                case INT_SECOND_FIELD_START:
//                    if (m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst >= 0) {
//                        m_iIntSecond--;
//                    }
//                    if(m_iIntSecond < 0) {
//                        m_iIntSecond = 9;
//                        m_iIntThird--;
//                    }
//                    if (m_iIntThird * 10 + m_iIntSecond < 0) {
//                        m_iIntSecond = 7;
//                        m_iIntThird = 1;
//                    }
//                    break;
//                case INT_FIRST_FIELD_START:
//                    if (m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst >= 0) {
//                        m_iIntFirst--;
//                    }
//                    if(m_iIntFirst < 0) {
//                        m_iIntFirst = 9;
//                        m_iIntSecond--;
//                    }
//                    if(m_iIntSecond < 0) {
//                        m_iIntSecond = 9;
//                        m_iIntThird--;
//                    }
//                    if (m_iIntThird * 100 + m_iIntSecond * 10 + m_iIntFirst < 0) {
//                        m_iIntFirst = 9;
//                        m_iIntSecond = 7;
//                        m_iIntThird = 1;
//                    }
//                    break;
//                case FRAC_FIRST_FIELD_START:
//                    if (m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst >= 0) {
//                        m_iFracFirst--;
//                    }
//                    if(m_iFracFirst < 0) {
//                        m_iFracFirst = 9;
//                        m_iIntFirst--;
//                    }
//                    if(m_iIntFirst < 0) {
//                        m_iIntFirst = 9;
//                        m_iIntSecond--;
//                    }
//                    if(m_iIntSecond < 0) {
//                        m_iIntSecond = 9;
//                        m_iIntThird--;
//                    }
//                    if (m_iIntThird * 1000 + m_iIntSecond * 100 + m_iIntFirst * 10 + m_iFracFirst    < 0) {
//                        m_iFracFirst = 9;
//                        m_iIntFirst = 9;
//                        m_iIntSecond = 7;
//                        m_iIntThird = 1;
//                    }
//                    break;
//            }
//            break;
//        case VK_RIGHT:
//            switch (m_SelStart) {
//                case SIGN_FIELD_START:
//                    m_SelStart = INT_THIRD_FIELD_START;
//                    break;
//                case INT_THIRD_FIELD_START:
//                    m_SelStart = INT_SECOND_FIELD_START;
//                    break;
//                case INT_SECOND_FIELD_START:
//                    m_SelStart = INT_FIRST_FIELD_START;
//                    break;
//                case INT_FIRST_FIELD_START:
//                    m_SelStart = FRAC_FIRST_FIELD_START;
//                    break;
//                case FRAC_FIRST_FIELD_START:
//                    m_SelStart = INT_THIRD_FIELD_START;
//                    break;
//            }
//            switch (m_SelStop) {
//                case SIGN_FIELD_STOP:
//                    m_SelStart = INT_THIRD_FIELD_STOP;
//                    break;
//                case INT_THIRD_FIELD_STOP:
//                    m_SelStop = INT_SECOND_FIELD_STOP;
//                    break;
//                case INT_SECOND_FIELD_STOP:
//                    m_SelStop = INT_FIRST_FIELD_STOP;
//                    break;
//                case INT_FIRST_FIELD_STOP:
//                    m_SelStop = FRAC_FIRST_FIELD_STOP;
//                    break;
//                case FRAC_FIRST_FIELD_STOP:
//                    m_SelStop = INT_THIRD_FIELD_STOP;
//                    break;
//            }
//            break;
//        case VK_LEFT:
//            switch (m_SelStart) {
//                case FRAC_FIRST_FIELD_START:
//                    m_SelStart = INT_FIRST_FIELD_START;
//                    break;
//                case INT_FIRST_FIELD_START:
//                    m_SelStart = INT_SECOND_FIELD_START;
//                    break;
//                case INT_SECOND_FIELD_START:
//                    m_SelStart = INT_THIRD_FIELD_START;
//                    break;
//                case INT_THIRD_FIELD_START:
//                    m_SelStart = FRAC_FIRST_FIELD_START;
//                    break;
//            }
//            switch (m_SelStop) {
//                case FRAC_FIRST_FIELD_STOP:
//                    m_SelStop = INT_FIRST_FIELD_STOP;
//                    break;
//                case INT_FIRST_FIELD_STOP:
//                    m_SelStop = INT_SECOND_FIELD_STOP;
//                    break;
//                case INT_SECOND_FIELD_STOP:
//                    m_SelStop = INT_THIRD_FIELD_STOP;
//                    break;
//                case INT_THIRD_FIELD_STOP:
//                    m_SelStop = FRAC_FIRST_FIELD_STOP;
//                    break;
//            }
//            break;
//    }
//}

// ///////////////////////////////////////////
// マウス左ボタン（フィールド指定）
//void CDpNumCtrl::DpLButtonDown6(int pos)
// ///////////////////////////////////////////
//{
//    if ((pos <= INT_THIRD_FIELD_START)) {
//        //AfxMessageBox("Deg Hi!");
//        m_SelStart = INT_THIRD_FIELD_START;
//        m_SelStop = INT_THIRD_FIELD_STOP;
//    } else if ((pos >= INT_SECOND_FIELD_START) && (pos <= INT_SECOND_FIELD_STOP)) {
//        m_SelStart = INT_SECOND_FIELD_START;
//        m_SelStop = INT_SECOND_FIELD_STOP;
//    } else if ((pos >= INT_FIRST_FIELD_START) && (pos <= INT_FIRST_FIELD_STOP)) {
//        m_SelStart = INT_FIRST_FIELD_START;
//        m_SelStop = INT_FIRST_FIELD_STOP;
//    } else if ((pos >= FRAC_FIRST_FIELD_START) && (pos <= FRAC_FIRST_FIELD_STOP)) {
//        m_SelStart = FRAC_FIRST_FIELD_START;
//        m_SelStop = FRAC_FIRST_FIELD_STOP;
//    }
//}