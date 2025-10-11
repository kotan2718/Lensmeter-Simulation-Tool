
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


#pragma once

extern CDC  g_memDC1;        //* Reference: Memory DC (Virtual Screen)
extern CDC  g_memDC2;        //* Reference: Memory DC (Virtual Screen)
extern CStatic g_pict1;        //* Reference: Picture Control DDX Variables
extern CStatic g_pict2;        //* Reference: Picture Control DDX Variables

//* Width and height of the picture box
extern long g_lPictureBoxSizeX, g_lPictureBoxSizeY;
extern double g_dWindowPosLeft, g_dWindowPosRight;
extern double g_dWindowPosTop, g_dWindowPosBottom;

extern long g_lPictureBoxSizeX2, g_lPictureBoxSizeY2;
extern double g_dWindowPosLeft2, g_dWindowPosRight2;
extern double g_dWindowPosTop2, g_dWindowPosBottom2;

namespace CommonParamsDef {
    //* RayTrace Lens Params
    struct rtLensDat {
        int ldp_iKY2;        //* Number of surfaces to trace

        //* KOUSEIMEN_MAX; //* Maximum number of configuration surfaces. The value is specified in StdAfx.h
        double ldp_dC[KOUSEIMEN_MAX];                //* Radius of curvature of each boundary surface
        double ldp_dD[KOUSEIMEN_MAX - 1];            //* Distance between boundary surface
        double ldp_dDKsub[KOUSEIMEN_MAX - 1];        //* Auxiliary arrays used in drawing lenses
        double ldp_dDK;                              //* Auxiliary variables used in drawing lenses
        double ldp_dD6;                              //* m_dD6: Distance from the rear surface of the tested lens
                                                     //*        to the first surface of the condenser lens: m_dC(7)
        double ldp_dN[KOUSEIMEN_MAX + 1];            //* Refractive Index
        double ldp_dLensDiameter[KOUSEIMEN_MAX];     //* Effective diameter of each surface: Calculate the aperture of each lens
                                                     //*                                     from the aperture setting value
        double ldp_dD_DefaultLengthAll;              //* Distance from the edge of the collimator to the edge of the objective lens
                                                     //* (excluding the thickness of the tested lens)

        int ldp_nASNO[KOUSEIMEN_MAX];                //* Aspheric flag
        double ldp_dRISIN[KOUSEIMEN_MAX];            //* Conic Coefficient
        int ldp_nASGV[KOUSEIMEN_MAX];                //* Order of aspherical surfaces
        int ldp_nAS[KOUSEIMEN_MAX];                  //* Flag : Even order (rotational symmetry)
                                                     //*        Odd-order (rotationally symmetric or asymmetric)
        double ldp_dAC[KOUSEIMEN_MAX][KOUSEIMEN_MAX];//* Aspheric coefficient

        int ldp_nTORIC[KOUSEIMEN_MAX];               //* Toric surface flag
        double ldp_dCylCV2[KOUSEIMEN_MAX], ldp_dCylTheta[KOUSEIMEN_MAX];

        int ldp_nSHAX[KOUSEIMEN_MAX];                //* Optical axis shift
        double ldp_dAxSHV[KOUSEIMEN_MAX][4];
        //*
        int ldp_nTLAX[KOUSEIMEN_MAX];                //* Eccentricity
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

