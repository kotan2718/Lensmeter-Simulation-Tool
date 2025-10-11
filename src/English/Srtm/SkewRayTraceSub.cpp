
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


#include "stdafx.h"
#include "RayTrace.h"



BOOL CRayTrace::AxShift(int iNyu)
{
    //*
    //* sub function AXShift
    //* AXShift as Axial SHift
    //*
    //* mother program   : SkewRayTrace
    //* daughter program :
    //*
    //*
    //*

    m_dAMZ = m_dAMZ - m_dAxSHV[iNyu][1];
    m_dAMY = m_dAMY - m_dAxSHV[iNyu][2];

    m_dAMX = m_dAMX - m_dAxSHV[iNyu][3];

    double dDELM;
    dDELM = -(m_dAMZ * m_dDZI + m_dAMY * m_dDYI + m_dAMX * m_dDXI);
    m_dQI = m_dQI + dDELM;
    m_dAMZ = m_dAMZ + dDELM * m_dDZI;
    m_dAMY = m_dAMY + dDELM * m_dDYI;
    m_dAMX = m_dAMX + dDELM * m_dDXI;

    return TRUE;
}


BOOL CRayTrace::CONVERT(double dBZI, double dBYI, double dBXI, int iInverse)
{
    //
    //* sub function CONVERT
    //* CONVERT as convert π to π-wave coordinate or π-wave to π coordinate
    //
    //* mother program   : HS,HE
    //* daughter program :
    //
    //
    //
    if(iInverse == 0) {
        //
        //* normal convert
        //*
        m_dVZ = m_dTrans[1][1] * dBZI + m_dTrans[1][2] * dBYI + m_dTrans[1][3] * dBXI;
        m_dVY = m_dTrans[2][1] * dBZI + m_dTrans[2][2] * dBYI + m_dTrans[2][3] * dBXI;
        m_dVX = m_dTrans[3][1] * dBZI + m_dTrans[3][2] * dBYI + m_dTrans[3][3] * dBXI;
    }
    else {
        //
        //* inverse convert
        //*
        m_dVZ = m_dTrans[1][1] * dBZI + m_dTrans[2][1] * dBYI + m_dTrans[3][1] * dBXI;
        m_dVY = m_dTrans[1][2] * dBZI + m_dTrans[2][2] * dBYI + m_dTrans[3][2] * dBXI;
        m_dVX = m_dTrans[1][3] * dBZI + m_dTrans[2][3] * dBYI + m_dTrans[3][3] * dBXI;
    }

    return TRUE;
}



