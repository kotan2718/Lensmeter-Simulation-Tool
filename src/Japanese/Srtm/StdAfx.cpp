
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


// stdafx.cpp : 標準インクルードファイルを含むソース ファイル
//              Wvr.pch : 生成されるプリコンパイル済ヘッダー
//              stdafx.obj : 生成されるプリコンパイル済タイプ情報

#include "stdafx.h"

//* /////////////////////////////////////////////////////////////////////////
//* ダブル -> 文字列変換, 四捨五入 : STR$(数値,cut)
//* 新処理（四捨五入）
LPTSTR str_cvt(double sn, int cut)
//* /////////////////////////////////////////////////////////////////////////
{
//* 返却文字列
static _TCHAR ds[80];
    //* フォーマット用文字列 "%.xxxf" を作る
    CString cStrFormatBuf;    //* 充分な桁数をとる(+8)
    cStrFormatBuf.Format(_T(".%df"), cut + 8);
    cStrFormatBuf = _T("%") + cStrFormatBuf;
CString cStrBuf;
    cStrBuf.Format(cStrFormatBuf, sn);

CString cStrSeisu;
    cStrSeisu = cStrBuf.Left(cStrBuf.Find(_T(".")));
BOOL minusFlg = FALSE;
    if (cStrSeisu.Left(1) == _T("-")) {
        minusFlg = TRUE;
        cStrSeisu = cStrSeisu.Mid(1);
    }
    long seisu = _wtol(cStrSeisu);
CString cStrShosu;
    cStrShosu = _T("0") + cStrBuf.Mid(cStrBuf.Find(_T(".")), cut + 1);
    double shosu = _wtof(cStrShosu);
    //* 四捨五入する桁の文字を取ってくる
CString cStrControl = cStrBuf.Mid(cStrBuf.Find(_T(".")) + 1 + cut, 1);
    //*
    if (cut < 1) {
        if (_wtoi(cStrControl) >= 5)
            seisu ++;
        cStrBuf.Format(_T("%d"), seisu);
    }
    else {
        //* 四捨五入
        if (_wtoi(cStrControl) >= 5) {
            shosu = shosu * pow(10.0, (double)cut);
            shosu = shosu + 1.0;
            shosu = shosu / pow(10.0, (double)cut);
        }
        double dret;
            dret = (double)seisu + shosu;
        if (shosu == 0.0)
            cStrBuf.Format(_T("%d"), seisu);
        else {
            cStrBuf.Format(_T("%f"), dret);
            cStrBuf.TrimRight(_T("0"));
        }
    }
    if (minusFlg) {
        cStrBuf = _T("-") + cStrBuf;
    }

    //wcscpy_s(ds, sizeof(ds), cStrBuf);
    _tcscpy(ds, cStrBuf);
    return ds;
}


