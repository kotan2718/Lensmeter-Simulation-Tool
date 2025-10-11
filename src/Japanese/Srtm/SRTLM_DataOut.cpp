
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


// SRTLMDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "SRTLM.h"
#include "SRTLMDlg.h"
#include "GlobalDef.h"
#include "Version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////


void CSRTLMDlg::OnButtonFileOut()
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

    //* ファイルダイヤログの構築（初期設定する）
    CFileDialog dlg(
        FALSE,          //* BOOL bOpenFileDialog,
        _T("srt"),      //* LPCTSTR lpszDefExt = NULL,
        _T("SrtlmDat"), //* LPCTSTR lpszFileName = NULL,
        OFN_NONETWORKBUTTON | OFN_NOTESTFILECREATE | OFN_OVERWRITEPROMPT, //* DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        _T("SRTLM Files (*.srt)|*.srt|All Files (*.*)|*.*||"),            //* LPCTSTR lpszFilter = NULL,
        NULL);                                                            //* CWnd* pParentWnd = NULL);
    //* ファイルダイヤログを開く
    if (dlg.DoModal() == IDCANCEL) {
        return;
    }
    //*
    //* ファイルダイヤログがＯＫで戻ってきたとき
    //*
    m_strSRTLM_FilePath = dlg.m_ofn.lpstrFile;

    //*
    //* ファイルの書き込み
    //
    //* +++++++++++++++++++++++++++++++
    //* SRTLM データの取得
    //* +++++++++++++++++++++++++++++++
    DatFileOutPut(m_strSRTLM_FilePath);

    m_bFileWriteFlg = TRUE;

    m_bSyokika = false;
    MainProgram();
}

//* ===================================================
//* 変換ファイル出力
BOOL CSRTLMDlg::DatFileOutPut(LPCTSTR fname)
//* ===================================================
{
    //* Title
    CString strTitle = "//*  SRTLM_Dat < Skew Ray Trace Lens Meter Version > Ver. ";
    strTitle += STR_VERSION;
    strTitle += " by Kazuo Kawamura\n";

    CString strWrite;

    CStdioFile file3;
    file3.Open(fname, CFile::modeCreate |  CFile::modeWrite | CFile::typeText);

    strWrite.Format(_T("//* \n"));
    file3.WriteString(strWrite);
    strWrite.Format(_T("//* =================================================================================\n"));
    file3.WriteString(strWrite);
    strWrite.Format(strTitle);
    file3.WriteString(strWrite);
    strWrite.Format(_T("//* =================================================================================\n"));
    file3.WriteString(strWrite);
    strWrite.Format(_T("//* \n"));
    file3.WriteString(strWrite);

    strWrite.Format(_T("//* [ number of surfaces : m_iKY2 ] \n"));
    file3.WriteString(strWrite);
    strWrite.Format(_T("m_iKY2 = %d \n"), m_iKY2);
    file3.WriteString(strWrite);
    strWrite.Format(_T("\n"));
    file3.WriteString(strWrite);

    switch(m_iKY2)
    {
    case 11:
        strWrite.Format(_T("//* [ radius of curvature : r ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[5] = %.12f \n"), 1.0 / m_dC[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[6] = %.12f \n"), 1.0 / m_dC[6]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ distance between interfaces : m_dD ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dD[5] = %.12f \n"), m_dD[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ refractive index : m_dN ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dN[6] = %.12f \n"), m_dN[6]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ toric face flag : m_nTORIC ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_nTORIC[5] = %d \n"), m_nTORIC[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ toric surface Max radius of curvature : m_dCylCV2 ]  \n"));
        file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dCylCV2[5] = %.12f \n"), 1.0 / m_dCylCV2[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ principal longitudinal direction of toric plane : m_dCylTheta ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dCylTheta[5] = %f \n"), m_dCylTheta[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        break;

    case 13:
        strWrite.Format(_T("//* [radius of curvature : r] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[5] = %.12f \n"), 1.0 / m_dC[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[6] = %.12f \n"),  1.0 / m_dC[6]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[7] = %.12f \n"),  1.0 / m_dC[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[8] = %.12f \n"),  1.0 / m_dC[8]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ distance between interfaces : m_dD ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dD[5] = %.12f \n"), m_dD[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dD[6] = %.12f \n"), m_dD[6]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dD[7] = %.12f \n"), m_dD[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ refractive index : m_dN ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dN[6] = %.12f \n"), m_dN[6]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dN[7] = %.12f \n"), m_dN[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dN[8] = %.12f \n"), m_dN[8]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ toric face flag : m_nTORIC ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_nTORIC[5] = %d \n"), m_nTORIC[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_nTORIC[7] = %d \n"), m_nTORIC[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ toric surface Max radius of curvature : m_dCylCV2 ]  \n"));
        file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dCylCV2[5] = %.12f \n"),  1.0 / m_dCylCV2[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dCylCV2[7] = %.12f \n"),  1.0 / m_dCylCV2[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ principal longitudinal direction of toric plane : m_dCylTheta ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dCylTheta[5] = %f \n"), m_dCylTheta[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dCylTheta[7] = %f \n"), m_dCylTheta[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        break;

    case 15:
        strWrite.Format(_T("//* [radius of curvature : r] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[5] = %.12f \n"),  1.0 / m_dC[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[6] = %.12f \n"),  1.0 / m_dC[6]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[7] = %.12f \n"),  1.0 / m_dC[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[8] = %.12f \n"),  1.0 / m_dC[8]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[9] = %.12f \n"),  1.0 / m_dC[9]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dC[10] = %.12f \n"),  1.0 / m_dC[10]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ distance between interfaces : m_dD ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dD[5] = %.12f \n"), m_dD[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dD[6] = %.12f \n"), m_dD[6]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dD[7] = %.12f \n"), m_dD[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dD[8] = %.12f \n"), m_dD[8]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dD[9] = %.12f \n"), m_dD[9]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);


        strWrite.Format(_T("//* [ refractive index : m_dN ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dN[6] = %.12f \n"), m_dN[6]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dN[7] = %.12f \n"), m_dN[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dN[8] = %.12f \n"), m_dN[8]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dN[9] = %.12f \n"), m_dN[9]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dN[10] = %.12f \n"), m_dN[10]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ toric face flag : m_nTORIC ] \n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_nTORIC[5] = %d \n"), m_nTORIC[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_nTORIC[7] = %d \n"), m_nTORIC[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_nTORIC[9] = %d \n"), m_nTORIC[9]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ toric surface Max radius of curvature : m_dCylCV2 ]  \n"));
        file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dCylCV2[5] = %.12f \n"),  1.0 / m_dCylCV2[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dCylCV2[7] = %.12f \n"),  1.0 / m_dCylCV2[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("Pre_m_dCylCV2[9] = %.12f \n"),  1.0 / m_dCylCV2[9]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        strWrite.Format(_T("//* [ principal longitudinal direction of toric plane : m_dCylTheta ]\n"));
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dCylTheta[5] = %f \n"), m_dCylTheta[5]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dCylTheta[7] = %f \n"), m_dCylTheta[7]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("m_dCylTheta[9] = %f \n"), m_dCylTheta[9]);
            file3.WriteString(strWrite);
        strWrite.Format(_T("\n"));
        file3.WriteString(strWrite);

        break;
    }

    file3.Close();
    return TRUE;
}



