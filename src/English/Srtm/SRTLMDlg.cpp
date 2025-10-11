
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
#include "GlobalDef.h"
#include "Version.h"
#include "RayTrace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generates virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // Message handler does not exist.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRTLMDlg dialog

CSRTLMDlg::CSRTLMDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CSRTLMDlg::IDD, pParent)
{
    m_rTrace = new CRayTrace;

    //{{AFX_DATA_INIT(CSRTLMDlg)
    m_strRadius1 = _T("");
    m_strRadius2max = _T("");
    m_strRadius2min = _T("");
    //}}AFX_DATA_INIT
    // Note: LoadIcon does not require a Win32 DestroyIcon sub-sequence.
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    /////////////////////////////////////////////////////
    //* First half begins

    //* Data files I/O
    m_strSRTLM_FilePath = "";
    m_bSRTLM_DatFlg = false;
    m_bFileReadFlg = false;
    m_bFileWriteFlg = false;
    m_iKY2LineNum = 0;
    m_iLineCount = 0;
    m_strPartsValue = "";
    m_strPartsArrayNum = "";
    m_strPartsType = "";

    //* Backup in case initialization is performed after data entry.
    m_iIKY2_backUp = 0;
    for (int i = 0; i <= KOUSEIMEN_MAX; i++) {
        m_dC_backUp[i] = 0.0;
        m_nTORIC_backUp[i] = 0;
        m_dCylCV2_backUp[i] = 0.0;
        m_dCylTheta_backUp[i] = 0.0;
    }
    for (int i = 0; i < KOUSEIMEN_MAX; i++) {
        m_dD_backUp[i] = 0.0;
    }
    for (int i = 0; i <= KOUSEIMEN_MAX + 1; i++) {
        m_dN_backUp[i] = 0.0;
    }

    //* Initial angle of the crosshairs on the scale plate in picture2.
    m_dPintGlassMemori = 0.0;

    m_bSyokika = true;
    m_bSetSpinScrollFlg = true;
    m_bChangeEditFlg = false;

    m_iCoronaFlg = 0;
    m_bKeisyaRendou = false;
    m_bJujiRendou = false;
    m_bHantenFlg = false;
    m_bAFFlg = true;

    m_dDefaultObjZ = -9999.0;
    m_dNowDefaultObjZ = -9999.0;

    //* R_KINJIK
    m_dObjPoint1 = 0.0, m_dObjPoint2 = 0.0;

    //* Nyusyatakasa
    m_dVSC_h = 0.0;

    //* The Scale Plate
    m_dPintGlassBar = 0.0;

    //* Lens Settings
    m_dDVS = 0.0, m_dDVC = 0.0, m_dAx = 0.0;
    m_dRefractiveIndex = 0.0, m_dThickness = 0.0, m_dD1d = 0.0;
    m_dAx_Hyouji = 0.0;
    m_dAx2 = 0.0;           //* 20230610 Add  Lens Data : Ax
    m_dAx2_Hyouji = 0.0;    //* 20230610 Add  Lens Data : Ax

    m_dRadius1 = 0.0, m_dRadius2min = 0.0, m_dRadius2max = 0.0;

    //* Default size of picture2
    m_dWin2DefaultSize = 10.0;
    //* Default magnification of picture2
    m_dWin2Mag = 15.0;

    DefaultDataIn();

    DataIn();       //* Changes "m_dWin2DefaultSize" in DataIn()

    //* Picture Box magnification setting
    m_dWin1Mag = 0.9;
    //* PictureBox size
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
    g_dWindowPosLeft2 = g_dWindowPosLeft2  * m_dWin2Mag;
    g_dWindowPosRight2 = g_dWindowPosRight2 * m_dWin2Mag;
    g_dWindowPosTop2 = g_dWindowPosTop2 * m_dWin2Mag;
    g_dWindowPosBottom2 = g_dWindowPosBottom2 * m_dWin2Mag;
    /////////////////////////////////////////////////////
    //* First half ends
}

void CSRTLMDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSRTLMDlg)
    DDX_Control(pDX, IDC_EDIT_TARGET_DPT, m_DpStrTargetDiopter);
    DDX_Control(pDX, IDC_EDIT_T, m_DpStrThickness);
    DDX_Control(pDX, IDC_EDIT_SPH, m_DpStrSph);
    DDX_Control(pDX, IDC_EDIT_PG_DEG, m_DpStrPintGlassDeg);
    DDX_Control(pDX, IDC_EDIT_N, m_DpStrRefractiveIndex);
    DDX_Control(pDX, IDC_EDIT_LP_Y, m_DpStrLensPosY);
    DDX_Control(pDX, IDC_EDIT_LP_X, m_DpStrLensPosX);
    DDX_Control(pDX, IDC_EDIT_L_TILT_Y, m_DpStrLensTiltY);
    DDX_Control(pDX, IDC_EDIT_L_TILT_X, m_DpStrLensTiltX);
    DDX_Control(pDX, IDC_EDIT_CYL, m_DpStrCyl);
    DDX_Control(pDX, IDC_EDIT_CURVE, m_DpStrCurve);
    DDX_Control(pDX, IDC_EDIT_AX, m_DpStrAx);
    DDX_Control(pDX, IDC_PICT2, g_pict2);
    DDX_Control(pDX, IDC_PICT, g_pict1);
    DDX_Text(pDX, IDC_EDIT_R1, m_strRadius1);
    DDX_Text(pDX, IDC_EDIT_R2_MAX, m_strRadius2max);
    DDX_Text(pDX, IDC_EDIT_R2_MIN, m_strRadius2min);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_CHECK_AF, m_Check_AF);
    DDX_Control(pDX, IDC_CHECK_KEISYA, m_Check_Keisya);
    DDX_Control(pDX, IDC_EDIT_AX2, m_DpStrAx2);         //* 20230610 Add  Lens Data : Ax
}

