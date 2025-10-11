
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


// SRTLMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SRTLM.h"
#include "SRTLMDlg.h"

#include "DpNumCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//* Processing when the edit box and button are pressed

//* When the numeric value is changed
void CSRTLMDlg::OnKillfocusEditTargetDpt()
{
    // TODO: Please add the code for the control notification handler at this location.

    //* Called when the data in the edit box is modified directly
    UpdateData(TRUE);    //* Displayed data -> Internal

    m_dDpt = m_DpStrTargetDiopter.GetData();

    //* Processing when out-of-range data is entered
    if (m_dDpt > m_dTargetDiopterMax)    m_dDpt = m_dTargetDiopterMax;
    if (m_dDpt < m_dTargetDiopterMin)    m_dDpt = m_dTargetDiopterMin;

    Target(m_dDpt, &m_dObjZ);

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonTargetDefault()
{
    // TODO: Please add the code for the control notification handler at this location.
    //* Diopterダイヤル
    if(m_dNowDefaultObjZ = -9999.0) {
        m_dObjZ = m_dDefaultObjZ;
    }
    else {
        m_dObjZ = m_dNowDefaultObjZ;
    }

    Diopter(m_dObjZ, &m_dDpt);

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}

//* lens position

    //* lens position edit box
void CSRTLMDlg::OnKillfocusEditLpX()
{
    // TODO: Please add the code for the control notification handler at this location.

    //* Called when the data in the edit box is modified directly
    UpdateData(TRUE);    // Displayed data -> Internal

    m_dTLX[5] = m_DpStrLensPosX.GetData();

    //* Processing when out-of-range data is entered
    if (m_dTLX[5] > m_dLensPosXmax)    m_dTLX[5] = m_dLensPosXmax;
    if (m_dTLX[5] < m_dLensPosXmin)    m_dTLX[5] = m_dLensPosXmin;

    m_dTLX[6] = m_dTLX[5];

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}

    //* lens position reset button
void CSRTLMDlg::OnButtonLpX0()
{
    // TODO: Please add the code for the control notification handler at this location.
    switch(m_bJujiRendou)
    {
    case true:
        m_dTLX[5] = 0.0, m_dTLX[6] = 0.0;
        m_dTLY[5] = 0.0, m_dTLY[6] = 0.0;
        if (m_bKeisyaRendou) {
            SRTLM_Keisya_Rendou();    //* Calling this function changes m_dHenFai[5],[6] and m_dHenTheta[5],[6]
        }
        m_iLensPosXOld = 0;
        m_iLensPosYOld = 0;
        break;
    case false:
        m_dTLX[5] = 0.0, m_dTLX[6] = 0.0;
        if (m_bKeisyaRendou) {
            SRTLM_Keisya_Rendou();    //* Calling this function changes m_dHenFai[5],[6] and m_dHenTheta[5],[6]
        }
        m_iLensPosXOld = 0;
        break;
    }

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}


void CSRTLMDlg::OnKillfocusEditLpY()
{
    // TODO: Please add the code for the control notification handler at this location.

    //* Called when the data in the edit box is modified directly
    UpdateData(TRUE);    // Displayed data -> Internal

    m_dTLY[5] = m_DpStrLensPosY.GetData();

    //* Processing when out-of-range data is entered
    if (m_dTLY[5] > m_dLensPosYmax)    m_dTLY[5] = m_dLensPosYmax;
    if (m_dTLY[5] < m_dLensPosYmin)    m_dTLY[5] = m_dLensPosYmin;

    m_dTLY[6] = m_dTLY[5];

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonLpY0()
{
    // TODO: Please add the code for the control notification handler at this location.
    switch(m_bJujiRendou)
    {
    case true:
        m_dTLX[5] = 0.0, m_dTLX[6] = 0.0;
        m_dTLY[5] = 0.0, m_dTLY[6] = 0.0;
        if (m_bKeisyaRendou) {
            SRTLM_Keisya_Rendou();    //* Calling this function changes m_dHenFai[5],[6] and m_dHenTheta[5],[6]
        }
        m_iLensPosXOld = 0;
        m_iLensPosYOld = 0;
        break;
    case false:
        m_dTLY[5] = 0.0, m_dTLY[6] = 0.0;
        if (m_bKeisyaRendou) {
            SRTLM_Keisya_Rendou();    //* Calling this function changes m_dHenFai[5],[6] and m_dHenTheta[5],[6]
        }
        m_iLensPosYOld = 0;
        break;
    }

    m_bSetSpinScrollFlg = true;
    m_bSyokika = false;
    Invalidate(FALSE);
}


void CSRTLMDlg::OnKillfocusEditPgDeg()
{
    // TODO: Please add the code for the control notification handler at this location.

    //* Called when the data in the edit box is modified directly
    UpdateData(TRUE);    // Displayed data -> Internal

    m_dPintGlassMemori = m_DpStrPintGlassDeg.GetData();

    //* Processing when out-of-range data is entered
    if(m_dPintGlassMemori > 180.0 || m_dPintGlassMemori < 0.0) {
        m_dPintGlassMemori = fmod(m_dPintGlassMemori, 180.0);
    }

    Ax_Henkan(3, m_dPintGlassMemori);

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonPgRotate0()
{
    // TODO: Please add the code for the control notification handler at this location.

    m_dPintGlassMemori = 0.0;
    m_dPintGlassBar = m_dPintGlassMemori;

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnKillfocusEditLTiltX()
{
    // TODO: Please add the code for the control notification handler at this location.

    //* Called when the data in the edit box is modified directly
    UpdateData(TRUE);    // Displayed data -> Internal

    m_dHenFai[5] = m_DpStrLensTiltX.GetData();

    //* Processing when out-of-range data is entered
    if(m_dHenFai[5] > m_dLensTiltXmax)    m_dHenFai[5] = m_dLensTiltXmax;
    if(m_dHenFai[5] < m_dLensTiltXmin)    m_dHenFai[5] = m_dLensTiltXmin;

    m_dHenFai[6] = m_dHenFai[5];

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonLTiltX0()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_dHenFai[5] = 0.0;
    m_dHenFai[6] = m_dHenFai[5];

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnKillfocusEditLTiltY()
{
    // TODO: Please add the code for the control notification handler at this location.

    //* Called when the data in the edit box is modified directly
    UpdateData(TRUE);    // Displayed data -> Internal

    m_dHenTheta[5] = m_DpStrLensTiltY.GetData();

    //* Processing when out-of-range data is entered
    if(m_dHenTheta[5] > m_dLensTiltYmax)    m_dHenTheta[5] = m_dLensTiltYmax;
    if(m_dHenTheta[5] < m_dLensTiltYmin)    m_dHenTheta[5] = m_dLensTiltYmin;

    m_dHenTheta[6] = m_dHenTheta[5];

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonLTiltY0()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_dHenTheta[5] = 0.0;
    m_dHenTheta[6] = m_dHenTheta[5];

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonLRotate0()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_dCylTheta[5] = 0.0;
    m_dCylTheta[6] = 0.0;
    m_dAx_Hyouji = 0.0;

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;

    if(m_bKeisyaRendou) {
        SRTLM_Keisya_Rendou();    //* Calling this function changes m_dHenFai[5],[6] and m_dHenTheta[5],[6]
    }

    Invalidate(FALSE);
}


//* 20230610 Lens Data : Ax
void CSRTLMDlg::OnSetfocusEditAx2()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditAx2()
{
    // TODO: If this is a RICHEDIT control, in order for it to send this notification,
    //       you must override the CDialog::OnInitDialog() function and
    //       call CRichEditCtrl(). SetEventMask() // with the ENM_CHANGE flag ORed in the mask.
    // TODO: Add your control notification handler code here.
    if(m_bChangeEditFlg) {
        if (m_bEditSphFlg == true) {
            m_bEditSphFlg = false;
            goto EXIT;
        }
        if (m_bEditCylFlg == true) {
            m_bEditCylFlg = false;
            goto EXIT;
        }
        if (m_bEditIndxFlg == true) {
            m_bEditIndxFlg = false;
            goto EXIT;
        }
        if (m_bEditThcknssFlg == true) {
            m_bEditThcknssFlg = false;
            goto EXIT;
        }
        if (m_bEditCrvFlg == true) {
            m_bEditCrvFlg = false;
            goto EXIT;
        }

        UpdateData(TRUE);

        //* from m_DpStrSph data
        m_dDVS = m_DpStrSph.GetData();

        m_dAx2 = m_DpStrAx2.GetData();
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dAx = m_dAx2;                          //* 20230610 Lens Data : Since Ax has been changed, the lens rotation Ax must also be changed

        m_dThickness = m_DpStrThickness.GetData();
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();
        m_dD1d = m_DpStrCurve.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;

        Invalidate(FALSE);

        m_bChangeEditFlg = true;
EXIT:;
    }
}

void CSRTLMDlg::OnKillfocusEditAx2()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = false;
}


void CSRTLMDlg::OnSetfocusEditSph()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditSph()
{
    // TODO: If this is a RICHEDIT control, the control will not send this notification unless
    //       you override the CDialog::OnInitDialog() function to send the CRichEditCrtl().SetEventMask() message
    //       to the control with the ENM_CHANGE flag ORed into the lParam mask.

    // TODO: Please add the code for the control notification handler at this location.
    if(m_bChangeEditFlg) {

        UpdateData(TRUE);

        //* from m_DpStrSph data
        m_dDVS = m_DpStrSph.GetData();

        m_dAx = m_DpStrAx.GetData();
        if(m_dAx > 90)    m_dAx = m_dAx - 180;
        m_dAx2 = m_DpStrAx2.GetData();          //* 20230610 Add  Lens Data : Ax
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dThickness = m_DpStrThickness.GetData();
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();
        m_dD1d = m_DpStrCurve.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;

        Invalidate(FALSE);

        m_bChangeEditFlg = true;

        m_bEditSphFlg = true;

    }
}

void CSRTLMDlg::OnKillfocusEditSph()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = false;
}

void CSRTLMDlg::OnSetfocusEditCyl()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditCyl()
{
    // TODO: If this is a RICHEDIT control, the control will not send this notification unless
    //       you override the CDialog::OnInitDialog() function to send the CRichEditCrtl().SetEventMask() message
    //       to the control with the ENM_CHANGE flag ORed into the lParam mask.

    // TODO: Please add the code for the control notification handler at this location.
    if(m_bChangeEditFlg) {

        UpdateData(TRUE);

        m_dDVC = m_DpStrCyl.GetData();

        m_dAx = m_DpStrAx.GetData();
        if(m_dAx > 90)    m_dAx = m_dAx - 180;
        m_dAx2 = m_DpStrAx2.GetData();          //* 20230610 Add  Lens Data : Ax
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dThickness = m_DpStrThickness.GetData();
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();
        m_dD1d = m_DpStrCurve.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;
        Invalidate(FALSE);

        m_bChangeEditFlg = true;

        m_bEditCylFlg = true;

    }
}

void CSRTLMDlg::OnKillfocusEditCyl()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = false;
}


void CSRTLMDlg::OnKillfocusEditAx()
{
    // TODO: Please add the code for the control notification handler at this location.

    UpdateData(TRUE);

    m_dAx = m_DpStrAx.GetData();
    if(m_dAx > 90)    m_dAx = m_dAx - 180;
    m_dThickness = m_DpStrThickness.GetData();
    m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();
    m_dD1d = m_DpStrCurve.GetData();

    Make_Lens();
    m_bSetSpinScrollFlg = true;
    Invalidate(FALSE);
}


void CSRTLMDlg::OnSetfocusEditN()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditN()
{
    // TODO: If this is a RICHEDIT control, the control will not send this notification unless
    //       you override the CDialog::OnInitDialog() function to send the CRichEditCrtl().SetEventMask() message
    //       to the control with the ENM_CHANGE flag ORed into the lParam mask.

    // TODO: Please add the code for the control notification handler at this location.
    if(m_bChangeEditFlg) {

        UpdateData(TRUE);

        //* from m_strRefractiveIndex data
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();

        if(m_dRefractiveIndex < 1.0)    m_dRefractiveIndex = 1.0;
        if(m_dRefractiveIndex > 2.5)    m_dRefractiveIndex = 2.5;

        m_dAx = m_DpStrAx.GetData();
        if(m_dAx > 90)    m_dAx = m_dAx - 180;
        m_dAx2 = m_DpStrAx2.GetData();          //* 20230610 Add  Lens Data : Ax
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dThickness = m_DpStrThickness.GetData();
        m_dD1d = m_DpStrCurve.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;
        Invalidate(FALSE);

        m_bChangeEditFlg = true;

       m_bEditIndxFlg = true;
    }
}

void CSRTLMDlg::OnKillfocusEditN()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = false;
}


void CSRTLMDlg::OnSetfocusEditT()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditT()
{
    // TODO: If this is a RICHEDIT control, the control will not send this notification unless
    //       you override the CDialog::OnInitDialog() function to send the CRichEditCrtl().SetEventMask() message
    //       to the control with the ENM_CHANGE flag ORed into the lParam mask.

    // TODO: Please add the code for the control notification handler at this location.
    if(m_bChangeEditFlg) {

        UpdateData(TRUE);

        //* from m_strLensThickness data
        m_dThickness = m_DpStrThickness.GetData();
        if(m_dThickness < 0.0)    m_dThickness = 0.0;
        if(m_dThickness > 30.0)    m_dThickness = 30.0;

        m_dAx = m_DpStrAx.GetData();
        if(m_dAx > 90)    m_dAx = m_dAx - 180;
        m_dAx2 = m_DpStrAx2.GetData();          //* 20230610 Add  Lens Data : Ax
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();
        m_dD1d = m_DpStrCurve.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;
        Invalidate(FALSE);

        m_bChangeEditFlg = true;

        m_bEditThcknssFlg = true;
    }
}

void CSRTLMDlg::OnKillfocusEditT()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = false;
}


