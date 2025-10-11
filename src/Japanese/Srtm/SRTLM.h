
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


// SRTLM.h : SRTLM アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_SRTLM_H__856265B9_C462_4623_9EC9_A6755D3F35E2__INCLUDED_)
#define AFX_SRTLM_H__856265B9_C462_4623_9EC9_A6755D3F35E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"        // メイン シンボル

#include  <stdio.h>
#include  <math.h>
#include  <stdlib.h>

/////////////////////////////////////////////////////////////////////////////
// CSRTLMApp:
// このクラスの動作の定義に関しては SRTLM.cpp ファイルを参照してください。
//

class CSRTLMApp : public CWinApp
{
public:
    CSRTLMApp();

// オーバーライド
    // ClassWizard は仮想関数のオーバーライドを生成します。
    //{{AFX_VIRTUAL(CSRTLMApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// インプリメンテーション

    //{{AFX_MSG(CSRTLMApp)
        // メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
        //        この位置に生成されるコードを編集しないでください。
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SRTLM_H__856265B9_C462_4623_9EC9_A6755D3F35E2__INCLUDED_)
