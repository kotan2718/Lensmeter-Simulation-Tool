
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


// SRTLMDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "SRTLM.h"
#include "SRTLMDlg.h"

#include "DpNumCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//* エディットボックスとボタンが押されたときの処理

// 数値が変更された場合
void CSRTLMDlg::OnKillfocusEditTargetDpt()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

    //* エディットボックスのデータが直接変更された場合に呼ばれる
    UpdateData(TRUE);    // 表示データ -> 内部

    m_dDpt = m_DpStrTargetDiopter.GetData();

    //* レンジをはずれたデータが入力された場合の処理
    if (m_dDpt > m_dTargetDiopterMax)    m_dDpt = m_dTargetDiopterMax;
    if (m_dDpt < m_dTargetDiopterMin)    m_dDpt = m_dTargetDiopterMin;

    Target(m_dDpt, &m_dObjZ);

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonTargetDefault()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    //* Diopterダイヤル
    if(m_dNowDefaultObjZ = -9999.0) {
        m_dObjZ = m_dDefaultObjZ;
    }
    else {
        m_dObjZ = m_dNowDefaultObjZ;
    }

    Diopter(m_dObjZ, &m_dDpt);

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}

//* lens position

    //* lens position edit box
void CSRTLMDlg::OnKillfocusEditLpX()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

    //* エディットボックスのデータが直接変更された場合に呼ばれる
    UpdateData(TRUE);    // 表示データ -> 内部

    m_dTLX[5] = m_DpStrLensPosX.GetData();

    //* レンジをはずれたデータが入力された場合の処理
    if (m_dTLX[5] > m_dLensPosXmax)    m_dTLX[5] = m_dLensPosXmax;
    if (m_dTLX[5] < m_dLensPosXmin)    m_dTLX[5] = m_dLensPosXmin;

    m_dTLX[6] = m_dTLX[5];

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}

    //* lens position reset button
void CSRTLMDlg::OnButtonLpX0()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    switch(m_bJujiRendou)
    {
    case true:
        m_dTLX[5] = 0.0, m_dTLX[6] = 0.0;
        m_dTLY[5] = 0.0, m_dTLY[6] = 0.0;
        if (m_bKeisyaRendou) {
            SRTLM_Keisya_Rendou();    //* この関数の呼び出しでm_dHenFai[5],[6]及びm_dHenTheta[5],[6]が変更される
        }
        m_iLensPosXOld = 0;
        m_iLensPosYOld = 0;
        break;
    case false:
        m_dTLX[5] = 0.0, m_dTLX[6] = 0.0;
        if (m_bKeisyaRendou) {
            SRTLM_Keisya_Rendou();    //* この関数の呼び出しでm_dHenFai[5],[6]及びm_dHenTheta[5],[6]が変更される
        }
        m_iLensPosXOld = 0;
        break;
    }

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}


void CSRTLMDlg::OnKillfocusEditLpY()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

    //* エディットボックスのデータが直接変更された場合に呼ばれる
    UpdateData(TRUE);    // 表示データ -> 内部

    m_dTLY[5] = m_DpStrLensPosY.GetData();

    //* レンジをはずれたデータが入力された場合の処理
    if (m_dTLY[5] > m_dLensPosYmax)    m_dTLY[5] = m_dLensPosYmax;
    if (m_dTLY[5] < m_dLensPosYmin)    m_dTLY[5] = m_dLensPosYmin;

    m_dTLY[6] = m_dTLY[5];

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonLpY0()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    switch(m_bJujiRendou)
    {
    case true:
        m_dTLX[5] = 0.0, m_dTLX[6] = 0.0;
        m_dTLY[5] = 0.0, m_dTLY[6] = 0.0;
        if (m_bKeisyaRendou) {
            SRTLM_Keisya_Rendou();    //* この関数の呼び出しでm_dHenFai[5],[6]及びm_dHenTheta[5],[6]が変更される
        }
        m_iLensPosXOld = 0;
        m_iLensPosYOld = 0;
        break;
    case false:
        m_dTLY[5] = 0.0, m_dTLY[6] = 0.0;
        if (m_bKeisyaRendou) {
            SRTLM_Keisya_Rendou();    //* この関数の呼び出しでm_dHenFai[5],[6]及びm_dHenTheta[5],[6]が変更される
        }
        m_iLensPosYOld = 0;
        break;
    }

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}


