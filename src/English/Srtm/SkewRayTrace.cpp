
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


#include "stdafx.h"
#include "RayTrace.h"


int CRayTrace::SkewRayTrace(int IKK)
{
    //*
    //* ****************************************************************************
    //* Ray Tracing
    //*
    double dGI, dOM1, dW, dVF, dD12;
    double dCOSI, dCOSId;
    double dSINI2, dSINI2d;
    double dDIM1;
    long lCol;
    m_dPPI = 0.0;
    m_dAL  = 0.0, m_dAM  = 0.0, m_dBN  = 0.0;
    m_dAMZ = 0.0, m_dAMY = 0.0, m_dAMX = 0.0;
    dGI = 0.0, m_dPSL = 0.0;
    m_dD3 = 0.0;

    for (int iNyu = 1; iNyu <= m_iKY2; iNyu++) {
        //*
        //* ray check
        //*
        if (iNyu == 1) {
            if (!RAYCHECK()) {
                return WNG_RAY_HEIGHT_OVER;        //* 200-> The tracing ray has moved outside the effective aperture
            }
        }
        //*
        //* ---------------------------------------------------------------------------
        //* When the tracking surface is spherical and coaxial   : m_iAsphericFlg <- 0
        //*                              aspheric or non-coaxial : m_iAsphericFlg <- 1
        //*                                Aspheric: rotational symmetry : m_iASP <- 2
        //*                                          toric               : m_iASP <- 1
        //*
        m_iAsphericFlg = 0;
        if(m_nASNO[iNyu] == 1 || m_nTORIC[iNyu] == 1 || m_nSHAX[iNyu] == 1 || m_nTLAX[iNyu] != 0) {
            m_iASP = 2;
            m_iAsphericFlg = 1;
        }

        if(m_nTORIC[iNyu] == 1) {
            m_iASP = 1;
        }

        //* -----------------------------------------------------------------------------------
        //* Setting the starting position for ray tracing
        //* Generally, the entrance pupil plane is the starting position,
        //* but in this program, the starting position is set to a plane
        //* perpendicular to the optical axis passing through the vertex of the first surface,
        //* or to an arbitrary position.
        //*
        if(iNyu == 1) {
            dDIM1 = -m_dQNTP;
        }
        else {
            dDIM1 = m_dD[iNyu - 1];
        }
        //*
        m_dZMD = m_dAZ - dDIM1;
        m_dPPI = -m_dZMD * m_dDZI - m_dAY * m_dDYI - m_dAX * m_dDXI;

        //* --------------------------------------------------------------------
        //* The case is determined based on whether the tracking surface is
        //* coaxial and spherical, non-coaxial or aspheric, or toric.
        //*

        //* --------------------------------------------------------------------
        //* Ray tracing on coaxial and spherical
        if(m_iAsphericFlg == 0) {
            if (!SRTSph(iNyu)) {
                return ERR_RAY_TRACE_SPH;        //* error code: 110 <- 1: Untraceable, 1: coaxial and spherical, 0: SRTSph
            }
        }
        //* --------------------------------------------------------------------

        //* --------------------------------------------------------------------
        //* non-coaxial or aspheric
        if(m_iAsphericFlg == 1) {
            //*
            //*
            m_dAMZ = m_dZMD + m_dPPI * m_dDZI;
            m_dAMY = m_dAY + m_dPPI * m_dDYI;
            m_dAMX = m_dAX + m_dPPI * m_dDXI;
            //*
            m_dQI = m_dPPI;
            //*
            //* Processing when the optical axis is changed midway
            if(m_nSHAX[iNyu] == 1)    AxShift(iNyu);
            //*
            //* Processing when eccentricity occurs
            if(m_nTLAX[iNyu] != 0)    HS(iNyu);

            //*
            //* Ray tracing the toric surface
            //*
            if (m_iASP == 1) {
                if (!SRTToric(iNyu)) {
                    return ERR_RAY_TRACE_TORIC; //* error code: 121 <- 1: Untraceable, 2: non-coaxial or aspheric, 1: SRTToric
                }
            }
            //*
            //* Ray tracing Rotationally Symmetric Aspheric Surfaces
            //*
            if (m_iASP == 2) {
                if (!SRTAsph(iNyu)) {
                    return ERR_RAY_TRACE_ASPH;  //* error code: 122 <- 1: Untraceable, 2: non-coaxial or aspheric, 2: SRTAsph
                }
            }

            dOM1 = 1.0 / sqrt(m_dAL * m_dAL + m_dAM * m_dAM + m_dBN * m_dBN);
            m_dAL = m_dAL * dOM1;
            m_dAM = m_dAM * dOM1;
            m_dBN = m_dBN * dOM1;
        }
        //* --------------------------------------------------------------------

        //*
        //* Refraction processing
        //*
        dW = m_dN[iNyu] / m_dN[iNyu + 1];
        dVF = fabs(dW);
        dCOSI = m_dDZI * m_dAL + m_dDYI * m_dAM + m_dDXI * m_dBN;
        dSINI2 = 1.0 - dCOSI * dCOSI;
        dSINI2d = dW * dW * dSINI2;
        dD12 = 1.0 - dSINI2d;

        if (dD12 < 0.0) {
            return ERR_RAY_TRACE;               //* error code: 100 <- 1: Untraceable, 0: None specified, 0: SkewRayTrace
        }

        dCOSId = sqrt(dD12);

        if(dCOSI < 0.0)    dCOSId = -dCOSId;
        if(dW < 0.0)    dCOSId = -dCOSId;

        dGI = dCOSId - dCOSI * dVF;
        m_dDZI = dVF * m_dDZI + dGI * m_dAL;
        m_dDYI = dVF * m_dDYI + dGI * m_dAM;
        m_dDXI = dVF * m_dDXI + dGI * m_dBN;
        //* --------------------------------------------------------------------

        if(m_nTLAX[iNyu] != 0)    HE(iNyu);

        if(IKK == 0) {
            if(iNyu == 5) {
                lCol = RGB(0, 0, 255); //* QBColor(0)
            }
            else {
                lCol = RGB(255, 0, 0); //* QBColor(12)
            }

            RP(iNyu, lCol);
        }

        if(IKK == 9) {
            if(iNyu == 5) {
                lCol = RGB(255, 0, 0); //* QBColor(0)
            }
            else {
                lCol = RGB(0, 0, 255); //* QBColor(12)
            }

            RP(iNyu, lCol);
        }
    }

    return 0;            //*  0 -> Normal termination
}



