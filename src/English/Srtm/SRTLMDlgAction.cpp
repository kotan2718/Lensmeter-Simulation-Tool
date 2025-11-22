
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//* DlgAction
//* Calculate various quantities when the tested lens is moved (shift, tilt, rotation, etc.)


BOOL CSRTLMDlg::Ax_Henkan(int iNum, double dAx)
{
    switch(iNum)
    {
    //* Lens rotation
    case 1:
        if(dAx <=  0.0)    dAx = 180.0 + dAx;
        if(dAx > 180.0)    dAx = dAx - 180.0;

        m_dAx_Hyouji = dAx;
        break;
    case 2:
        if(dAx <= -180.0)    dAx = dAx + 180.0;

        m_dCylTheta[6] = dAx;
        break;

        //* focusing scale rotation
    case 3:
        if(dAx > 90.0)    dAx = dAx - 180;

        m_dPintGlassBar = dAx;
        break;
    case 4:
        if(dAx < 0.0)    dAx = dAx + 180.0;

        m_dPintGlassMemori = dAx;
        break;
    case 5:
        if(dAx > 90) {
            dAx = dAx - 180;
        }

        m_dAx = dAx;
        break;

    //* Lens Data Ax 20230610 Add
    case 6:
        if(dAx <=  0.0)    dAx = 180.0 + dAx;
        if(dAx > 180.0)    dAx = dAx - 180.0;

        m_dAx2_Hyouji = dAx;
        break;
    }

    return TRUE;
}

BOOL CSRTLMDlg::Diopter(double dTrgtPos, double *dDpt)
{
    //* Converting target position -> diopter value
    *dDpt = -0.0000041750955 * dTrgtPos * dTrgtPos * dTrgtPos * dTrgtPos
            - 0.0001906840676 * dTrgtPos * dTrgtPos * dTrgtPos
            - 0.0116389794109 * dTrgtPos * dTrgtPos + 0.3746509001894 * dTrgtPos + 17.810542663152;

    //* 20230412
    //* Round to the nearest “0” or “5” at the third decimal place
    //* Ex.
    //* +5.79→+5.80, -4.73→-4.75, -0.21→-0.20, ...
    int iTmp1, iTmp2, iTmp3;
    iTmp1 = (int)(abs(*dDpt) * 100);
    iTmp2 = (int)((abs(*dDpt) * 100.0 / 10));
    iTmp2 = iTmp2 * 10;
    iTmp3 = iTmp1 - iTmp2;
    switch (iTmp3) {
        case 0:
        case 1:
        case 2:
        case 3:
            iTmp3 = 0;
            break;
        case 4:
        case 5:
        case 6:
            iTmp3 = 5;
            break;
        case 7:
        case 8:
        case 9:
            iTmp3 = 10;
            break;
    }
    iTmp2 = iTmp2 + iTmp3;
    if (*dDpt > 0.0) {
        *dDpt = (double)(iTmp2 / 100.0);
    }
    else {
        *dDpt = -(double)(iTmp2 / 100.0);
    }
    return TRUE;
}


BOOL CSRTLMDlg::Target(double dDpt, double *dObjZ)
{
    //* Converting diopter value -> target position
    *dObjZ = 0.0;
    *dObjZ = 0.0000041713409 * m_dDpt * m_dDpt * m_dDpt * m_dDpt
            + 0.0003321979561 * m_dDpt * m_dDpt * m_dDpt
            + 0.0183794318877 * m_dDpt * m_dDpt + 1.0608780513192 * m_dDpt - 27.8040783108784;

    return TRUE;
}



