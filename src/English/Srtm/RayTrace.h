
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


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
    //* Creating a Corona Image (Pint Glass)
    //* and Drawing (Screen)
    void MakeCorona(int nIKK, int nJKK);
    //* ================================================

    //* ================================================
    //* Drawing a Corona Image
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
    int m_iKY2;    //* Number of surfaces to trace

        //* KOUSEIMEN_MAX; //* Maximum number of configuration surfaces. The value is specified in StdAfx.h
    double m_dC[KOUSEIMEN_MAX];                 //* Radius of curvature of each boundary surface
    double m_dD[KOUSEIMEN_MAX - 1];             //* Distance between boundary surface
    double m_dDKsub[KOUSEIMEN_MAX - 1];         //* Auxiliary arrays used in drawing lenses
    double m_dDK;                               //* Auxiliary variables used in drawing lenses
    double m_dD6;                               //* m_dD6: Distance from the rear surface of the tested lens
                                                //*        to the first surface of the condenser lens: m_dC(7)
    double m_dN[KOUSEIMEN_MAX + 1];             //* Refractive Index
    double m_dLensDiameter[KOUSEIMEN_MAX];      //* Effective diameter of each surface: Calculate the aperture of each lens
                                                //*                                     from the aperture setting value
    double m_dD_DefaultLengthAll;               //* Distance from the edge of the collimator to the edge of the objective lens
                                                //* (excluding the thickness of the tested lens)
    int m_nASNO[KOUSEIMEN_MAX];                 //* Aspheric flag
    double m_dRISIN[KOUSEIMEN_MAX];             //* Conic Coefficient
    int m_nASGV[KOUSEIMEN_MAX];                 //* Order of aspherical surfaces
    int m_nAS[KOUSEIMEN_MAX];                   //* Flag : Even order (rotational symmetry)
                                                //*        Odd-order (rotationally symmetric or asymmetric)
    double m_dAC[KOUSEIMEN_MAX][KOUSEIMEN_MAX]; //* Aspheric coefficient

    int m_nTORIC[KOUSEIMEN_MAX];                //* Toric surface flag
    double m_dCylTheta5;
    double m_dCylCV2[KOUSEIMEN_MAX], m_dCylTheta[KOUSEIMEN_MAX];

    int m_nSHAX[KOUSEIMEN_MAX];                 //* Optical axis shift
    double m_dAxSHV[KOUSEIMEN_MAX][4];

    int m_nTLAX[KOUSEIMEN_MAX];                 //* Eccentricity
    double m_dTLZ[KOUSEIMEN_MAX], m_dTLY[KOUSEIMEN_MAX], m_dTLX[KOUSEIMEN_MAX];
    double m_dHenTheta[KOUSEIMEN_MAX], m_dHenFai[KOUSEIMEN_MAX];

    double m_dRXA;
    double m_dRYA;
    double m_dRZA;

    double m_dSY;                            //* Aperture radius on the first surface
    double m_dDepth;
    double m_dRZtargetZero;
    double m_dRZhikenLens;
    double m_dRZpintGlass;
    //* ////////////////////////////

    //* ////////////////////////////
    //* /// RayTrace Initialize ////
    //* ////////////////////////////
    int m_iIR;
    double m_dAX;     //* vector ｒ...The intersection point of the ray and the ν surface
                      //* (the vector from the origin of the ν surface to the intersection point)
    double m_dAY;
    double m_dAZ;
    double m_dQNTP;   //* Distance from the first surface to the ray initial coordinate plane (entrance pupil)
    double m_dObjX;   //* target position
    double m_dObjY;
    double m_dObjZ;
    double m_dDXI;    //* vector Ｑ...Ray from ν-1 surface to ν surface
    double m_dDYI;
    double m_dDZI;

    double m_dPintGlassMemori;
    double m_dCoronaSize;
    double m_dCoronaConfusion;
    int m_iCoronaFlg;
    //* ////////////////////////////

    double m_dTrans[4][4]; //* Coordinate transformation in the case of eccentricity

    //* Drawing lenses and specifying surface shapes in ray tracing
    int m_iAsphericFlg;
    int m_iASP;

    double m_dAMZ, m_dAMY, m_dAMX;   //* vector Ｍ : The foot of the perpendicular line dropped from
                                     //*             the origin of the ν surface to the ray of light
    double m_dAL, m_dAM, m_dBN;      //* vector Ｅ : The normal line directed from the intersection point of
                                     //*             the ν surface and the ray toward the center of the ν surface
    double m_dAZI, m_dAYI, m_dAXI;   //* vector ｒ...vector ｒ : The intersection point of the ray and the ν surface (the vector
                                     //*             from the origin of the ν surface to the intersection point)

    double m_dD3;                    //* Variable used in SkewRay()->RP()

    double m_dZMD;                   //* Distance from the ν - 1 surface to the ν surface along the optical axis
    double m_dPPI;                   //* Length along the ray from the ν-1 surface to the ν surface

    double m_dQI;                    //* Length along the ray from the ν surface to the ν + 1 surface
    double m_dPSL;                   //* Optical path length of m_dQI

    //* m_dNowDefaultObjZ is the default value when lens data is changed

    double m_dRX, m_dRY, m_dRZ;      //* 3D pre-projection data passed to R3D()
    double m_dRX3, m_dRY3, m_dRZ3;   //* Data after projection from 3D to 2D using R3D()

    //* CTM, HT
    double m_dEZ, m_dEY, m_dEX;

    //* GLS
    int m_iIDFlg;
    double m_dLengthL, m_dDeltaL;

    //* DT
    //* Placing these arrays after m_StockAX[][] and m_StockAY[][] causes an error during memory release at termination. Why?
    double m_dCylSin[KOUSEIMEN_MAX], m_dCylCos[KOUSEIMEN_MAX];

    double m_dAX0, m_dAY0;            //* The intersection point of the principal ray and the ν surface

    //* MakeCorona, PGCorona
    double m_dStockAX[CORONA_NUM][CORONA_RAY_CNT2];        //* Stock of images on the screen
    double m_dStockAY[CORONA_NUM][CORONA_RAY_CNT2];

};