void CSRTLMDlg::OnSetfocusEditCurve()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = true;
}

void CSRTLMDlg::OnChangeEditCurve()
{
    // TODO: If this is a RICHEDIT control, the control will not send this notification unless
    //       you override the CDialog::OnInitDialog() function to send the CRichEditCrtl().SetEventMask() message
    //       to the control with the ENM_CHANGE flag ORed into the lParam mask.

    // TODO: Please add the code for the control notification handler at this location.
    if(m_bChangeEditFlg) {

        UpdateData(TRUE);

        //* from m_strCurve data
        m_dD1d = m_DpStrCurve.GetData();

        if(m_dD1d < -100.0)    m_dD1d = -100.0;
        if(m_dD1d > 100.0)    m_dD1d = 100.0;

        m_dAx = m_DpStrAx.GetData();
        if(m_dAx > 90)    m_dAx = m_dAx - 180;
        m_dAx2 = m_DpStrAx2.GetData();          //* 20230610 Add  Lens Data : Ax
        if(m_dAx2 > 90)    m_dAx2 = m_dAx2 - 180;
        m_dThickness = m_DpStrThickness.GetData();
        m_dRefractiveIndex = m_DpStrRefractiveIndex.GetData();

        Make_Lens();
        m_bSetSpinScrollFlg = true;
        Invalidate(FALSE);

        m_bChangeEditFlg = true;

        m_bEditCrvFlg = true;
    }
}