void CSRTLMDlg::OnKillfocusEditPgDeg()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

    //* エディットボックスのデータが直接変更された場合に呼ばれる
    UpdateData(TRUE);    //* 表示データ -> 内部

    m_dPintGlassMemori = m_DpStrPintGlassDeg.GetData();

    //* レンジをはずれたデータが入力された場合の処理
    if(m_dPintGlassMemori > 180.0 || m_dPintGlassMemori < 0.0) {
        m_dPintGlassMemori = fmod(m_dPintGlassMemori, 180.0);
    }

    Ax_Henkan(3, m_dPintGlassMemori);

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonPgRotate0()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

    m_dPintGlassMemori = 0.0;
    m_dPintGlassBar = m_dPintGlassMemori;

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnKillfocusEditLTiltX()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

    //* エディットボックスのデータが直接変更された場合に呼ばれる
    UpdateData(TRUE);    //* 表示データ -> 内部

    m_dHenFai[5] = m_DpStrLensTiltX.GetData();

    //* レンジをはずれたデータが入力された場合の処理
    if(m_dHenFai[5] > m_dLensTiltXmax)    m_dHenFai[5] = m_dLensTiltXmax;
    if(m_dHenFai[5] < m_dLensTiltXmin)    m_dHenFai[5] = m_dLensTiltXmin;

    m_dHenFai[6] = m_dHenFai[5];

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonLTiltX0()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_dHenFai[5] = 0.0;
    m_dHenFai[6] = m_dHenFai[5];

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnKillfocusEditLTiltY()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

    //* エディットボックスのデータが直接変更された場合に呼ばれる
    UpdateData(TRUE);    //* 表示データ -> 内部

    m_dHenTheta[5] = m_DpStrLensTiltY.GetData();

    //* レンジをはずれたデータが入力された場合の処理
    if(m_dHenTheta[5] > m_dLensTiltYmax)    m_dHenTheta[5] = m_dLensTiltYmax;
    if(m_dHenTheta[5] < m_dLensTiltYmin)    m_dHenTheta[5] = m_dLensTiltYmin;

    m_dHenTheta[6] = m_dHenTheta[5];

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonLTiltY0()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_dHenTheta[5] = 0.0;
    m_dHenTheta[6] = m_dHenTheta[5];

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonLRotate0()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_dCylTheta[5] = 0.0;
    m_dCylTheta[6] = 0.0;
    m_dAx_Hyouji = 0.0;

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;

    if(m_bKeisyaRendou) {
        SRTLM_Keisya_Rendou();    //* この関数の呼び出しでm_dHenFai[5],[6]及びm_dHenTheta[5],[6]が変更される
    }

    Invalidate(FALSE);
}


//* 20230610 Lens Data : Ax
void CSRTLMDlg::OnSetfocusEditAx2()
{
    // TODO: ここにコントロール通知ハンドラー コードを追加します。
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditAx2()
{
    // TODO: これが RICHEDIT コントロールの場合、このコントロールが
    // この通知を送信するには、CDialog::OnInitDialog() 関数をオーバーライドし、
    // CRichEditCtrl().SetEventMask() を
    // OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。
    // TODO: ここにコントロール通知ハンドラー コードを追加してください。
    if(m_bChangeEditFlg) {
        if (m_bEditSphFlg == true) {
            m_bEditSphFlg = false;
            goto EXIT;
        }
        if (m_bEditCylFlg == true) {
            m_bEditCylFlg = false;
            goto EXIT;
        }
        if (m_bEditIndxFlg == true) {
            m_bEditIndxFlg = false;
            goto EXIT;
        }
        if (m_bEditThcknssFlg == true) {
            m_bEditThcknssFlg = false;
            goto EXIT;
        }
        if (m_bEditCrvFlg == true) {
            m_bEditCrvFlg = false;
            goto EXIT;
        }

        UpdateData(TRUE);

        //* from m_DpStrSph data
        m_dDVS = m_DpStrSph.GetData();

        m_dAx2 = m_DpStrAx2.GetData();
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dAx = m_dAx2;                          //* 20230610 Lens Data : Ax が変更されたので、レンズ回転のAxも変更する

        m_dThickness = m_DpStrThickness.GetData();
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();
        m_dD1d = m_DpStrCurve.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;

        Invalidate(FALSE);

        m_bChangeEditFlg = true;
EXIT:;
    }
}

void CSRTLMDlg::OnKillfocusEditAx2()
{
    // TODO: ここにコントロール通知ハンドラー コードを追加します。
    m_bChangeEditFlg = false;
}


void CSRTLMDlg::OnSetfocusEditSph()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditSph()
{
    // TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
    // 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
    // メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
    // ライドしない限りこの通知を送りません。

    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    if(m_bChangeEditFlg) {

        UpdateData(TRUE);

        //* from m_DpStrSph data
        m_dDVS = m_DpStrSph.GetData();

        m_dAx = m_DpStrAx.GetData();
        if(m_dAx > 90)    m_dAx = m_dAx - 180;
        m_dAx2 = m_DpStrAx2.GetData();          //* 20230610 Add  Lens Data : Ax
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dThickness = m_DpStrThickness.GetData();
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();
        m_dD1d = m_DpStrCurve.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;

        Invalidate(FALSE);

        m_bChangeEditFlg = true;

        m_bEditSphFlg = true;

    }
}

void CSRTLMDlg::OnKillfocusEditSph()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_bChangeEditFlg = false;
}

