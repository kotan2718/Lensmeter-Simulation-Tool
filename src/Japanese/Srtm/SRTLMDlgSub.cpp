
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


// SRTLM.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "SRTLM.h"
#include "SRTLMDlg.h"
#include "GlobalDef.h"
#include "Ransu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CSRTLMDlg::DataInBefore()
{
    baseLensDataInitialize(KOUSEIMEN_MAX);
    baseLensDataTransfer(KOUSEIMEN_MAX);
}
BOOL CSRTLMDlg::DataIn()
{
    //* /////////////////////////////////////////////////////////////////////////
    //* 境界面の数
    //* m_iKY2 = 11, 13, 15;
    if(!m_bFileReadFlg) m_iKY2 = 11;
    //* /////////////////////////////////////////////////////////////////////////
    //
    m_dQNTP = 0.0, m_dSY = 2.0;
    //
    m_dObjZ = -27.8040783108784; //* Target Position Default(0.0)
    m_dObjY = 0.0;
    m_dObjX = 0.0;
    //
    m_iIR = 0;
    //
    m_dDepth = 100000.0;
    //
    m_dRXA = KK_PI / 180.0 * 25.0;
    m_dRYA = KK_PI / 180.0 * 25.0;
    m_dRZA = KK_PI / 180.0 * -11.1;
    //
    m_dC[1] = 1.0 / 220.0, m_dC[2] = -1.0 / 34.5;
    m_dC[3] = 1.0 / 211.0, m_dC[4] = -1.0 / 41.0;

    //* /////////////////////////////////////////////////////////////////////////
    if(!m_bFileReadFlg) {
        //* C-1.00
        //* m_dC[5] = -1.0 / 103.524960629267;
        //* m_dC[6] = -1.0 / 130.890052356021;

        //* C-5.00
        //* m_dC[5] = -1.0 / 49.91652754591;
        //* m_dC[6] = -1.0 / 100.0;
        m_dC[5] = -1.0 / 59.906103286385;
        m_dC[6] = -1.0 / 120.000000000000;

        //* S+1.00
        //* m_dC[5] = -1.0 / 98.5634477;
        //* m_dC[6] = -1.0 / 83.33333333333;

    }
    //* /////////////////////////////////////////////////////////////////////////

    switch(m_iKY2){
    case 11:
        m_dC[7] = 1.0 / 67.5, m_dC[8] = -1.0 / 206.0;
        m_dC[9] = 1.0 / 65.0, m_dC[10] = -1.0 / 228.0, m_dC[11] = 0.0;
        break;
    case 13:
        m_dC[9] = 1.0 / 67.5, m_dC[10] = -1.0 / 206.0;
        m_dC[11] = 1.0 / 65.0, m_dC[12] = -1.0 / 228.0, m_dC[13] = 0.0;
        break;
    case 15:
        m_dC[11] = 1.0 / 67.5, m_dC[12] = -1.0 / 206.0;
        m_dC[13] = 1.0 / 65.0, m_dC[14] = -1.0 / 228.0, m_dC[15] = 0.0;
        break;
    }

    m_dD[0] = 0.0, m_dD[1] = 2.0, m_dD[2] = 5.0, m_dD[3] = 4.0, m_dD[4] = 45.0;

    //* /////////////////////////////////////////////////////////////////////////
    if(!m_bFileReadFlg) {
        ////m_dD[5] = 3.0;//1.0;
        m_dD[5] = 1.0;
        //* m_dD[8] = 3.0;
        //* m_dD[9] = 2.0;
    }
    //* /////////////////////////////////////////////////////////////////////////

    switch(m_iKY2){
    case 11:
        m_dD[6] = 55.0, m_dD[7] = 4.0, m_dD[8] = 5.01, m_dD[9] = 2.0;
        m_dD[10] = 46.7521502636818;
        break;
    case 13:
        m_dD[8] = 55.0, m_dD[9] = 4.0, m_dD[10] = 5.01, m_dD[11] = 2.0;
        m_dD[12] = 46.7521502636818;
        break;
    case 15:
        m_dD[10] = 55.0, m_dD[11] = 4.0, m_dD[12] = 5.01, m_dD[13] = 2.0;
        m_dD[14] = 46.7521502636818;
        break;
    }

    //* コリメータ1の検算用
    //* m_dN[5] = 1.0, m_dN[6] = 1.0, m_dN[7] = 1.0, m_dN[8] = 1.523
    //* コリメータ2の検算用
    //* m_dN[5] = 1.0, m_dN[6] = 1.523, m_dN[7] = 1.0, m_dN[8] = 1.0 '1.523
    //* m_dN[9] = 1.0, m_dN[10] = 1.0, m_dN[11] = 1.0, m_dN[12] = 1.0

    m_dN[1] = 1.0, m_dN[2] = 1.523, m_dN[3] = 1.0;
    m_dN[4] = 1.523, m_dN[5] = 1.0;

    //* /////////////////////////////////////////////////////////////////////////
    if(!m_bFileReadFlg) {
        //m_dN[6] = 1.5;
        m_dN[6] = 1.6;
    }
    //* /////////////////////////////////////////////////////////////////////////

    switch(m_iKY2){
    case 11:
        m_dN[7] = 1.0, m_dN[8] = 1.523;
        m_dN[9] = 1.0, m_dN[10] = 1.5, m_dN[11] = 1.0, m_dN[12] = 1.0;
        break;
    case 13:
        m_dN[9] = 1.0, m_dN[10] = 1.523;
        m_dN[11] = 1.0, m_dN[12] = 1.5, m_dN[13] = 1.0, m_dN[14] = 1.0;
        break;
    case 15:
        m_dN[11] = 1.0, m_dN[12] = 1.523;
        m_dN[13] = 1.0, m_dN[14] = 1.5, m_dN[15] = 1.0, m_dN[16] = 1.0;
        break;
    }

    m_nTORIC[1] = 0, m_nTORIC[2] = 0;
    m_nTORIC[3] = 0, m_nTORIC[4] = 0;

    //* /////////////////////////////////////////////////////////////////////////
    if(!m_bFileReadFlg) {
        //* 7 面は一般にトーリック面ではないが，被検レンズをひっくり返す場合に
        //* 対処して予めトーリックの属性を持たせている
        m_nTORIC[5] = 1;
        m_nTORIC[6] = 1;
    }
    //* /////////////////////////////////////////////////////////////////////////

    switch(m_iKY2){
    case 11:
        m_nTORIC[7] = 0, m_nTORIC[8] = 0;
        m_nTORIC[9] = 0;
        m_nTORIC[10] = 0, m_nTORIC[11] = 0;
        break;
    case 13:
        m_nTORIC[9] = 0, m_nTORIC[10] = 0;
        m_nTORIC[11] = 0;
        m_nTORIC[12] = 0, m_nTORIC[13] = 0;
        break;
    case 15:
        m_nTORIC[11] = 0, m_nTORIC[12] = 0;
        m_nTORIC[13] = 0;
        m_nTORIC[14] = 0, m_nTORIC[15] = 0;
        break;
    }

    //* /////////////////////////////////////////////////////////////////////////
    if(!m_bFileReadFlg) {
        //* C-1.00
        //* m_dCylCV2[5] = -1.0 / 130.890052356021, m_dCylTheta[5] = 0.0;
        //* m_dCylCV2[7] = m_dC[6], m_dCylTheta[6] = m_dCylTheta[5];

        //* C-5.00
        //* m_dCylCV2[5] = -1.0 / 99.666666666667;
        //* m_dCylCV2[6] = m_dC[6];

        //* S+1.00
        //* m_dCylCV2[5] = -1.0 / 98.5634477;
        m_dCylCV2[5] = -1.0 / 119.625000000000;
        m_dCylCV2[6] = m_dC[6];

        m_dCylTheta[5] = 0.0; //-10.0;
        m_dCylTheta[6] = m_dCylTheta[5];
    }
    //* /////////////////////////////////////////////////////////////////////////

    //* 回転対称非球面のときそのNo.が入る
    m_nASNO[1] = 0, m_nASNO[2] = 0, m_nASNO[3] = 0;
    m_nASNO[4] = 0, m_nASNO[5] = 0, m_nASNO[6] = 0;
    m_nASNO[7] = 0;
    //m_nASNO[7] = 7; //* 非球面のチェック OK
    m_nASNO[8] = 0, m_nASNO[9] = 0, m_nASNO[10] = 0, m_nASNO[11] = 0;

    //* /////////////////////////////////////////////////////////////////////////
    if(m_bFileReadFlg) {
        switch(m_iKY2){
        case 13:
            m_nASNO[12] = 0, m_nASNO[13] = 0;
            break;
        case 15:
            m_nASNO[12] = 0, m_nASNO[13] = 0;
            m_nASNO[14] = 0, m_nASNO[15] = 0;
            break;
        }
    }
    //* /////////////////////////////////////////////////////////////////////////


    //* m_dRISIN[i] は円錐係数,m_nASGV[i] は次数,m_dAC[i][j] はその非球面係数

    //* 非球面係数が偶数次のみの場合は "1"，奇数次も含む場合は "2"
    m_nAS[1] = 0, m_nAS[2] = 0, m_nAS[3] = 0;
    m_nAS[4] = 0, m_nAS[5] = 0, m_nAS[6] = 0;
    m_nAS[7] = 0;
    m_nAS[8] = 0, m_nAS[9] = 0, m_nAS[10] = 0, m_nAS[11] = 0;

    //* /////////////////////////////////////////////////////////////////////////
    if(m_bFileReadFlg) {
        switch(m_iKY2){
        case 13:
            m_nAS[12] = 0, m_nAS[13] = 0;
            break;
        case 15:
            m_nAS[12] = 0, m_nAS[13] = 0;
            m_nAS[14] = 0, m_nAS[15] = 0;
            break;
        }
    }
    //* /////////////////////////////////////////////////////////////////////////


    //* 光軸のシフト
    //* 問題有り....これは完全に追跡光線の光軸がシフトしてしまう
    //* 今回は使っていない
    m_nSHAX[1] = 0, m_nSHAX[2] = 0;
    m_nSHAX[3] = 0, m_nSHAX[4] = 0;

    m_nSHAX[5] = 0, m_nSHAX[6] = 0;
    m_nSHAX[7] = 0, m_nSHAX[8] = 0;

    m_nSHAX[9] = 0, m_nSHAX[10] = 0;
    m_nSHAX[11] = 0;

    //* /////////////////////////////////////////////////////////////////////////
    if(m_bFileReadFlg) {
        switch(m_iKY2){
        case 13:
            m_nSHAX[12] = 0, m_nSHAX[13] = 0;
            break;
        case 15:
            m_nSHAX[12] = 0, m_nSHAX[13] = 0;
            m_nSHAX[14] = 0, m_nSHAX[15] = 0;
            break;
        }
    }
    //* /////////////////////////////////////////////////////////////////////////


    //* 光軸の偏心はシフトとは違い偏心が効くのは m_nTLAX[i] が ON になっている面
    //* だけなので偏心させたい面全ての m_nTLAX[i] を ON にして偏心に必要な vector
    //* 成分を与えておく

    m_nTLAX[1] = 0, m_nTLAX[2] = 0;
    m_nTLAX[3] = 0, m_nTLAX[4] = 0;

    m_nTLAX[5] = 1, m_nTLAX[6] = 1;

    m_nTLAX[7] = 0, m_nTLAX[8] = 0;
    m_nTLAX[9] = 0, m_nTLAX[10] = 0, m_nTLAX[11] = 0;

    m_dHenTheta[1] = 0.0, m_dHenFai[1] = 0.0;
    m_dHenTheta[2] = 0.0, m_dHenFai[2] = 0.0;
    m_dHenTheta[3] = 0.0, m_dHenFai[3] = 0.0;
    m_dHenTheta[4] = 0.0, m_dHenFai[4] = 0.0;

    m_dHenTheta[5] = 0.0, m_dHenFai[5] = 0.0;
    m_dHenTheta[6] = 0.0, m_dHenFai[6] = 0.0;

    m_dHenTheta[7] = 0.0, m_dHenFai[7] = 0.0;
    m_dHenTheta[8] = 0.0, m_dHenFai[8] = 0.0;
    m_dHenTheta[9] = 0.0, m_dHenFai[9] = 0.0;
    m_dHenTheta[10] = 0.0, m_dHenFai[10] = 0.0;

    m_dHenTheta[11] = 0.0, m_dHenFai[11] = 0.0;

    //* これでレンズをシフトさせている。
    //* だからやっぱり偏心か...
    //m_dTLZ[5] = 0.0, m_dTLY[5] = 5.0, m_dTLX[5] = 0.0;
    //m_dTLZ[6] = 0.0, m_dTLY[6] = 5.0, m_dTLX[6] = 0.0;
    m_dTLZ[5] = 0.0, m_dTLY[5] = 0.0, m_dTLX[5] = 0.0;
    m_dTLZ[6] = 0.0, m_dTLY[6] = 0.0, m_dTLX[6] = 0.0;
    //m_dTLZ[7] = 0.0, m_dTLY[7] = 5.0, m_dTLX[7] = 0.0;
    //m_dTLZ[8] = 0.0, m_dTLY[8] = 5.0, m_dTLX[8] = 0.0;


    //* /////////////////////////////////////////////////////////////////////////
    if(m_bFileReadFlg) {
        switch(m_iKY2){
        case 13:
            m_nTLAX[12] = 0, m_nTLAX[13] = 0;
            break;
        case 15:
            m_nTLAX[12] = 0, m_nTLAX[13] = 0;
            m_nTLAX[14] = 0, m_nTLAX[15] = 0;
            break;
        }
    }
    //* /////////////////////////////////////////////////////////////////////////



    //* コリメータの端から対物レンズの端までの距離（除く 被検レンズの厚み）
    m_dD_DefaultLengthAll = 0.0;
    for(int i = 1; i < m_iKY2 - 1; i++) {
        switch(m_iKY2){
        case 11:
            if(i != 5)    m_dD_DefaultLengthAll = m_dD_DefaultLengthAll + m_dD[i];
            break;
        case 13: //* D[6] のチェック
            if(i < 5 || i > 7)    m_dD_DefaultLengthAll = m_dD_DefaultLengthAll + m_dD[i];
            break;
        case 15:
            if(i < 5 || i > 9)    m_dD_DefaultLengthAll = m_dD_DefaultLengthAll + m_dD[i];
            break;
        }
    }

    m_dRZtargetZero = -m_dObjZ;
    m_dRZhikenLens = -(m_dD[1] + m_dD[2] + m_dD[3] + m_dD[4]);

    switch(m_iKY2){
    case 11:
        //* 被検レンズ1枚
        m_dRZpintGlass = m_dRZhikenLens - (m_dD[6] + m_dD[7] + m_dD[8] + m_dD[9] + m_dD[10]); //* m_dD[6]に被検レンズの厚みが含まれている
        break;
    case 13:
        //* 被検レンズ2枚
        m_dRZpintGlass = m_dRZhikenLens - (m_dD[8] + m_dD[9] + m_dD[10] + m_dD[11] + m_dD[12]); //* m_dD[6]に被検レンズの厚みが含まれている
        break;
    case 15:
        //* 被検レンズ3枚
        m_dRZpintGlass = m_dRZhikenLens - (m_dD[10] + m_dD[11] + m_dD[12] + m_dD[13] + m_dD[14]); //* m_dD[6]に被検レンズの厚みが含まれている
        break;
    }

    //* 被検レンズ裏面頂点からピントグラスまでの距離（これの1/100が1プリズム）
    //* m_dRZpintGlass - m_dRZhikenLens

    //* S-2.00D，前面カーブ4，インデックス1.50，中心厚0.00 のモデルレンズを
    //* 5mmずらしたときの主光線のピントグラスの位置
    //* 0.51733091244028
    //* コリメータ2をはずしたときのピントグラスでの位置
    //* 1.13563865457563

    //* 目盛り盤やコロナ像の大きさの正規化
    //* m_dCoronaSize = -(m_dRZpintGlass - m_dRZhikenLens) / 100 * 0.51733091244028 / 1.13563865457563;
    m_dCoronaSize = -(m_dRZpintGlass - m_dRZhikenLens) / 100 * 0.515039404171801 / 1.14685761552409;
    m_dCoronaConfusion = 8.0; //* コロナのぼけ具合の調整(*4 で目盛盤の大きさと一致するがぼけ量が短すぎる)

    m_dWin2DefaultSize = m_dCoronaSize;
    m_dWin2Mag = 15.0;

    //* 目盛盤の十字線の初期角度
    m_dPintGlassMemori = 0.0;

    //* Ax初期値の格納
    if(m_nTORIC[5] != 0) {
        m_dCylTheta5 = m_dCylTheta[5];
        m_dAx2 = -m_dCylTheta[5];   //* 20230610 Add Lens Data : Ax
    }

    //* 被検レンズ C(5)_AN(6)_D(5)_C(6) の中心厚 D(5)
    //*                 AN(7)_D(6)_    のレンズ間距離
    //*            C(7)_AN(8)_D(7)_C(8) の中心厚 D(7)
    //*                 AN(9)_D(8)_   のレンズ間距離
    //*            C(9)_AN(10)_D(9)_C(10) の中心厚 D(9) に応じて，
    //*
    //* 集光レンズ1 C(11)_C(12) までの距離 D(10)を変え，
    //* C(5):被検レンズ裏面 から 集光レンズ第1面:C(11) までの距離を一定に保つ
    //* そのためにD(10)の初期値を m_dD6 に格納する

    m_dD6 = m_dD[m_iKY2 - 5];
    switch (m_iKY2)
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

    baseLensDataTransfer(m_iKY2);

    return TRUE;

}



