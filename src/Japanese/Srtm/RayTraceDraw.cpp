
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#include "stdafx.h"
#include "RayTrace.h"
#include "GlobalDef.h"
#include "DrawFunc.h"


BOOL CRayTrace::GLS1()
{
    //*
    //* sub function GLS
    //* GLS as Graphics of Lens Shaping
    //*
    //* 曲面のy,x-データを与えて zを計算しプロットさせる
    //*
    //* mother program   : MainProgram()
    //* daughter program : KyokumenSelect(), GLSSUB(), R3D()
    //*

    //* --------------------------------------
    //* スクリーン基準線
    m_dFunc->P_Line(44 + 18, 5, 74 + 18, 5, RGB(156, 156, 156));
    m_dFunc->P_Line(59 + 18, 20, 59 + 18, -10, RGB(156, 156, 156));
    //* --------------------------------------
    //* ピントグラスへのキャラクタセット
    m_dFunc->P_Char_Set("Pint Glass", "Times New Roman", 12, 71, -13, RGB(0, 0, 0));
    m_dFunc->P_Char_Set("= View from Target =", "Times New Roman", 12, 65, -16, RGB(0, 0, 0));


    //
    // ---------------------------------------

    double dDD[KOUSEIMEN_MAX];
    long lCol;
    double dRGXS, dRGYS;
    double dRGXE, dRGYE;

    //* 光軸の描画
    lCol = RGB(156, 156, 156); //7;
    m_dRX = 0.0, m_dRY = 0.0, m_dRZ = -500.0;
    R3D();

    dRGXS = g_dWindowPosLeft, dRGYS = m_dRY3 * g_dWindowPosLeft / m_dRX3;
    m_dRX = 0.0, m_dRY = 0.0, m_dRZ = 500.0;
    R3D();

    dRGXE = g_dWindowPosRight, dRGYE = m_dRY3 * g_dWindowPosRight / m_dRX3;

    m_dFunc->P_Line(dRGXS, dRGYS, dRGXE, dRGYE, lCol);

    //*
    //* 境界面間距離の格納
    //*

    //* m_dD_DefaultLengthAll: コリメータの端から対物レンズの端までの距離（除く 被検レンズの厚み）
    //* DataIn() で計算済み
    m_dDK = m_dD_DefaultLengthAll;
    //* m_dDK = 122.01;
    int nAXY = 0;

    for(int iNyu = m_iKY2 - 1; iNyu > 0; iNyu--) {
        dDD[iNyu] = m_dD[iNyu];
        if (iNyu == m_iKY2 - 1)  dDD[m_iKY2 - 1] = 0.0;
//*20230417 add_start
        if (iNyu > 6) {
                m_dDK = m_dDK - dDD[iNyu];
            m_dDKsub[iNyu] = m_dDK;
        }
        else if (iNyu == 6) {
            m_dDK = 56.0 + m_dD[5];
            m_dDKsub[iNyu] = m_dDK;
        }
        else {
            m_dDKsub[1] =  0.0;
            m_dDKsub[2] =  2.0;
            m_dDKsub[3] =  7.0;
            m_dDKsub[4] = 11.0;
            m_dDKsub[5] = 56.0;
        }
//*20230417 add_end
    }

    //*
    //* レンズの描画
    //*
    //* コリメータまで

    for (int iNyu = 4; iNyu > 0; iNyu--) {
            switch (iNyu)
        {
        case 1:
            m_dLengthL = 10.0;
            m_dDeltaL = 2.0;
            m_dDK = m_dDKsub[iNyu];
            break;
        case 2:
            m_dLengthL = 10.0;
            m_dDeltaL = 2.0;
            m_dDK = m_dDKsub[iNyu];
            break;
        case 3:
            m_dLengthL = 10.0;
            m_dDeltaL = 2.0;
            m_dDK = m_dDKsub[iNyu];
            break;
        case 4:
            m_dLengthL = 10.0;
            m_dDeltaL = 2.0;
            m_dDK = m_dDKsub[iNyu];
            break;
        }

        GLS_Kyokumen_Select(iNyu);
    }

    m_iIDFlg = 0;
    //
    return TRUE;
}