void CSRTLMDlg::OnKillfocusEditCurve()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_bChangeEditFlg = false;
}

void CSRTLMDlg::OnButtonMag1()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_dWin2Mag = 15.0;
    m_iCoronaFlg = 0;

    m_bPicBoxSizeFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonMag2()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_dWin2Mag = 15.0 / 2.0;
    m_iCoronaFlg = 0;

    m_bPicBoxSizeFlg = true;
    Invalidate(FALSE);
}

void CSRTLMDlg::OnButtonMag10()
{
    // TODO: Please add the code for the control notification handler at this location.
    m_dWin2Mag = 1.0;
    m_iCoronaFlg = 1;

    m_bPicBoxSizeFlg = true;
    Invalidate(FALSE);
}


void CSRTLMDlg::OnCheckKeisya()
{
    // TODO: Please add the code for the control notification handler at this location.
    if(m_bKeisyaRendou) {
        m_bKeisyaRendou = false;
    }
    else {
        m_bKeisyaRendou = true;
    }
}

void CSRTLMDlg::OnCheckPg()
{
    // TODO: Please add the code for the control notification handler at this location.
    if(m_bJujiRendou) {
        m_bJujiRendou = false;
    }
    else {
        m_bJujiRendou = true;
    }
}

void CSRTLMDlg::OnCheckAf()
{
    // TODO: Please add the code for the control notification handler at this location.
    if(m_bAFFlg) {
        m_bAFFlg = false;
    }
    else {
        m_bAFFlg = true;
    }
}

