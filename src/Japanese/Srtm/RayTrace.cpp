
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#include "stdafx.h"
#include "RayTrace.h"
#include "GlobalDef.h"
#include "DrawFunc.h"


CRayTrace::CRayTrace()
{
    m_dFunc = new CDrawFunc;

    m_iKY2 = KOUSEIMEN_MAX;                 //* 追跡する曲面の数

    for (int i = 0; i <= m_iKY2; i++) {
        m_dC[i] = 0.0;                      //* 各境界面の曲率半径
    }
    for (int i = 0; i < m_iKY2; i++) {
        m_dD[i] = 0.0;                      //* 境界面間距離
    }
    for (int i = 0; i < m_iKY2; i++) {
        m_dDKsub[i] = 0.0;                  //* レンズの描画で使われる補助配列
    }
    m_dDK = 0.0;                            //* レンズの描画で使われる補助変数
    m_dD6 = 0.0;                            //* m_dC(6):被検レンズ裏面 から 集光レンズ第1面:m_dC(7) までの距離

    for (int i = 0; i < m_iKY2 + 1; i++) {
        m_dN[i] = 1;                        //* 屈折率
    }
    for (int i = 0; i <= m_iKY2; i++) {
        m_dLensDiameter[i] = 0.0;            //* 各面の有効径: 絞り設定値から各レンズの口径を算出
    }
    m_dD_DefaultLengthAll = 0.0;            //* コリメータの端から対物レンズの端までの距離（除く 被検レンズの厚み）

    for (int i = 0; i <= m_iKY2; i++) {
        m_nASNO[i] = 0;                     //* 非球面かどうか
    }
    for (int i = 0; i <= m_iKY2; i++) {
        m_dRISIN[i] = 0.0;                  //* 円錐係数
        m_nASGV[i] = 0;                     //* 非球面の次数
        m_nAS[i] = 0;                       //* 偶数次（回転対称）かどうか
                                            //* 奇数次（回転対称か非対称）か

        for (int j = 0; j <= m_iKY2; j++) {
            m_dAC[i][j] = 0.0;              //* 非球面係数
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

    m_dSY = 0.0;
    m_dDepth = 0.0;
    m_dRZtargetZero = 0.0;
    m_dRZhikenLens = 0.0;
    m_dRZpintGlass = 0.0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m_dTrans[i][j] = 0.0;                //* 偏心があった場合の座標変換
        }
    }
    //* レンズの描画，光線追跡での曲面形状の指定
    m_iAsphericFlg = 0;
    m_iASP = 0;

    m_dAMZ = 0.0, m_dAMY = 0.0, m_dAMX = 0.0; //* vector Ｍ...ν面へ向かう光線にν面の原点から降ろした垂線の足
    m_dAL = 0.0, m_dAM = 0.0, m_dBN = 0.0;    //* vector Ｅ ν面と光線との交点からν面の中心へ向かう法線
    m_dAZI = 0.0, m_dAYI = 0.0, m_dAXI = 0.0; //* vector ｒ...光線とν面との交点(ν面の原点から交点までのベクトル)

    m_dD3 = 0.0;                              //* SkewRay()->RP()で使用される変数

    m_dZMD = 0.0;                             //* 光軸上でν - 1 面からν面までの距離
    m_dPPI = 0.0;                             //* ν - 1 面からν面までの光線に沿った長さ

    m_dQI = 0.0;                              //* ν面からν + 1 面までの光線に沿った長さ
    m_dPSL = 0.0;                             //* m_dQIの光路長

    m_dRX = 0.0, m_dRY = 0.0, m_dRZ = 0.0;    //* R3D()に渡す3Dの射影前データ
    m_dRX3 = 0.0, m_dRY3 = 0.0, m_dRZ3 = 0.0; //* R3D()による3Dから2Dへの射影後のデータ

    //* CTM, HT
    m_dEZ = 0.0, m_dEY = 0.0, m_dEX = 0.0;

    //* GLS
    m_iIDFlg = 0;
    m_dLengthL = 0.0, m_dDeltaL = 0.0;

    //* DT
    for (int i = 0; i <= m_iKY2; i++) {
        m_dCylSin[i];
        m_dCylCos[i];
    }

    m_dAX0 = 0.0, m_dAY0 = 0.0;               //* 主光線とν面との交点

    //* MakeCorona, PGCorona
    for (int i = 0; i < CORONA_NUM; i++) {
        for (int j = 0; j < CORONA_RAY_CNT; j++) {
            m_dStockAX[i][j] = 0.0;                //* スクリーン上の像のストック
            m_dStockAY[i][j] = 0.0;
        }
    }
}