BOOL CRayTrace::GLS2()
{
    //*
    //* ターゲットとピントグラス基準位置の描画
    //*
    long lCol;
    int nAXY = 0;

    m_iIDFlg = 1;

    double dRGXS, dRGYS;
    double dRGXE, dRGYE;


    for (int nIKK = 1; nIKK <= 2; nIKK++) {
        for (int iNyu = 1; iNyu <= 2; iNyu++) {
            m_dLengthL = 2.5;
            m_dDeltaL = 0.5;

            for (int nJKK = 0; nJKK <= 5; nJKK++) {
    //
    if (nAXY == 0) {
        m_dRX = 0.0;
        m_dRY = m_dLengthL - double(nJKK) * m_dDeltaL;
    }
    else {
        m_dRX = double(nJKK) * m_dDeltaL;
        m_dRY = 0.0;
    }
    //
    switch (iNyu)
    {
    case 1:
        m_dRZ = -m_dObjZ;
        break;
    case 2:
        m_dRZ = m_dRZpintGlass;
        break;
    }

    lCol = RGB(156, 156, 156); //* 15;
    if (m_dRX >= 0.0) {
        m_dRX = m_dRX + m_dRZ / m_dDepth;
    }
    else {
        m_dRX = m_dRX - m_dRZ / m_dDepth;
    }
    if (m_dRY >= 0.0) {
        m_dRY = m_dRY + m_dRZ / m_dDepth;
    }
    else {
        m_dRY = m_dRY - m_dRZ / m_dDepth;
    }

    R3D();

    if (nJKK == 0) {
        dRGXS = m_dRX3, dRGYS = m_dRY3;
        dRGXE = m_dRX3, dRGYE = m_dRY3;
    }
    else {
        dRGXS = m_dRGX0, dRGYS = m_dRGY0;
        dRGXE = m_dRX3, dRGYE = m_dRY3;
    }

    m_dFunc->P_Line(dRGXS, dRGYS, dRGXE, dRGYE, lCol);

    m_dRGX0 = dRGXE, m_dRGY0 = dRGYE;
            }
        }
        nAXY = 1;
    }
    //*
    //* ターゲット諸設定位置の描画
    //*
    m_iIDFlg = 1;

    m_dLengthL = 2.5;
    m_dDeltaL = 0.5;

    for (int nJKK = 0; nJKK <= 5; nJKK++) {
        //
        m_dRX = m_dLengthL + 0.5 + double(nJKK) * m_dDeltaL;
        m_dRY = 0.0;
        //
        m_dRZ = m_dRZtargetZero;
        lCol = RGB(255, 0, 0);

        if (m_dRX >= 0.0) {
            m_dRX = m_dRX + m_dRZ / m_dDepth;
        }
        else {
            m_dRX = m_dRX - m_dRZ / m_dDepth;
        }
        if (m_dRY >= 0.0) {
            m_dRY = m_dRY + m_dRZ / m_dDepth;
        }
        else {
            m_dRY = m_dRY - m_dRZ / m_dDepth;
        }

        R3D();

        if (nJKK == 0) {
            dRGXS = m_dRX3, dRGYS = m_dRY3;
            dRGXE = m_dRX3, dRGYE = m_dRY3;
        }
        else {

            dRGXS = m_dRGX0, dRGYS = m_dRGY0;
            dRGXE = m_dRX3, dRGYE = m_dRY3;
        }

        m_dFunc->P_Line(dRGXS, dRGYS, dRGXE, dRGYE, lCol);

        m_dRGX0 = dRGXE, m_dRGY0 = dRGYE;
    }


    m_dFunc->P_Char_Set("0.00", "Times New Roman", 10, -7, -9.5, RGB(0, 0, 0));
    //*
    //*
    //* レンズの描画
    //*
    //* 被検レンズと対物レンズ

    m_iIDFlg = 1;
    switch(m_iKY2)
    {
    case 11:
    {
        for(int iNyu = m_iKY2 - 1; iNyu >= 5; iNyu--) {
            switch(iNyu)
            {
            case 5:
                m_dLengthL = 20.0;
                //* m_dLengthL = 25.0;    // 20230701_これだと大きくなりすぎる_コリメーター系と対物レンズを取っ払ったら描画できるかな？
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 6:
                m_dLengthL = 20.0;
                //* m_dLengthL = 25.0;    // 20230701_これだと大きくなりすぎる_コリメーター系と対物レンズを取っ払ったら描画できるかな？
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 7: //* (m_iKY2 - 4):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 8: //* (m_iKY2 - 3):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 9: //* (m_iKY2 - 2):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 10: //* (m_iKY2 - 1):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 11: //m_iKY2:
                m_dLengthL = 20.0;
                m_dDeltaL = 8.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            }
            GLS_Kyokumen_Select(iNyu);
        }
        break;
    }
    case 13:
    {
        for(int iNyu = m_iKY2 - 1; iNyu >= 5; iNyu--) {
            switch(iNyu)
            {
            case 5:
                m_dLengthL = 20.0;
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 6:
                m_dLengthL = 20.0;
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 7:
                m_dLengthL = 20.0;
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 8:
                m_dLengthL = 20.0;
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 9: //* (m_iKY2 - 4):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 10: //* (m_iKY2 - 3):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 11: //* (m_iKY2 - 2):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 12: //* (m_iKY2 - 1):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 13: //* m_iKY2:
                m_dLengthL = 20.0;
                m_dDeltaL = 8.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            }
            GLS_Kyokumen_Select(iNyu);
        }
        break;
    }
    case 15:
    {
        for(int iNyu = m_iKY2 - 1; iNyu >= 5; iNyu--) {
            switch(iNyu)
            {
            case 5:
                m_dLengthL = 20.0;
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 6:
                m_dLengthL = 20.0;
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 7:
                m_dLengthL = 20.0;
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 8:
                m_dLengthL = 20.0;
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 9:
                m_dLengthL = 20.0;
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 10:
                m_dLengthL = 20.0;
                m_dDeltaL = 4.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 11: //* (m_iKY2 - 4):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 12: //* (m_iKY2 - 3):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 13: //* (m_iKY2 - 2):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 14: //* (m_iKY2 - 1):
                m_dLengthL = 15.0;
                m_dDeltaL = 3.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            case 15: //* m_iKY2:
                m_dLengthL = 20.0;
                m_dDeltaL = 8.0;
                m_dDK = m_dDKsub[iNyu];
                break;
            }
            GLS_Kyokumen_Select(iNyu);
            }
        }
        break;
    }

    m_iIDFlg = 0;

    return TRUE;
}

