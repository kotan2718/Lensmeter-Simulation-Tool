
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#pragma once

#include "GlobalDef.h"
#include "DrawFunc.h"

class CRayTrace
{
public:
    CRayTrace();
    ~CRayTrace();

    //* RayTrace Lens Params
    void setLensData(CommonParamsDef::rtLensDat*);

    //* RayTrace Init Params
    void setInit(CommonParamsDef::rtInit*);

    //* Ray Trace Main
    int RayTraceMain(double dVSC_h, int nStepIR);


    //SkewRayTrace

    //* ================================================
    int SkewRayTrace(int IKK);
    //* ================================================


    //* GLS as Graphics of Lens Shaping

    //* ================================================
    BOOL GLS1();
    //* ================================================

    //* ================================================
    BOOL GLS2();
    //* ================================================

    //* ================================================
    //* コロナ像の作成（ピントグラス）と描画(スクリーン)
    void MakeCorona(int nIKK, int nJKK);
    //* ================================================

    //* ================================================
    //* コロナ像の描画（ピントグラス）
    BOOL PGCorona(long lCoronaCol);
    //* ================================================

    //* RayTrace_sub

    //* ++++++++++++++++++++++++++++++++++++++++++++++++
    //
    BOOL DT();
    //* ++++++++++++++++++++++++++++++++++++++++++++++++

private:
    CDrawFunc* m_dFunc;

    //SkewRayTrace

    //* ++++++++++++++++++++++++++++++++++++++++++++++++
    BOOL RP(int iNyu, long lCol);
    //* ++++++++++++++++++++++++++++++++++++++++++++++++

    //* ------------------------------------------------
    BOOL SRTSph(int iNyu);
    //* ------------------------------------------------

    //* ------------------------------------------------
    BOOL SRTAsph(int iNyu);
    //* ------------------------------------------------

    //* ------------------------------------------------
    BOOL SRTToric(int iNyu);
    //* ------------------------------------------------

    //* GLS as Graphics of Lens Shaping

    //* ------------------------------------------------
    BOOL GLS_Kyokumen_Select(int iNyu);
    //* ------------------------------------------------

    //* ++++++++++++++++++++++++++++++++++++++++++++++++
    long LensColor(int iNyu);
    //* ++++++++++++++++++++++++++++++++++++++++++++++++

    //* ------------------------------------------------
    BOOL GLSSUB(int iNyu, int JKK, long lCol);
    double m_dRGX0, m_dRGY0;
    //* ------------------------------------------------

    //* RayTrace_sub

    //* ++++++++++++++++++++++++++++++++++++++++++++++++
    //* AxShift
    BOOL AxShift(int iNyu);
    //* ++++++++++++++++++++++++++++++++++++++++++++++++

    //* ++++++++++++++++++++++++++++++++++++++++++++++++
    //*
    BOOL CONVERT(double dBZI, double dBYI, double dBXI, int iInverse);

    double m_dVZ, m_dVY, m_dVX;
    //* ++++++++++++++++++++++++++++++++++++++++++++++++

    //* ++++++++++++++++++++++++++++++++++++++++++++++++
    //
    BOOL CTM(double dVEZ, double dVEY, double dVEX);
    //* ++++++++++++++++++++++++++++++++++++++++++++++++

    //* ++++++++++++++++++++++++++++++++++++++++++++++++
    //
    BOOL R3D();
    //* ++++++++++++++++++++++++++++++++++++++++++++++++

    //* ++++++++++++++++++++++++++++++++++++++++++++++++
    //
    BOOL HE(int iNyu);
    //* ++++++++++++++++++++++++++++++++++++++++++++++++

    //* ++++++++++++++++++++++++++++++++++++++++++++++++
    BOOL HS(int iNyu);
    //* ++++++++++++++++++++++++++++++++++++++++++++++++

    //* ++++++++++++++++++++++++++++++++++++++++++++++++
    BOOL RAYCHECK();
    //* ++++++++++++++++++++++++++++++++++++++++++++++++

    //* ////////////////////////////
    //* /// RayTrace Lens Params ///
    //* ////////////////////////////
    int m_iKY2;    //* 追跡する曲面の数