BOOL CSRTLMDlg::PictureBoxSize()
{
    //* ピクチャーボックスの倍率の設定
    m_dWin1Mag = 0.9;
    //* ピクチャーボックスの大きさ
    g_dWindowPosLeft = -30.0;
    g_dWindowPosRight = 105.0;
    g_dWindowPosTop = 78.0;
    g_dWindowPosBottom = -22.0;

    //* ピクチャーボックスの正規化
    g_dWindowPosLeft = g_dWindowPosLeft * m_dWin1Mag;
    g_dWindowPosRight = g_dWindowPosRight * m_dWin1Mag;
    g_dWindowPosTop = g_dWindowPosTop * m_dWin1Mag;
    g_dWindowPosBottom = g_dWindowPosBottom * m_dWin1Mag;

    //* ピクチャーボックス2の大きさ
    g_dWindowPosLeft2 = -m_dWin2DefaultSize;
    g_dWindowPosRight2 = m_dWin2DefaultSize;
    g_dWindowPosTop2 = m_dWin2DefaultSize;
    g_dWindowPosBottom2 = -m_dWin2DefaultSize;

    //* ピクチャーボックス2の正規化
    g_dWindowPosLeft2 = g_dWindowPosLeft2 * m_dWin2Mag;
    g_dWindowPosRight2 = g_dWindowPosRight2 * m_dWin2Mag;
    g_dWindowPosTop2 = g_dWindowPosTop2 * m_dWin2Mag;
    g_dWindowPosBottom2 = g_dWindowPosBottom2 * m_dWin2Mag;

    return TRUE;

}

