
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
#include "msdirent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

void CSRTLMDlg::OnButtonFileIn() 
{
    // TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
#define CHAR_LEN (256)
    TCHAR *cdir;

    //* 現在のディレクトリを取得
    cdir = new TCHAR[CHAR_LEN];
    GetCurrentDirectory(CHAR_LEN, cdir);
    //* 1つ上の階層のdatディレクトリを指定
    *(wcsrchr(cdir, L'\\')) = 0;
    wcscat_s(cdir, CHAR_LEN, _T("\\dat"));

    //* ファイルダイヤログの構築（初期設定する）
    CFileDialog dlg(
        TRUE,    //* BOOL bOpenFileDialog,
        NULL,    //* LPCTSTR lpszDefExt = NULL,
        NULL,    //* LPCTSTR lpszFileName = NULL,
        OFN_NONETWORKBUTTON | OFN_NOTESTFILECREATE | OFN_OVERWRITEPROMPT, //* DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        _T("SRTLM Files (*.srt)|*.srt|All Files (*.*)|*.*||"),            //* LPCTSTR lpszFilter = NULL,
        NULL);                                                            //* CWnd* pParentWnd = NULL);
    //* ファイルダイヤログを開く
    dlg.m_ofn.lpstrInitialDir = cdir;

    if (dlg.DoModal() == IDCANCEL) {
        delete[] cdir;
        return;
    }

    //
    //* ファイルダイヤログがＯＫで戻ってきたとき
    //
    m_strSRTLM_FilePath = dlg.m_ofn.lpstrFile;

    delete[] cdir;

    //
    //* ファイルの中を読み、データを取得する。
    //

    //* ++++++++++++++++++++++++++++++++++++++++++++++++++++
    //* データファイルが SRTLM のデータファイルかどうか，
    //* また１セットのデータで構成されているかどうかを調べる
    //* ++++++++++++++++++++++++++++++++++++++++++++++++++++
    if (!GetSRTLM_Dat(m_strSRTLM_FilePath)) {
        AfxMessageBox(_T("このデータファイルは SRTLM のデータではないか，或いは複数のデータがセットされています。"));
        return;
    }

    DataInBefore(); //* 配列などの初期化

    //* +++++++++++++++++++++++++++++++
    //* SRTLM データの取得
    //* +++++++++++++++++++++++++++++++
    DatFileInPut(m_strSRTLM_FilePath);
    
    m_bFileReadFlg = TRUE;
    
    m_bSyokika = true;
    OnStart();
}


//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++
//* ファイルの中を読み、SRTLM_Dat行があるかどうかを調べる
BOOL CSRTLMDlg::GetSRTLM_Dat(LPCTSTR strPath)
//* ++++++++++++++++++++++++++++++++++++++++++++++++++++++
{
    
    //* SRTLM_Dat行が1行だけ存在するかどうかを示すフラグ
    BOOL bSRTLM_DatFlg = FALSE;
    
    //* SRTLM_Dat の数の初期値
    int iSRTLM_DatNum = 0;
    
    CStdioFile file;
    if (!file.Open(strPath, CFile::modeRead | CFile::typeText)) {
        return FALSE;
    }
    //
    //* データの読み込み開始
    //
    CString m_cStrDispBuf;  //* 表示用文字列バッファ
    CString cStrBuf;        //* 読み込み用文字列バッファ
    while (file.ReadString(cStrBuf))
    {
        //* 表示用に退避
        m_cStrDispBuf = cStrBuf;
        
        //* SRTLM_Dat行を見つける
        if (cStrBuf.Find(_T("SRTLM_Dat")) >= 0) {
            iSRTLM_DatNum++;
            continue;
        }
    }
    file.Close();

    if (iSRTLM_DatNum == 1)    bSRTLM_DatFlg = true;

    if (bSRTLM_DatFlg) {
        //* SRTLM_Datが１つだけのファイルの場合
        return true;
    }
    else {
        //* SRTLM_Dat行が存在しないか，複数のSRTLM_Dat行が存在するファイルの場合
        return false;
    }

}