BEGIN_MESSAGE_MAP(CSRTLMDlg, CDialog)
    //{{AFX_MSG_MAP(CSRTLMDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_HSCROLL()
    ON_EN_KILLFOCUS(IDC_EDIT_LP_X, OnKillfocusEditLpX)
    ON_WM_VSCROLL()
    ON_BN_CLICKED(IDC_BUTTON_LP_X_0, OnButtonLpX0)
    ON_EN_KILLFOCUS(IDC_EDIT_LP_Y, OnKillfocusEditLpY)
    ON_BN_CLICKED(IDC_BUTTON_LP_Y_0, OnButtonLpY0)
    ON_BN_CLICKED(IDC_BUTTON_TARGET_DEFAULT, OnButtonTargetDefault)
    ON_EN_KILLFOCUS(IDC_EDIT_PG_DEG, OnKillfocusEditPgDeg)
    ON_EN_KILLFOCUS(IDC_EDIT_SPH, OnKillfocusEditSph)
    ON_EN_KILLFOCUS(IDC_EDIT_N, OnKillfocusEditN)
    ON_EN_KILLFOCUS(IDC_EDIT_T, OnKillfocusEditT)
    ON_EN_KILLFOCUS(IDC_EDIT_CYL, OnKillfocusEditCyl)
    ON_EN_KILLFOCUS(IDC_EDIT_AX, OnKillfocusEditAx)
    ON_EN_KILLFOCUS(IDC_EDIT_L_TILT_X, OnKillfocusEditLTiltX)
    ON_EN_KILLFOCUS(IDC_EDIT_L_TILT_Y, OnKillfocusEditLTiltY)
    ON_BN_CLICKED(IDC_BUTTON_L_ROTATE_0, OnButtonLRotate0)
    ON_BN_CLICKED(IDC_BUTTON_L_TILT_X_0, OnButtonLTiltX0)
    ON_BN_CLICKED(IDC_BUTTON_L_TILT_Y_0, OnButtonLTiltY0)
    ON_BN_CLICKED(IDC_BUTTON_MAG_1, OnButtonMag1)
    ON_BN_CLICKED(IDC_BUTTON_MAG_10, OnButtonMag10)
    ON_BN_CLICKED(IDC_BUTTON_MAG_2, OnButtonMag2)
    ON_BN_CLICKED(IDC_BUTTON_PG_ROTATE_0, OnButtonPgRotate0)
    ON_EN_KILLFOCUS(IDC_EDIT_CURVE, OnKillfocusEditCurve)
    ON_BN_CLICKED(IDC_CHECK_KEISYA, OnCheckKeisya)
    ON_BN_CLICKED(IDC_CHECK_PG, OnCheckPg)
    ON_BN_CLICKED(IDC_CHECK_REVERSE, OnCheckReverse)
    ON_BN_CLICKED(IDC_CHECK_AF, OnCheckAf)
    ON_BN_CLICKED(IDC_RESET_CURRENT, OnResetCurrent)
    ON_BN_CLICKED(IDC_BUTTON_FILE_OUT, OnButtonFileOut)
    ON_BN_CLICKED(IDC_BUTTON_FILE_IN, OnButtonFileIn)
    ON_EN_KILLFOCUS(IDC_EDIT_TARGET_DPT, OnKillfocusEditTargetDpt)
    ON_EN_CHANGE(IDC_EDIT_SPH, OnChangeEditSph)
    ON_EN_SETFOCUS(IDC_EDIT_SPH, OnSetfocusEditSph)
    ON_EN_CHANGE(IDC_EDIT_CYL, OnChangeEditCyl)
    ON_EN_SETFOCUS(IDC_EDIT_CYL, OnSetfocusEditCyl)
    ON_EN_CHANGE(IDC_EDIT_N, OnChangeEditN)
    ON_EN_SETFOCUS(IDC_EDIT_N, OnSetfocusEditN)
    ON_EN_CHANGE(IDC_EDIT_T, OnChangeEditT)
    ON_EN_SETFOCUS(IDC_EDIT_T, OnSetfocusEditT)
    ON_EN_CHANGE(IDC_EDIT_CURVE, OnChangeEditCurve)
    ON_EN_SETFOCUS(IDC_EDIT_CURVE, OnSetfocusEditCurve)
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_BUTTON_RESET, OnStart)
    ON_EN_CHANGE(IDC_EDIT_AX2, &CSRTLMDlg::OnChangeEditAx2)         //* 20230610 Add  Lens Data : Ax
    ON_EN_KILLFOCUS(IDC_EDIT_AX2, &CSRTLMDlg::OnKillfocusEditAx2)   //* 20230610 Add  Lens Data : Ax
    ON_EN_SETFOCUS(IDC_EDIT_AX2, &CSRTLMDlg::OnSetfocusEditAx2)     //* 20230610 Add  Lens Data : Ax
    //}}AFX_MSG_MAP
    ON_WM_DESTROY()
    END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRTLMDlg message handlers