BOOL CRayTrace::SRTSph(int iNyu)
{
    //*
    //* sub function SRTSph
    //* SRTSph as Skew Ray Trace of Spherical surface
    //*
    //* mother program   : SkewRayTrace
    //* daughter program :
    //*
    double dCAMV, dA12, dDELQI;

    m_dAMZ = m_dZMD + m_dPPI * m_dDZI;
    dCAMV = m_dC[iNyu] * (m_dZMD * m_dZMD + m_dAY * m_dAY + m_dAX * m_dAX - m_dPPI * m_dPPI) - m_dAMZ * 2.0;
    //*
    if(fabs(dCAMV) < 1E-30) {
        dDELQI = 0.0;
    }
    else
    {
        //*
        dA12 = 1.0 - m_dC[iNyu] * dCAMV / (m_dDZI * m_dDZI);
        if(dA12 < 0.0) {
            return false;
        }
        //*
        dDELQI = dCAMV / (m_dDZI * (1.0 + sqrt(dA12)));
    }

    m_dQI = m_dPPI + dDELQI;
    m_dPSL = m_dPSL + m_dQI * m_dN[iNyu];
    //*
    m_dAZ = m_dZMD + m_dQI * m_dDZI;
    m_dAY = m_dAY + m_dQI * m_dDYI;
    m_dAX = m_dAX + m_dQI * m_dDXI;

    m_dAL = 1.0 - m_dAZ * m_dC[iNyu];
    m_dAM = -m_dAY * m_dC[iNyu];
    m_dBN = -m_dAX * m_dC[iNyu];

    return true;
}



