
//*  DpNumCtrl クラス
//*  Original Author: Masakazu Irie
//*  Modified by: Kazuo Kawamura (for SRTLM project)
//*
//*  本コードの詳細なライセンス条件については LICENSE ファイルを参照してください。


// DpNumCtrl.cpp : インプリメンテーション ファイル
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
    // 屈折力
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
// CDpNumCtrl メッセージ ハンドラ


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
    case 0:    //* 屈折力
        DpSetData0(m_dValue1, m_dValue2, m_iType);
        break;
    case 1:    //* Lensの角度
        DpSetData1(m_dValue1, m_iType);
        break;
    case 2:    //* 屈折率
        DpSetData2(m_dValue1, m_iType);
        break;
    case 3:    //* レンズ位置，傾斜
        DpSetData3(m_dValue1, m_iType);
        break;
    case 4:    //* レンズ厚
        DpSetData4(m_dValue1, m_iType);
        break;
    case 5:    //* レンズカーブ
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
//* フォーマット表示ルーチン
///////////////////////////////////////////
void CDpNumCtrl::FormatAndDisplay()
{
    CString cStrBuf;

    switch(m_iNumDispType)
    {
    case 0:    //* 屈折力
        {
            //* キーフェッチ "VK_UP" での "-0.00 => +0.00" への変換処理
            //* "VK_DOWN" での "+0.00 => -0.00" への変換は OnKeyDown() に記述
            if(m_iIntSecond == 0 && m_iIntFirst == 0 && m_iFracFirst == 0 && m_iFracSecond == 0) {
                m_strSign = "+";
            }
            cStrBuf.Format(_T("%s %01d%01d.%01d%01d"), m_strSign, m_iIntSecond, m_iIntFirst, m_iFracFirst, m_iFracSecond);
            break;
        }
    case 1:    //* Lensの角度
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
    case 2:    //* 屈折率
        {
            cStrBuf.Format(_T("   %01d.%01d%01d%01d"), m_iIntFirst, m_iFracFirst, m_iFracSecond, m_iFracThird);
            break;
        }
    case 3:    //* レンズ位置，傾斜
        {
            //* キーフェッチ "VK_UP" での "-0.00 => +0.00" への変換処理
            //* "VK_DOWN" での "+0.00 => -0.00" への変換は OnKeyDown() に記述
            if(m_iIntSecond == 0 && m_iIntFirst == 0 && m_iFracFirst == 0 ) {
                m_strSign = "+";
            }
            cStrBuf.Format(_T("%s %01d%01d.%01d"), m_strSign, m_iIntSecond, m_iIntFirst, m_iFracFirst);
            break;
        }
    case 4:    //* レンズ厚
        {
            cStrBuf.Format(_T("  %01d%01d.%01d%01d"), m_iIntSecond, m_iIntFirst, m_iFracFirst, m_iFracSecond);
            break;
        }
    case 5:    //* レンズカーブ
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
//* キャラクタチェック
/////////////////////////////////////////
void CDpNumCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    m_nChar = nChar;
    switch(m_iNumDispType)
    {
    case 0:    //* 屈折力
        DpCharacterCheck0(m_nChar);
        break;
    case 1:    //* Lensの角度
        DpCharacterCheck1(m_nChar);
        break;
    case 2:    //* 屈折率
        DpCharacterCheck2(m_nChar);
        break;
    case 3:    //* レンズ位置，傾斜
        DpCharacterCheck3(m_nChar);
        break;
    case 4:    //* レンズ厚
        DpCharacterCheck4(m_nChar);
        break;
    case 5:    //* レンズカーブ
        DpCharacterCheck5(m_nChar);
        break;
    }
    //
    FormatAndDisplay();
}
/////////////////////////////////////////////
//* キーフェッチ
/////////////////////////////////////////////
void CDpNumCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    m_nChar = nChar;
    switch(m_iNumDispType)
    {
    case 0:    //* 屈折力
        DpKeyFetch0(m_nChar);
        break;
    case 1:    //* Lensの角度
        DpKeyFetch1(m_nChar);
        break;
    case 2:    //* 屈折率
        DpKeyFetch2(m_nChar);
        break;
    case 3:    //* レンズ位置，傾斜
        DpKeyFetch3(m_nChar);
        break;
    case 4:    //* レンズ厚
        DpKeyFetch4(m_nChar);
        break;
    case 5:    //* レンズカーブ
        DpKeyFetch5(m_nChar);
        break;
    }

    FormatAndDisplay();
}
/////////////////////////////////////
//* マウス左ボタン（フィールド指定）
/////////////////////////////////////
void CDpNumCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    //* 標準のルーチン
    CEdit::OnLButtonDown(nFlags, point);
    m_pos = this->CharFromPos(point);
    switch(m_iNumDispType)
    {
    case 0:    //* 屈折力
        DpLButtonDown0(m_pos);
        break;
    case 1:    //* Lensの角度
        DpLButtonDown1(m_pos);
        break;
    case 2:    //* 屈折率
        DpLButtonDown2(m_pos);
        break;
    case 3:    //* レンズ位置，傾斜
        DpLButtonDown3(m_pos);
        break;
    case 4:    //* レンズ厚
        DpLButtonDown4(m_pos);
        break;
    case 5:    //* レンズカーブ
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
//* 現在フィールドのクリアルーチン
///////////////////////////////////////////
void CDpNumCtrl::OnClearField()
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
//* 標準動作のキャンセルルーチン
//
/////////////////////////////////////////////////////
//
//////////////////////////////////////////////
//* ドラッグ＆ドロップを禁止するため
//////////////////////////////////////////////
void CDpNumCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
}
//////////////////////////////////////////////
//* ダブルクリック禁止
//////////////////////////////////////////////
void CDpNumCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
}
//////////////////////////////////////////////
//* CEditの標準トラックメニューを出さないための何もしないハンドラ
//////////////////////////////////////////////
void CDpNumCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
}