BOOL CSRTLMDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    // TODO: Add extra initialization here

    //* Dialog Title
    //* Get the current year
    char year[5];
    GetYear(year);
    CString cyear;
    cyear = year;
    cyear = cyear.Mid(0, 4);
    CString strTitle = "SRTLM Ver. ";
    strTitle += STR_VERSION;
    strTitle += " ";
    strTitle += cyear;
    strTitle += " by Kazuo Kawamura ";
    SetWindowText(strTitle);

    /////////////////////////////////////////////////////
    //* Second half begins
    //* Background color of Edit Controls that users cannot change
    m_IjirunaColor=RGB(205,205,205);
    m_IjirunaBrush.CreateSolidBrush(m_IjirunaColor);   // The background color of the EditControl that users cannot change.

    //* Colors set in the EditControl that users can change.
    m_IjiruyoiColor=RGB(235,255,255);
    m_IjiruyoiBrush.CreateSolidBrush(m_IjiruyoiColor);   // The background color of the EditControl that users can change.

    //* Initialization of Picture Box 1
    ///////////////////////////////////////////////
    m_pDC1 = new CClientDC(&g_pict1);

    g_memDC1.CreateCompatibleDC(m_pDC1);

    CRect rc;
    g_pict1.GetClientRect(&rc);
    m_bmpMemDC1.CreateCompatibleBitmap(m_pDC1, rc.Width(), rc.Height());
    g_memDC1.SelectObject(&m_bmpMemDC1);

    g_lPictureBoxSizeX = rc.Width();
    g_lPictureBoxSizeY = rc.Height();

    //* Initialization of Picture Box 2
    ///////////////////////////////////////////////
    m_pDC2 = new CClientDC(&g_pict2);

    g_memDC2.CreateCompatibleDC(m_pDC2);

    CRect rc2;

    g_pict2.GetClientRect(&rc2);
    m_bmpMemDC2.CreateCompatibleBitmap(m_pDC2, rc2.Width(), rc2.Height());
    g_memDC2.SelectObject(&m_bmpMemDC2);

    g_lPictureBoxSizeX2 = rc2.Width();
    g_lPictureBoxSizeY2 = rc2.Height();


    //* Initialization of the Spin Buttons.

    //* target
    //* Upper and lower limits of the Diopter Dial
    m_dTargetDiopterMin = -25.0;
    m_dTargetDiopterMax = 15.0;
    CSpinButtonCtrl* pSpin_target_dpt = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_TARGET_DPT);
    pSpin_target_dpt->SetRange(int(m_dTargetDiopterMin * 100.0), int(m_dTargetDiopterMax * 100.0));
    //* Initial position of the Diopter Dial
    pSpin_target_dpt->SetPos(0);

    //* Pint Glass Rotatation Rane
    CSpinButtonCtrl* pSpin_PG_rotate = (CSpinButtonCtrl*) GetDlgItem (IDC_SPIN_PG_ROTATE);
    pSpin_PG_rotate ->SetRange(-90, 90);
    //* Pint Glass Initial Angle
    pSpin_PG_rotate->SetPos(0);

    //* Lens Rotation Range
    CSpinButtonCtrl* pSpin_lens_rotate = (CSpinButtonCtrl*) GetDlgItem (IDC_SPIN_LENS_ROTATE);
    pSpin_lens_rotate ->SetRange(-90, 90);
    //* Axis Initial Angle
    pSpin_lens_rotate->SetPos(0);


    //* Lens Position

    //* Upper and Lower limits of the Lens Position 'x'
    m_dLensPosXmin = -45.0;
    m_dLensPosXmax = 45.0;
    m_iLensPosXOld = 0;
    CSpinButtonCtrl* pSpin_lp_x = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_LP_X);
    pSpin_lp_x->SetRange(int(m_dLensPosXmin * 10.0), int(m_dLensPosXmax * 10.0));
    //* Lens Position 'x' Initial Position
    pSpin_lp_x->SetPos(0);

    //* Upper and Lower limits of the Lens Position 'y'
    m_dLensPosYmin = -45.0;
    m_dLensPosYmax = 45.0;
    m_iLensPosYOld = 0;
    CSpinButtonCtrl* pSpin_lp_y = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_LP_Y);
    pSpin_lp_y->SetRange(int(m_dLensPosYmin * 10.0), int(m_dLensPosYmax * 10.0));
    //* Lens Position 'y' Initial Position
    pSpin_lp_y->SetPos(0);


    //* Lens Tilt

    //* Upper and Lower limits of the Lens Tilt 'x'
    m_dLensTiltXmin = -45.0;
    m_dLensTiltXmax = 45.0;
    CSpinButtonCtrl* pSpin_tilt_x = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_L_TILT_X);
    pSpin_tilt_x->SetRange(int(m_dLensTiltXmin * 10.0), int(m_dLensTiltXmax * 10.0));
    //* Lens Tilt 'x' Initial Position
    pSpin_tilt_x->SetPos(0);

    //* Upper and Lower limits of the Lens Tilt 'y'
    m_dLensTiltYmin = -45.0;
    m_dLensTiltYmax = 45.0;
    CSpinButtonCtrl* pSpin_tilt_y = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_L_TILT_Y);
    pSpin_tilt_y->SetRange(int(m_dLensTiltYmin * 10.0), int(m_dLensTiltYmax * 10.0));
    //* Lens Tilt 'y' Initial Position
    pSpin_tilt_y->SetPos(0);


    //* Slider Initialization

    CSliderCtrl* pSlider_target_dpt = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_TARGET_DPT);
    pSlider_target_dpt->SetRange(int(m_dTargetDiopterMin * 4.0), int(m_dTargetDiopterMax * 4.0));
    //* Slider Initial Position
    pSlider_target_dpt->SetPos(1);

    //* Pint Glass Rotatation
    CSliderCtrl* pSlider_PG_rotate = (CSliderCtrl*) GetDlgItem (IDC_SLIDER_PG_ROTATE);
    pSlider_PG_rotate->SetRange(-90, 90);
    //* Pint Glass Initial Angle
    pSlider_PG_rotate->SetPos(1);

    //* Lens Rotation Range
    CSliderCtrl* pSlider_lens_rotate = (CSliderCtrl*) GetDlgItem (IDC_SLIDER_LENS_ROTATE);
    pSlider_lens_rotate->SetRange(-90, 90);
    //* Axis Initial Angle
    pSlider_lens_rotate->SetPos(5);

    m_Check_Keisya.SetCheck(1);
    m_Check_AF.SetCheck(1);

    /////////////////////////////////////////////////////
    //* Second half ends

    return TRUE;  // return TRUE  unless you set the focus to a control
}


void CSRTLMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSRTLMDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();

        //* Memory Release
        m_bmpMemDC1.DeleteObject();
        //* Memory Release
        m_bmpMemDC2.DeleteObject();

        MainProgram();

        //* Paste
        m_pDC1->BitBlt(0, 0, g_lPictureBoxSizeX, g_lPictureBoxSizeY, &g_memDC1, 0, 0, SRCCOPY);

        //* Paste
        m_pDC2->BitBlt(0, 0, g_lPictureBoxSizeX2, g_lPictureBoxSizeY2, &g_memDC2, 0, 0, SRCCOPY);
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSRTLMDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CSRTLMDlg::OnStart()
{
    // TODO: Please add the code for the control notification handler at this location.
    //* Reset All
    if(m_bHantenFlg) {
        CButton* chkHanten = (CButton*) GetDlgItem (IDC_CHECK_REVERSE);
        chkHanten->SetCheck(0);
        m_bHantenFlg = false;
    }

    if(m_bJujiRendou) {
        CButton* chkJuji = (CButton*) GetDlgItem (IDC_CHECK_PG);
        chkJuji->SetCheck(0);
        m_bJujiRendou = false;
    }

    if(m_bFileReadFlg)    GetBackUpFileData();

    DataIn();
    m_bSyokika = true;
    m_bSetSpinScrollFlg = true;
    m_bChangeEditFlg = false;
    m_bPicBoxSizeFlg = true;

    m_iLensPosXOld = 0;
    m_iLensPosYOld = 0;

    //* Memory Release
    m_bmpMemDC1.DeleteObject();
    //* Memory Release
    m_bmpMemDC2.DeleteObject();

    MainProgram();

    //* Paste
    m_pDC1->BitBlt(0, 0, g_lPictureBoxSizeX, g_lPictureBoxSizeY, &g_memDC1, 0, 0, SRCCOPY);

    //* Paste
    m_pDC2->BitBlt(0, 0, g_lPictureBoxSizeX2, g_lPictureBoxSizeY2, &g_memDC2, 0, 0, SRCCOPY);
}