BOOL CRayTrace::GLS_Kyokumen_Select(int iNyu)
{
    long lCol = LensColor(iNyu);
    long lCol2;
    int nJKK, j_num;

    //* 曲面形状の選択
    m_iAsphericFlg = 0;
    if(m_nASNO[iNyu] == 1 || m_nTORIC[iNyu] == 1 || m_nSHAX[iNyu] == 1 || m_nTLAX[iNyu] != 0) {
        m_iASP = 2;
        m_iAsphericFlg = 1;
    }

    if(m_nTORIC[iNyu] == 1) {
        m_iASP = 1;
    }

    //* 垂直方向断面描画
    for(nJKK = 0; nJKK <= 5; nJKK++) {
        m_dRX = 0.0;
        m_dRY = m_dLengthL - double(nJKK) * m_dDeltaL;

        j_num = nJKK;
        GLSSUB(iNyu, j_num, lCol);
    }

    //* 水平方向断面描画
    for(nJKK = 0; nJKK <= 5; nJKK++)
    {
        m_dRX = double(nJKK) * m_dDeltaL;
        m_dRY = 0.0;

        j_num = nJKK;
        GLSSUB(iNyu, j_num, lCol);
    }

    if(iNyu >= 5) {
        for(nJKK = 0; nJKK <= 36; nJKK++)
        {
            //
            m_dRX = m_dLengthL * cos(KK_PI / 180.0 * double(nJKK) * 10.0);
            m_dRY = m_dLengthL * sin(KK_PI / 180.0 * double(nJKK) * 10.0);
            //
            j_num = nJKK;
            GLSSUB(iNyu, j_num, lCol);
        }
    }
    else {
        for(nJKK = 9; nJKK <= 36; nJKK++)
        {
            //
            m_dRX = m_dLengthL * cos(KK_PI / 180.0 * double(nJKK) * 10.0);
            m_dRY = m_dLengthL * sin(KK_PI / 180.0 * double(nJKK) * 10.0);
            //
            j_num = nJKK;
            GLSSUB(iNyu, j_num, lCol);
        }
    }

    //
    if(iNyu % 2 == 0) {
        //* m_dRX = -1.51
        m_dRX = -2.75; //* -1.71;
        m_dRY = -0.51;
        R3D();

        if(iNyu < 5) {
            lCol2 = RGB(200, 235, 255);
            m_dFunc->P_FloodFill(m_dRX3, m_dRY3, lCol, lCol2);
        }
    }


    return TRUE;

}

