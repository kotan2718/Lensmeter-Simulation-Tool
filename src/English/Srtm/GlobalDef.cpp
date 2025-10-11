
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


#include "stdafx.h"
#include "GlobalDef.h"

CDC  g_memDC1;      // Declaration: Memory DC (Virtual Screen)
CDC  g_memDC2;      // Declaration: Memory DC (Virtual Screen)
CStatic g_pict1;    // Declaration: Picture Control DDX Variables
CStatic g_pict2;    // Declaration: Picture Control DDX Variables

// Width and height of the picture box
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