void CSRTLMDlg::OnSetfocusEditCyl()
{
    //* TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditCyl()
{
    // TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
    // 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
    // メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
    // ライドしない限りこの通知を送りません。

    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    if(m_bChangeEditFlg) {

        UpdateData(TRUE);

        m_dDVC = m_DpStrCyl.GetData();

        m_dAx = m_DpStrAx.GetData();
        if(m_dAx > 90)    m_dAx = m_dAx - 180;
        m_dAx2 = m_DpStrAx2.GetData();          //* 20230610 Add  Lens Data : Ax
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dThickness = m_DpStrThickness.GetData();
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();
        m_dD1d = m_DpStrCurve.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;
        Invalidate(FALSE);

        m_bChangeEditFlg = true;

        m_bEditCylFlg = true;

    }
}

void CSRTLMDlg::OnKillfocusEditCyl()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_bChangeEditFlg = false;
}


void CSRTLMDlg::OnKillfocusEditAx()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

    UpdateData(TRUE);

    m_dAx = m_DpStrAx.GetData();
    if(m_dAx > 90)    m_dAx = m_dAx - 180;
    m_dThickness = m_DpStrThickness.GetData();
    m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();
    m_dD1d = m_DpStrCurve.GetData();

    Make_Lens();
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}


void CSRTLMDlg::OnSetfocusEditN()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditN()
{
    // TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
    // 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
    // メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
    // ライドしない限りこの通知を送りません。

    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    if(m_bChangeEditFlg) {

        UpdateData(TRUE);

        //* from m_strRefractiveIndex data
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();

        if(m_dRefractiveIndex < 1.0)    m_dRefractiveIndex = 1.0;
        if(m_dRefractiveIndex > 2.5)    m_dRefractiveIndex = 2.5;

        m_dAx = m_DpStrAx.GetData();
        if(m_dAx > 90)    m_dAx = m_dAx - 180;
        m_dAx2 = m_DpStrAx2.GetData();          //* 20230610 Add  Lens Data : Ax
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dThickness = m_DpStrThickness.GetData();
        m_dD1d = m_DpStrCurve.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;
        Invalidate(FALSE);

        m_bChangeEditFlg = true;

       m_bEditIndxFlg = true;
    }
}

void CSRTLMDlg::OnKillfocusEditN()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_bChangeEditFlg = false;
}


void CSRTLMDlg::OnSetfocusEditT()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditT()
{
    // TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
    // 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
    // メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
    // ライドしない限りこの通知を送りません。

    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    if(m_bChangeEditFlg) {

        UpdateData(TRUE);

        //* from m_strLensThickness data
        m_dThickness = m_DpStrThickness.GetData();
        if(m_dThickness < 0.0)    m_dThickness = 0.0;
        if(m_dThickness > 30.0)    m_dThickness = 30.0;

        m_dAx = m_DpStrAx.GetData();
        if(m_dAx > 90)    m_dAx = m_dAx - 180;
        m_dAx2 = m_DpStrAx2.GetData();          //* 20230610 Add  Lens Data : Ax
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();
        m_dD1d = m_DpStrCurve.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;
        Invalidate(FALSE);

        m_bChangeEditFlg = true;

        m_bEditThcknssFlg = true;
    }
}

void CSRTLMDlg::OnKillfocusEditT()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_bChangeEditFlg = false;
}


void CSRTLMDlg::OnSetfocusEditCurve()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditCurve()
{
    // TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
    // 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
    // メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
    // ライドしない限りこの通知を送りません。

    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    if(m_bChangeEditFlg) {

        UpdateData(TRUE);

        //from m_strCurve data
        m_dD1d = m_DpStrCurve.GetData();

        if(m_dD1d < -100.0)    m_dD1d = -100.0;
        if(m_dD1d > 100.0)    m_dD1d = 100.0;

        m_dAx = m_DpStrAx.GetData();
        if(m_dAx > 90)    m_dAx = m_dAx - 180;
        m_dAx2 = m_DpStrAx2.GetData();          //* 20230610 Add  Lens Data : Ax
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dThickness = m_DpStrThickness.GetData();
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;
        Invalidate(FALSE);

        m_bChangeEditFlg = true;

        m_bEditCrvFlg = true;
    }
}

void CSRTLMDlg::OnKillfocusEditCurve()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_bChangeEditFlg = false;
}

