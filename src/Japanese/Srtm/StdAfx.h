
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00 //* Windows 10 以上
#endif
// stdafx.h : 標準のシステム インクルード ファイル、
//            または参照回数が多く、かつあまり変更されない
//            プロジェクト専用のインクルード ファイルを記述します。
//

#if !defined(AFX_STDAFX_H__47A0BEC3_E745_4790_B267_7A2A21F0F3D5__INCLUDED_)
#define AFX_STDAFX_H__47A0BEC3_E745_4790_B267_7A2A21F0F3D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN        // Windows ヘッダーから殆ど使用されないスタッフを除外します。

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdisp.h>        // MFC のオートメーション クラス
#include <afxdtctl.h>        // MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>            // MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT

//* エディットボックス入力コントロール
#include "DpNumCtrl.h"

//* ダブル -> 文字列変換, 四捨五入 : STR$(数値,cut)
//* 新処理（四捨五入）
LPTSTR str_cvt(double sn, int cut);

//* 二乗の定義 これくらいしかなかった (^_^;
#define SQUARE(x)    ((x) * (x))

//* ラジアンの定義
#define RAD(x)    ((x) * 3.14159265358979 / 180.0)

#define KK_PI    3.14159265358979 //* 3238462643383279

//* コロナの数
#define CORONA_NUM        36
//* 1個のコロナを描くのに必要な光線数
#define CORONA_RAY_CNT    11

//* レンズ構成の境界面の総数の上限
#define KOUSEIMEN_MAX    15

//* error、及び warning
#define ERR_RAY_TRACE            100    //* 1: 追跡不可能, 0: 特定なし, 0: SkewRayTrace
#define ERR_RAY_TRACE_SPH        110    //* 1: 追跡不可能, 1: 共軸かつ球面, 0: SRTSph
#define ERR_RAY_TRACE_TORIC      121    //* 1: 追跡不可能, 2: 非球面或は非光軸, 1: SRTToric
#define ERR_RAY_TRACE_ASPH       122    //* 1: 追跡不可能, 2: 非球面或は非光軸, 2: SRTAsph
#define ERR_RAY_TRACE_ASPH2      124    //* 1: 追跡不可能, 2: 非球面或は非光軸, 4: SRTAsph2
#define ERR_RAY_TRACE_HENSPH     123    //* 1: 追跡不可能, 2: 非球面或は非光軸, 3: SRTHenSph
#define WNG_RAY_HEIGHT_OVER      200    //* 追跡している光線が有効径から外れた


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STDAFX_H__47A0BEC3_E745_4790_B267_7A2A21F0F3D5__INCLUDED_)