CRayTrace::~CRayTrace()
{
    delete m_dFunc;
}

//* Ray Trace Main
int CRayTrace::RayTraceMain(double dVSC_h, int nStepIR)
{
    //* 主光線のスクリーン上の座標を取得

    double dOBEZ, dOBEY, dOBEX;
    double dTOBE, dTOBEI;

    double dDeltaX, dDeltaY;

    for (int nIKK = 0; nIKK < 36; nIKK++) {
        for (int nJKK = 0; nJKK < m_iIR + 1; nJKK++) {
            dDeltaX = double(nJKK) * cos(KK_PI / 18.0 * double(nIKK)) / 4.0; //* 2.0
            dDeltaY = double(nJKK) * sin(KK_PI / 18.0 * double(nIKK)) / 4.0; //* 2.0
            m_dAX = dVSC_h * dDeltaX / double(nStepIR);
            m_dAY = dVSC_h * dDeltaY / double(nStepIR);
            m_dAZ = m_dQNTP;
            //*
            //* ----------------------------------------
            //* 光線基準面における初期設定
            //*
            dOBEZ = -m_dObjZ + m_dAZ + m_dQNTP;
            dOBEY = -m_dObjY + m_dAY;
            dOBEX = -m_dObjX + m_dAX;
            dTOBE = sqrt(SQUARE(dOBEZ) + SQUARE(dOBEY) + SQUARE(dOBEX));
            dTOBEI = 1.0 / dTOBE;
            m_dDZI = dOBEZ * dTOBEI;
            m_dDYI = dOBEY * dTOBEI;
            m_dDXI = dOBEX * dTOBEI;
            //*
            //* -----------------------------------------
            //*
            int iResult = SkewRayTrace(nIKK);
            switch (iResult)
            {
            case ERR_RAY_TRACE:        //* 1: 追跡不可能, 0: 特定なし,         0: SkewRayTrace
            case ERR_RAY_TRACE_SPH:    //* 1: 追跡不可能, 1: 共軸かつ球面,     0: SRTSph
            case ERR_RAY_TRACE_TORIC:  //* 1: 追跡不可能, 2: 非球面或は非光軸, 1: SRTToric
            case ERR_RAY_TRACE_ASPH:   //* 1: 追跡不可能, 2: 非球面或は非光軸, 2: SRTAsph
            case ERR_RAY_TRACE_ASPH2:  //* 1: 追跡不可能, 2: 非球面或は非光軸, 4: SRTAsph2
            case ERR_RAY_TRACE_HENSPH: //* 1: 追跡不可能, 2: 非球面或は非光軸, 3: SRTHenSph
    return iResult;
    break;
            default:
    break;
            }
            if (iResult != WNG_RAY_HEIGHT_OVER) {
    MakeCorona(nIKK, nJKK);
            }

            //*
            //* ------------------------------------------
            //*
        }
    }

    return 0;
}