long CSRTLMDlg::CoronaColor()
{
    double dKai1, dKai2;
    double dObjZtmp;
    double dColorPosition;

    dKai1 = 1.0 / (m_dObjPoint1 / 1000.0);
    dKai2 = 1.0 / (m_dObjPoint2 / 1000.0);
    dObjZtmp = 1.0 / (m_dObjZ / 1000.0);

    dColorPosition = 0.5 * SQUARE(dObjZtmp - dKai1)  * SQUARE(dObjZtmp - dKai2);

    //* 20251025 (Ver.2.23.0) Start ///////////////////////
    ////if(dColorPosition > 127.0)    dColorPosition = 100.0; //* 27.0;
    if (dColorPosition > 78.0)    dColorPosition = 100.0; //* 27.0;

    ////return RGB(128 + int(dColorPosition * 1.0), 255, 128 + int(dColorPosition * 1.0));
    if (dColorPosition >= 100.0 ) {
        return RGB(200, 234, 200);
    }
    else {
        return RGB(112 + int(dColorPosition * 1.0), 224 + int(dColorPosition * 0.1), 112 + int(dColorPosition * 1.0));
    }
    //* 20251025 (Ver.2.23.0)   End ///////////////////////
}



BOOL CSRTLMDlg::R_KINJIKU()
{
    int iAspKinjiku;
    double dImage1, dImage2;
    double dImageTmp, dImageTmp2;
    double dObjTmp;

    //* Backtracing the target position from the screen position (Paraxial region)
    //
    //
    //* ----------------------------------------------------------------------
    //* Ray-traced surface : sphere : m_iASP <- 0
    //*                      toric  : m_iASP <- 1
    //
    //* Collimator 1 verification (debug)
    //* m_iKY2 = 6
    //* m_dD(5) = 1.79769313486232E+307

    iAspKinjiku = 0;
    int i;
    for(i = 1; i < m_iKY2 + 1; i++) {
        if(m_nTORIC[i] == 1) {
            iAspKinjiku = 1;
        }
    }
    //* -----------------------------------------------------------------------

    dImage1 = -m_dD[m_iKY2 - 1];
    int j;
    for(j = m_iKY2 - 1; j > 0; j--) {

        if(j < m_iKY2 - 1)    dImage1 = dImage1 - m_dD[j];

        dImageTmp = (m_dN[j] - m_dN[j + 1]) * -m_dC[j];
        dImageTmp2 = m_dN[j + 1] / dImage1;
        dImage1 = m_dN[j] / (dImageTmp + dImageTmp2);
    }

    //* The direction of ray tracing is reversed, so the sign changes.
    m_dObjPoint1 = -dImage1;

    if(iAspKinjiku == 1) {
        dImage2 = -m_dD[m_iKY2 - 1];
        for(j = m_iKY2 - 1; j > 0; j--) {
            if(j < m_iKY2 - 1) dImage2 = dImage2 - m_dD[j];

            if(j == 5) {
                dImageTmp = (m_dN[j] - m_dN[j + 1]) * -m_dCylCV2[j];
            }
            else {
                dImageTmp = (m_dN[j] - m_dN[j + 1]) * -m_dC[j];
            }

            dImageTmp2 = m_dN[j + 1] / dImage2;
            dImage2 = m_dN[j] / (dImageTmp + dImageTmp2);
        }

        m_dObjPoint2 = -dImage2;
    }
    else {
        m_dObjPoint2 = m_dObjPoint1;
    }

    if(m_dObjPoint1 > m_dObjPoint2) {
        dObjTmp = 0.0;
        dObjTmp = m_dObjPoint1;
        m_dObjPoint1 = m_dObjPoint2;
        m_dObjPoint2 = dObjTmp;
    }

    //* Collimator verification (for debug)
    //* R_KINJIKU_Debug();
    //* R_KINJIKU_Debug2();

    //* Nyusyatakasa();

    return TRUE;
}


BOOL CSRTLMDlg::Nyusyatakasa()
{
    double d_VSC;
    d_VSC = m_dDVS + m_dDVC / 2.0;

    if(d_VSC > 0.0) {
        m_dVSC_h = 0.0071 * d_VSC * d_VSC * d_VSC - 0.0835 * d_VSC * d_VSC + 0.4362 * d_VSC + 2.356;
        m_dVSC_h = 2.356 / m_dVSC_h;
    }
    else {
        m_dVSC_h = 1.0;
    }

    return TRUE;
}


