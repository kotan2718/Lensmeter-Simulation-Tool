
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


// SRTLMDlg.h : ヘッダー ファイル
//

#include "afxwin.h"

#if !defined(AFX_SRTLMDLG_H__FD51EBB6_089E_4544_946E_057CF09C9AC7__INCLUDED_)
#define AFX_SRTLMDLG_H__FD51EBB6_089E_4544_946E_057CF09C9AC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RayTrace.h"
#include "DpNumCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSRTLMDlg ダイアログ

class CSRTLMDlg : public CDialog
{
// 構築
public:
    CSRTLMDlg(CWnd* pParent = NULL);    // 標準のコンストラクタ

// ダイアログ データ
    //{{AFX_DATA(CSRTLMDlg)
    enum { IDD = IDD_SRTLM_DIALOG };
    CDpNumCtrl    m_DpStrTargetDiopter;
    CDpNumCtrl    m_DpStrThickness;
    CDpNumCtrl    m_DpStrSph;
    CDpNumCtrl    m_DpStrPintGlassDeg;
    CDpNumCtrl    m_DpStrRefractiveIndex;
    CDpNumCtrl    m_DpStrLensPosY;
    CDpNumCtrl    m_DpStrLensPosX;
    CDpNumCtrl    m_DpStrLensTiltY;
    CDpNumCtrl    m_DpStrLensTiltX;
    CDpNumCtrl    m_DpStrCyl;
    CDpNumCtrl    m_DpStrCurve;
    CDpNumCtrl    m_DpStrAx;
    CDpNumCtrl    m_DpStrAx2;           //* 20230610 Add  Lens Data : Ax
    CString    m_strRadius1;
    CString    m_strRadius2max;
    CString    m_strRadius2min;
    //}}AFX_DATA

private:
    CRayTrace* m_rTrace;

    CDC* m_pDC1;
    CDC* m_pDC2;
    CBitmap m_bmpMemDC1;
    CBitmap m_bmpMemDC2;


    //* ////////////////////////////////////////////////
    //* SRTLM MainProgram
    //* ////////////////////////////////////////////////
    BOOL MainProgram();


    //* ////////////////////////////////////////////////
    //* ファイル入出力
    //* ////////////////////////////////////////////////

    //* ファイル入力
    //* ================================================

    //* ファイルの中を読み、SRTLM_Dat行があるかどうかを調べる
    //* ------------------------------------------------
    BOOL GetSRTLM_Dat(LPCTSTR strPath);

    //* データファイル入力
    //* ------------------------------------------------
    BOOL DatFileInPut(LPCTSTR strPath);

    //* m_iKY2 の数値文字列を抽出する子関数
    //* ------------------------------------------------
    BOOL GetPartsKY2(CString cStrkk_Parts);

    //* m_iKY2 の数値文字列を抽出する子関数
    //* ------------------------------------------------
    BOOL GetParts1523(CString cStrkk_Parts);

    //* m_dC[n], m_dD[n]....などの数値文字列を抽出する子関数
    //* ------------------------------------------------
    BOOL GetParts(CString cStrkk_Parts);

    //* 数値を配列に代入
    //* ------------------------------------------------
    BOOL DatToArray();

    //* ファイルからデータを呼び込んだ後に，
    //* All_Reset が実行された場合に，保存してあったデータを
    //* 配列に代入する
    //* ------------------------------------------------
    BOOL GetBackUpFileData();

    //* ファイル出力
    //* ================================================

    //* 変換ファイル出力
    //* ------------------------------------------------
    BOOL DatFileOutPut(LPCTSTR fname);


    //* ////////////////////////////////////////////////
    //* DlgAction
    //* 被検レンズが動かされたとき(シフト チルト 回転など)の諸量を計算する
    //* ////////////////////////////////////////////////

    //* Ax 変換
    //* ------------------------------------------------
    BOOL Ax_Henkan(int iNum, double dAx);

    //* target -> Diopter
    //* ------------------------------------------------
    BOOL Diopter(double, double*);

    //* Diopter -> Target
    //* ------------------------------------------------
    BOOL Target(double, double*);