BOOL CSRTLMDlg::DataInitialize()
{
    switch (m_iKY2)
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

    //* 与えられたレンズによるターゲットの位置決め
    R_KINJIKU();

    if (m_bAFFlg) { //* AF ON(通常モード)
        m_dObjZ = m_dObjPoint1;
        m_dDefaultObjZ = m_dObjPoint1;
        m_dNowDefaultObjZ = m_dObjPoint1; //* 20230521 Lens Data変更後に｢初期化｣ボタンが押下され、更に｢現在のデータで初期化｣ボタンが押下されたときでも、DataIn()で読み込まれたデータのターゲット位置に戻すための処理
    } else {        //* AF OFF
        Ransu rnd;
        int j;
        //* ターゲット位置
        m_dObjZ = m_dObjPoint1;
        Diopter(m_dObjPoint1, &m_dDpt);
        j = rnd.RansuGet1();
        m_dDpt = m_dDpt + (double)j / 100.0;    //* +/-1Dの誤差を与える(乱数についてはクラス Ransu 参照)
        Target(m_dDpt, &m_dObjZ);
        m_dDefaultObjZ = m_dObjZ;
        m_dNowDefaultObjZ = m_dObjZ; //* 20230521 Lens Data変更後に｢初期化｣ボタンが押下され、更に｢現在のデータで初期化｣ボタンが押下されたときでも、DataIn()で読み込まれたデータのターゲット位置に戻すための処理

        //* レンズ位置
        j = rnd.RansuGet1();
        m_dTLY[5] = m_dTLY[5] + (int)(j / 20); //* +/-5mmの誤差を与える
        m_iLensPosYOld = (int)m_dTLY[5]* 10;
        if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
        m_dTLY[6] = m_dTLY[5];
        j = rnd.RansuGet1();
        m_dTLX[5] = m_dTLX[5] + (int)(j / 20); //* +/-5mmの誤差を与える
        m_iLensPosXOld = (int)m_dTLX[5]* 10;
        if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
        m_dTLX[6] = m_dTLX[5];

        //* レンズ回転
        j = rnd.RansuGet2();
        m_dCylTheta[5] = m_dCylTheta[5] + j;    //* +/-15°の誤差を与える
        m_dCylTheta[6] = m_dCylTheta[6] + j;

    }

    double d5d, d6d, d5vd, d5d2, d5vd2;
    d5d = 0.0, d6d = 0.0, d5vd = 0.0;
    d6d = (m_dN[6] - m_dN[7]) * (-m_dC[6] * 1000.0);      //* as d1'
    d5d = (m_dN[5] - m_dN[6]) * (-m_dCylCV2[5] * 1000.0); //* as d2'min
    d5d2 = (m_dN[5] - m_dN[6]) * (-m_dC[5] * 1000.0);     //* as d2'max

    if(d6d == 0.0) {
        d5vd = 0.0;
        d5vd2 = 0.0;
    }
    else {
        d5vd = m_dN[6] / (m_dN[6] / d6d - m_dD[5] / 1000.0) + d5d;
        d5vd2 = m_dN[6] / (m_dN[6] / d6d - m_dD[5] / 1000.0) + d5d2;
    }

    m_dDVS = d5vd;
    m_dDVC = d5vd2 - d5vd;
    m_dD1d = d6d;

    m_dRefractiveIndex = m_dN[6];
    m_dThickness = m_dD[5];

    if(m_dC[6] == 0.0) {
        m_dRadius1 = -1.79769313486232E+307;
    }
    else {
        m_dRadius1 = -1.0 / m_dC[6];
    }

    if(m_dC[5] == 0.0) {
        m_dRadius2max = -1.79769313486232E+307;
    }
    else {
        m_dRadius2max = -1.0 / m_dC[5];
    }

    if(m_dCylCV2[5] == 0.0) {
        m_dRadius2min = -1.79769313486232E+307;
    }
    else {
        m_dRadius2min = -1.0 / m_dCylCV2[5];
    }

    //* 距離データ->Diopter換算
    Diopter(m_dObjZ, &m_dDpt);

    m_bSyokika = false;

    m_bKeisyaRendou = true;

    return TRUE;

}

