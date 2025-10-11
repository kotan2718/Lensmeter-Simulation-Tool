
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


// stdafx.cpp : Source files including standard include files
//              Wvr.pch : Generated precompiled header
//              stdafx.obj : Generated precompiled type information

#include "stdafx.h"

//* /////////////////////////////////////////////////////////////////////////
//* double -> Convert to string, Rounding : STR$(numerical value, cut)
//*  New processing (Rounding)
LPTSTR str_cvt(double sn, int cut)
//* /////////////////////////////////////////////////////////////////////////
{
//* Returned string
static _TCHAR ds[80];
    //* Create a format string "%.xxxf"
    CString cStrFormatBuf;    // Ensure sufficient digit length(+8)
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
    //* Retrieve the character from the digit for rounding
CString cStrControl = cStrBuf.Mid(cStrBuf.Find(_T(".")) + 1 + cut, 1);
    //*
    if (cut < 1) {
        if (_wtoi(cStrControl) >= 5)
            seisu ++;
        cStrBuf.Format(_T("%d"), seisu);
    }
    else {
        // Rounding
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


