
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


// SRTLMDlg.h : header file
//

#include "afxwin.h"

#if !defined(AFX_SRTLMDLG_H__FD51EBB6_089E_4544_946E_057CF09C9AC7__INCLUDED_)
#define AFX_SRTLMDLG_H__FD51EBB6_089E_4544_946E_057CF09C9AC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RayTrace.h"
#include "DpNumCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSRTLMDlg Dialog

class CSRTLMDlg : public CDialog
{
// Construction
public:
    CSRTLMDlg(CWnd* pParent = NULL);    // Standard constructor

// Dialog Data
    //{{AFX_DATA(CSRTLMDlg)
    enum { IDD = IDD_SRTLM_DIALOG };
    CDpNumCtrl    m_DpStrTargetDiopter;
    CDpNumCtrl    m_DpStrThickness;
    CDpNumCtrl    m_DpStrSph;
    CDpNumCtrl    m_DpStrPintGlassDeg;
    CDpNumCtrl    m_DpStrRefractiveIndex;
    CDpNumCtrl    m_DpStrLensPosY;
    CDpNumCtrl    m_DpStrLensPosX;
    CDpNumCtrl    m_DpStrLensTiltY;
    CDpNumCtrl    m_DpStrLensTiltX;
    CDpNumCtrl    m_DpStrCyl;
    CDpNumCtrl    m_DpStrCurve;
    CDpNumCtrl    m_DpStrAx;
    CDpNumCtrl    m_DpStrAx2;           //* 20230610 Add  Lens Data : Ax
    CString    m_strRadius1;
    CString    m_strRadius2max;
    CString    m_strRadius2min;
    //}}AFX_DATA

private:
    CRayTrace* m_rTrace;

    CDC* m_pDC1;
    CDC* m_pDC2;
    CBitmap m_bmpMemDC1;
    CBitmap m_bmpMemDC2;


    //* ////////////////////////////////////////////////
    //* SRTLM MainProgram
    //* ////////////////////////////////////////////////
    BOOL MainProgram();


    //* ////////////////////////////////////////////////
    //* File I/O
    //* ////////////////////////////////////////////////

    //* File Input
    //* ================================================

//* Read the contents of the file and check whether it contains an SRTLM_Dat line
    //* ------------------------------------------------
    BOOL GetSRTLM_Dat(LPCTSTR strPath);

    //* Data File Input
    //* ------------------------------------------------
    BOOL DatFileInPut(LPCTSTR strPath);

    //* Sub function to extract numeric string of m_iKY2
    //* ------------------------------------------------
    BOOL GetPartsKY2(CString cStrkk_Parts);

    //* m_iKY2 の数値文字列を抽出する子関数
    //* ------------------------------------------------
    BOOL GetParts1523(CString cStrkk_Parts);

    //* Sub function to extract numeric strings such as m_dC[n], m_dD[n]....
    //* ------------------------------------------------
    BOOL GetParts(CString cStrkk_Parts);

    //* Assign values to arrays
    //* ------------------------------------------------
    BOOL DatToArray();

//* If All_Reset is executed after loading data
//* from a file, the saved data is assigned to the array.
    //* ------------------------------------------------
    BOOL GetBackUpFileData();

    //* File outputFile output
    //* ================================================

    //* Converted File Output
    //* ------------------------------------------------
    BOOL DatFileOutPut(LPCTSTR fname);


    //* ////////////////////////////////////////////////
    //* DlgAction
    //* Calculate various quantities when the tested lens is moved (shift, tilt, rotation, etc.)
    //* ////////////////////////////////////////////////

    //* Ax Conversion
    //* ------------------------------------------------
    BOOL Ax_Henkan(int iNum, double dAx);

    //* target -> Diopter
    //* ------------------------------------------------
    BOOL Diopter(double, double*);

    //* Diopter -> Target
    //* ------------------------------------------------
    BOOL Target(double, double*);

    //* Calculate the color of the corona image
    //* ------------------------------------------------
    long CoronaColor();

    //* Height of the incident ray
    //* ------------------------------------------------
    BOOL Nyusyatakasa();

    //* Tested Lens settings
    //* ------------------------------------------------
    BOOL Make_Lens();

    //* Paraxial ray reverse tracing
    //* ------------------------------------------------
    BOOL R_KINJIKU();

    //* Paraxial ray reverse tracing (debug)
    //* ------------------------------------------------
    BOOL R_KINJIKU_Debug();
    BOOL R_KINJIKU_Debug2();
    //* ------------------------------------------------

    //* Tilt linkage
    //* ------------------------------------------------
    BOOL SRTLM_Keisya_Rendou();