BOOL CRayTrace::SRTAsph(int iNyu)
{
    //*
    //* sub function SRTAsph
    //* SRTAsph as Skew Ray Trace of Aspherical surface
    //*
    //* mother program   : SkewRayTrace
    //* daughter program :

    double dZND;
    double dDELQI, dC2AV, dY2X2, dBVALS, dVConic;
    double dVH1, dVH2, dZSum, dSum1;
    double dHVAL;
    double dBVAL, dVBRI;
    int nASGVI, nj;

    dDELQI = -m_dAMZ / m_dDZI;
    m_dQI = m_dQI + dDELQI;
    m_dAZI = 0.0;
    m_dAYI = m_dAMY + dDELQI * m_dDYI;
    m_dAXI = m_dAMX + dDELQI * m_dDXI;
    //*
    nASGVI = m_nASGV[iNyu];
    nj = m_nASNO[iNyu];
    //*
    if(m_dRISIN[iNyu] == 0.0)    m_dRISIN[iNyu] = 1.0;

    dC2AV = SQUARE(m_dC[iNyu]) * m_dRISIN[iNyu];
    //*
    int iEABS;
    iEABS = 1;
    double dEVOLD;
    dEVOLD = 10000000000.0;
    //*
    int iJTRY, nL;
    for(iJTRY = 1; iJTRY <= 200; iJTRY++) {
        dY2X2 = m_dAYI * m_dAYI + m_dAXI * m_dAXI;
        dBVALS = 1.0 - dY2X2 * dC2AV;

        if(dBVALS <= 0.0) {
            return false;
        }

        dBVAL = sqrt(dBVALS);
        dVBRI = m_dC[iNyu] / dBVAL;
        dVConic = dY2X2 * m_dC[iNyu] / (1.0 + dBVAL);
        //*
        if(m_nAS[iNyu] == 1) {
            dVH1 = 1.0;
            dZSum = 0.0;
            //*
            dVH2 = 1.0;
            dSum1 = 0.0;
            //*
            for(nL = 1; nL <= nASGVI; nL++) {
                dVH1 = dVH1 * dY2X2;
                dZSum = dZSum + m_dAC[nj][nL] * dVH1;
                dSum1 = dSum1 + double(nL) * m_dAC[nj][nL] * dVH2;
                dVH2 = dVH2 * dY2X2;
            }
            //*
            dZND = dVConic + dZSum;
            m_dAL = 1.0;
            m_dAM = -m_dAYI * dVBRI - 2.0 * m_dAYI * dSum1;
            m_dBN = -m_dAXI * dVBRI - 2.0 * m_dAXI * dSum1;
        }
        else {
            //*
            dHVAL = sqrt(dY2X2);
            dVH1 = dHVAL;
            dZSum = 0.0;
            //*
            dVH2 = 1.0;
            dSum1 = 0.0;
            //*
            for(nL = 1; nL <= nASGVI;nL++) {
                dVH1 = dVH1 * dHVAL;
                dZSum = dZSum + m_dAC[nj][nL] * dVH1;
                dSum1 = dSum1 + (double(nL) + 1.0) * m_dAC[nj][nL] * dVH2;
                dVH2 = dVH2 + dHVAL;
            }
            //*
            dZND = dVConic + dZSum;
            m_dAL = 1.0;
            m_dAM = -m_dAYI * dVBRI - m_dAYI * dSum1;
            m_dBN = -m_dAXI * dVBRI - m_dAXI * dSum1;
        }
        //*
        if (iEABS == 0) {
            double dPSLI;
            dPSLI = m_dQI * fabs(m_dN[iNyu]);
            m_dPSL = m_dPSL + dPSLI;
            //
            m_dAZ = m_dAZI;
            m_dAY = m_dAYI;
            m_dAX = m_dAXI;

            return TRUE;
        }
        //*

        //* SUCAPR
        double dE;
        dE = (dZND - m_dAZI) * m_dDZI;
        //*
        if(fabs(dE) < 0.00000000000001)    iEABS = 0;
        //*
        m_dAZI = m_dAZI + dE * m_dDZI;
        m_dAYI = m_dAYI + dE * m_dDYI;
        m_dAXI = m_dAXI + dE * m_dDXI;
        //*
        m_dQI = m_dQI + dE;
        //*
    }

    return true;
}