void CSRTLMDlg::OnCheckReverse()
{
    // TODO: Please add the code for the control notification handler at this location.
    if(m_bHantenFlg) {
        m_bHantenFlg = false;
    }
    else {
        m_bHantenFlg = true;
    }

    double d_C6tmp = m_dC[6];
    double d_CylCV26tmp = m_dCylCV2[6];
    double d_CylTheta6tmp = m_dCylTheta[5];

    m_dC[6] = -m_dC[5];
    m_dCylCV2[6] = -m_dCylCV2[5];

    //* Depending on the center thickness D(6) of the tested lens C(6)__AN(7)_D(6)__C(7),
    //* the distance D(7) to the condenser lens 1 C(8)__C(9) is changed,
    //* while keeping the distance from the rear surface of the tested lens C(6)
    // to the first surface of the condenser lens C(8) constant.

    switch(m_iKY2)
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

    m_dC[5] = -d_C6tmp;
    m_dCylCV2[5] = -d_CylCV26tmp;

    m_dCylTheta[6] = m_dCylTheta[5];
    m_dCylTheta[5] = d_CylTheta6tmp;

    R_KINJIKU();

    m_dObjZ = m_dObjPoint1;
    Diopter(m_dObjPoint1, &m_dDpt);

    m_bSyokika = false;
    m_bSetSpinScrollFlg = true;

    Invalidate(FALSE);
}