//* RayTrace Lens Params
void CRayTrace::setLensData(CommonParamsDef::rtLensDat* params)
{
    m_iKY2 = params->ldp_iKY2;                               //* 追跡する曲面の数

    for (int i = 0; i <= m_iKY2; i++) {
        m_dC[i] = params->ldp_dC[i];                         //* 各境界面の曲率半径
    }
    for (int i = 0; i < m_iKY2; i++) {
        m_dD[i] = params->ldp_dD[i];                         //* 境界面間距離
    }
    for (int i = 0; i < m_iKY2; i++) {
        m_dDKsub[i] = params->ldp_dDKsub[i];                 //* レンズの描画で使われる補助配列
    }
    m_dDK = params->ldp_dDK;                                 //* レンズの描画で使われる補助変数
    m_dD6 = params->ldp_dD6;                                 //* m_dC(6):被検レンズ裏面 から 集光レンズ第1面:m_dC(7) までの距離
    for (int i = 0; i <= m_iKY2 + 1; i++) {
        m_dN[i] = params->ldp_dN[i];                         //* 屈折率
    }
    for (int i = 0; i <= m_iKY2; i++) {
        m_dLensDiameter[i] = params->ldp_dLensDiameter[i];   //* 各面の有効径: 絞り設定値から各レンズの口径を算出
    }
    m_dD_DefaultLengthAll = params->ldp_dD_DefaultLengthAll; //* コリメータの端から対物レンズの端までの距離（除く 被検レンズの厚み）
    for (int i = 0; i <= m_iKY2; i++) {
        m_nASNO[i] = params->ldp_nASNO[i];                   //* 非球面かどうか
    }
    for (int i = 0; i <= m_iKY2; i++) {
        m_dRISIN[i] = params->ldp_dRISIN[i];                 //* 円錐係数
        m_nASGV[i] = params->ldp_nASGV[i];                   //* 非球面の次数
        m_nAS[i] = params->ldp_nAS[i];                       //* 偶数次（回転対称）か
                                                             //* 奇数次（回転対称か非対称）か
        for (int j = 0; j <= m_iKY2; j++) {
            m_dAC[i][j] = params->ldp_dAC[i][j];             //* その非球面係数
        }
        m_nTORIC[i] = params->ldp_nTORIC[i];                 //* トーリック面かどうか
        m_dCylCV2[i] = params->ldp_dCylCV2[i];
        m_dCylTheta[i] = params->ldp_dCylTheta[i];
        m_nSHAX[i] = params->ldp_nSHAX[i];                   //* 光軸のシフト
        m_nTLAX[i] = params->ldp_nTLAX[i];                   //* 偏心
        for (int j = 0; j <= 3; j++) {
            m_dAxSHV[i][j] = params->ldp_dAxSHV[i][j];
        }
        m_dTLZ[i] = params->ldp_dTLZ[i];
        m_dTLY[i] = params->ldp_dTLY[i];
        m_dTLX[i] = params->ldp_dTLX[i];
        m_dHenTheta[i] = params->ldp_dHenTheta[i];
        m_dHenFai[i] = params->ldp_dHenFai[i];
    }
    m_dRXA = params->ldp_dRXA;
    m_dRYA = params->ldp_dRYA;
    m_dRZA = params->ldp_dRZA;

    m_dSY = params->ldp_dSY;
    m_dDepth = params->ldp_dDepth;
    m_dRZtargetZero = params->ldp_dRZtargetZero;
    m_dRZhikenLens = params->ldp_dRZhikenLens;
    m_dRZpintGlass = params->ldp_dRZpintGlass;
}

//* RayTrace Init Params
void CRayTrace::setInit(CommonParamsDef::rtInit* params_rt)
{
    m_iIR = params_rt->ldp_iIR;
    m_dAX = params_rt->ldp_dAX;
    m_dAY = params_rt->ldp_dAY;
    m_dAZ = params_rt->ldp_dAZ;
    m_dQNTP = params_rt->ldp_dQNTP;
    m_dObjX = params_rt->ldp_dObjX;
    m_dObjY = params_rt->ldp_dObjY;
    m_dObjZ = params_rt->ldp_dObjZ;
    m_dDXI = params_rt->ldp_dDXI;
    m_dDYI = params_rt->ldp_dDYI;
    m_dDZI = params_rt->ldp_dDZI;

    m_dTLX[5] = params_rt->ldp_dTLX5;
    m_dTLX[6] = params_rt->ldp_dTLX6;
    m_dTLY[5] = params_rt->ldp_dTLY5;
    m_dTLY[6] = params_rt->ldp_dTLY6;
    m_dHenFai[5] = params_rt->ldp_dHenFai5;
    m_dHenFai[6] = params_rt->ldp_dHenFai6;
    m_dHenTheta[5] = params_rt->ldp_dHenTheta5;
    m_dHenTheta[6] = params_rt->ldp_dHenTheta6;
    m_dCylTheta[5] = params_rt->ldp_dCylTheta5;
    m_dCylTheta[6] = params_rt->ldp_dCylTheta6;
    m_dCylCV2[5] = params_rt->ldp_dCylCV25;
    m_dCylCV2[6] = params_rt->ldp_dCylCV26;
    m_dC[5] = params_rt->ldp_dC5;
    m_dC[6] = params_rt->ldp_dC6;
    m_dD[5] = params_rt->ldp_dD5;
    m_dD[8] = params_rt->ldp_dD8;
    m_dD[10] = params_rt->ldp_dD10;
    m_dN[5] = params_rt->ldp_dN5;
    m_dN[6] = params_rt->ldp_dN6;
    m_dPintGlassMemori = params_rt->ldp_dPintGlassMemori;
    m_dCoronaSize = params_rt->ldp_dCoronaSize;
    m_dCoronaConfusion = params_rt->ldp_dCoronaConfusion;
    m_iCoronaFlg = params_rt->ldp_iCoronaFlg;

}