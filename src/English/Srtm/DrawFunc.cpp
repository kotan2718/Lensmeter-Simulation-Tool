
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


#include "stdafx.h"
#include "DrawFunc.h"
#include "GlobalDef.h"


CDrawFunc::CDrawFunc()
{
}


CDrawFunc::~CDrawFunc()
{
}

//* Handling significant digits when calculated values are close to zero.
//* For expressions like sin(π / 180.0 * deg), when deg = 180.0, garbage remains beyond the tenth decimal place,
//* so handle that.
//
double CDrawFunc::YukouNum(double x)
{
    if (fabs(x) < 0.0000000001) {
        x = 0.0;
    }

    return(x);
}

int CDrawFunc::DtoP(double dNumericalValue, bool bNumValXYFlg)
{
    //* When drawing data calculated in a Cartesian coordinate system, convert it to pixel coordinates.
    //* Since VC++ seems to treat the coordinate system as a pixel coordinate system,

    //* The problem is that the PictureBox's Width and Height cannot be obtained...
    //* Ideally, I want to get the PictureBox's Width and Height values here...
    //* Resolved by writing it in SRTLMDlg.cpp's OnInitDialog.

    double awxl;
    awxl = -g_dWindowPosLeft;
    double awyt;
    awyt = g_dWindowPosTop;
    double awx;
    awx = g_dWindowPosRight - g_dWindowPosLeft;
    double awy;
    awy = g_dWindowPosTop - g_dWindowPosBottom;

    switch (bNumValXYFlg)
    {
    case true: //* x-coordinate: Cartesian coordinate system -> Pixel coordinate system
        iNumericalValue = int(double(g_lPictureBoxSizeX) / awx * awxl + dNumericalValue * double(g_lPictureBoxSizeX) / awx);
        break;
    case false: //* y-coordinate: Cartesian coordinate system -> Pixel coordinate system
        iNumericalValue = int(double(g_lPictureBoxSizeY) / awy * awyt - dNumericalValue * double(g_lPictureBoxSizeY) / awy);
        break;
    }

    return(iNumericalValue);
}

//* Draw a point
BOOL CDrawFunc::P_Pset(double dPsetX, double dPsetY, long l_Color)
{
    //* dPsetX:  Point_x;
    //* dPsetY:  Point_y;
    //* l_Color: Color;

    CRect rc;
    g_pict1.GetClientRect(rc);

    CRgn rgn;
    rgn.CreateRectRgnIndirect(rc);
    g_memDC1.SelectObject(rgn);

    g_memDC1.SetPixel(DtoP(dPsetX, true), DtoP(dPsetY, false), l_Color);



    ///////////////////////////////////////////////
    rgn.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}

BOOL CDrawFunc::P_Line(double dLineStartX, double dLineStartY,
    double dLineEndX, double dLineEndY, long l_Color)
{
    //* dLineStartX: Line segment start point_x;
    //* dLineStartY: Line segment start point_y;
    //* dLineStartX: Line segment end point_x;
    //* dLineStartY: Line segment end point_y;
    //* l_Color:     Color;

    CRect rc;
    g_pict1.GetClientRect(rc);

    CRgn rgn;
    rgn.CreateRectRgnIndirect(rc);
    g_memDC1.SelectObject(rgn);

    CPen pen, *oldPen;
    pen.CreatePen(PS_SOLID, 1, l_Color);
    oldPen = g_memDC1.SelectObject(&pen);

    g_memDC1.MoveTo(DtoP(dLineStartX, true), DtoP(dLineStartY, false));
    g_memDC1.LineTo(DtoP(dLineEndX, true), DtoP(dLineEndY, false));



    ///////////////////////////////////////////////
    rgn.DeleteObject();

    g_memDC1.SelectObject(oldPen);
    pen.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}

//* Dashed line
BOOL CDrawFunc::P_LineD(double dLineStartX, double dLineStartY,
    double dLineEndX, double dLineEndY, long l_Color)
{
    //* dLineStartX: Line segment start point_x;
    //* dLineStartY: Line segment start point_y;
    //* dLineStartX: Line segment end point_x;
    //* dLineStartY: Line segment end point_y;
    //* l_Color:     Color;

    CRect rc;
    g_pict1.GetClientRect(rc);

    CRgn rgn;
    rgn.CreateRectRgnIndirect(rc);
    g_memDC1.SelectObject(rgn);

    CPen pen, *oldPen;
    pen.CreatePen(PS_SOLID, 1, l_Color);
    oldPen = g_memDC1.SelectObject(&pen);

    g_memDC1.SetBkMode(TRANSPARENT);
    g_memDC1.MoveTo(DtoP(dLineStartX, true), DtoP(dLineStartY, false));
    g_memDC1.LineTo(DtoP(dLineEndX, true), DtoP(dLineEndY, false));



    ///////////////////////////////////////////////
    rgn.DeleteObject();

    g_memDC1.SelectObject(oldPen);
    pen.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}