    //* ////////////////////////////////////////////////
    //* Dlg_sub
    //* ////////////////////////////////////////////////

    //* Initialization
    //* ------------------------------------------------
    //* Data
    void DataInBefore();
    BOOL DefaultDataIn();   //* 20230707 add
    BOOL DataIn();

    //* Picture Box
    //* ------------------------------------------------
    BOOL PictureBoxSize();

    //* ------------------------------------------------
    BOOL DataInitialize();

    //* Initialization of Lens Constructions
    //* ------------------------------------------------
    void baseLensDataInitialize(int iKY2);
    //* Inform the lens constructions to the class "RayTrace"

    //* ------------------------------------------------
    void baseLensDataTransfer(int iKY2);

    //* Inform class "RayTrace" of dialog changes
    //* ------------------------------------------------
    void RayTraceInitialize();

    //* Ray Trace Error State
    //* ------------------------------------------------
    void rtErrState(int iResult);

    //* 20230709 Add Obtaine the date to include in the copyright <- Since it's not working out, I'll put it in the title
    void* GetYear(char* year);



    //* File I/O
    //* ------------------------------------------------
    CString m_strSRTLM_FilePath;

    bool m_bSRTLM_DatFlg;

    bool m_bFileReadFlg;
    bool m_bFileWriteFlg;

    int m_iKY2LineNum;
    int m_iLineCount;

    CString m_strPartsValue;
    CString m_strPartsArrayNum;
    CString m_strPartsType;

    //* Backup in case initialization is executed after data entry
    int m_iIKY2_backUp;
    double m_dC_backUp[KOUSEIMEN_MAX];
    double m_dD_backUp[KOUSEIMEN_MAX - 1];
    double m_dN_backUp[KOUSEIMEN_MAX + 1];
    int m_nTORIC_backUp[KOUSEIMEN_MAX];
    double m_dCylCV2_backUp[KOUSEIMEN_MAX];
    double m_dCylTheta_backUp[KOUSEIMEN_MAX];

    //* Edit
    //* ------------------------------------------------
    bool m_bChangeEditFlg;
    bool m_bSyokika;

    bool m_bKeisyaRendou;
    bool m_bJujiRendou;
    bool m_bHantenFlg;
    bool m_bAFFlg;
    bool m_bFccf1523Flg;    //* 20251027 (Ver.2.24.0) Add  Front Curve : Whether to fix to the refractive index of crown glass

    /* Taboo move */
    bool  m_bEditSphFlg     = false;
    bool  m_bEditCylFlg     = false;
    bool  m_bEditIndxFlg    = false;
    bool  m_bEditCrvFlg     = false;
    bool  m_bEditThcknssFlg = false;

    //* Picture Box
    //* ------------------------------------------------
    bool m_bPicBoxSizeFlg;

    double m_dWin1Mag;
    double m_dWin2DefaultSize, m_dWin2Mag;

    //* Scroll bar, Spin button
    //* ------------------------------------------------
    bool m_bSetSpinScrollFlg;
    //* target
    double m_dTargetDiopterMin;
    double m_dTargetDiopterMax;

    //* lens position
    //* x
    double m_dLensPosXmin;
    double m_dLensPosXmax;
    int    m_iLensPosXOld;
    //* y
    double m_dLensPosYmin;
    double m_dLensPosYmax;
    int    m_iLensPosYOld;

    //* lens tilt
    //* x
    double m_dLensTiltXmin;
    double m_dLensTiltXmax;
    //* y
    double m_dLensTiltYmin;
    double m_dLensTiltYmax;

    //* Lens settings
    //* ------------------------------------------------
    double m_dDVS, m_dDVC, m_dAx;
    double m_dRefractiveIndex, m_dThickness, m_dD1d;
    double m_dAx_Hyouji;
    double m_dAx2, m_dAx2_Hyouji;   //* 20230610 Add  Lens Data : Ax
    double m_dRadius1, m_dRadius2min, m_dRadius2max;


    //* Data Initialize
    //* ------------------------------------------------
    //* m_dDefaultObjZ is the initial value when called in Data_In
    //* m_dNowDefaultObjZ is the default value when lens data changes
    double m_dDefaultObjZ, m_dNowDefaultObjZ;


    //* R_KINJIK
    //* ------------------------------------------------
    double m_dObjPoint1, m_dObjPoint2;

    //* Nyusyatakasa
    //* ------------------------------------------------
    double m_dVSC_h;

    //* Pint Glass
    //* ------------------------------------------------
    double m_dPintGlassBar;