BOOL CRayTrace::CTM(double dVEZ, double dVEY, double dVEX)
{
    //*
    //* sub function CTM
    //* CTM as generation Coordinate Transformation Matrix
    //*
    //* When the optical axis vector ez of the new coordinate system π-wave due to decentering is given as
    //* (vz,vy,vx) in the old coordinate system π, calculate ey and ex and create a coordinate transformation matrix.
    //*
    //* mother program   :HS
    //* daughter program :
    //*

    //* normalize Z-direction vector
    //*
    //* Form1.Print dVEZ
    double dDDI;
    double dVDSQ, dSQZYI, dSQE1Y;
    dDDI = 1.0 / sqrt(dVEZ * dVEZ + dVEY * dVEY + dVEX * dVEX);
    m_dEZ = dVEZ * dDDI;
    m_dEY = dVEY * dDDI;
    m_dEX = dVEX * dDDI;
    //*
    //* Z-direction
    //*
    //* programmed according to eq.(3.3.9)
    m_dTrans[1][1] = m_dEZ;
    m_dTrans[1][2] = m_dEY;
    m_dTrans[1][3] = m_dEX;
    //*
    if(fabs(m_dEX) <= 0.8) {
        dVDSQ = 1.0 - m_dEX *m_dEX;
        dSQZYI = 1.0 / sqrt(dVDSQ);
        //*
        //* Y-direction
        //* programmed according to (3.3.4)
        m_dTrans[2][1] = -m_dEY * dSQZYI;
        m_dTrans[2][2] =  m_dEZ * dSQZYI;
        m_dTrans[2][3] =  0.0;
        //*
        //* X-direction
        //* programmed according to (3.3.11)
        m_dTrans[3][1] = -m_dTrans[1][3] * m_dTrans[2][2];
        m_dTrans[3][2] =  m_dTrans[1][3] * m_dTrans[2][1];
        m_dTrans[3][3] =  m_dTrans[1][1] * m_dTrans[2][2] - m_dTrans[1][2] * m_dTrans[2][1];
        return TRUE;
    }

    dVDSQ = 1.0 - m_dEY * m_dEY;
    dSQE1Y = 1.0 / sqrt(dVDSQ);
    //*
    //* X-direction
    //* programmed according to (3.3.12)
    m_dTrans[3][1] = -m_dEX * dSQE1Y;
    m_dTrans[3][2] =  0.0;
    m_dTrans[3][3] =  m_dEZ * dSQE1Y;
    //*
    //* Y-direction
    //* programmed according to (3.3.13)
    m_dTrans[2][1] = -m_dTrans[1][2] * m_dTrans[3][3];
    m_dTrans[2][2] =  m_dTrans[1][1] * m_dTrans[3][3] - m_dTrans[1][3] * m_dTrans[3][1];
    m_dTrans[2][3] =  m_dTrans[1][2] * m_dTrans[3][1];

    return TRUE;
}

BOOL CRayTrace::DT()
{
    int i;
    for(i = 1; i < m_iKY2 + 1; i++) {
        if(m_nTORIC[i] != 0) {
            m_dCylCos[i] = cos(KK_PI / 180.0 * m_dCylTheta[i]);
            m_dCylSin[i] = sin(KK_PI / 180.0 * m_dCylTheta[i]);
        }
    }

    return TRUE;
}


BOOL CRayTrace::R3D()
{
    double dRX1, dRY1, dRZ1, dRX2, dRY2, dRZ2;

    dRX1 = m_dRX;
    dRY1 = m_dRY * cos(m_dRXA) - m_dRZ * sin(m_dRXA);
    dRZ1 = m_dRY * sin(m_dRXA) + m_dRZ * cos(m_dRXA);
    dRX2 = dRX1 * cos(m_dRYA) - dRZ1 * sin(m_dRYA);
    dRY2 = dRY1;
    dRZ2 = dRX1 * sin(m_dRYA) + dRZ1 * cos(m_dRYA);
    m_dRX3 = dRX2 * cos(m_dRZA) - dRY2 * sin(m_dRZA);
    m_dRY3 = dRX2 * sin(m_dRZA) + dRY2 * cos(m_dRZA);
    m_dRZ3 = dRZ2;

    return TRUE;
}



BOOL CRayTrace::HE(int iNyu)
{
    //*
    //* sub function HE
    //* HE as Hensin End
    //*
    //* mother program   : SkewRayTrace
    //* daughter program : CONVERT
    //*
    //* convert intersection point vector  pi-wave to pi coordinate
    CONVERT(m_dAZ, m_dAY, m_dAX, 1);

    m_dAZ = m_dVZ, m_dAY = m_dVY,  m_dAX = m_dVX;

    m_dAZ = m_dAZ + m_dTLZ[iNyu];
    m_dAY = m_dAY + m_dTLY[iNyu];
    m_dAX = m_dAX + m_dTLX[iNyu];

    //* convert vector Q pi-wave to pi coordinate
    CONVERT(m_dDZI, m_dDYI, m_dDXI, 1);

    m_dDZI = m_dVZ, m_dDYI = m_dVY,  m_dDXI = m_dVX;

    return TRUE;
}