void CSRTLMDlg::baseLensDataTransfer(int iKY2)
{
    //* RayTrace Lens Params

    params.ldp_iKY2 = iKY2;                 //* 追跡する曲面の数

    for (int i = 0; i <= iKY2; i++) {
        params.ldp_dC[i] = m_dC[i];         //* 各境界面の曲率半径
    }
    for (int i = 0; i < iKY2; i++) {
        params.ldp_dD[i] = m_dD[i];          //* 境界面間距離
    }
    for (int i = 0; i < iKY2; i++) {
        params.ldp_dDKsub[i] = m_dDKsub[i];            //* レンズの描画で使われる補助配列
    }
    params.ldp_dDK = m_dDK;                            //* レンズの描画で使われる補助変数
    params.ldp_dD6 = m_dD6;                            //* m_dD6:被検レンズ裏面 から 集光レンズ第1面:m_dC(7) までの距離
    for (int i = 0; i <= iKY2 + 1; i++) {
        params.ldp_dN[i] = m_dN[i];                    //* 屈折率
    }
    for (int i = 0; i <= iKY2; i++) {
        params.ldp_dLensDiameter[i] = m_dLensDiameter[i];   //* 各面の有効径: 絞り設定値から各レンズの口径を算出
    }
    params.ldp_dD_DefaultLengthAll = m_dD_DefaultLengthAll; //* コリメータの端から対物レンズの端までの距離（除く 被検レンズの厚み）
    for (int i = 0; i <= iKY2; i++) {
        params.ldp_nASNO[i] = m_nASNO[i];   //* 非球面かどうか
    }
    for (int i = 0; i <= iKY2; i++) {
        params.ldp_dRISIN[i] = m_dRISIN[i]; //* 円錐係数
        params.ldp_nASGV[i] = m_nASGV[i];   //* 非球面の次数
        params.ldp_nAS[i] = m_nAS[i];       //* 偶数次（回転対称）か
                                            //* 奇数次（回転対称か非対称）か
        for (int j = 0; j <= iKY2; j++) {
            params.ldp_dAC[i][j] = m_dAC[i][j];  //* その非球面係数
        }
        params.ldp_nTORIC[i] = m_nTORIC[i];      //* トーリック面かどうか
        params.ldp_dCylCV2[i] = m_dCylCV2[i];
        params.ldp_dCylTheta[i] = m_dCylTheta[i];
        params.ldp_nSHAX[i] = m_nSHAX[i];        //* 光軸のシフト
        params.ldp_nTLAX[i] = m_nTLAX[i];        //* 偏心
        for (int j = 1; j <= 3; j++) {
            params.ldp_dAxSHV[i][j] = m_dAxSHV[i][j];
        }
        params.ldp_dTLZ[i] = m_dTLZ[i];
        params.ldp_dTLY[i] = m_dTLY[i];
        params.ldp_dTLX[i] = m_dTLX[i];
        params.ldp_dHenTheta[i] = m_dHenTheta[i];
        params.ldp_dHenFai[i] = m_dHenFai[i];
    }
    params.ldp_dRXA = m_dRXA;
    params.ldp_dRYA = m_dRYA;
    params.ldp_dRZA = m_dRZA;

    params.ldp_dSY = m_dSY;
    params.ldp_dDepth = m_dDepth;
    params.ldp_dRZtargetZero = m_dRZtargetZero;
    params.ldp_dRZhikenLens = m_dRZhikenLens;
    params.ldp_dRZpintGlass = m_dRZpintGlass;

    m_rTrace->setLensData(&params);
}

