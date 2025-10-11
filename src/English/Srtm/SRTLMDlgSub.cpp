
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


// SRTLM.cpp : Define classes for applications.
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
    //* Number of Boundary Surfaces
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

    //* For verifying collimator 1
    //* m_dN[5] = 1.0, m_dN[6] = 1.0, m_dN[7] = 1.0, m_dN[8] = 1.523
    //* For verifying collimator 2
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
        //* The 7th surface is generally not toric, but it is pre-set with
        //* toric attributes to correspond  to cases where the tested lens is inverted.
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

    //* If the surface is rotationally symmetrical aspherical, it's nuber is setted
    m_nASNO[1] = 0, m_nASNO[2] = 0, m_nASNO[3] = 0;
    m_nASNO[4] = 0, m_nASNO[5] = 0, m_nASNO[6] = 0;
    m_nASNO[7] = 0;
    //m_nASNO[7] = 7; //* Aspheric surface check OK
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


    //* m_dRISIN[i] : conic coefficient, m_nASGV[i] : order, m_dAC[i][j]: Its aspheric coefficient

    //* If the aspheric coefficient is only of even order, use “1”; if it includes odd orders, use “2”.
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


    //* Optical axis shift
    //* Problematic....This completely shifts the optical axis of the tracing ray
    //* Unused in this version
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

    //* Unlike shifting, eccentricity only affects surfaces where m_nTLAX[i] is ON.
    //* Therefore, set m_nTLAX[i] to ON for all surfaces where eccentricity is desired
    //* and provide the necessary vector components for eccentricity.

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

    //* This is how the lens is shifted;
    //* So it really is eccentricity after all...
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



    //* Distance from the edge of the collimator to the edge of the objective lens (excluding the thickness of the tested lens)
    m_dD_DefaultLengthAll = 0.0;
    for(int i = 1; i < m_iKY2 - 1; i++) {
        switch(m_iKY2){
        case 11:
            if(i != 5)    m_dD_DefaultLengthAll = m_dD_DefaultLengthAll + m_dD[i];
            break;
        case 13: //* Check for D[6]
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
        //* Number of tested lenses : 1
        m_dRZpintGlass = m_dRZhikenLens - (m_dD[6] + m_dD[7] + m_dD[8] + m_dD[9] + m_dD[10]); //* m_dD[6]に被検レンズの厚みが含まれている
        break;
    case 13:
        //* Number of tested lenses : 2
        m_dRZpintGlass = m_dRZhikenLens - (m_dD[8] + m_dD[9] + m_dD[10] + m_dD[11] + m_dD[12]); //* m_dD[6]に被検レンズの厚みが含まれている
        break;
    case 15:
        //* Number of tested lenses : 3
        m_dRZpintGlass = m_dRZhikenLens - (m_dD[10] + m_dD[11] + m_dD[12] + m_dD[13] + m_dD[14]); //* m_dD[6]に被検レンズの厚みが含まれている
        break;
    }

    //* Distance from the rear vertex of the tested lens to the pint glass (1/100th of this distance equals 1 prism)
    //* m_dRZpintGlass - m_dRZhikenLens

    //* Position of the principal ray on the Pint-Glass
    //* when a model lens with S-2.00D, front curve 4, index 1.50, and center thickness 0.00 is shifted by 5mm.
    //* 0.51733091244028
    //* Position on the Pint-Glass when the collimator 2 is removed
    //* 1.13563865457563

    //* Normalization of Pint-Glas and Corona Image Sizes
    //* m_dCoronaSize = -(m_dRZpintGlass - m_dRZhikenLens) / 100 * 0.51733091244028 / 1.13563865457563;
    m_dCoronaSize = -(m_dRZpintGlass - m_dRZhikenLens) / 100 * 0.515039404171801 / 1.14685761552409;
    m_dCoronaConfusion = 8.0; //* Adjusting the blur amount of the corona image (*4.0 matches the Pint-Glass size but the blur amount is too small)
    m_dWin2DefaultSize = m_dCoronaSize;
    m_dWin2Mag = 15.0;

    //* Initial angle of the crosshairs on the Pint-Glass
    m_dPintGlassMemori = 0.0;

    //* Stores the initial value of Ax
    if(m_nTORIC[5] != 0) {
        m_dCylTheta5 = m_dCylTheta[5];
        m_dAx2 = -m_dCylTheta[5];   //* 20230610 Add Lens Data : Ax
    }

    //* tested lens       C(5)_AN(6)_D(5)_C(6)   : Center thickness D(5)
    //*                      AN(7)_D(6)_       : Distance between lenses
    //*                 C(7)_AN(8)_D(7)_C(8)   : Center thickness D(7)
    //*                      AN(9)_D(8)_       : Distance between lenses
    //*                 C(9)_AN(10)_D(9)_C(10) : 中心厚 D(9) に応じて，
    //*
    //* Adjust the distance D(10) to the condenser lens 1 C(11)_C(12) according to the center thickness D(9),
    //* maintaining a constant distance from the C(5): back surface of the tested lens
    //* to the C(11): first surface of the condenser lens.
    //* To achieve this, store the initial value of D(10) in m_dD6.

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
    //* Picture Box Magnification Setting
    m_dWin1Mag = 0.9;
    //* Picture Box size
    g_dWindowPosLeft = -30.0;
    g_dWindowPosRight = 105.0;
    g_dWindowPosTop = 78.0;
    g_dWindowPosBottom = -22.0;

    //* Picture Box Normalization
    g_dWindowPosLeft = g_dWindowPosLeft * m_dWin1Mag;
    g_dWindowPosRight = g_dWindowPosRight * m_dWin1Mag;
    g_dWindowPosTop = g_dWindowPosTop * m_dWin1Mag;
    g_dWindowPosBottom = g_dWindowPosBottom * m_dWin1Mag;

    //* Picture Box 2 size
    g_dWindowPosLeft2 = -m_dWin2DefaultSize;
    g_dWindowPosRight2 = m_dWin2DefaultSize;
    g_dWindowPosTop2 = m_dWin2DefaultSize;
    g_dWindowPosBottom2 = -m_dWin2DefaultSize;

    //* Picture Box 2 Normalization
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

    //* Target positioning with a given lens
    R_KINJIKU();

    if (m_bAFFlg) { //* AF ON(Normal Mode)
        m_dObjZ = m_dObjPoint1;
        m_dDefaultObjZ = m_dObjPoint1;
        m_dNowDefaultObjZ = m_dObjPoint1; //* 20230521 Processing to return to the target position of the data read by DataIn() even when the "Initialize" button is pressed after changing the Lens Data and then the "Initialize with Current Data" button is pressed again
    } else {        //* AF OFF
        Ransu rnd;
        int j;
        //* Target position
        m_dObjZ = m_dObjPoint1;
        Diopter(m_dObjPoint1, &m_dDpt);
        j = rnd.RansuGet1();
        m_dDpt = m_dDpt + (double)j / 100.0;    //* Produces an error of +/-1D (for random numbers, see the "Ransu" class)
        Target(m_dDpt, &m_dObjZ);
        m_dDefaultObjZ = m_dObjZ;
        m_dNowDefaultObjZ = m_dObjZ; //* 20230521 Processing to return to the target position of the data read by DataIn() even when the "Initialize" button is pressed after changing the Lens Data and then the "Initialize with Current Data" button is pressed again

        //* Lens position
        j = rnd.RansuGet1();
        m_dTLY[5] = m_dTLY[5] + (int)(j / 20); //* given : an error of +/-5mm
        m_iLensPosYOld = (int)m_dTLY[5]* 10;
        if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
        m_dTLY[6] = m_dTLY[5];
        j = rnd.RansuGet1();
        m_dTLX[5] = m_dTLX[5] + (int)(j / 20); //* given : an error of +/-5mm
        m_iLensPosXOld = (int)m_dTLX[5]* 10;
        if(m_bKeisyaRendou)    SRTLM_Keisya_Rendou();
        m_dTLX[6] = m_dTLX[5];

        //* Lens rotation
        j = rnd.RansuGet2();
        m_dCylTheta[5] = m_dCylTheta[5] + j;    //* given : an error of +/-15°
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

    //* Distance data -> Converted to diopters
    Diopter(m_dObjZ, &m_dDpt);

    m_bSyokika = false;

    m_bKeisyaRendou = true;

    return TRUE;

}

void CSRTLMDlg::baseLensDataTransfer(int iKY2)
{
    //* RayTrace Lens Params

    params.ldp_iKY2 = iKY2;                //* Number of surfaces to trace

    for (int i = 0; i <= iKY2; i++) {
        params.ldp_dC[i] = m_dC[i];        //* Radius of curvature of each boundary surface
    }
    for (int i = 0; i < iKY2; i++) {
        params.ldp_dD[i] = m_dD[i];        //* Distance between boundary surface
    }
    for (int i = 0; i < iKY2; i++) {
        params.ldp_dDKsub[i] = m_dDKsub[i];            //* Auxiliary arrays used in drawing lenses
    }
    params.ldp_dDK = m_dDK;                            //* Auxiliary variables used in drawing lenses
    params.ldp_dD6 = m_dD6;                            //* m_dD6: Distance from the rear surface of the tested lens
                                                       //*        to the first surface of the condenser lens: m_dC(7)
    for (int i = 0; i <= iKY2 + 1; i++) {
        params.ldp_dN[i] = m_dN[i];            //* Refractive Index
    }
    for (int i = 0; i <= iKY2; i++) {
        params.ldp_dLensDiameter[i] = m_dLensDiameter[i]; //* Effective diameter of each surface: Calculate the aperture of each lens
                                                          //*                                     from the aperture setting value
    }
    params.ldp_dD_DefaultLengthAll = m_dD_DefaultLengthAll; //* Distance from the edge of the collimator to the edge of the objective lens
                                                            //* (excluding the thickness of the tested lens)
    for (int i = 0; i <= iKY2; i++) {
        params.ldp_nASNO[i] = m_nASNO[i];   //* Aspheric flag
    }
    for (int i = 0; i <= iKY2; i++) {
        params.ldp_dRISIN[i] = m_dRISIN[i]; //* Conic Coefficient
        params.ldp_nASGV[i] = m_nASGV[i];   //* Order of aspherical surfaces
        params.ldp_nAS[i] = m_nAS[i];       //* Flag : Even order (rotational symmetry)
                                            //*        Odd-order (rotationally symmetric or asymmetric)
        for (int j = 0; j <= iKY2; j++) {
            params.ldp_dAC[i][j] = m_dAC[i][j];    //* Aspheric coefficient
        }
        params.ldp_nTORIC[i] = m_nTORIC[i];        //* Toric surface flag
        params.ldp_dCylCV2[i] = m_dCylCV2[i];
        params.ldp_dCylTheta[i] = m_dCylTheta[i];
        params.ldp_nSHAX[i] = m_nSHAX[i];          //* Optical axis shift
        params.ldp_nTLAX[i] = m_nTLAX[i];          //* Eccentricity
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

    params.ldp_iKY2 = iKY2;                 //* Number of surfaces to trace

    for (int i = 0; i <= iKY2; i++) {
        m_dC[i] = 0.0;                      //* Radius of curvature of each boundary surface
    }
    for (int i = 0; i < iKY2; i++) {
        m_dD[i] = 0.0;                      //* Distance between boundary surface
    }
    for (int i = 0; i < iKY2; i++) {
        params.ldp_dDKsub[i] = 0.0;         //* Auxiliary arrays used in drawing lenses
    }
    params.ldp_dDK = 0.0;                   //* Auxiliary variables used in drawing lenses
    params.ldp_dD6 = 0.0;                   //* m_dD6: Distance from the rear surface of the tested lens
                                            //*        to the first surface of the condenser lens: m_dC(7)
    for (int i = 0; i <= iKY2 + 1; i++) {
        m_dN[i] = 1.0;                      //* Refractive Index
    }
    for (int i = 0; i <= iKY2; i++) {
        m_dLensDiameter[i] = 9999.0;        //* Effective diameter of each surface: Calculate the aperture of each lens
                                            //*                                     from the aperture setting value
    }
    m_dD_DefaultLengthAll = 0.0;            //* Distance from the edge of the collimator to the edge of the objective lens
                                            //* (excluding the thickness of the tested lens)
    for (int i = 0; i <= iKY2; i++) {
        m_nASNO[i] = 0;                     //* Aspheric flag
    }
    for (int i = 0; i <= iKY2; i++) {
        m_dRISIN[i] = 0.0;                  //* Conic Coefficient
        m_nASGV[i] = 0;                     //* Order of aspherical surfaces
        m_nAS[i] = 0;                       //* Flag : Even order (rotational symmetry)
                                            //*        Odd-order (rotationally symmetric or asymmetric)
        for (int j = 0; j <= iKY2; j++) {
            params.ldp_dAC[i][j] = 0.0;     //* Aspheric coefficient
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

    params.ldp_dSY = 0.0;
    params.ldp_dDepth = 0.0;
    params.ldp_dRZtargetZero = 0.0;
    params.ldp_dRZhikenLens = 0.0;
    params.ldp_dRZpintGlass = 0.0;

    m_rTrace->setLensData(&params);
}

//* Notify class "CRayTrace" of dialog changes
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
    case ERR_RAY_TRACE:                     //* 1: Untraceable, 0: None specified,          0: SkewRayTrace
        message = "SkewRayTrace";
        break;
    case ERR_RAY_TRACE_SPH:                 //* 1: Untraceable, 1: Spherical and coaxial,   0: SRTSph
        message = "SkewRayTrace SRTSph";
        break;
    case ERR_RAY_TRACE_TORIC:               //* 1: Untraceable, 2: Aspheric or non-coaxial, 1: SRTToric
        message = "SkewRayTrace SRTToric";
        break;
    case ERR_RAY_TRACE_ASPH:                //* //* 1: Untraceable, 2: Aspheric or non-coaxial, 2: SRTAsph
        message = "SkewRayTrace SRTAsph";
        break;
    case ERR_RAY_TRACE_ASPH2:               //* 1: 1: Untraceable, 2: Aspheric or non-coaxial, 4: SRTAsph2
        message = "SkewRayTrace SRTAsph2";
        break;
    case ERR_RAY_TRACE_HENSPH:              //* 1: Untraceable, 2: Aspheric or non-coaxial, 3: SRTHenSph
        message = "SkewRayTrace SRTHenSph";
        break;
    default:
        break;
    }

    str.Format(_T("ERR !!! No Intersection at %s"), message); AfxMessageBox(str); //I want to end the program with OK
}

//* 20230709 Add : Obtaine the date to include in the copyright <- Since it's not working out, I'll put it in the title
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
