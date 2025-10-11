
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#pragma once

extern CDC  g_memDC1;        //* 参照: メモリDC(仮想画面)
extern CDC  g_memDC2;        //* 参照: メモリDC(仮想画面)
extern CStatic g_pict1;        //* 参照: ピクチャーコントロールのDDX変数
extern CStatic g_pict2;        //* 参照: ピクチャーコントロールのDDX変数

//* ピクチャーボックスの幅と高さ
extern long g_lPictureBoxSizeX, g_lPictureBoxSizeY;
extern double g_dWindowPosLeft, g_dWindowPosRight;
extern double g_dWindowPosTop, g_dWindowPosBottom;

extern long g_lPictureBoxSizeX2, g_lPictureBoxSizeY2;
extern double g_dWindowPosLeft2, g_dWindowPosRight2;
extern double g_dWindowPosTop2, g_dWindowPosBottom2;

namespace CommonParamsDef {
    //* RayTrace Lens Params
    struct rtLensDat {
        int ldp_iKY2;        //* 追跡する曲面の数

        //* KOUSEIMEN_MAX; //* 構成面の数の上限。数値は StdAfx.h で指定
        double ldp_dC[KOUSEIMEN_MAX];                //* 各境界面の曲率半径
        double ldp_dD[KOUSEIMEN_MAX - 1];            //* 境界面間距離
        double ldp_dDKsub[KOUSEIMEN_MAX - 1];        //* レンズの描画で使われる補助配列
        double ldp_dDK;                              //* レンズの描画で使われる補助変数
        double ldp_dD6;                              //* m_dC(6):被検レンズ裏面 から 集光レンズ第1面:m_dC(7) までの距離
        double ldp_dN[KOUSEIMEN_MAX + 1];            //* 屈折率
        double ldp_dLensDiameter[KOUSEIMEN_MAX];     //* 各面の有効径: 絞り設定値から各レンズの口径を算出
        double ldp_dD_DefaultLengthAll;              //* コリメータの端から対物レンズの端までの距離（除く 被検レンズの厚み）

        int ldp_nASNO[KOUSEIMEN_MAX];                //* 非球面かどうか
        double ldp_dRISIN[KOUSEIMEN_MAX];            //* 円錐係数
        int ldp_nASGV[KOUSEIMEN_MAX];                //* 非球面の次数
        int ldp_nAS[KOUSEIMEN_MAX];                  //* 偶数次（回転対称）か
                                                     //* 奇数次（回転対称か非対称）か
        double ldp_dAC[KOUSEIMEN_MAX][KOUSEIMEN_MAX];//* その非球面係数

        int ldp_nTORIC[KOUSEIMEN_MAX];               //* トーリック面かどうか
        double ldp_dCylCV2[KOUSEIMEN_MAX], ldp_dCylTheta[KOUSEIMEN_MAX];

        int ldp_nSHAX[KOUSEIMEN_MAX];                //* 光軸のシフト
        double ldp_dAxSHV[KOUSEIMEN_MAX][4];
        //*
        int ldp_nTLAX[KOUSEIMEN_MAX];                //* 偏心
        double ldp_dTLZ[KOUSEIMEN_MAX], ldp_dTLY[KOUSEIMEN_MAX], ldp_dTLX[KOUSEIMEN_MAX];
        double ldp_dHenTheta[KOUSEIMEN_MAX], ldp_dHenFai[KOUSEIMEN_MAX];

        double ldp_dDepth;

        double ldp_dRXA;
        double ldp_dRYA;
        double ldp_dRZA;

        double ldp_dSY;
        double ldp_dRZtargetZero;
        double ldp_dRZhikenLens;
        double ldp_dRZpintGlass;
    };

    //* RayTrace Initialize
    struct rtInit {
        int ldp_iIR;
        double ldp_dAX;
        double ldp_dAY;
        double ldp_dAZ;
        double ldp_dQNTP;
        double ldp_dObjX;
        double ldp_dObjY;
        double ldp_dObjZ;    //* target position
        double ldp_dDpt;     //* target position to Diopter
        double ldp_dDXI;
        double ldp_dDYI;
        double ldp_dDZI;
        double ldp_dTLX5;
        double ldp_dTLX6;
        double ldp_dTLY5;
        double ldp_dTLY6;
        double ldp_dHenFai5;
        double ldp_dHenFai6;
        double ldp_dHenTheta5;
        double ldp_dHenTheta6;
        double ldp_dCylTheta5;
        double ldp_dCylTheta6;
        double ldp_dCylCV25;
        double ldp_dCylCV26;
        double ldp_dC5;
        double ldp_dC6;
        double ldp_dD5;
        double ldp_dD8;
        double ldp_dD10;
        double ldp_dN5;
        double ldp_dN6;
        double ldp_dPintGlassMemori;
        double ldp_dCoronaSize;
        double ldp_dCoronaConfusion;
        int ldp_iCoronaFlg;
    };
}

class CGlobalDef
{
public:
    CGlobalDef();
    ~CGlobalDef();
};