BOOL CSRTLMDlg::R_KINJIKU_Debug()
{
    double dImage1;
    double dImageTmp, dImageTmp2;

    //* Verification of whether the target position obtained by R_KINJIK is correct
    //
    //* Collimator 2 verification (debug)
    //* m_iKY2 = 11;
    //* m_dD[6] = -1.79769313486232E+307;

//*    dImage1 = m_dD[6]; //* Collimator 2 verification (debug)
//*    dImage1 = -27.8040783108784; //* for debug
    dImage1 = m_dObjPoint1;

    int j;
//*    for(j = 8; j < m_iKY2; j++) //* Collimator 2 verification
    for(j = 1; j < m_iKY2; j++) {
//*        if(j > 9)    dImage1 = dImage1 - m_dD[j - 1]; //* Collimator 2 verification (debug)
        if(j > 1)    dImage1 = dImage1 - m_dD[j - 1];

        dImageTmp = (m_dN[j + 1] - m_dN[j]) * m_dC[j];
        dImageTmp2 = m_dN[j] / dImage1;
        dImage1 = m_dN[j + 1] / (dImageTmp + dImageTmp2);
    }

    return TRUE;
}



BOOL CSRTLMDlg::R_KINJIKU_Debug2()
{
    double dImage1;
    double dImageTmp, dImageTmp2;

    //* Collimator 1 verification

    //*
    //* ----------------------------------------------------------------------
    //* Ray-traced surface : sphere : m_iASP <- 0
    //*                      toric  : m_iASP <- 1
    //* Collimator 1 verification
    //* m_iKY2 = 5;
    m_dD[4] = 1.79769313486232E+307;

    //* -----------------------------------------------------------------------

    dImage1 = -m_dD[m_iKY2 - 7];
    int j;
    for(j = m_iKY2 - 7; j > 0; j--) {
        if(j < 5)    dImage1 = dImage1 - m_dD[j];

        dImageTmp = (m_dN[j] - m_dN[j + 1]) * -m_dC[j];
        dImageTmp2 = m_dN[j + 1] / dImage1;
        dImage1 = m_dN[j] / (dImageTmp + dImageTmp2);
    }

    return TRUE;
}