BOOL CRayTrace::GLSSUB(int iNyu, int nJKK, long lCol)
{
    double dRGXS, dRGYS;
    double dRGXE, dRGYE;

    if (m_iAsphericFlg == 0) {
        //* 共軸かつ球面レンズの描画
        m_dRZ = m_dC[iNyu] * (m_dRY * m_dRY + m_dRX * m_dRX) /
            (1.0 + sqrt(1.0 - m_dC[iNyu] * m_dC[iNyu] * (m_dRY * m_dRY + m_dRX * m_dRX)));
        m_dRZ = -(m_dRZ + m_dDK);
    }

    if(m_iAsphericFlg == 1) {
        //*
        //* 非球面または非共軸レンズの描画
        //*
        if(m_iASP == 1) {
            //*
            //* トーリックレンズの描画
            //* Ax 180 で計算させて，最後に指定の角度に回転させて出力。
            //* どうしてこうなってしまったんだろう？
            double dCOSST, dSINST;
            dCOSST = 1.0; //* m_dCylCos(iNyu)
            dSINST = 0.0; //* m_dCylSin(iNyu)

            double dVALCY, dVALCX, dVALCYX;
            dVALCY = m_dC[iNyu];
            dVALCX = m_dCylCV2[iNyu];
            dVALCYX = dVALCX * dVALCY;

            double dRYB, dRXB;
            dRYB = m_dRY * dCOSST + m_dRX * dSINST;
            dRXB = -m_dRY * dSINST + m_dRX * dCOSST;

            double dDSQ12, dALPHAI, dQ12, dD12;
            dD12 = 1.0 - SQUARE(dRYB * dVALCY);
            dDSQ12 = sqrt(dD12);
            dALPHAI = 1.0 / (1.0 + dDSQ12);
            dQ12 = (1.0 - dRYB * dRYB * dVALCYX * dALPHAI) *(1.0 - dRYB * dRYB * dVALCYX * dALPHAI)
                    - (dRXB * dVALCX) * (dRXB * dVALCX);

            double dBUNSI;
            dBUNSI = 2.0 * dRYB * dRYB * dVALCY * dALPHAI
                    - dRYB * dRYB * dRYB * dRYB * dVALCYX * dVALCY * dALPHAI * dALPHAI + dRXB * dRXB * dVALCX;
            m_dRZ = dBUNSI / (1.0 + sqrt(dQ12));
            m_dRY = dRYB * m_dCylCos[iNyu] + dRXB * m_dCylSin[iNyu];
            m_dRX = -dRYB * m_dCylSin[iNyu] + dRXB * m_dCylCos[iNyu];

            //* 光軸がシフトした場合の処理
            if(m_nSHAX[iNyu] == 1)    AxShift(iNyu);

            //* 偏心が行われた場合の処理
            if(m_nTLAX[iNyu] != 0)    HS(iNyu);

            m_dRZ = -(m_dRZ + m_dDK);
        }

        if(m_iASP == 2) {
            //* 回転対称非球面レンズの描画
            if(m_dRISIN[iNyu] == 0)    m_dRISIN[iNyu] = 1;

            double dC2AV;
            dC2AV = m_dC[iNyu] * m_dC[iNyu] * m_dRISIN[iNyu];

            int nSGVI, nj;
            nSGVI = m_nASGV[iNyu];
            nj = m_nASNO[iNyu];

            double dRYRX, dBVALS, dBVAL, dVBRI, dVConic;
            double dVH1, dVH2, dZSum, dSum1;
            double dHVAL;
            dRYRX = m_dRY * m_dRY + m_dRX * m_dRX;
            dBVALS = 1.0 - dRYRX * dC2AV;
            dBVAL = sqrt(dBVALS);
            dVBRI = m_dC[iNyu] / dBVAL;
            dVConic = dRYRX * m_dC[iNyu] / (1.0 + dBVAL);

            if(m_nAS[iNyu] == 1) {
                //* 非球面係数が偶数次のみの場合
                dVH1 = 1.0;
                dZSum = 0.0;

                dVH2 = 1.0;
                dSum1 = 0.0;

                int i;
                for(i = 1; i <= nSGVI; i++) {
                    dVH1 = dVH1 * dRYRX;
                    dZSum = dZSum + m_dAC[nj][i] * dVH1;
                    dSum1 = dSum1 + double(i) * m_dAC[nj][i] * dVH2;
                    dVH2 = dVH2 * dRYRX;
                }
            }
            else {
                //* 非球面係数が奇数次も含む場合
                dHVAL = sqrt(dRYRX);
                dVH1 = dHVAL;
                dZSum = 0.0;

                dVH2 = 1.0;
                dSum1 = 0.0;

                int i;
                for(i = 1; i <= nSGVI; i++) {
                    dVH1 = dVH1 * dHVAL;
                    dZSum = dZSum + m_dAC[nj][i] * dVH1;
                    dSum1 = dSum1 + (double(i) + 1) * m_dAC[nj][i] * dVH2;
                    dVH2 = dVH2 + dHVAL;
                }
            }

            m_dRZ = dVConic + dZSum;

            //* 光軸がシフトした場合の処理
            if(m_nSHAX[iNyu] == 1)    AxShift(iNyu);

            //* 偏心が行われた場合の処理
            if(m_nTLAX[iNyu] != 0)    HS(iNyu);

            m_dRZ = -(m_dRZ + m_dDK);
        }
    }

    if(m_dRX >= 0.0) {
        m_dRX = m_dRX + m_dRZ / m_dDepth;
    }
    else {
        m_dRX = m_dRX - m_dRZ / m_dDepth;
    }

    if(m_dRY >= 0.0) {
        m_dRY = m_dRY + m_dRZ / m_dDepth;
    }
    else {
        m_dRY = m_dRY - m_dRZ / m_dDepth;
    }

    R3D();

    if(iNyu >= 5) {
        if(nJKK == 0) {
            dRGXS = m_dRX3, dRGYS = m_dRY3;
            dRGXE = m_dRX3, dRGYE = m_dRY3;
        }
        else {
            dRGXS = m_dRGX0, dRGYS = m_dRGY0;
            dRGXE = m_dRX3, dRGYE = m_dRY3;
        }
    }
    else {
        if(nJKK == 0 || nJKK == 9) {
            dRGXS = m_dRX3, dRGYS = m_dRY3;
            dRGXE = m_dRX3, dRGYE = m_dRY3;
        }
        else {
            dRGXS = m_dRGX0, dRGYS = m_dRGY0;
            dRGXE = m_dRX3, dRGYE = m_dRY3;
        }
    }

    m_dFunc->P_Line(dRGXS, dRGYS, dRGXE, dRGYE, lCol);

    m_dRGX0 = dRGXE, m_dRGY0 = dRGYE;

    return TRUE;
}