//* データファイル入力
//* ***************************************************
BOOL CSRTLMDlg::DatFileInPut(LPCTSTR strPath)
//* ***************************************************
{
    CString strBuff;

    CStdioFile file;
    file.Open(strPath, CFile::modeRead | CFile::typeText);

    while (file.ReadString(strBuff))
    {
        //* 希望の文字列が見つかったら処理開始
        if (strBuff.Find(_T("m_iKY2")) >= 0) {
            GetPartsKY2(strBuff);
            continue;
        }
        //* 20251027 (Ver.2.24.0) m_bFccf1523Flg
        //* Front Curve : Whether to fix to the refractive index of crown glass
        if (strBuff.Find(_T("m_Check_Fccf1523")) >= 0) {
            GetParts1523(strBuff);
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
//* m_iKY2 の数値文字列を抽出する子関数
BOOL CSRTLMDlg::GetPartsKY2(CString cStrkk_Parts)
//* ---------------------------------------------------
{
    CString strParts;
    strParts = cStrkk_Parts;

    //* 数値の抜き取り
    int iLenParts;
    iLenParts = strParts.GetLength();
    int iLenPartsAll = iLenParts;

    int  ch = '=';
    _TCHAR *pdest;
    int result;

    pdest = (_TCHAR*)_tcschr(strParts, ch);
    result = pdest - strParts + 1;

    if (pdest != NULL) {
        iLenParts = iLenParts - result;
        strParts = strParts.Right(iLenParts);
    }

    //* 数値の右に ";" 或いは "//" でコメントがあった場合にそれをカットする
    int  ch2 = ';';
    _TCHAR *pdest2;
    int result2;
    pdest2 = (_TCHAR*)_tcschr(strParts, ch2);
    result2 = pdest2 - strParts + 1;

    if (pdest2 != NULL) {
        iLenParts = iLenParts - result2;
        strParts = strParts.Left(iLenParts);
    }

    int  ch3 = '/';
    _TCHAR *pdest3;
    int result3;
    pdest3 = (_TCHAR*)_tcschr(strParts, ch3);
    result3 = pdest3 - strParts + 1;

    if (pdest3 != NULL) {
        iLenParts = iLenParts - result3;
        strParts = strParts.Left(iLenParts);
    }
    m_iKY2 = _wtoi(strParts);

    return TRUE;
}


//* 20251027 (Ver.2.24.0) m_bFccf1523Flg
//* Front Curve : Whether to fix to the refractive index of crown glass
//* ---------------------------------------------------
//* m_bFccf1523Flg の数値文字列を抽出する子関数
BOOL CSRTLMDlg::GetParts1523(CString cStrkk_Parts)
//* ---------------------------------------------------
{
    CString strParts;
    strParts = cStrkk_Parts;

    //* 数値の抜き取り
    int iLenParts;
    iLenParts = strParts.GetLength();
    int iLenPartsAll = iLenParts;

    int  ch = '=';
    _TCHAR *pdest;
    int result;

    pdest = (_TCHAR*)_tcschr(strParts, ch);
    result = pdest - strParts + 1;

    if (pdest != NULL) {
        iLenParts = iLenParts - result;
        strParts = strParts.Right(iLenParts);
    }

    //* 数値の右に ";" 或いは "//" でコメントがあった場合にそれをカットする
    int  ch2 = ';';
    _TCHAR *pdest2;
    int result2;
    pdest2 = (_TCHAR*)_tcschr(strParts, ch2);
    result2 = pdest2 - strParts + 1;

    if (pdest2 != NULL) {
        iLenParts = iLenParts - result2;
        strParts = strParts.Left(iLenParts);
    }

    int  ch3 = '/';
    _TCHAR *pdest3;
    int result3;
    pdest3 = (_TCHAR*)_tcschr(strParts, ch3);
    result3 = pdest3 - strParts + 1;

    if (pdest3 != NULL) {
        iLenParts = iLenParts - result3;
        strParts = strParts.Left(iLenParts);
    }

    m_bFccf1523Flg = _wtoi(strParts);

    return TRUE;
}

//* ---------------------------------------------------
//* 指定の数値文字列を抽出する子関数
BOOL CSRTLMDlg::GetParts(CString cStrkk_Parts)
//* ---------------------------------------------------
{
    CString strParts;
    strParts = cStrkk_Parts;

    //* 数値の抜き取り
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
    
    //数値の右に ";" 或いは "//" でコメントがあった場合にそれをカットする
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


    //* データの種類と配列番号の抜き取り
    strParts = cStrkk_Parts;

    iLenParts = iLenPartsAll;

    int  ch4 = '[';
    _TCHAR *pdest4;
    int result4;
    pdest4 = (_TCHAR*)_tcschr(strParts, ch4);
    result4 = pdest4 - strParts + 1;

    if(pdest4 != NULL)     {
        iLenParts = iLenParts - result4;

        //* タイプ確定
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

        //* 配列番号確定
        m_strPartsArrayNum = strParts.Left(iLenParts);
    }
    
    DatToArray();

    return TRUE;
}



//* ---------------------------------------------------
//* 数値を配列に代入
BOOL CSRTLMDlg::DatToArray()
{
    if(m_strPartsType == "Pre_m_dC") {
        //* 曲率データ取得
        ///////////////////////////////////////////
        //*    m_dC[6] = -1.0 / 49.91652754591;
        //*    m_dC[7] = -1.0 / 100.0;
        ///////////////////////////////////////////
        m_dC[ _wtoi(m_strPartsArrayNum) ] = 1.0 / _wtof(m_strPartsValue);
        //* 初期設定が実行された場合のバックアップ
        m_dC_backUp[ _wtoi(m_strPartsArrayNum) ] = 1.0 / _wtof(m_strPartsValue);
    }

    if(m_strPartsType == "m_dD") {
        //* 境界面間距離の取得
        ///////////////////////////////////////////
        //*    m_dD[6] = 3.0;//1.0;
        ///////////////////////////////////////////
        m_dD[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
        //* 初期設定が実行された場合のバックアップ
        m_dD_backUp[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
    }

    if(m_strPartsType == "m_dN") {
        //* 屈折率の取得
        ///////////////////////////////////////////
        //*    m_dN[7] = 1.5;
        ///////////////////////////////////////////
        m_dN[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
        //* 初期設定が実行された場合のバックアップ
        m_dN_backUp[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
    }

    if(m_strPartsType == "m_nTORIC") {
        //* トーリック面のフラグの取得
        ///////////////////////////////////////////
        //* C-1.00
        //*     m_nTORIC[6] = 1;
        //*     m_nTORIC[7] = 1;
        ///////////////////////////////////////////
        m_nTORIC[ _wtoi(m_strPartsArrayNum) ] = _wtoi(m_strPartsValue);
        m_nTORIC[ _wtoi(m_strPartsArrayNum) + 1 ] = _wtoi(m_strPartsValue);
        //* 初期設定が実行された場合のバックアップ
        m_nTORIC_backUp[ _wtoi(m_strPartsArrayNum) ] = _wtoi(m_strPartsValue);
        m_nTORIC_backUp[ _wtoi(m_strPartsArrayNum) + 1 ] = _wtoi(m_strPartsValue);
    }

    if(m_strPartsType == "Pre_m_dCylCV2") {
        //* トーリック面の曲率の取得
        ///////////////////////////////////////////
        //* C-1.00
        //*     m_dCylCV2[6] = -1.0 / 130.890052356021;
        //*     m_dCylCV2[7] = m_dC[7];
        ///////////////////////////////////////////
        m_dCylCV2[ _wtoi(m_strPartsArrayNum) ] = 1.0 / _wtof(m_strPartsValue);
        m_dCylCV2[ _wtoi(m_strPartsArrayNum) + 1 ] = m_dC[ _wtoi(m_strPartsArrayNum) + 1 ];
        //* 初期設定が実行された場合のバックアップ
        m_dCylCV2_backUp[ _wtoi(m_strPartsArrayNum) ] = 1.0 / _wtof(m_strPartsValue);
        m_dCylCV2_backUp[ _wtoi(m_strPartsArrayNum) + 1 ] = m_dC[ _wtoi(m_strPartsArrayNum) + 1 ];
    }

    if(m_strPartsType == "m_dCylTheta") {
        //* トーリック面の(-)乱視軸の取得
        ///////////////////////////////////////////
        //* C-1.00
        //*     m_dCylTheta[6] = 0.0;
        //*     m_dCylTheta[7] = m_dCylTheta[6];
        ///////////////////////////////////////////
        m_dCylTheta[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
        m_dCylTheta[ _wtoi(m_strPartsArrayNum) + 1 ] = m_dCylTheta[ _wtoi(m_strPartsArrayNum) ];
        //* 初期設定が実行された場合のバックアップ
        m_dCylTheta_backUp[ _wtoi(m_strPartsArrayNum) ] = _wtof(m_strPartsValue);
        m_dCylTheta_backUp[ _wtoi(m_strPartsArrayNum) + 1 ] = m_dCylTheta[ _wtoi(m_strPartsArrayNum) ];
    }

    return TRUE;
}

//* ---------------------------------------------------
//* ファイルからデータを呼び込んだ後に，
//* All_Reset が実行された場合に，保存してあったデータを
//* 配列に代入する
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

    //成功
    return TRUE;
}

//* ---------------------------------------------------
//* デフォルトで読み込むレンズデータを取得する
BOOL CSRTLMDlg::DefaultDataIn()
{
#define CHAR_LEN (256)
    DIR *dir;
    struct dirent *dp;

    char pattern[] = "#";
    char tgt[CHAR_LEN];
    memset(tgt, '0', CHAR_LEN);
    char *find; /* パターンの存在する位置のアドレス格納用 */
    int flgFind = 0;
    TCHAR *cdir;

    //* 現在のディレクトリを取得
    cdir = new TCHAR[CHAR_LEN];
    GetCurrentDirectory(CHAR_LEN, cdir);
    //* 1つ上の階層のdatディレクトリを指定
    *(wcsrchr(cdir, L'\\')) = 0;
    wcscat_s(cdir, CHAR_LEN, _T("\\dat"));

    //* 以下、c++で処理したかったが、うまく行かなかったので、
    //* cで処理することにした

    //* 先頭に[#]がついたファイルを検索する
    //* 見つかったら起動時のレンズデータとして処理する
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

        /* textからpatternを検索 */
        find = strstr(dp->d_name, pattern);

        if (find != NULL) {
            /* パターンが存在する場合 */
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
        DataInBefore(); //* 配列などの初期化
        return FALSE;
    }
    strcat_s(dst, CHAR_LEN, "\\");
    strcat_s(dst, CHAR_LEN, tgt);
    m_strSRTLM_FilePath = dst;

    //* ++++++++++++++++++++++++++++++++++++++++++++++++++++
    //* データファイルが SRTLM のデータファイルかどうか，
    //* また１セットのデータで構成されているかどうかを調べる
    //* ++++++++++++++++++++++++++++++++++++++++++++++++++++
    if (!GetSRTLM_Dat(m_strSRTLM_FilePath)) {
        AfxMessageBox(_T("このデータファイルは SRTLM のデータではないか，或いは複数のデータがセットされています。"));
        m_bFileReadFlg = FALSE;
        m_bSyokika = true;
        return FALSE; //* SRTLM で処理できない
    }

    DataInBefore(); //* 配列などの初期化

    //* +++++++++++++++++++++++++++++++
    //* SRTLM データの取得
    //* +++++++++++++++++++++++++++++++
    DatFileInPut(m_strSRTLM_FilePath);
    
    //* ファイル選択前にＯＫボタンが押されたときのエラー回避
    //* ファイルが正しく選択されたので "WvrDlgCtrl::OnOK()" で
    //* ＯＫボタンが押されてもエラー回避は行われない
    m_bFileReadFlg = TRUE;
    
    m_bSyokika = true;

    return true;
}