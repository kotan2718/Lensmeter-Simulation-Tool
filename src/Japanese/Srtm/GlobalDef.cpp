
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#include "stdafx.h"
#include "GlobalDef.h"

CDC  g_memDC1;        // 宣言: メモリDC(仮想画面)
CDC  g_memDC2;        // 宣言: メモリDC(仮想画面)
CStatic g_pict1;    // 宣言: ピクチャーコントロールのDDX変数
CStatic g_pict2;    // 宣言: ピクチャーコントロールのDDX変数

// ピクチャーボックスの幅と高さ
long g_lPictureBoxSizeX, g_lPictureBoxSizeY;
double g_dWindowPosLeft, g_dWindowPosRight;
double g_dWindowPosTop, g_dWindowPosBottom;

long g_lPictureBoxSizeX2, g_lPictureBoxSizeY2;
double g_dWindowPosLeft2, g_dWindowPosRight2;
double g_dWindowPosTop2, g_dWindowPosBottom2;


CGlobalDef::CGlobalDef()
{
}


CGlobalDef::~CGlobalDef()
{
}
