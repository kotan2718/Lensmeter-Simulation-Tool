
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
#include "msdirent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

void CSRTLMDlg::OnButtonFileIn()
{
    // TODO: Please add the code for the control notification handler at this location
#define CHAR_LEN (256)
    TCHAR *cdir;

    //* Obtain the current directory
    cdir = new TCHAR[CHAR_LEN];
    GetCurrentDirectory(CHAR_LEN, cdir);
    //* Specify the [dat] directory one level up
    *(wcsrchr(cdir, L'\\')) = 0;
    wcscat_s(cdir, CHAR_LEN, _T("\\dat"));

    //* File Dialog Construction (Initial Setup)
    CFileDialog dlg(
        TRUE,    //* BOOL bOpenFileDialog,
        NULL,    //* LPCTSTR lpszDefExt = NULL,
        NULL,    //* LPCTSTR lpszFileName = NULL,
        OFN_NONETWORKBUTTON | OFN_NOTESTFILECREATE | OFN_OVERWRITEPROMPT,   //* DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        _T("SRTLM Files (*.srt)|*.srt|All Files (*.*)|*.*||"),              //* LPCTSTR lpszFilter = NULL,
        NULL);                                                              //* CWnd* pParentWnd = NULL);
    //* Open the file dialog
    dlg.m_ofn.lpstrInitialDir = cdir;

    if (dlg.DoModal() == IDCANCEL) {
        delete[] cdir;
        return;
    }

    //*
    //* When the file dialog returns with OK
    //
    m_strSRTLM_FilePath = dlg.m_ofn.lpstrFile;

    delete[] cdir;

    //*
    //* Read the contents of the file to obtain the desired data.
    //*

    //* ++++++++++++++++++++++++++++++++++++++++++++++++++++
    //* Check whether the data file is an SRTLM data file
    //* and whether it consists of one set of data
    //* ++++++++++++++++++++++++++++++++++++++++++++++++++++
    if (!GetSRTLM_Dat(m_strSRTLM_FilePath)) {
        AfxMessageBox(_T("This data file is not SRTLM data or contains multiple data sets."));
        return; //* Cannot be processed by SRTLM
    }

    DataInBefore(); //* Initialization of arrays, etc.

    //* +++++++++++++++++++++++++++++++
    //* Obtain the SRTLM Data
    //* +++++++++++++++++++++++++++++++
    DatFileInPut(m_strSRTLM_FilePath);

    m_bFileReadFlg = TRUE;

    m_bSyokika = true;
    OnStart();
}


//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++
//* Read the contents of the file and check whether
//* it contains an SRTLM_Dat line
BOOL CSRTLMDlg::GetSRTLM_Dat(LPCTSTR strPath)
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++
{

    //* Flag indicating whether only one SRTLM_Dat line exists
    BOOL bSRTLM_DatFlg = FALSE;

    //* Initial value for SRTLM_Dat count
    int iSRTLM_DatNum = 0;


    CStdioFile file;
    if (!file.Open(strPath, CFile::modeRead | CFile::typeText)) {
        return FALSE;
    }
    //*
    //* Starting data load
    //*
    CString m_cStrDispBuf;  //* String buffer for display
    CString cStrBuf;        //* String buffer for loading
    while (file.ReadString(cStrBuf))
    {
        //* Reserved for display
        m_cStrDispBuf = cStrBuf;

        //* Find the SRTLM_Dat line
        if (cStrBuf.Find(_T("SRTLM_Dat")) >= 0) {
            iSRTLM_DatNum++;
            continue;
        }
    }
    file.Close();

    if (iSRTLM_DatNum == 1)    bSRTLM_DatFlg = true;

    if (bSRTLM_DatFlg) {
        //* When the file contains only one SRTLM_Dat line
        return true;
    }
    else {
        //* When the file either does not contain SRTLM_Dat line or contains multiple SRTLM_Dat lines
        return false;
    }

}


