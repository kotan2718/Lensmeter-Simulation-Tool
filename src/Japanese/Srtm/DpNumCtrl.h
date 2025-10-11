
//*  DpNumCtrl クラス
//*  Original Author: Masakazu Irie
//*  Modified by: Kazuo Kawamura (for SRTLM project)
//*
//*  本コードの詳細なライセンス条件については LICENSE ファイルを参照してください。


#if !defined(AFX_DpNumCtrl_H__955A2301_C2C3_11D3_89EA_0040C7990626__INCLUDED_)
#define AFX_DpNumCtrl_H__955A2301_C2C3_11D3_89EA_0040C7990626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DpNumCtrl.h : ヘッダー ファイル
//
//
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CDpNumCtrl ウィンドウ

class CDpNumCtrl : public CEdit
{
// コンストラクション
public:
    CDpNumCtrl();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
    // ClassWizard は仮想関数のオーバーライドを生成します。
    //{{AFX_VIRTUAL(CDpNumCtrl)
    //}}AFX_VIRTUAL

// インプリメンテーション
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

    // 生成されたメッセージ マップ関数
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

    //* 屈折力の表示
    int m_iIntMaxPlus;
    int m_iIntMaxMinus;

    int m_iMax;
    int m_iMin;

    void FormatAndDisplay();

    //* The following are used to mark the beginning and ending positions
    //* of the individual fields in the formatted display.

    enum {  //*                           [+,-] 0 0 0 . 0 0 0
            SIGN_FIELD_START        = 0,    //* 正負符号    start position.
            SIGN_FIELD_STOP         = 1,    //* 正負符号    stop position (+1).
            INT_THIRD_FIELD_START   = 1,    //* 整数100の位 start position.
            INT_THIRD_FIELD_STOP    = 2,    //* 整数100の位 stop position (+1).
            INT_SECOND_FIELD_START  = 2,    //* 整数 10の位 start position.
            INT_SECOND_FIELD_STOP   = 3,    //* 整数 10の位 stop position (+1).
            INT_FIRST_FIELD_START   = 3,    //* 整数  1の位 start position.
            INT_FIRST_FIELD_STOP    = 4,    //* 整数  1の位 stop position (+1).
            FRAC_FIRST_FIELD_START  = 5,    //* 小数第  1位 start position.
            FRAC_FIRST_FIELD_STOP   = 6,    //* 小数第  1位 stop position (+1).
            FRAC_SECOND_FIELD_START = 6,    //* 小数第  2位 start position.
            FRAC_SECOND_FIELD_STOP  = 7,    //* 小数第  2位 stop position (+1).
            FRAC_THIRD_FIELD_START  = 7,    //* 小数第  2位 start position.
            FRAC_THIRD_FIELD_STOP   = 8};   //* 小数第  2位 stop position (+1).

            //* 屈折力表示                [+,-]00.00
            //* 角度の表示                    000.0
            //* 屈折率の表示                    0.000
            //* レンズ位置，傾斜の表示    [+,-]00.0
            //* レンズ厚の表示                 00.00


    //* The following two variables are used to mark the beginning and ending
    //* positions of the field we are currently on.  That is, the field currently
    //* highlighted.
    int m_SelStop;
    int m_SelStart;


//    数値データの構造
    // 屈折力
    CString m_strSign;              //* The current sign setting.
    int m_iIntThird;                //* The current integer 100の位.
    int m_iIntSecond;               //* The current integer  10の位.
    int m_iIntFirst;                //* The current integer   1の位.
    int m_iFracFirst;               //* The current fraction 第 1位.
    int m_iFracSecond;              //* The current fraction 第 2位.
    int m_iFracThird;               //* The current fraction 第 3位.

    double m_dNumValue;             //* The current numerical value.
    int m_iNumDispType;
public:
//    afx_msg void OnEditAx2();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DpNumCtrl_H__955A2301_C2C3_11D3_89EA_0040C7990626__INCLUDED_)