void CSRTLMDlg::baseLensDataInitialize(int iKY2)
{
    //* RayTrace Lens Params

    params.ldp_iKY2 = iKY2;                 //* 追跡する曲面の数

    for (int i = 0; i <= iKY2; i++) {
        m_dC[i] = 0.0;                      //* 各境界面の曲率半径
    }
    for (int i = 0; i < iKY2; i++) {
        m_dD[i] = 0.0;                      //* 境界面間距離
    }
    for (int i = 0; i < iKY2; i++) {
        params.ldp_dDKsub[i] = 0.0;         //* レンズの描画で使われる補助配列
    }
    params.ldp_dDK = 0.0;                   //* レンズの描画で使われる補助変数
    params.ldp_dD6 = 0.0;                   //* m_dC(6):被検レンズ裏面 から 集光レンズ第1面:m_dC(7) までの距離
    for (int i = 0; i <= iKY2 + 1; i++) {
        m_dN[i] = 1.0;                      //* 屈折率
    }
    for (int i = 0; i <= iKY2; i++) {
        m_dLensDiameter[i] = 9999.0;        //* 各面の有効径: 絞り設定値から各レンズの口径を算出
    }
    m_dD_DefaultLengthAll = 0.0;            //* コリメータの端から対物レンズの端までの距離（除く 被検レンズの厚み）
    for (int i = 0; i <= iKY2; i++) {
        m_nASNO[i] = 0;                     //* 非球面かどうか
    }
    for (int i = 0; i <= iKY2; i++) {
        m_dRISIN[i] = 0.0;                  //* 円錐係数
        m_nASGV[i] = 0;                     //* 非球面の次数
        m_nAS[i] = 0;                       //* 偶数次（回転対称）か
        									//* 奇数次（回転対称か非対称）か
        for (int j = 0; j <= iKY2; j++) {
            params.ldp_dAC[i][j] = 0.0;     //* その非球面係数
        }
        m_nTORIC[i] = 0;                    //* トーリック面かどうか
        m_dCylCV2[i] = 0.0;
        m_dCylTheta[i] = 0.0;
        m_nSHAX[i] = 0;                     //* 光軸のシフト
        m_nTLAX[i] = 0;                     //* 偏心
        for (int j = 1; j <= 3; j++) {
            m_dAxSHV[i][j] = 0.0;
        }
        m_dTLZ[i] = 0.0;
        m_dTLY[i] = 0.0;
        m_dTLX[i] = 0.0;
        m_dHenTheta[i] = 0.0;
        m_dHenFai[i] = 0.0;
    }
    m_dRXA = 0.0;
    m_dRYA = 0.0;
    m_dRZA = 0.0;

    params.ldp_dSY = 0.0;
    params.ldp_dDepth = 0.0;
    params.ldp_dRZtargetZero = 0.0;
    params.ldp_dRZhikenLens = 0.0;
    params.ldp_dRZpintGlass = 0.0;

    m_rTrace->setLensData(&params);
}