    //* コロナ像の色を計算
    //* ------------------------------------------------
    long CoronaColor();

    //* 入射高さ
    //* ------------------------------------------------
    BOOL Nyusyatakasa();

    //* 被検レンズ設定
    //* ------------------------------------------------
    BOOL Make_Lens();

    //* 近軸逆追跡
    //* ------------------------------------------------
    BOOL R_KINJIKU();

    //* 近軸逆追跡のデバッグ
    //* ------------------------------------------------
    BOOL R_KINJIKU_Debug();
    BOOL R_KINJIKU_Debug2();
    //* ------------------------------------------------

    //* 傾斜連動
    //* ------------------------------------------------
    BOOL SRTLM_Keisya_Rendou();


    //* ////////////////////////////////////////////////
    //Dlg_sub
    //* ////////////////////////////////////////////////

    //* 初期化
    //* ------------------------------------------------
    //* Data
    void DataInBefore();
    BOOL DefaultDataIn();   //* 20230707 add
    BOOL DataIn();

    //* ピクチャーボックス
    //* ------------------------------------------------
    BOOL PictureBoxSize();

    //* ------------------------------------------------
    BOOL DataInitialize();

    //* レンズ構成の初期化
    //* ------------------------------------------------
    void baseLensDataInitialize(int iKY2);
    //* レンズ構成をclass CRayTraceに伝える

    //* ------------------------------------------------
    void baseLensDataTransfer(int iKY2);

    //* ダイアログの変更をclass CRayTraceに伝える
    //* ------------------------------------------------
    void RayTraceInitialize();

    //* Ray Trace Error State
    //* ------------------------------------------------
    void rtErrState(int iResult);

    //* 20230709 Add コピーライトに入れる西暦取得<-うまく行かないのでタイトルに入れることにする
    void* GetYear(char* year);



    //* ファイル入出力
    //* ------------------------------------------------
    CString m_strSRTLM_FilePath;

    bool m_bSRTLM_DatFlg;

    bool m_bFileReadFlg;
    bool m_bFileWriteFlg;

    int m_iKY2LineNum;
    int m_iLineCount;

    CString m_strPartsValue;
    CString m_strPartsArrayNum;
    CString m_strPartsType;

    //* データ入力後に初期化が実行された場合に備えてのバックアップ
    int m_iIKY2_backUp;
    double m_dC_backUp[KOUSEIMEN_MAX];
    double m_dD_backUp[KOUSEIMEN_MAX - 1];
    double m_dN_backUp[KOUSEIMEN_MAX + 1];
    int m_nTORIC_backUp[KOUSEIMEN_MAX];
    double m_dCylCV2_backUp[KOUSEIMEN_MAX];
    double m_dCylTheta_backUp[KOUSEIMEN_MAX];

    //* エディット
    //* ------------------------------------------------
    bool m_bChangeEditFlg;
    bool m_bSyokika;

    bool m_bKeisyaRendou;
    bool m_bJujiRendou;
    bool m_bHantenFlg;
    bool m_bAFFlg;
    bool m_bFccf1523Flg;    //* 20251027 (Ver.2.24.0) Add  Front Curve : Whether to fix to the refractive index of crown glass

    //* 20251030 (Ver.2.26.0) Changed to Static Text
    /////* 禁じ手 */
    ////bool  m_bEditSphFlg     = false;
    ////bool  m_bEditCylFlg     = false;
    ////bool  m_bEditIndxFlg    = false;
    ////bool  m_bEditCrvFlg     = false;
    ////bool  m_bEditThcknssFlg = false;

    //* ピクチャーボックス
    //* ------------------------------------------------
    bool m_bPicBoxSizeFlg;

    double m_dWin1Mag;
    double m_dWin2DefaultSize, m_dWin2Mag;

    //* スクロールバー，スピンボタン
    //* ------------------------------------------------
    bool m_bSetSpinScrollFlg;
    //* target
    double m_dTargetDiopterMin;
    double m_dTargetDiopterMax;