long CRayTrace::LensColor(int iNyu)
{
    long lCol;

    if(m_iKY2 == 15) {
        switch(iNyu)
        {
        case 14:
            lCol = RGB(128, 128, 128);
            break;
        case 13:
            lCol = RGB(126, 126, 126);
            break;
        case 12:
            lCol = RGB(124, 124, 124);
            break;
        case 11:
            lCol = RGB(122, 122, 122);
            break;

        case 4:
            lCol = RGB(128, 128, 128);
            break;
        case 3:
            lCol = RGB(126, 126, 126);
            break;
        case 2:
            lCol = RGB(124, 124, 124);
            break;
        case 1:
            lCol = RGB(122, 122, 122);
            break;

        case 6:
            lCol = RGB(216, 0, 186);
            break;
        case 5:
            lCol = RGB(216, 0, 186);
            break;

        case 8:
            lCol = RGB(0, 186, 186);
            break;
        case 7:
            lCol = RGB(0, 186, 186);
            break;

        case 10:
            lCol = RGB(156, 156, 255);
            break;
        case 9:
            lCol = RGB(186, 186, 255);
            break;
        }
    }

    if(m_iKY2 == 13) {
        switch(iNyu)
        {
        case 12:
            lCol = RGB(128, 128, 128);
            break;
        case 11:
            lCol = RGB(126, 126, 126);
            break;
        case 10:
            lCol = RGB(124, 124, 124);
            break;
        case 9:
            lCol = RGB(122, 122, 122);
            break;

        case 4:
            lCol = RGB(128, 128, 128);
            break;
        case 3:
            lCol = RGB(126, 126, 126);
            break;
        case 2:
            lCol = RGB(124, 124, 124);
            break;
        case 1:
            lCol = RGB(120, 120, 120);
            break;

        case 6:
            lCol = RGB(216, 0, 186);
            break;
        case 5:
            lCol = RGB(216, 0, 186);
            break;

        case 8:
            lCol = RGB(0, 186, 186);
            break;
        case 7:
            lCol = RGB(0, 186, 186);
            break;
        }
    }

    if(m_iKY2 == 11) {
        switch(iNyu)
        {
        case 10:
            lCol = RGB(128, 128, 128);
            break;
        case 9:
            lCol = RGB(126, 126, 126);
            break;
        case 8:
            lCol = RGB(124, 124, 124);
            break;
        case 7:
            lCol = RGB(122, 122, 122);
            break;

        case 4:
            lCol = RGB(128, 128, 128);
            break;
        case 3:
            lCol = RGB(126, 126, 126);
            break;
        case 2:
            lCol = RGB(124, 124, 124);
            break;
        case 1:
            lCol = RGB(122, 122, 122);
            break;

        case 6:
            lCol = RGB(216, 0, 186);
            break;
        case 5:
            lCol = RGB(216, 0, 186);
            break;
        }
    }

    return lCol;
}