    //* KOUSEIMEN_MAX; //* 構成面の数の上限。数値は StdAfx.h で指定
    double m_dC[KOUSEIMEN_MAX];              //* 各境界面の曲率半径
    double m_dD[KOUSEIMEN_MAX - 1];          //* 境界面間距離
    double m_dDKsub[KOUSEIMEN_MAX - 1];      //* レンズの描画で使われる補助配列
    double m_dDK;                            //* レンズの描画で使われる補助変数
    double m_dD6;                            //* m_dC(6):被検レンズ裏面 から 集光レンズ第1面:m_dC(7) までの距離
    double m_dN[KOUSEIMEN_MAX + 1];          //* 屈折率
    double m_dLensDiameter[KOUSEIMEN_MAX];   //各面の有効径: 絞り設定値から各レンズの口径を算出
    double m_dD_DefaultLengthAll;            //コリメータの端から対物レンズの端までの距離（除く 被検レンズの厚み）
    int m_nASNO[KOUSEIMEN_MAX];              //* 非球面かどうか
    double m_dRISIN[KOUSEIMEN_MAX];          //* 円錐係数
    int m_nASGV[KOUSEIMEN_MAX];              //* 非球面の次数
    int m_nAS[KOUSEIMEN_MAX];                //* 偶数次（回転対称）か
                                             //* 奇数次（回転対称か非対称）か
    double m_dAC[KOUSEIMEN_MAX][KOUSEIMEN_MAX]; //* その非球面係数

    int m_nTORIC[KOUSEIMEN_MAX];             //* トーリック面かどうか
    double m_dCylTheta5;
    double m_dCylCV2[KOUSEIMEN_MAX], m_dCylTheta[KOUSEIMEN_MAX];

    int m_nSHAX[KOUSEIMEN_MAX];              //* 光軸のシフト
    double m_dAxSHV[KOUSEIMEN_MAX][4];

    int m_nTLAX[KOUSEIMEN_MAX];              //* 偏心
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
    //* ////////////////////////////

    //* ////////////////////////////
    //* /// RayTrace Initialize ////
    //* ////////////////////////////
    int m_iIR;
    double m_dAX;     //* vector ｒ...光線とν面との交点(ν面の原点から交点までのベクトル)
    double m_dAY;
    double m_dAZ;
    double m_dQNTP;   //* 第1面から光線初期座標面(入射瞳)までの距離
    double m_dObjX;   //* target position
    double m_dObjY;
    double m_dObjZ;
    double m_dDXI;    //* vector Ｑ...ν-1 面からν面へ向かう光線
    double m_dDYI;
    double m_dDZI;

    double m_dPintGlassMemori;
    double m_dCoronaSize;
    double m_dCoronaConfusion;
    int m_iCoronaFlg;
    //* ////////////////////////////

    double m_dTrans[4][4]; //* 偏心があった場合の座標変換

    //* レンズの描画，光線追跡での曲面形状の指定
    int m_iAsphericFlg;
    int m_iASP;

    double m_dAMZ, m_dAMY, m_dAMX;   //* vector Ｍ...ν面へ向かう光線にν面の原点から降ろした垂線の足
    double m_dAL, m_dAM, m_dBN;      //* vector Ｅ ν面と光線との交点からν面の中心へ向かう法線
    double m_dAZI, m_dAYI, m_dAXI;   //* vector ｒ...光線とν面との交点(ν面の原点から交点までのベクトル)

    double m_dD3;                    //* SkewRay()->RP()で使用される変数

    double m_dZMD;                   //* 光軸上でν - 1 面からν面までの距離
    double m_dPPI;                   //* ν - 1 面からν面までの光線に沿った長さ

    double m_dQI;                    //* ν面からν + 1 面までの光線に沿った長さ
    double m_dPSL;                   //* m_dQIの光路長

    //* m_dNowDefaultObjZはレンズデータ変更時の初期設定値

    double m_dRX, m_dRY, m_dRZ;      //* R3D()に渡す3Dの射影前データ
    double m_dRX3, m_dRY3, m_dRZ3;   //* R3D()による3Dから2Dへの射影後のデータ

    //* CTM, HT
    double m_dEZ, m_dEY, m_dEX;

    //* GLS
    int m_iIDFlg;
    double m_dLengthL, m_dDeltaL;

    //* DT
    //* これらの配列をm_StockAX[][], m_StockAY[][]の後ろに持ってくると、終了時のメモリー解放でエラーが出る。何故？
    double m_dCylSin[KOUSEIMEN_MAX], m_dCylCos[KOUSEIMEN_MAX];

    double m_dAX0, m_dAY0;            //* 主光線とν面との交点

    //* MakeCorona, PGCorona
    double m_dStockAX[CORONA_NUM][CORONA_RAY_CNT2];        //* スクリーン上の像のストック
    double m_dStockAY[CORONA_NUM][CORONA_RAY_CNT2];

};