//* Data file input
//* ***************************************************
BOOL CSRTLMDlg::DatFileInPut(LPCTSTR strPath)
//* ***************************************************
{
    CString strBuff;

    CStdioFile file;
    file.Open(strPath, CFile::modeRead | CFile::typeText);

    while (file.ReadString(strBuff))
    {
        //* When the desired string is found, processing begins.
        if (strBuff.Find(_T("m_iKY2")) >= 0) {
            GetPartsKY2(strBuff);
            continue;
        }
        if (strBuff.Find(_T("m_dC[")) >= 0) {
            GetParts(strBuff);
            continue;
        }
        if (strBuff.Find(_T("m_dD[")) >= 0) {
            GetParts(strBuff);
            continue;
        }
        if (strBuff.Find(_T("m_dN[")) >= 0) {
            GetParts(strBuff);
            continue;
        }
        if (strBuff.Find(_T("m_nTORIC[")) >= 0) {
            GetParts(strBuff);
            continue;
        }
        if (strBuff.Find(_T("m_dCylCV2[")) >= 0) {
            GetParts(strBuff);
            continue;
        }
        if (strBuff.Find(_T("m_dCylTheta[")) >= 0) {
            GetParts(strBuff);
            continue;
        }
    }
    file.Close();

    return TRUE;
}


//* ---------------------------------------------------
//* Sub function to extract numeric string of m_iKY2
BOOL CSRTLMDlg::GetPartsKY2(CString cStrkk_Parts)
//* ---------------------------------------------------
{
    CString strParts;
    strParts = cStrkk_Parts;

    //* Extraction of numerical value
    int iLenParts;
    iLenParts = strParts.GetLength();
    int iLenPartsAll = iLenParts;

    int  ch = '=';
    _TCHAR *pdest;
    int result;

    pdest = (_TCHAR*)_tcschr(strParts, ch);
    result = pdest - strParts + 1;

    if(pdest != NULL)     {
        iLenParts = iLenParts - result;
        strParts = strParts.Right(iLenParts);
    }

    //* If there is a comment to the right of a numeric value using “;” or “//”, cut it off
    int  ch2 = ';';
    _TCHAR *pdest2;
    int result2;
    pdest2 = (_TCHAR*)_tcschr(strParts, ch2);
    result2 = pdest2 - strParts + 1;

    if(pdest2 != NULL)     {
        iLenParts = iLenParts - result2;
        strParts = strParts.Left(iLenParts);
    }

    int  ch3 = '/';
    _TCHAR *pdest3;
    int result3;
    pdest3 = (_TCHAR*)_tcschr(strParts, ch3);
    result3 = pdest3 - strParts + 1;

    if(pdest3 != NULL)     {
        iLenParts = iLenParts - result3;
        strParts = strParts.Left(iLenParts);
    }
    m_iKY2 = _wtoi(strParts);

    return TRUE;
}


//* ---------------------------------------------------
//* Sub function to extract numeric strings such as m_dC[n], m_dD[n]....
BOOL CSRTLMDlg::GetParts(CString cStrkk_Parts)
//* ---------------------------------------------------
{
    CString strParts;
    strParts = cStrkk_Parts;

    //* Extraction of numerical value
    int iLenParts;
    iLenParts = strParts.GetLength();
    int iLenPartsAll = iLenParts;

    int  ch = '=';
    _TCHAR *pdest;
    int result;

    pdest = (_TCHAR*)_tcschr(strParts, ch);
    result = pdest - strParts + 1;

    if(pdest != NULL)     {
        iLenParts = iLenParts - result;
        strParts = strParts.Right(iLenParts);
    }

    //* If there is a comment to the right of a numeric value using “;” or “//”, cut it off
    int  ch2 = ';';
    _TCHAR *pdest2;
    int result2;
    pdest2 = (_TCHAR*)_tcschr(strParts, ch2);
    result2 = pdest2 - strParts + 1;

    if(pdest2 != NULL)     {
        iLenParts = result2 - 1;
        strParts = strParts.Left(iLenParts);
    }

    int  ch3 = '/';
    _TCHAR *pdest3;
    int result3;
    pdest3 = (_TCHAR*)_tcschr(strParts, ch3);
    result3 = pdest3 - strParts + 1;

    if(pdest3 != NULL)     {
        iLenParts = result3 - 1;
        strParts = strParts.Left(iLenParts);
    }
    m_strPartsValue = strParts;


    //* Extraction of data type and array index
    strParts = cStrkk_Parts;

    iLenParts = iLenPartsAll;

    int  ch4 = '[';
    _TCHAR *pdest4;
    int result4;
    pdest4 = (_TCHAR*)_tcschr(strParts, ch4);
    result4 = pdest4 - strParts + 1;

    if(pdest4 != NULL)     {
        iLenParts = iLenParts - result4;

        //* Type Confirmed
        m_strPartsType = strParts.Left(result4 - 1);

        strParts = strParts.Right(iLenParts);
    }

    int  ch5 = ']';
    _TCHAR *pdest5;
    int result5;
    pdest5 = (_TCHAR*)_tcschr(strParts, ch5);
    result5 = pdest5 - strParts + 1;

    if(pdest5 != NULL)     {
        iLenParts = iLenParts - result5;

        //* Confirmed array index
        m_strPartsArrayNum = strParts.Left(iLenParts);
    }

    DatToArray();

    return TRUE;
}