void CSRTLMDlg::OnButtonMag1()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_dWin2Mag = 15.0;
    m_iCoronaFlg = 0;

    m_bPicBoxSizeFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonMag2()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_dWin2Mag = 15.0 / 2.0;
    m_iCoronaFlg = 0;

    m_bPicBoxSizeFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonMag10()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    m_dWin2Mag = 1.0;
    m_iCoronaFlg = 1;

    m_bPicBoxSizeFlg = true;
    Invalidate(FALSE);
}


void CSRTLMDlg::OnCheckKeisya()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    if(m_bKeisyaRendou) {
        m_bKeisyaRendou = false;
    }
    else {
        m_bKeisyaRendou = true;
    }
}

void CSRTLMDlg::OnCheckPg()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    if(m_bJujiRendou) {
        m_bJujiRendou = false;
    }
    else {
        m_bJujiRendou = true;
    }
}

void CSRTLMDlg::OnCheckAf()
{
    // TODO: ここにコントロール通知ハンドラー コードを追加します。
    if(m_bAFFlg) {
        m_bAFFlg = false;
    }
    else {
        m_bAFFlg = true;
    }
}

void CSRTLMDlg::OnCheckReverse()
{
    //* TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    if(m_bHantenFlg) {
        m_bHantenFlg = false;
    }
    else {
        m_bHantenFlg = true;
    }

    double d_C6tmp = m_dC[6];
    double d_CylCV26tmp = m_dCylCV2[6];
    double d_CylTheta6tmp = m_dCylTheta[5];

    m_dC[6] = -m_dC[5];
    m_dCylCV2[6] = -m_dCylCV2[5];

    //* 被検レンズ C(6)__AN(7)_D(6)__C(7) の中心厚 D(6) に応じて，
    //* 集光レンズ1 C(8)__C(9) までの距離 D(7)を変え，
    //* C(6):被検レンズ裏面 から 集光レンズ第1面:C(8) までの距離を一定に保つ

    switch(m_iKY2)
    {
    case 15:
        m_dD[10] = m_dD6 - (m_dD[5] + m_dD[6] + m_dD[7] + m_dD[8] + m_dD[9]);
        break;
    case 13:
        m_dD[8] = m_dD6 - (m_dD[5] + m_dD[6] + m_dD[7]);
        break;
    case 11:
        m_dD[6] = m_dD6 - m_dD[5];
        break;
    }

    m_dC[5] = -d_C6tmp;
    m_dCylCV2[5] = -d_CylCV26tmp;

    m_dCylTheta[6] = m_dCylTheta[5];
    m_dCylTheta[5] = d_CylTheta6tmp;

    R_KINJIKU();

    m_dObjZ = m_dObjPoint1;
    Diopter(m_dObjPoint1, &m_dDpt);

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;

    Invalidate(FALSE);
}

void CSRTLMDlg::OnResetCurrent()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    // Diopterダイヤル
    if(m_dNowDefaultObjZ == -9999.0) {
        m_dObjZ = m_dDefaultObjZ;
    }
    else {
        m_dObjZ = m_dNowDefaultObjZ;
    }

    Diopter(m_dObjZ, &m_dDpt);

    //* 被検レンズ Ax 回転(-)
    //* 個々の処理は偏心とは異なるからなぁ...どうしよう
    m_dCylTheta[5] = -m_dAx2;       //* 20230610 Mod  Lens DataにAxを表示するように変更したので、このAxをカレントの基準に変更
    m_dCylTheta[6] = -m_dAx2;       //* 20230610 Mod
    m_dAx_Hyouji   = m_dAx2;        //* 20230610 Mod
    m_dAx2_Hyouji  = m_dAx2;        //* 20230610 Add  Lens Data : Ax

    //* レンズポジション
    //* 偏心はTORIC面が指定されているか否かの
    //* レンズ回転とは異なり，ポジションを移動させれば
    //* TLX や HenFai などに具体的な数値が代入されるので，
    //* 常に初期化する必要がある。

    //* 水平方向
    m_dTLX[5] = 0.0;
    m_dTLX[6] = 0.0;
    //* 垂直方向
    m_dTLY[5] = 0.0;
    m_dTLY[6] = 0.0;

    //* ピントグラス十字線の回転
    m_dPintGlassMemori = 0.0;

    //* レンズ傾斜
    //* 水平方向
    m_dHenFai[5] = 0.0;
    m_dHenFai[6] = 0.0;
    //* 垂直方向
    m_dHenTheta[5] = 0.0;
    m_dHenTheta[6] = 0.0;

    //* Spin Control 諸量の初期化
    m_iLensPosXOld = 0;
    m_iLensPosYOld = 0;

    m_bSetSpinScrollFlg = true;

    Invalidate(FALSE);
}