//* ダイアログの変更をclass CRayTraceに伝える
void  CSRTLMDlg::RayTraceInitialize()
{
    //* Set Ray Trace Initialize
    CommonParamsDef::rtInit params_rt;
    params_rt.ldp_iIR = m_iIR;
    params_rt.ldp_dAX = m_dAX;
    params_rt.ldp_dAY = m_dAY;
    params_rt.ldp_dAZ = m_dAZ;
    params_rt.ldp_dQNTP = m_dQNTP;
    params_rt.ldp_dObjX = m_dObjX;
    params_rt.ldp_dObjY = m_dObjY;
    params_rt.ldp_dObjZ = m_dObjZ;
    params_rt.ldp_dDXI = m_dDXI;
    params_rt.ldp_dDYI = m_dDYI;
    params_rt.ldp_dDZI = m_dDZI;

    params_rt.ldp_dDpt = m_dDpt;    //* target position to Diopter
    params_rt.ldp_dTLX5 = m_dTLX[5];
    params_rt.ldp_dTLX6 = m_dTLX[6];
    params_rt.ldp_dTLY5 = m_dTLY[5];
    params_rt.ldp_dTLY6 = m_dTLY[6];
    params_rt.ldp_dHenFai5 = m_dHenFai[5];
    params_rt.ldp_dHenFai6 = m_dHenFai[6];
    params_rt.ldp_dHenTheta5 = m_dHenTheta[5];
    params_rt.ldp_dHenTheta6 = m_dHenTheta[6];
    params_rt.ldp_dCylTheta5 = m_dCylTheta[5];
    params_rt.ldp_dCylTheta6 = m_dCylTheta[6];
    params_rt.ldp_dCylCV25 = m_dCylCV2[5];
    params_rt.ldp_dCylCV26 = m_dCylCV2[6];
    params_rt.ldp_dC5 = m_dC[5];
    params_rt.ldp_dC6 = m_dC[6];
    params_rt.ldp_dD5 = m_dD[5];
    params_rt.ldp_dD8 = m_dD[8];
    params_rt.ldp_dD10 = m_dD[10];
    params_rt.ldp_dN5 = m_dN[5];
    params_rt.ldp_dN6 = m_dN[6];
    params_rt.ldp_dPintGlassMemori = m_dPintGlassMemori;
    params_rt.ldp_dCoronaSize = m_dCoronaSize;
    params_rt.ldp_dCoronaConfusion = m_dCoronaConfusion;
    params_rt.ldp_iCoronaFlg = m_iCoronaFlg;

    m_rTrace->setInit(&params_rt);
}