BOOL CRayTrace::HS(int iNyu)
{
    //*
    //* subroutin HS
    //* HS as Hensin Start
    //*
    //* mother program   : SkewRayTrace
    //* daughter program : CTM,CONVERT
    //*

    double dDELM;
    m_dEZ = cos(KK_PI / 180.0 * m_dHenTheta[iNyu]) * cos(KK_PI / 180.0 * m_dHenFai[iNyu]);
    m_dEY = sin(KK_PI / 180.0 * m_dHenTheta[iNyu]);
    m_dEX = cos(KK_PI / 180.0 * m_dHenTheta[iNyu]) * sin(KK_PI / 180.0 * m_dHenFai[iNyu]);
    //*

    CTM(m_dEZ, m_dEY, m_dEX);

    if(m_iIDFlg == 1) {
        //* The routine referenced by the GLSSUB subfunction
        //* Called when coordinate system transformation occurs during drowing lens
        CONVERT(m_dRZ, m_dRY, m_dRX, 1);

        m_dRZ = m_dVZ, m_dRY = m_dVY,  m_dRX = m_dVX;

        m_dRZ = m_dRZ + m_dTLZ[iNyu];
        m_dRY = m_dRY + m_dTLY[iNyu];
        m_dRX = m_dRX + m_dTLX[iNyu];
        return TRUE;
    }

    //* convert vector M
    CONVERT(m_dAMZ, m_dAMY, m_dAMX, 0);

    m_dAMZ = m_dVZ, m_dAMY = m_dVY,  m_dAMX = m_dVX;

    m_dAMZ = m_dAMZ - m_dTLZ[iNyu];
    m_dAMY = m_dAMY - m_dTLY[iNyu];
    m_dAMX = m_dAMX - m_dTLX[iNyu];
    //*
    //*
    //* convert vector Q
    CONVERT(m_dDZI, m_dDYI, m_dDXI, 0);

    m_dDZI = m_dVZ, m_dDYI = m_dVY,  m_dDXI = m_dVX;

    //*
    dDELM = -(m_dAMZ * m_dDZI + m_dAMY * m_dDYI + m_dAMX * m_dDXI);
    m_dQI = m_dQI + dDELM;
    m_dAMZ = m_dAMZ + dDELM * m_dDZI;
    m_dAMY = m_dAMY + dDELM * m_dDYI;
    m_dAMX = m_dAMX + dDELM * m_dDXI;
    //*

    return TRUE;
}


BOOL CRayTrace::RAYCHECK()
{
    //*
    //* Check for incident ray：Cut off ray passing outside the pupil
    //*                         and marks it with #1 for distinction.
    //*
    //*
    double dCheck;
    dCheck = m_dSY * m_dSY - (m_dAX * m_dAX + m_dAY * m_dAY);
    if(dCheck < 0.0) {
        return false;
    }

    return true;
}


BOOL CRayTrace::RP(int iNyu, long lCol)
{
    //*
    //* sub function RP
    //* RP as Ray Plot
    //*
    //* mother program   : SkewRayTrace
    //* daughter program :
    //*

    double dRGXS, dRGYS;
    double dRGXE, dRGYE;

    m_dD3 = m_dD3 + m_dD[iNyu - 1];
    if(iNyu == 1) {
        m_dRX = 0.0, m_dRY = 0.0, m_dRZ = -m_dObjZ;
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

        dRGXS = m_dRX3, dRGYS = m_dRY3;

        m_dRX = m_dAX, m_dRY = m_dAY, m_dRZ = -(m_dAZ + m_dD3);
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

        dRGXE = m_dRX3, dRGYE = m_dRY3;
    }
    else {

        //* Height of incident ray at the reference value
        m_dRX = m_dAX, m_dRY = m_dAY, m_dRZ = -(m_dAZ + m_dD3);
        dRGXS = m_dRGX0, dRGYS = m_dRGY0;

        R3D();
        dRGXE = m_dRX3, dRGYE = m_dRY3;
    }

    m_dFunc->P_Line(dRGXS, dRGYS, dRGXE, dRGYE, lCol);

    m_dRGX0 = dRGXE, m_dRGY0 = dRGYE;

    return TRUE;
}