BOOL CSRTLMDlg::Make_Lens()
{
    double d_f1d, d_f1d_crown, d_f2d, d_f2d2, d_D2d, d_D2d2;
    double dIndexReference;
    dIndexReference = 1.523;
    if(m_dD1d != 0.0) {
        //* 20251027 (Ver.2.24.0) m_bFccf1523Flg
        //* Front Curve : Whether to fix to the refractive index of crown glass
        if (m_bFccf1523Flg != true) {
            d_f1d = 1000.0 * m_dRefractiveIndex / m_dD1d;
            m_dRadius1 = d_f1d * (m_dRefractiveIndex - 1.0) / m_dRefractiveIndex;
        }
        else {
            d_f1d_crown = 1000.0 * dIndexReference / m_dD1d;
            d_f1d = m_dRadius1 / (m_dRefractiveIndex - 1.0) * m_dRefractiveIndex;
            m_dRadius1 = d_f1d_crown * (dIndexReference - 1.0) / dIndexReference;
        }
    }
    else {
        d_f1d = -1.79769313486232E+307;
        m_dRadius1 = -1.79769313486232E+307;
    }
    d_D2d = m_dDVS - (1000.0 * m_dRefractiveIndex / d_f1d) / (1.0 - 0.001 * m_dThickness / m_dRefractiveIndex * (1000.0 * m_dRefractiveIndex / d_f1d));
    d_f2d = 1000.0 / d_D2d;
    m_dRadius2min = d_f2d * (1.0 - m_dRefractiveIndex);

    if(m_dRadius2min == 0.0) {
        m_dRadius2min = -1.79769313486232E+307;
    }

    if(m_dDVC != 0.0) {
        d_D2d2 = (m_dDVS + m_dDVC) - (1000.0 * m_dRefractiveIndex / d_f1d) / (1.0 - 0.001 * m_dThickness / m_dRefractiveIndex * (1000.0 * m_dRefractiveIndex / d_f1d));
        d_f2d2 = 1000.0 / d_D2d2;
        m_dRadius2max = d_f2d2 * (1.0 - m_dRefractiveIndex);

        if(m_dRadius2max == 0.0) {
            m_dRadius2max = -1.79769313486232E+307;
        }
    }
    else {
        m_dRadius2max = m_dRadius2min;
    }

    m_dC[6] = -1.0 / m_dRadius1;
    m_dCylCV2[6] = m_dC[6];
    m_dD[5] = m_dThickness;

    //* The distance m_dD(6) to the first collecting lens C(6)__C(7) is adjusted
    //* according to the center thickness m_dD(5) of the tested lens C(5)__AN(6)_D(5)__C(6),
    //* maintaining a constant distance from the rear surface of the tested lens C(6) to the first surface of
    //* the collecting lens C(7).

    switch(m_iKY2)
    {
    case 15:
        m_dD[11] = m_dD6 - (m_dD[5] + m_dD[6] + m_dD[7] + m_dD[8] + m_dD[9]);
        break;
    case 13:
        m_dD[8] = m_dD6 - (m_dD[5] + m_dD[6] + m_dD[7]);
        break;
    case 11:
        m_dD[6] = m_dD6 - m_dD[5];
        break;
    }

    m_dN[6] = m_dRefractiveIndex;

    m_dC[5] = -1.0 / m_dRadius2max;
    if(m_dDVC != 0.0) {
        m_dCylCV2[5] = -1.0 / m_dRadius2min;
        m_dCylTheta[5] = -m_dAx;
        m_dCylTheta[6] = m_dCylTheta[5];
    }
    else {
        m_dCylCV2[5] = -1.0 / m_dRadius2max;
        m_dCylTheta[5] = 0.0;
        m_dCylTheta[6] = m_dCylTheta[5];
    }


    R_KINJIKU();

    m_dObjZ = m_dObjPoint1;

    m_dNowDefaultObjZ = m_dObjPoint1;

    Diopter(m_dObjPoint1, &m_dDpt);

    m_DpStrTargetDiopter.SetData(m_dDpt, 0.0, 0, 0);

    m_bSyokika = false;

    return TRUE;
}

