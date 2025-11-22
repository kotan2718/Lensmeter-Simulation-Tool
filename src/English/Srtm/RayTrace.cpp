
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


#include "stdafx.h"
#include "RayTrace.h"
#include "GlobalDef.h"
#include "DrawFunc.h"


CRayTrace::CRayTrace()
{
    m_dFunc = new CDrawFunc;

    m_iKY2 = KOUSEIMEN_MAX;                 //* Number of surfaces to trace

    for (int i = 0; i <= m_iKY2; i++) {
        m_dC[i] = 0.0;                      //* Radius of curvature of each boundary surface
    }
    for (int i = 0; i < m_iKY2; i++) {
        m_dD[i] = 0.0;                      //* Distance between boundary surface
    }
    for (int i = 0; i < m_iKY2; i++) {
        m_dDKsub[i] = 0.0;                  //* Auxiliary arrays used in drawing lenses
    }
    m_dDK = 0.0;                            //* Auxiliary variables used in drawing lenses
    m_dD6 = 0.0;                            //* m_dD6 : Distance from the rear surface of the tested lens
                                            //*         to the first surface of the condenser lens: m_dC(7)
    for (int i = 0; i < m_iKY2 + 1; i++) {
        m_dN[i] = 1;                        //* Refractive Index
    }
    for (int i = 0; i <= m_iKY2; i++) {
        m_dLensDiameter[i] = 0.0;           //* Effective diameter of each surface: Calculate the aperture of each lens
                                            //*                                     from the aperture setting value
    }
    m_dD_DefaultLengthAll = 0.0;            //* Distance from the edge of the collimator to the edge of the objective lens
                                            //* (excluding the thickness of the tested lens)

    for (int i = 0; i <= m_iKY2; i++) {
        m_nASNO[i] = 0;                     //* Aspheric flag
    }
    for (int i = 0; i <= m_iKY2; i++) {
        m_dRISIN[i] = 0.0;                  //* Conic Coefficient
        m_nASGV[i] = 0;                     //* Order of aspherical surfaces
        m_nAS[i] = 0;                       //* Flag : Even order (rotational symmetry)
                                            //*        Odd-order (rotationally symmetric or asymmetric)

        for (int j = 0; j <= m_iKY2; j++) {
            m_dAC[i][j] = 0.0;              //* Aspheric coefficient
        }
        m_nTORIC[i] = 0;                    //* Toric surface flag
        m_dCylCV2[i] = 0.0;
        m_dCylTheta[i] = 0.0;
        m_nSHAX[i] = 0;                     //* Optical axis shift
        m_nTLAX[i] = 0;                     //* Eccentricity
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
            m_dTrans[i][j] = 0.0;                //* Coordinate transformation in the case of eccentricity
        }
    }
    //* Drawing lenses and specifying surface shapes in ray tracing
    m_iAsphericFlg = 0;
    m_iASP = 0;

    m_dAMZ = 0.0, m_dAMY = 0.0, m_dAMX = 0.0; //* vector Ｍ : The foot of the perpendicular line dropped from
                                              //*             the origin of the ν surface to the ray of light
                                              //*             heading towards the ν surface
    m_dAL = 0.0, m_dAM = 0.0, m_dBN = 0.0;    //* vector Ｅ : The normal line directed from the intersection point of
                                              //*             the ν surface and the ray toward the center of the ν surface
    m_dAZI = 0.0, m_dAYI = 0.0, m_dAXI = 0.0; //* vector ｒ : The intersection point of the ray and the ν surface (the vector
                                              //*             from the origin of the ν surface to the intersection point)

    m_dD3 = 0.0;                              //* Variable used in SkewRay()->RP()

    m_dZMD = 0.0;                             //* Distance from the ν - 1 surface to the ν surface along the optical axis
    m_dPPI = 0.0;                             //* Length along the ray from the ν-1 surface to the ν surface

    m_dQI = 0.0;                              //* Length along the ray from the ν surface to the ν + 1 surface
    m_dPSL = 0.0;                             //* Optical path length of m_dQI

    m_dRX = 0.0, m_dRY = 0.0, m_dRZ = 0.0;    //* 3D pre-projection data passed to R3D()
    m_dRX3 = 0.0, m_dRY3 = 0.0, m_dRZ3 = 0.0; //* Data after projection from 3D to 2D using R3D()

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

    m_dAX0 = 0.0, m_dAY0 = 0.0;               //* The intersection point of the principal ray and the ν surface

    //* MakeCorona, PGCorona
    for (int i = 0; i < CORONA_NUM; i++) {
        for (int j = 0; j < CORONA_RAY_CNT; j++) {
            m_dStockAX[i][j] = 0.0;                //* Stock of images on the screen
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
    //* Obtain the coordinates of the principal ray on the screen

    double dOBEZ, dOBEY, dOBEX;
    double dTOBE, dTOBEI;

    double dDeltaX, dDeltaY;

    for (int nIKK = 0; nIKK < 36; nIKK++) {
        for (int nJKK = 0; nJKK < m_iIR + 1; nJKK++) {
            if (m_iCoronaFlg == 0) {
                dDeltaX = double(nJKK) * cos(KK_PI / 18.0 * double(nIKK)) / 4.0; //* 2.0
                dDeltaY = double(nJKK) * sin(KK_PI / 18.0 * double(nIKK)) / 4.0; //* 2.0
            }
            else {
                dDeltaX = double(nJKK) * 0.2777777777777778 * cos(KK_PI / 18.0 * double(nIKK)) / 4.0; //* 2.0
                dDeltaY = double(nJKK) * 0.2777777777777778 * sin(KK_PI / 18.0 * double(nIKK)) / 4.0; //* 2.0
            }
            m_dAX = dVSC_h * dDeltaX / double(nStepIR);
            m_dAY = dVSC_h * dDeltaY / double(nStepIR);
            m_dAZ = m_dQNTP;
            //*
            //* ----------------------------------------
            //* Initial setting at the ray reference plane
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
            case ERR_RAY_TRACE:        //* 1: Untraceable, 0: None specified,          0: SkewRayTrace
            case ERR_RAY_TRACE_SPH:    //* 1: Untraceable, 1: Spherical and coaxial,   0: SRTSph
            case ERR_RAY_TRACE_TORIC:  //* 1: Untraceable, 2: Aspheric or non-coaxial, 1: SRTToric
            case ERR_RAY_TRACE_ASPH:   //* 1: Untraceable, 2: Aspheric or non-coaxial, 2: SRTAsph
            case ERR_RAY_TRACE_ASPH2:  //* 1: Untraceable, 2: Aspheric or non-coaxial, 4: SRTAsph2
            case ERR_RAY_TRACE_HENSPH: //* 1: Untraceable, 2: Aspheric or non-coaxial, 3: SRTHenSph
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
    m_iKY2 = params->ldp_iKY2;                               //* Number of surfaces to trace

    for (int i = 0; i <= m_iKY2; i++) {
        m_dC[i] = params->ldp_dC[i];                         //* Radius of curvature of each boundary surface
    }
    for (int i = 0; i < m_iKY2; i++) {
        m_dD[i] = params->ldp_dD[i];                         //* Distance between boundary surface
    }
    for (int i = 0; i < m_iKY2; i++) {
        m_dDKsub[i] = params->ldp_dDKsub[i];                 //* Auxiliary arrays used in drawing lenses
    }
    m_dDK = params->ldp_dDK;                                 //* Auxiliary variables used in drawing lenses
    m_dD6 = params->ldp_dD6;                                 //* m_dC(6):Distance from the rear surface of the tested lens
                                                             //* to the first surface of the condenser lens: m_dC(7)
    for (int i = 0; i <= m_iKY2 + 1; i++) {
        m_dN[i] = params->ldp_dN[i];                         //* Refractive Index
    }
    for (int i = 0; i <= m_iKY2; i++) {
        m_dLensDiameter[i] = params->ldp_dLensDiameter[i];   //* Effective diameter of each surface: Calculate the aperture of each lens
                                                             //*                                     from the aperture setting value
    }
    m_dD_DefaultLengthAll = params->ldp_dD_DefaultLengthAll; //* Distance from the edge of the collimator to the edge of the objective lens
                                                             //* (excluding the thickness of the tested lens)
    for (int i = 0; i <= m_iKY2; i++) {
        m_nASNO[i] = params->ldp_nASNO[i];                   //* Aspheric flag
    }
    for (int i = 0; i <= m_iKY2; i++) {
        m_dRISIN[i] = params->ldp_dRISIN[i];                 //* Conic Coefficient
        m_nASGV[i] = params->ldp_nASGV[i];                   //* Order of aspherical surfaces
        m_nAS[i] = params->ldp_nAS[i];                       //* Flag : Even order (rotational symmetry)
                                                             //*        Odd-order (rotationally symmetric or asymmetric)
        for (int j = 0; j <= m_iKY2; j++) {
            m_dAC[i][j] = params->ldp_dAC[i][j];             //* Aspheric coefficient
        }
        m_nTORIC[i] = params->ldp_nTORIC[i];                 //* Toric surface flag
        m_dCylCV2[i] = params->ldp_dCylCV2[i];
        m_dCylTheta[i] = params->ldp_dCylTheta[i];
        m_nSHAX[i] = params->ldp_nSHAX[i];                   //* Optical axis shift
        m_nTLAX[i] = params->ldp_nTLAX[i];                   //* Eccentricity
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