BOOL CRayTrace::SRTToric(int iNyu)
{
    //*
    //* sub function SRTToric
    //* SRTToric as Skew Ray Trace of Toric surface
    //*
    //* mother program   : SkewRayTrace
    //* daughter program :
    //*

    double dZND;
    double dD12;
    double dCOSST, dSINST;

    m_dAZI = m_dAMZ;
    m_dAYI = m_dAMY;
    m_dAXI = m_dAMX;

    dCOSST = m_dCylCos[iNyu];
    dSINST = -m_dCylSin[iNyu];

    double dVALCY, dVALCX, dVALCYX;
    dVALCY = m_dC[iNyu];
    dVALCX = m_dCylCV2[iNyu];
    dVALCYX = dVALCX * dVALCY;

    int iEABS;
    iEABS = 1;
    double dEVOLD;
    dEVOLD = 10000000000.0;

    int iJTRY;
    for(iJTRY = 1; iJTRY <= 200; iJTRY++) {
        double dAYIB, dAXIB;
        dAYIB = m_dAYI * dCOSST + m_dAXI * dSINST;
        dAXIB = -m_dAYI * dSINST + m_dAXI * dCOSST;
        //*
        dD12 = 1.0 - SQUARE(dAYIB * dVALCY);

        if(dD12 < 0.0) {
            return false;
        }

        double dDSQ12, dALPHAI, dQ12;
        dDSQ12 = sqrt(dD12);
        dALPHAI = 1.0 / (1.0 + dDSQ12);
        dQ12 = SQUARE(1.0 - dAYIB * dAYIB * dVALCYX * dALPHAI)  - SQUARE(dAXIB * dVALCX);

        if(dQ12 < 0.0) {
            return false;
        }

        double dBUNSI;
        dBUNSI = 2.0 * dAYIB * dAYIB * dVALCY * dALPHAI
                - dAYIB  * dAYIB * dAYIB * dAYIB * dVALCYX * dVALCY * dALPHAI * dALPHAI
                + dAXIB * dAXIB * dVALCX;
        dZND = dBUNSI / (1.0 + sqrt(dQ12));

        m_dAL = 1.0 - dVALCX * dZND;

        double dAMB, dBNB;
        dAMB = ((dVALCX - dVALCY) / dDSQ12 - dVALCX) * dAYIB;
        dBNB = -dAXIB * dVALCX;

        m_dAM = dAMB * dCOSST - dBNB * dSINST;
        m_dBN = dAMB * dSINST + dBNB * dCOSST;

        if(iEABS == 0) {
            double dPSLI;
            dPSLI = m_dQI * fabs(m_dN[iNyu]);
            m_dPSL = m_dPSL + dPSLI;

            m_dAZ = m_dAZI;
            m_dAY = m_dAYI;
            m_dAX = m_dAXI;

            return true;
        }

        //* SUCAPR
        double dE;
        dE = (dZND - m_dAZI) * m_dDZI;

        if(fabs(dE) < 0.00000000000001)    iEABS = 0;

        m_dAZI = m_dAZI + dE * m_dDZI;
        m_dAYI = m_dAYI + dE * m_dDYI;
        m_dAXI = m_dAXI + dE * m_dDXI;

        m_dQI = m_dQI + dE;

    }

    return true;
}