void CRayTrace::MakeCorona(int nIKK, int nJKK)
{
    if (nIKK == 0 && nJKK == 0) {
        //* 2002.06.06
        //* コロナのぼけ具合とプリズム量の関係について，調べておくこと。
        //* " / 2.0" を入れないとプリズム量が２倍で効いてくる
        m_dAX0 = m_dAX * m_dCoronaSize * m_dCoronaConfusion / 2.0;
        m_dAY0 = m_dAY * m_dCoronaSize * m_dCoronaConfusion / 2.0;
    }

    m_dStockAX[nIKK][nJKK] = m_dAX * m_dCoronaSize * m_dCoronaConfusion - m_dAX0;
    m_dStockAY[nIKK][nJKK] = m_dAY * m_dCoronaSize * m_dCoronaConfusion - m_dAY0;
    //* PintGlass1での結像
    m_dFunc->P_Pset(m_dAX * m_dCoronaSize * 4.0 + 59.0 + 18.0, m_dAY * m_dCoronaSize * 4.0 + 5.0, RGB(255, 0, 0)); // RGB(0, 128, 0)
}

BOOL CRayTrace::PGCorona(long lCoronaCol)
{
    //* PintGlassへのコロナ像の描画

    double dPx, dPy;
    int nIKK, nJKK, jjj;
    nIKK = 0, nJKK = 0, jjj = 0;
    if (m_iCoronaFlg == 0) {
        for (nIKK = 0; nIKK <36; nIKK++) {
            for (nJKK = 0; nJKK < m_iIR + 1; nJKK++) {
                for (jjj = 0; jjj < 36; jjj++) {
                    dPx = m_dCoronaSize * cos(KK_PI / 18.0 * double(jjj));
                    dPy = m_dCoronaSize * sin(KK_PI / 18.0 * double(jjj));
                    m_dFunc->P_Pset2(-m_dStockAX[nIKK][nJKK] + dPx, m_dStockAY[nIKK][nJKK] + dPy, lCoronaCol);
                }
            }
        }
    }
    else {
        for (nIKK = 0; nIKK < 36; nIKK++) {
            for (nJKK = 0; nJKK < m_iIR + 1; nJKK++) {
                m_dFunc->P_Pset2(-m_dStockAX[nIKK][nJKK], m_dStockAY[nIKK][nJKK], lCoronaCol);
            }
        }
    }
    //* ピントグラス目盛盤

    CPen pen2, *oldPen2;
    pen2.CreatePen(PS_SOLID, 1, RGB(156, 156, 156));
    oldPen2 = g_memDC2.SelectObject(&pen2);

    //* m_dPintGlassMemori = 180.0 で以下の計算を行うと，
    //* sin(...) でこける....ゼロにマイナスの符号が付いてしまう
    //* KK_PI /180.0 * m_dPintGlassMemori で m_dPintGlassMemori が 0.0 のときと 180.0 のときで
    //* sin 関数の計算結果が異なり，180.0 だと，-0.0000000000000014...となることが分かった

    double dPGMag;
    dPGMag = 1.0;

    double dPGCos, dPGSin;
    dPGCos = dPGMag * m_dCoronaSize * cos(KK_PI / 180.0 * m_dPintGlassMemori);
    dPGCos = m_dFunc->YukouNum(dPGCos);

    dPGSin = dPGMag * m_dCoronaSize * sin(KK_PI / 180.0 * m_dPintGlassMemori);
    dPGSin = m_dFunc->YukouNum(dPGSin);

    //* 十字線_水平方向
    m_dFunc->P_Line2(-15.0 * dPGCos, -15.0 * dPGSin, 15.0 * dPGCos, 15.0 * dPGSin, RGB(156, 156, 156));


    //* 十字線_垂直方向
    m_dFunc->P_Line2(8.0 * dPGSin, -8.0 * dPGCos, -8.0 * dPGSin, 8.0 * dPGCos, RGB(156, 156, 156));

    //* プリズム表示線_水平方向
    int i;
    double dPriLine;
    for (i = 0; i < 3; i++) {
        dPriLine = 2.0 + 4.0 * double(i);
        m_dFunc->P_Line2(dPriLine * dPGCos + 1.2 * dPGSin, dPriLine * dPGSin - 1.2 * dPGCos,
             dPriLine * dPGCos - 1.2 * dPGSin, dPriLine * dPGSin + 1.2 * dPGCos, RGB(156, 156, 156));
        m_dFunc->P_Line2(-dPriLine * dPGCos + 1.2 * dPGSin, -dPriLine * dPGSin - 1.2 * dPGCos,
             -dPriLine * dPGCos - 1.2 * dPGSin, -dPriLine * dPGSin + 1.2 * dPGCos, RGB(156, 156, 156));
    }

    //* プリズム表示線_垂直方向
    dPriLine = 2.0;
    m_dFunc->P_Line2(dPriLine * dPGSin + 2.0 * dPGCos, -dPriLine * dPGCos + 2.0 * dPGSin,
         dPriLine * dPGSin - 2.0 * dPGCos, -dPriLine * dPGCos - 2.0 * dPGSin, RGB(156, 156, 156));
    m_dFunc->P_Line2(-dPriLine * dPGSin + 2.0 * dPGCos, dPriLine * dPGCos + 2.0 * dPGSin,
         -dPriLine * dPGSin - 2.0 * dPGCos, dPriLine * dPGCos - 2.0 * dPGSin, RGB(156, 156, 156));

    //* 目盛盤のラジアル
    int j;
    double dRadiusCos;
    double dRadiusSin;

    for (j = 0; j < 13; j++) {
        dRadiusCos = dPGMag * m_dCoronaSize * cos(KK_PI / 18.0 * double(j) * 1.5);
        dRadiusCos = m_dFunc->YukouNum(dRadiusCos);

        dRadiusSin = dPGMag * m_dCoronaSize * sin(KK_PI / 18.0 * double(j) * 1.5);
        dRadiusSin = m_dFunc->YukouNum(dRadiusSin);

        if (j == 0 || j == 3 || j == 6 || j == 9 || j == 12) {
            m_dFunc->P_Line2(11.0 * dRadiusCos, 11.0 * dRadiusSin,
                 13.0 * dRadiusCos, 13.0 * dRadiusSin, RGB(156, 156, 156));
        }
        else {
            m_dFunc->P_Line2(11.0 * dRadiusCos, 11.0 * dRadiusSin,
                 12.0 * dRadiusCos, 12.0 * dRadiusSin, RGB(156, 156, 156));
        }
    }

    //* サークル
    m_dFunc->P_Circle2(0.0, 0.0, dPGMag * m_dCoronaSize * 4.0, 0.0, 2.0 * KK_PI, RGB(156, 156, 156));

    m_dFunc->P_Circle2(0.0, 0.0, dPGMag * m_dCoronaSize * 8.0, 0.0, 2.0 * KK_PI, RGB(156, 156, 156));

    m_dFunc->P_Circle2(0.0, 0.0, dPGMag * m_dCoronaSize * 11.0, 0.0, KK_PI, RGB(156, 156, 156));

    return TRUE;
}