//* Set the characters Q and Q'
BOOL CDrawFunc::P_Char_Set(CString strContents, CString strFontName, int iFontSize, double dPosCharX, double dPosCharY, long l_Color)
{
    //* strContents: Character to be displayed
    //* strFontName: Font to use
    //* strContents: Dont size
    //* dPosCharX:   Character set_x;
    //* dPosCharY:   Character set_x;
    //* l_Color:     Color;

    CRect rc;
    g_pict1.GetClientRect(rc);

    CRgn rgn;
    rgn.CreateRectRgnIndirect(rc);
    g_memDC1.SelectObject(rgn);

    CFont font, *oldFont;
    font.CreateFont(iFontSize, 0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, strFontName);
    oldFont = g_memDC1.SelectObject(&font);
    g_memDC1.SetBkMode(TRANSPARENT);
    g_memDC1.SetTextColor(l_Color);
    g_memDC1.TextOut(DtoP(dPosCharX, true), DtoP(dPosCharY, false), strContents);

    g_memDC1.SelectObject(oldFont);
    font.DeleteObject();

    ///////////////////////////////////////////////
    rgn.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}


BOOL CDrawFunc::P_Rectangle(double dLineStartX, double dLineStartY,
    double dLineEndX, double dLineEndY, long l_Color1, long l_Color2)
{
    //* dLineStartX: Rectangle start point_x;
    //* dLineStartY: Rectangle start point_y;
    //* dLineStartX: Rectangle end point_x;
    //* dLineStartY: Rectangle end point_y;
    //* l_Color1:    Border Color;
    //* l_Color2:    Fill Color;

    CRect rc;
    g_pict1.GetClientRect(rc);

    CRgn rgn;
    rgn.CreateRectRgnIndirect(rc);
    g_memDC1.SelectObject(rgn);

    CPen pen, *oldPen;
    pen.CreatePen(PS_SOLID, 1, l_Color1);
    oldPen = g_memDC1.SelectObject(&pen);

    CBrush brsh;
    CBrush* oldBrsh;
    brsh.CreateSolidBrush(l_Color2);
    oldBrsh = g_memDC1.SelectObject(&brsh);

    g_memDC1.Rectangle(DtoP(dLineStartX, true), DtoP(dLineStartY, false),
        DtoP(dLineEndX, true), DtoP(dLineEndY, false));


    ///////////////////////////////////////////////
    rgn.DeleteObject();

    g_memDC1.SelectObject(oldBrsh);
    brsh.DeleteObject();

    g_memDC1.SelectObject(oldPen);
    pen.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}

BOOL CDrawFunc::P_FloodFill(double dFillPosX, double dFillPosY, long l_Color1, long l_Color2)
{
    //* d_S_x:     Fill specified point_x;
    //* dFillPosX: Fill specified point_y;
    //* l_Color1:  Border Color;
    //* l_Color2:  Fill Color;

    CRect rc;
    g_pict1.GetClientRect(rc);

    CRgn rgn;
    rgn.CreateRectRgnIndirect(rc);
    g_memDC1.SelectObject(rgn);

    CPen pen, *oldPen;
    pen.CreatePen(PS_SOLID, 1, l_Color1);
    oldPen = g_memDC1.SelectObject(&pen);

    CBrush brsh;
    CBrush* oldBrsh;
    brsh.CreateSolidBrush(l_Color2);
    oldBrsh = g_memDC1.SelectObject(&brsh);

    g_memDC1.FloodFill(DtoP(dFillPosX, true), DtoP(dFillPosY, false), l_Color1);


    ///////////////////////////////////////////////
    rgn.DeleteObject();

    g_memDC1.SelectObject(oldBrsh);
    brsh.DeleteObject();

    g_memDC1.SelectObject(oldPen);
    pen.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}

BOOL CDrawFunc::P_Circle(double dCircCenterX, double dCircCenterY, double dCircRadius, double dCircStartAngle, double dCircEndAngle, long l_Color)
{
    //* dCircCenterX:    Center of a circle_x;
    //* dCircCenterY:    Center of a circle_y;
    //* dCircRadius:     Radius;
    //* dCircStartAngle: Start angle;
    //* dCircEndAngle:   End angle;
    //* l_Circ_Color:    Color;

    double dDDI;
    dDDI = 0.0;
    dDDI = fabs(dCircEndAngle - dCircStartAngle);

    if (dDDI > KK_PI) {
        dDDI = 2.0 * KK_PI - dDDI;
    }

    dDDI = dDDI / 36.0;

    double dCircStartAngleTmp;
    dCircStartAngleTmp = dCircStartAngle;

    double dx;
    double dy;
    dx = dCircRadius * cos(dCircStartAngleTmp);
    dy = dCircRadius * sin(dCircStartAngleTmp);

    CRect rc;
    g_pict1.GetClientRect(rc);

    CRgn rgn;
    rgn.CreateRectRgnIndirect(rc);
    g_memDC1.SelectObject(rgn);

    CPen pen, *oldPen;
    pen.CreatePen(PS_SOLID, 1, l_Color);
    oldPen = g_memDC1.SelectObject(&pen);

    int ix;
    int iy;
    ix = DtoP(dx + dCircCenterX, true);
    iy = DtoP(dy + dCircCenterY, false);
    g_memDC1.MoveTo(ix, iy);

    for (int i = 0; i < 36; i++) {
        dCircStartAngleTmp = dCircStartAngleTmp + dDDI;

        dx = dCircRadius * cos(dCircStartAngleTmp);
        dx = YukouNum(dx);
        dy = dCircRadius * sin(dCircStartAngleTmp);
        dy = YukouNum(dy);

        ix = DtoP(dx + dCircCenterX, true);
        iy = DtoP(dy + dCircCenterY, false);
        g_memDC1.LineTo(ix, iy);

    }


    ///////////////////////////////////////////////
    rgn.DeleteObject();

    g_memDC1.SelectObject(oldPen);
    pen.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}