//* ---------------------------------------------------
//* Assigning values to arrays
BOOL CSRTLMDlg::DatToArray()
{
    if(m_strPartsType == "Pre_m_dC") {
        //* Curvature Data Obtained
        ///////////////////////////////////////////
        //*    m_dC[6] = -1.0 / 49.91652754591;
        //*    m_dC[7] = -1.0 / 100.0;
        ///////////////////////////////////////////
        m_dC[ _wtoi(m_strPartsArrayNum) ] = 1.0 / _wtof(m_strPartsValue);
        //* Backup in case the initial setup is executed
        m_dC_backUp[ _wtoi(m_strPartsArrayNum) ] = 1.0 / _wtof(m_strPartsValue);
    }

    if(m_strPartsType == "m_dD") {
        //* Obtain the distance between boundary surfaces
        ///////////////////////////////////////////
        //*    m_dD[6] = 3.0;//1.0;
        ///////////////////////////////////////////
        m_dD[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
        //* Backup in case the initial setup is executed
        m_dD_backUp[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
    }

    if(m_strPartsType == "m_dN") {
        //* Obtain the refractive index
        ///////////////////////////////////////////
        //*    m_dN[7] = 1.5;
        ///////////////////////////////////////////
        m_dN[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
        //* Backup in case the initial setup is executed
        m_dN_backUp[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
    }

    if(m_strPartsType == "m_nTORIC") {
        //* Obtain the toric surface flag
        ///////////////////////////////////////////
        //* C-1.00
        //*     m_nTORIC[6] = 1;
        //*     m_nTORIC[7] = 1;
        ///////////////////////////////////////////
        m_nTORIC[ _wtoi(m_strPartsArrayNum) ] = _wtoi(m_strPartsValue);
        m_nTORIC[ _wtoi(m_strPartsArrayNum) + 1 ] = _wtoi(m_strPartsValue);
        //* Backup in case the initial setup is executed
        m_nTORIC_backUp[ _wtoi(m_strPartsArrayNum) ] = _wtoi(m_strPartsValue);
        m_nTORIC_backUp[ _wtoi(m_strPartsArrayNum) + 1 ] = _wtoi(m_strPartsValue);
    }

    if(m_strPartsType == "Pre_m_dCylCV2") {
        //* Obtain the curvature of the toric surface
        ///////////////////////////////////////////
        //* C-1.00
        //*     m_dCylCV2[6] = -1.0 / 130.890052356021;
        //*     m_dCylCV2[7] = m_dC[7];
        ///////////////////////////////////////////
        m_dCylCV2[ _wtoi(m_strPartsArrayNum) ] = 1.0 / _wtof(m_strPartsValue);
        m_dCylCV2[ _wtoi(m_strPartsArrayNum) + 1 ] = m_dC[ _wtoi(m_strPartsArrayNum) + 1 ];
        //* Backup in case the initial setup is executed
        m_dCylCV2_backUp[ _wtoi(m_strPartsArrayNum) ] = 1.0 / _wtof(m_strPartsValue);
        m_dCylCV2_backUp[ _wtoi(m_strPartsArrayNum) + 1 ] = m_dC[ _wtoi(m_strPartsArrayNum) + 1 ];
    }

    if(m_strPartsType == "m_dCylTheta") {
        //* Obtain the (-) astigmatism axis on the toric surface
        ///////////////////////////////////////////
        //* C-1.00
        //*     m_dCylTheta[6] = 0.0;
        //*     m_dCylTheta[7] = m_dCylTheta[6];
        ///////////////////////////////////////////
        m_dCylTheta[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
        m_dCylTheta[ _wtoi(m_strPartsArrayNum) + 1 ] = m_dCylTheta[ _wtoi(m_strPartsArrayNum) ];
        //* Backup in case the initial setup is executed
        m_dCylTheta_backUp[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
        m_dCylTheta_backUp[ _wtoi(m_strPartsArrayNum) + 1 ] = m_dCylTheta[ _wtoi(m_strPartsArrayNum) ];
    }

    return TRUE;
}

//* ---------------------------------------------------
//* If All_Reset is executed after loading data
//* from a file, the saved data is assigned to the array.
BOOL CSRTLMDlg::GetBackUpFileData()
{
    switch(m_iKY2)
    {
    case 11:
        m_dC[5] = m_dC_backUp[5];
        m_dC[6] = m_dC_backUp[6];
        m_dD[5] = m_dD_backUp[5];
        m_dN[6] = m_dN_backUp[6];
        m_nTORIC[5] = m_nTORIC_backUp[5];
        m_nTORIC[6] = m_nTORIC_backUp[6];
        m_dCylCV2[5] = m_dCylCV2_backUp[5];
        m_dCylCV2[6] = m_dCylCV2_backUp[6];
        m_dCylTheta[5] = m_dCylTheta_backUp[5];
        m_dCylTheta[6] = m_dCylTheta_backUp[6];
        break;
    case 13:
        m_dC[5] = m_dC_backUp[5];
        m_dC[6] = m_dC_backUp[6];
        m_dC[7] = m_dC_backUp[7];
        m_dC[8] = m_dC_backUp[8];
        //
        m_dD[5] = m_dD_backUp[5];
        m_dD[6] = m_dD_backUp[6];
        m_dD[7] = m_dD_backUp[7];
        //
        m_dN[6] = m_dN_backUp[6];
        m_dN[7] = m_dN_backUp[7];
        m_dN[8] = m_dN_backUp[8];
        //
        m_nTORIC[5] = m_nTORIC_backUp[5];
        m_nTORIC[6] = m_nTORIC_backUp[6];
        m_nTORIC[7] = m_nTORIC_backUp[7];
        m_nTORIC[8] = m_nTORIC_backUp[8];
        //
        m_dCylCV2[5] = m_dCylCV2_backUp[5];
        m_dCylCV2[6] = m_dCylCV2_backUp[6];
        m_dCylCV2[7] = m_dCylCV2_backUp[7];
        m_dCylCV2[8] = m_dCylCV2_backUp[8];
        //
        m_dCylTheta[5] = m_dCylTheta_backUp[5];
        m_dCylTheta[6] = m_dCylTheta_backUp[6];
        m_dCylTheta[7] = m_dCylTheta_backUp[7];
        m_dCylTheta[8] = m_dCylTheta_backUp[8];
        break;
    case 15:
        m_dC[5] = m_dC_backUp[5];
        m_dC[6] = m_dC_backUp[6];
        m_dC[7] = m_dC_backUp[7];
        m_dC[8] = m_dC_backUp[8];
        m_dC[9] = m_dC_backUp[9];
        m_dC[10] = m_dC_backUp[10];
        //
        m_dD[5] = m_dD_backUp[5];
        m_dD[6] = m_dD_backUp[6];
        m_dD[7] = m_dD_backUp[7];
        m_dD[8] = m_dD_backUp[8];
        m_dD[9] = m_dD_backUp[9];
        //
        m_dN[6] = m_dN_backUp[6];
        m_dN[7] = m_dN_backUp[7];
        m_dN[8] = m_dN_backUp[8];
        m_dN[9] = m_dN_backUp[9];
        m_dN[10] = m_dN_backUp[10];
        //
        m_nTORIC[5] = m_nTORIC_backUp[5];
        m_nTORIC[6] = m_nTORIC_backUp[6];
        m_nTORIC[7] = m_nTORIC_backUp[7];
        m_nTORIC[8] = m_nTORIC_backUp[8];
        m_nTORIC[9] = m_nTORIC_backUp[9];
        m_nTORIC[10] = m_nTORIC_backUp[10];
        //
        m_dCylCV2[5] = m_dCylCV2_backUp[5];
        m_dCylCV2[6] = m_dCylCV2_backUp[6];
        m_dCylCV2[7] = m_dCylCV2_backUp[7];
        m_dCylCV2[8] = m_dCylCV2_backUp[8];
        m_dCylCV2[9] = m_dCylCV2_backUp[9];
        m_dCylCV2[10] = m_dCylCV2_backUp[10];
        //
        m_dCylTheta[5] = m_dCylTheta_backUp[5];
        m_dCylTheta[6] = m_dCylTheta_backUp[6];
        m_dCylTheta[7] = m_dCylTheta_backUp[7];
        m_dCylTheta[8] = m_dCylTheta_backUp[8];
        m_dCylTheta[9] = m_dCylTheta_backUp[9];
        m_dCylTheta[10] = m_dCylTheta_backUp[10];
        break;
    }

    return TRUE;
}

//* ---------------------------------------------------
//* Obtain the lens data to be loaded by default
BOOL CSRTLMDlg::DefaultDataIn()
{
#define CHAR_LEN (256)
    DIR *dir;
    struct dirent *dp;

    char pattern[] = "#";
    char tgt[CHAR_LEN];
    memset(tgt, '0', CHAR_LEN);
    char *find; /* For storing the address where the pattern exists */
    int flgFind = 0;
    TCHAR *cdir;

    //* Obtain the current directory
    cdir = new TCHAR[CHAR_LEN];
    GetCurrentDirectory(CHAR_LEN, cdir);
    //* Specify the [dat] directory one level up
    *(wcsrchr(cdir, L'\\')) = 0;
    wcscat_s(cdir, CHAR_LEN, _T("\\dat"));

    //* I wanted to process the following in c++,
    //* but it didn't work out, so I decided to process it in c.

    //* Search for file beginning with [#].
    //* If found, process it as startup lens data.
    char dst[CHAR_LEN];
    ZeroMemory(&dst[0], CHAR_LEN);
    WideCharToMultiByte(CP_ACP, 0, &cdir[0], lstrlen(cdir), &dst[0], CHAR_LEN, NULL, NULL);
    delete[] cdir;

    dir = opendir(dst);
    if (dir == NULL) {
        m_bFileReadFlg = FALSE;
        m_bSyokika = true;
        return FALSE;
    }

    dp = readdir(dir);
    while (dp != NULL) {
        printf("%s\n", dp->d_name);

        /* Search forthe  pattern in text */
        find = strstr(dp->d_name, pattern);

        if (find != NULL) {
            /* When the pattern exists */
            flgFind = 1;
            strcpy_s(tgt, CHAR_LEN, dp->d_name);
            break;
        }

        dp = readdir(dir);
    }
    if (dir != NULL) {
        closedir(dir);
    }
    if (flgFind != 1) {
        DataInBefore(); //* Initialization of arrays, etc.
        return FALSE;
    }
    strcat_s(dst, CHAR_LEN, "\\");
    strcat_s(dst, CHAR_LEN, tgt);
    m_strSRTLM_FilePath = dst;

    //* ++++++++++++++++++++++++++++++++++++++++++++++++++++
    //* Check whether the data file is an SRTLM data file
    //* and whether it consists of one set of data
    //* ++++++++++++++++++++++++++++++++++++++++++++++++++++
    if (!GetSRTLM_Dat(m_strSRTLM_FilePath)) {
        AfxMessageBox(_T("This data file is not SRTLM data or contains multiple data sets."));
        m_bFileReadFlg = FALSE;
        m_bSyokika = true;
        return FALSE; //* Cannot be processed by SRTLM
    }

    DataInBefore(); //* Initialization of arrays, etc.

    //* +++++++++++++++++++++++++++++++
    //* Obtain the SRTLM Data
    //* +++++++++++++++++++++++++++++++
    DatFileInPut(m_strSRTLM_FilePath);

    m_bFileReadFlg = TRUE;

    m_bSyokika = true;

    return true;
}