    //* lens position
    //* x
    double m_dLensPosXmin;
    double m_dLensPosXmax;
    int    m_iLensPosXOld;
    //* y
    double m_dLensPosYmin;
    double m_dLensPosYmax;
    int    m_iLensPosYOld;

    //* lens tilt
    //* x
    double m_dLensTiltXmin;
    double m_dLensTiltXmax;
    //* y
    double m_dLensTiltYmin;
    double m_dLensTiltYmax;

    //* レンズ設定
    //* ------------------------------------------------
    double m_dDVS, m_dDVC, m_dAx;
    double m_dRefractiveIndex, m_dThickness, m_dD1d;
    double m_dAx_Hyouji;
    double m_dAx2, m_dAx2_Hyouji;   //* 20230610 Add  Lens Data : Ax
    double m_dRadius1, m_dRadius2min, m_dRadius2max;


    //* DataInitialize
    //* ------------------------------------------------
    //* m_dDefaultObjZはData_Inで呼び込まれたときの初期値
    //* m_dNowDefaultObjZはレンズデータ変更時の初期設定値
    double m_dDefaultObjZ, m_dNowDefaultObjZ;


    //* R_KINJIK
    //* ------------------------------------------------
    double m_dObjPoint1, m_dObjPoint2;

    //* Nyusyatakasa
    //* ------------------------------------------------
    double m_dVSC_h;

    //* 目盛盤
    //* ------------------------------------------------
    double m_dPintGlassBar;


    //* 直接数値を入力してもらいたくないEditControllのバックグラウンドカラーを変える
    CBrush m_IjirunaBrush;
    COLORREF m_IjirunaColor;

    //* 直接数値を入力してもいいEditControllのバックグラウンドカラーを変える
    CBrush m_IjiruyoiBrush;
    COLORREF m_IjiruyoiColor;


    //* 共通変数引き渡し(初期化時のみ通知すればよい変数)
    CommonParamsDef::rtLensDat params;

    //* ////////////////////////////
    //* /// RayTrace Lens Params ///
    //* ////////////////////////////

    int m_iKY2;    //* 追跡する曲面の数

    //* KOUSEIMEN_MAX; //* 構成面の数の上限。数値は StdAfx.h で指定
    double m_dC[KOUSEIMEN_MAX];                //* 各境界面の曲率半径
    double m_dD[KOUSEIMEN_MAX - 1];            //* 境界面間距離
    double m_dDKsub[KOUSEIMEN_MAX - 1];        //* レンズの描画で使われる補助配列
    double m_dDK;                              //* レンズの描画で使われる補助変数
    double m_dD6;                              //* m_dC(6):被検レンズ裏面 から 集光レンズ第1面:m_dC(7) までの距離
    double m_dN[KOUSEIMEN_MAX + 1];            //* 屈折率
    double m_dLensDiameter[KOUSEIMEN_MAX];     //* 各面の有効径: 絞り設定値から各レンズの口径を算出
    double m_dD_DefaultLengthAll;              //* コリメータの端から対物レンズの端までの距離（除く 被検レンズの厚み）
    int m_nASNO[KOUSEIMEN_MAX];                //* 非球面かどうか
    double m_dRISIN[KOUSEIMEN_MAX];            //* 円錐係数
    int m_nASGV[KOUSEIMEN_MAX];                //* 非球面の次数
    int m_nAS[KOUSEIMEN_MAX];                  //* 偶数次（回転対称）か
                                               //* 奇数次（回転対称か非対称）か
    double m_dAC[KOUSEIMEN_MAX][KOUSEIMEN_MAX]; //* その非球面係数

    int m_nTORIC[KOUSEIMEN_MAX];            //* トーリック面かどうか
    double m_dCylCV2[KOUSEIMEN_MAX], m_dCylTheta[KOUSEIMEN_MAX];
    double m_dCylTheta5;

    int m_nSHAX[KOUSEIMEN_MAX];                //* 光軸のシフト
    double m_dAxSHV[KOUSEIMEN_MAX][4];