BOOL CSRTLMDlg::MainProgram()
{
    CRect rc;
    g_pict1.GetClientRect(rc);
    g_memDC1.FillSolidRect(rc, RGB(255, 255, 255));

    CRect rc2;
    g_pict2.GetClientRect(rc2);
    g_memDC2.FillSolidRect(rc2, RGB(255, 255, 255));

    //* Picture Box Magnification Setting
    if(m_bPicBoxSizeFlg) {
        PictureBoxSize();
        m_bPicBoxSizeFlg = false;
    }

    //* Initial Screen Settings
    if (m_bSyokika) {
        DataInitialize();
    }

    m_rTrace->GLS1();


    //* Ray Tracing Main Routine

    Nyusyatakasa(); //* Obtain the value of m_dVSC_h


    /////////////////////////////
    //
    //* Ray Tracing Main Routine
    //
    /////////////////////////////

    //* Drawing the Corona Image: Review required between x1, x2 and x10
    int nStepIR;
    if (m_iCoronaFlg == 0) {
        m_iIR = 5;
        nStepIR = 1;
    }
    else {
        m_iIR = 10;
        nStepIR = 2;
    }

    //* Set Ray Trace Initialize
    RayTraceInitialize();

    m_rTrace->DT();

    int iResult = m_rTrace->RayTraceMain(m_dVSC_h, nStepIR);
    switch (iResult)
    {
    case ERR_RAY_TRACE:             //* 1: Untraceable, 0: None specified,          0: SkewRayTrace
    case ERR_RAY_TRACE_SPH:         //* 1: Untraceable, 1: Spherical and coaxial,   0: SRTSph
    case ERR_RAY_TRACE_TORIC:       //* 1: Untraceable, 2: Aspheric or non-coaxial, 1: SRTToric
    case ERR_RAY_TRACE_ASPH:        //* 1: Untraceable, 2: Aspheric or non-coaxial, 2: SRTAsph
    case ERR_RAY_TRACE_ASPH2:       //* 1: Untraceable, 2: Aspheric or non-coaxial, 4: SRTAsph2
    case ERR_RAY_TRACE_HENSPH:      //* 1: Untraceable, 2: Aspheric or non-coaxial, 3: SRTHenSph
        rtErrState(iResult);
        break;
    default:
        break;
    }

    m_rTrace->GLS2();

    long lCoronaCol = CoronaColor();
    m_rTrace->PGCorona(lCoronaCol);


    //* Display Change Details: Internal -> Dialog


    double dDVC = m_dDVC;
    if(!m_bChangeEditFlg)    m_DpStrSph.SetData(m_dDVS, dDVC, 0, 1);
    double dDVS = m_dDVS;
    if(!m_bChangeEditFlg)    m_DpStrCyl.SetData(m_dDVC, dDVS, 0, 2);

    m_dAx_Hyouji = -m_dCylTheta[5];
    Ax_Henkan(1, m_dAx_Hyouji);
    Ax_Henkan(2, m_dCylTheta[5]);
    m_dCylTheta[6] = m_dCylTheta[5];
    m_DpStrAx.SetData(m_dAx_Hyouji, 0.0, 1, 0);

    Ax_Henkan(6, m_dAx2);                           //* 20230610 Add  Lens Data : Ax
    m_DpStrAx2.SetData(m_dAx2_Hyouji, 0.0, 1, 0);   //* 20230610 Add  Lens Data : Ax

    if(!m_bChangeEditFlg)    m_DpStrRefractiveIndex.SetData(m_dRefractiveIndex, 0.0, 2, 0);
    if(!m_bChangeEditFlg)    m_DpStrThickness.SetData(m_dThickness, 0.0, 4, 0);
    if(!m_bChangeEditFlg)    m_DpStrCurve.SetData(m_dD1d, 0.0, 5, 3);


    m_DpStrLensPosX.SetData(m_dTLX[5], 0.0, 3, 0);
    m_DpStrLensPosY.SetData(m_dTLY[5], 0.0, 3, 0);

    m_DpStrLensTiltX.SetData(m_dHenFai[5], 0.0, 3, 0);
    m_DpStrLensTiltY.SetData(m_dHenTheta[5], 0.0, 3, 0);

    Ax_Henkan(3, m_dPintGlassMemori);
    m_DpStrPintGlassDeg.SetData(m_dPintGlassMemori, 0.0, 1, 0);

    //* Target position: Display set by Diopter
    m_DpStrTargetDiopter.SetData(m_dDpt, 0.0, 0, 0);

    //* Lens Data
    m_strRadius1.Format(_T("%+.7f"), m_dRadius1);
    m_strRadius2min.Format(_T("%+.7f"), m_dRadius2min);
    m_strRadius2max.Format(_T("%+.7f"), m_dRadius2max);

    //* Scrollbar Settings

    //* When manipulating scroll bars or spin buttons, MainProgram() is called only
    //* after the ScrollPosition is finalized, so the following ScrollPosition setting is canceled.
    //* The following function is called only when a value is entered directly into the edit box
    //* corresponding to the scroll bar or spin button, or when initialization occurs.
    if(m_bSetSpinScrollFlg == true) {
        //* Spin Buttons

        //* Target
        CSpinButtonCtrl* pSpin_target_dpt = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_TARGET_DPT);
        pSpin_target_dpt->SetPos(int(m_dDpt * 100.0));

        //* Pint Glass Rotation
        CSpinButtonCtrl* pSpin_PG_rotate = (CSpinButtonCtrl*) GetDlgItem (IDC_SPIN_PG_ROTATE);
        pSpin_PG_rotate -> SetPos(int(m_dPintGlassBar));

        //* Lens Rotation
        CSpinButtonCtrl* pSpin_lens_rotate = (CSpinButtonCtrl*) GetDlgItem (IDC_SPIN_LENS_ROTATE);
        pSpin_lens_rotate -> SetPos(int(-m_dCylTheta[5]));

        //* Lens Position 'x'
        CSpinButtonCtrl* pSpin_lp_x = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_LP_X);
        pSpin_lp_x->SetPos((int) (m_dTLX[5] * 10.0));

        //* Lens Position 'y'
        CSpinButtonCtrl* pSpin_lp_y = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_LP_Y);
        pSpin_lp_y->SetPos((int) (m_dTLY[5] * 10.0));


        //* Lens Tilt 'x'
        CSpinButtonCtrl* pSpin_tilt_x = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_L_TILT_X);
        pSpin_tilt_x->SetPos((int) (m_dHenFai[5] * 10.0));
        //* Lens Tilt 'y'
        CSpinButtonCtrl* pSpin_tilt_y = (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_L_TILT_Y);
        pSpin_tilt_y->SetPos((int) (m_dHenTheta[5] * 10.0));

        //* Slider

        //* Target
        CSliderCtrl* pSlider_target_dpt = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_TARGET_DPT);
        pSlider_target_dpt->SetPos(int(m_dDpt * 4.0));

        //* Pint Glass Rotation
        CSliderCtrl* pSlider_PG_rotate = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_PG_ROTATE);
        pSlider_PG_rotate->SetPos(int(m_dPintGlassBar) );

        //* Lens_Rotation
        CSliderCtrl* pSlider_lens_rotate = (CSliderCtrl*) GetDlgItem(IDC_SLIDER_LENS_ROTATE);
        pSlider_lens_rotate->SetPos(int(-m_dCylTheta[5]) );

        m_bSetSpinScrollFlg = false;
    }
    //* Internal Data -> Display
    UpdateData(FALSE);

    return TRUE;
}



void CSRTLMDlg::OnDestroy()
{
    CDialog::OnDestroy();

    // TODO: Add the message handler code here.
    //* Memory Release
    m_bmpMemDC1.DeleteObject();
    g_memDC1.DeleteDC();
    delete m_pDC1;

    m_bmpMemDC2.DeleteObject();
    g_memDC2.DeleteDC();
    delete m_pDC2;

    delete m_rTrace;
}