void CSRTLMDlg::rtErrState(int iResult)
{
    CString str, message;

    switch (iResult)
    {
    case ERR_RAY_TRACE:                     //* 1: 追跡不可能, 0: 特定なし,         0: SkewRayTrace
        message = "SkewRayTrace";
        break;
    case ERR_RAY_TRACE_SPH:                 //* 1: 追跡不可能, 1: 共軸かつ球面,     0: SRTSph
        message = "SkewRayTrace SRTSph";
        break;
    case ERR_RAY_TRACE_TORIC:               //* 1: 追跡不可能, 2: 非球面或は非光軸, 1: SRTToric
        message = "SkewRayTrace SRTToric";
        break;
    case ERR_RAY_TRACE_ASPH:                //* 1: 追跡不可能, 2: 非球面或は非光軸, 2: SRTAsph
        message = "SkewRayTrace SRTAsph";
        break;
    case ERR_RAY_TRACE_ASPH2:               //* 1: 追跡不可能, 2: 非球面或は非光軸, 4: SRTAsph2
        message = "SkewRayTrace SRTAsph2";
        break;
    case ERR_RAY_TRACE_HENSPH:              //* 1: 追跡不可能, 2: 非球面或は非光軸, 3: SRTHenSph
        message = "SkewRayTrace SRTHenSph";
        break;
    default:
        break;
    }

    str.Format(_T("ERR !!! No Intersection at %s"), message); AfxMessageBox(str); //OKでプログラムを終了させるようにしたいな
}

//* 20230709 Add コピーライトに入れる西暦取得<-うまく行かないのでタイトルに入れることにする
void* CSRTLMDlg::GetYear(char* year)
{
    char date[64];
//*    char year[5];
//*    memset(year, 0, sizeof(year));
    time_t t = time(NULL);
    strftime(date, sizeof(date), "%Y/%m/%d %a %H:%M:%S", localtime(&t));
    ////printf("%s\n", date);
    memmove(year, date, 4);
    return *(&year);
}