void CSRTLMDlg::OnResetCurrent()
{
    // TODO: Please add the code for the control notification handler at this location.
    //* Diopter dial
    if(m_dNowDefaultObjZ == -9999.0) {
        m_dObjZ = m_dDefaultObjZ;
    }
    else {
        m_dObjZ = m_dNowDefaultObjZ;
    }

    Diopter(m_dObjZ, &m_dDpt);

    //* tested lens Ax rotation(-)
    m_dCylTheta[5] = -m_dAx2;       //* 20230610 Mod  Changed to display Ax in the Lens Data group, so set this Ax as the current reference.
    m_dCylTheta[6] = -m_dAx2;       //* 20230610 Mod
    m_dAx_Hyouji   = m_dAx2;        //* 20230610 Mod
    m_dAx2_Hyouji  = m_dAx2;        //* 20230610 Add  Lens Data : Ax

    //* Lens position
    //* Unlike lens rotation, which depends on whether the TORIC surface is specified,
    //* eccentricity requires constant initialization because moving the position assigns
    //* specific values to TLX, HenFai, and other parameters.

    //* Horizpntal
    m_dTLX[5] = 0.0;
    m_dTLX[6] = 0.0;
    //* Vertical
    m_dTLY[5] = 0.0;
    m_dTLY[6] = 0.0;

    //* Rotation of the pint glass crosshairs
    m_dPintGlassMemori = 0.0;

    //* Lens tilt
    //* Horizpntal
    m_dHenFai[5] = 0.0;
    m_dHenFai[6] = 0.0;
    //* Vertical
    m_dHenTheta[5] = 0.0;
    m_dHenTheta[6] = 0.0;

    //* Spin Control Initialization of variables
    m_iLensPosXOld = 0;
    m_iLensPosYOld = 0;

    m_bSetSpinScrollFlg = true;

    Invalidate(FALSE);
}