    int m_nTLAX[KOUSEIMEN_MAX];                //* 偏心
    double m_dTLZ[KOUSEIMEN_MAX], m_dTLY[KOUSEIMEN_MAX], m_dTLX[KOUSEIMEN_MAX];
    double m_dHenTheta[KOUSEIMEN_MAX], m_dHenFai[KOUSEIMEN_MAX];

    double m_dRXA;
    double m_dRYA;
    double m_dRZA;

    double m_dSY;                            //* 第1面での絞りの半径
    double m_dDepth;
    double m_dRZtargetZero;
    double m_dRZhikenLens;
    double m_dRZpintGlass;
    //* //////////////////////////////

    //* ///////////////////////////
    //* /// RayTrace Initialize ///
    //* ///////////////////////////

    int m_iIR;
    double m_dAX;
    double m_dAY;
    double m_dAZ;
    double m_dQNTP;
    double m_dObjX;
    double m_dObjY;
    double m_dObjZ;    //* target position
    double m_dDXI;
    double m_dDYI;
    double m_dDZI;

    double m_dDpt;    //* target position to Diopter

    double m_dPintGlassMemori;
    double m_dCoronaSize;
    double m_dCoronaConfusion;
    int m_iCoronaFlg;
    ////////////////////////////////

    // ClassWizard は仮想関数のオーバーライドを生成します。
    //{{AFX_VIRTUAL(CSRTLMDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
    //}}AFX_VIRTUAL

// インプリメンテーション
protected:
    HICON m_hIcon;

    // 生成されたメッセージ マップ関数
    //{{AFX_MSG(CSRTLMDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnStart();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnKillfocusEditLpX();
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnButtonLpX0();
    afx_msg void OnKillfocusEditLpY();
    afx_msg void OnButtonLpY0();
    afx_msg void OnButtonTargetDefault();
    afx_msg void OnKillfocusEditPgDeg();
    afx_msg void OnKillfocusEditSph();
    afx_msg void OnKillfocusEditN();
    afx_msg void OnKillfocusEditT();
    afx_msg void OnKillfocusEditCyl();
    afx_msg void OnKillfocusEditAx();
    afx_msg void OnKillfocusEditLTiltX();
    afx_msg void OnKillfocusEditLTiltY();
    afx_msg void OnButtonLRotate0();
    afx_msg void OnButtonLTiltX0();
    afx_msg void OnButtonLTiltY0();
    afx_msg void OnButtonMag1();
    afx_msg void OnButtonMag10();
    afx_msg void OnButtonMag2();
    afx_msg void OnButtonPgRotate0();
    afx_msg void OnKillfocusEditCurve();
    afx_msg void OnCheckKeisya();
    afx_msg void OnCheckPg();
    afx_msg void OnCheckReverse();
    afx_msg void OnCheckAf();
    afx_msg void OnResetCurrent();
    afx_msg void OnButtonFileOut();
    afx_msg void OnButtonFileIn();
    afx_msg void OnKillfocusEditTargetDpt();
    afx_msg void OnChangeEditSph();
    afx_msg void OnSetfocusEditSph();
    afx_msg void OnChangeEditCyl();
    afx_msg void OnSetfocusEditCyl();
    afx_msg void OnChangeEditN();
    afx_msg void OnSetfocusEditN();
    afx_msg void OnChangeEditT();
    afx_msg void OnSetfocusEditT();
    afx_msg void OnChangeEditCurve();
    afx_msg void OnSetfocusEditCurve();
    afx_msg void OnChangeEditAx2();     //* 20230610 Add
    afx_msg void OnKillfocusEditAx2();  //* 20230610 Add
    afx_msg void OnSetfocusEditAx2();   //* 20230610 Add
    afx_msg void OnCheckFCCF();         //* 20251027 Add (Ver.2.24.0)
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnDestroy();
protected:
    CButton m_Check_AF;
    CButton m_Check_Keisya;
    CButton m_Check_Fccf1523; //* 20251027 (Ver.2.24.0) Add  Front Curve : Whether to fix to the refractive index of crown glass
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif //* !defined(AFX_SRTLMDLG_H__FD51EBB6_089E_4544_946E_057CF09C9AC7__INCLUDED_)