BOOL CSRTLMDlg::SRTLM_Keisya_Rendou()
{
    //* I found some patterns that weren't supported for convex rear surfaces and fixed them...maybe.
    //* The code below is temporary, so the overall branching might need review.

    double dSgnX, dSgnY;
    if (m_dTLY[5] > 0.0) {
        if (m_dTLX[5] > 0.0) {
            if (m_dC[5] <= 0.0) {
                dSgnX = 1.0;
            }
            else {
                dSgnX = -1.0;       //* The back surface is convex to the left
            }
            dSgnY = 1.0;
        }
        if (m_dTLX[5] < 0.0) {
            if (m_dC[5] <= 0.0) {
                dSgnX = -1.0;
            }
            else {
                dSgnX = 1.0;        //* The back surface is convex to the left
            }
            dSgnY = 1.0;
        }
        if (m_dTLX[5] == 0) {
            dSgnX = 1.0;
            if (m_dC[5] <= 0.0) {
                dSgnY = 1.0;
            } else {
                dSgnY = -1.0;       //* The back surface is convex to the left
            }
        }
    }
    if (m_dTLY[5] < 0.0) {
        if (m_dTLX[5] > 0.0) {
            if (m_dC[5] <= 0.0) {
                dSgnX = 1.0;
            }
            else {
                dSgnX = -1.0;       //* The back surface is convex to the left
            }
            dSgnY = -1.0;
        }
        if (m_dTLX[5] < 0.0) {
            if (m_dC[5] <= 0.0) {
                dSgnX = -1.0;
            }
            else {
                dSgnX = 1.0;        //* The back surface is convex to the left
            }
            dSgnY = -1.0;
        }
        if (m_dTLX[5] == 0) {
            dSgnX = -1.0;
            if (m_dC[5] <= 0.0) {
                dSgnY = -1.0;
            }
            else {
                dSgnY = 1.0;        //* The back surface is convex to the left
            }
        }
    }
    if (m_dTLY[5] == 0.0) {
        if (m_dTLX[5] > 0.0) {
            if (m_dC[5] <= 0.0) {
                dSgnX = 1.0;
            }
            else {
                dSgnX = -1.0;       //* The back surface is convex to the left
            }
            dSgnY = 1.0;
        }
        if (m_dTLX[5] < 0.0) {
            if (m_dC[5] <= 0.0) {
                dSgnX = -1.0;
            }
            else {
                dSgnX = 1.0;        //* The back surface is convex to the left
            }
            dSgnY = -1.0;
        }
        if (m_dTLX[5] == 0) {
            dSgnX = 1.0;
            if (m_dC[5] <= 0.0) {
                dSgnY = 1.0;
            } else {
                dSgnY = -1.0;       //* The back surface is convex to the left
            }
        }
    }

    double dTLxyX, dTLxyY;
    dTLxyX = m_dTLX[5] * cos(m_dCylTheta[5] * KK_PI / 180.0) - m_dTLY[5] * sin(m_dCylTheta[5] * KK_PI / 180.0);
    dTLxyY = m_dTLX[5] * sin(m_dCylTheta[5] * KK_PI / 180.0) + m_dTLY[5] * cos(m_dCylTheta[5] * KK_PI / 180.0);

    double dC5Fai, dC5Theta;
    dC5Fai = 1.0 / m_dCylCV2[5] - (1.0 / m_dCylCV2[5] - 1.0 / m_dC[5]) * SQUARE(sin(m_dCylTheta[5] * KK_PI / 180.0));

    dC5Theta = 1.0 / m_dCylCV2[5] - (1.0 / m_dCylCV2[5] - 1.0 / m_dC[5]) * SQUARE(cos(m_dCylTheta[5] * KK_PI / 180.0));

    if (fabs(m_dTLY[5]) >= fabs(m_dTLX[5])) {
        if (fabs(dTLxyY) >= fabs(dTLxyX)) {
            m_dHenFai[5] = dSgnX * fabs(asin(-dTLxyX / dC5Fai) * 180.0 / KK_PI);
            m_dHenFai[6] = m_dHenFai[5];
            m_dHenTheta[5] = dSgnY * fabs(asin(-dTLxyY / dC5Theta) * 180.0 / KK_PI);
            m_dHenTheta[6] = m_dHenTheta[5];
        }
        else {
            m_dHenFai[5] = dSgnX * fabs(asin(-dTLxyY / dC5Fai) * 180.0 / KK_PI);
            m_dHenFai[6] = m_dHenFai[5];
            m_dHenTheta[5] = dSgnY * fabs(asin(-dTLxyX / dC5Theta) * 180.0 / KK_PI);
            m_dHenTheta[6] = m_dHenTheta[5];
        }
    }
    else {
        if (fabs(dTLxyY) >= fabs(dTLxyX)) {
            m_dHenFai[5] = dSgnX * fabs(asin(-dTLxyY / dC5Fai) * 180.0 / KK_PI);
            m_dHenFai[6] = m_dHenFai[5];
            m_dHenTheta[5] = dSgnY * fabs(asin(-dTLxyX / dC5Theta) * 180.0 / KK_PI);
            m_dHenTheta[6] = m_dHenTheta[5];
        }
        else {
            m_dHenFai[5] = dSgnX * fabs(asin(-dTLxyX / dC5Fai) * 180.0 / KK_PI);
            m_dHenFai[6] = m_dHenFai[5];
            m_dHenTheta[5] = dSgnY * fabs(asin(-dTLxyY / dC5Theta) * 180.0 / KK_PI);
            m_dHenTheta[6] = m_dHenTheta[5];
        }
    }

    return TRUE;

}