    //* Change the background color of read-only EditControls
    CBrush m_IjirunaBrush;
    COLORREF m_IjirunaColor;

    //* Change the background color of editable EditControls
    CBrush m_IjiruyoiBrush;
    COLORREF m_IjiruyoiColor;


    //* Shared variable transfer (variables that only need to be notified during initialization)
    CommonParamsDef::rtLensDat params;

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
    double m_dCylCV2[KOUSEIMEN_MAX], m_dCylTheta[KOUSEIMEN_MAX];
    double m_dCylTheta5;

    int m_nSHAX[KOUSEIMEN_MAX];                 //* Optical axis shift
    double m_dAxSHV[KOUSEIMEN_MAX][4];

    int m_nTLAX[KOUSEIMEN_MAX];                 //* Eccentricity
    double m_dTLZ[KOUSEIMEN_MAX], m_dTLY[KOUSEIMEN_MAX], m_dTLX[KOUSEIMEN_MAX];
    double m_dHenTheta[KOUSEIMEN_MAX], m_dHenFai[KOUSEIMEN_MAX];

    double m_dRXA;
    double m_dRYA;
    double m_dRZA;

    double m_dSY;                               //* Aperture radius on the first surface
    double m_dDepth;
    double m_dRZtargetZero;
    double m_dRZhikenLens;
    double m_dRZpintGlass;
    //* //////////////////////////////

    //* ///////////////////////////
    //* /// RayTrace Initialize ///
    //* ///////////////////////////

    int m_iIR;
    double m_dAX;
    double m_dAY;
    double m_dAZ;
    double m_dQNTP;
    double m_dObjX;
    double m_dObjY;
    double m_dObjZ;    //* target position
    double m_dDXI;
    double m_dDYI;
    double m_dDZI;

    double m_dDpt;    //* target position to Diopter

    double m_dPintGlassMemori;
    double m_dCoronaSize;
    double m_dCoronaConfusion;
    int m_iCoronaFlg;
    ////////////////////////////////

    // ClassWizard generates virtual function overrides.
    //{{AFX_VIRTUAL(CSRTLMDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CSRTLMDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnStart();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnKillfocusEditLpX();
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnButtonLpX0();
    afx_msg void OnKillfocusEditLpY();
    afx_msg void OnButtonLpY0();
    afx_msg void OnButtonTargetDefault();
    afx_msg void OnKillfocusEditPgDeg();
    afx_msg void OnKillfocusEditSph();
    afx_msg void OnKillfocusEditN();
    afx_msg void OnKillfocusEditT();
    afx_msg void OnKillfocusEditCyl();
    afx_msg void OnKillfocusEditAx();
    afx_msg void OnKillfocusEditLTiltX();
    afx_msg void OnKillfocusEditLTiltY();
    afx_msg void OnButtonLRotate0();
    afx_msg void OnButtonLTiltX0();
    afx_msg void OnButtonLTiltY0();
    afx_msg void OnButtonMag1();
    afx_msg void OnButtonMag10();
    afx_msg void OnButtonMag2();
    afx_msg void OnButtonPgRotate0();
    afx_msg void OnKillfocusEditCurve();
    afx_msg void OnCheckKeisya();
    afx_msg void OnCheckPg();
    afx_msg void OnCheckReverse();
    afx_msg void OnCheckAf();
    afx_msg void OnResetCurrent();
    afx_msg void OnButtonFileOut();
    afx_msg void OnButtonFileIn();
    afx_msg void OnKillfocusEditTargetDpt();
    afx_msg void OnChangeEditSph();
    afx_msg void OnSetfocusEditSph();
    afx_msg void OnChangeEditCyl();
    afx_msg void OnSetfocusEditCyl();
    afx_msg void OnChangeEditN();
    afx_msg void OnSetfocusEditN();
    afx_msg void OnChangeEditT();
    afx_msg void OnSetfocusEditT();
    afx_msg void OnChangeEditCurve();
    afx_msg void OnSetfocusEditCurve();
    afx_msg void OnChangeEditAx2();     //* 20230610 Add
    afx_msg void OnKillfocusEditAx2();  //* 20230610 Add
    afx_msg void OnSetfocusEditAx2();   //* 20230610 Add
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnDestroy();
protected:
    CButton m_Check_AF;
    CButton m_Check_Keisya;
public:
    CButton m_Check_Fccf1523;
    afx_msg void OnCheckFCCF();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ inserts additional declarations immediately before the preceding line.

#endif //* !defined(AFX_SRTLMDLG_H__FD51EBB6_089E_4544_946E_057CF09C9AC7__INCLUDED_)
