
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00 //* Windows 10 or later
#endif

// stdafx.h : Describe standard system include files, or project-specific include files that
//            are referenced frequently and rarely modified.
//

#if !defined(AFX_STDAFX_H__47A0BEC3_E745_4790_B267_7A2A21F0F3D5__INCLUDED_)
#define AFX_STDAFX_H__47A0BEC3_E745_4790_B267_7A2A21F0F3D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN        // Exclude rarely used staff from the Windows header.

#include <afxwin.h>         // MFC Core and Standard Components
#include <afxext.h>         // MFC Extensions
#include <afxdisp.h>        // MFC Automation Classes
#include <afxdtctl.h>        // MFC Internet Explorer 4 Common Controls Support
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>            // MFC Windows Common Controls Support
#endif // _AFX_NO_AFXCMN_SUPPORT

//* Edit box input control
#include "DpNumCtrl.h"

//* double -> Convert to string, Rounding : STR$(numerical value, cut)
//*  New processing (Rounding)
LPTSTR str_cvt(double sn, int cut);

//* Definition of the square That was all there was (^^;
#define SQUARE(x)    ((x) * (x))

//* Definition of radians
#define RAD(x)    ((x) * 3.14159265358979 / 180.0)

#define KK_PI    3.14159265358979 //* 3238462643383279

//* Rounding up of a number
#define KK_CEIL  0.000000000000001 //* 20251112 (Ver.2.27.0) Fixed a bug where numerical data such as 1.54999... was not rounded at the specified decimal places.

//* Number of Coronas
#define CORONA_NUM        36
//* Number of rays required to draw one corona image
#define CORONA_RAY_CNT    11
#define CORONA_RAY_CNT2   37 //* 20251025 (Ver.2.23.0)

//* Lens constructions: Maximum total number of Boundary Surfaces
#define KOUSEIMEN_MAX    15

//* error、及び warning
#define ERR_RAY_TRACE            100    //* 1: Untraceable, 0: None specified,          0: SkewRayTrace
#define ERR_RAY_TRACE_SPH        110    //* 1: Untraceable, 1: Spherical and coaxial,   0: SRTSph
#define ERR_RAY_TRACE_TORIC      121    //* 1: Untraceable, 2: Aspheric or non-coaxial, 1: SRTToric
#define ERR_RAY_TRACE_ASPH       122    //* 1: Untraceable, 2: Aspheric or non-coaxial, 2: SRTAsph
#define ERR_RAY_TRACE_ASPH2      124    //* 1: Untraceable, 2: Aspheric or non-coaxial, 4: SRTAsph2
#define ERR_RAY_TRACE_HENSPH     123    //* 1: Untraceable, 2: Aspheric or non-coaxial, 3: SRTHenSph
#define WNG_RAY_HEIGHT_OVER      200    //* The tracing ray is outside the clear aperture


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ inserts additional declarations immediately before the preceding line.

#endif // !defined(AFX_STDAFX_H__47A0BEC3_E745_4790_B267_7A2A21F0F3D5__INCLUDED_)
