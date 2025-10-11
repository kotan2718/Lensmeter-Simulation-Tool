
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


#include "stdafx.h"
#include "DrawFunc.h"
#include "GlobalDef.h"

int CDrawFunc::DtoP2(double dNumericalValue, bool bNumValXYFlg)
{
    double awxl;
    awxl = -g_dWindowPosLeft2;
    double awyt;
    awyt = g_dWindowPosTop2;
    double awx;
    awx = g_dWindowPosRight2 - g_dWindowPosLeft2;
    double awy;
    awy = g_dWindowPosTop2 - g_dWindowPosBottom2;

    switch(bNumValXYFlg)
    {
    case true:  //* x-coordinate: Cartesian coordinate system -> Pixel coordinate system
        iNumericalValue = int(double(g_lPictureBoxSizeX2) / awx * awxl + dNumericalValue * double(g_lPictureBoxSizeX2) / awx);
        break;
    case false: //* y-coordinate: Cartesian coordinate system -> Pixel coordinate system
        iNumericalValue = int(double(g_lPictureBoxSizeY2) / awy * awyt - dNumericalValue * double(g_lPictureBoxSizeY2) / awy);
        break;
    }

    return(iNumericalValue);
}

//* Draw a point
BOOL CDrawFunc::P_Pset2(double dPsetX, double dPsetY, long l_Color)
{
    //* dPsetX:  Point_x;
    //* dPsetY:  Point_y;
    //* l_Color: Color;

    CRect rc2;
    g_pict1.GetClientRect(rc2);

    CRgn rgn2;
    rgn2.CreateRectRgnIndirect(rc2);
    g_memDC2.SelectObject(rgn2);

    g_memDC2.SetPixel(DtoP2(dPsetX, true), DtoP2(dPsetY, false), l_Color);

    ///////////////////////////////////////////////
    rgn2.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}

// ピクチャー2
BOOL CDrawFunc::P_Line2(double dLineStartX, double dLineStartY,
                  double dLineEndX, double dLineEndY, long l_Color)
{
    //* dLineStartX: Line segment start point_x;
    //* dLineStartY: Line segment start point_y;
    //* dLineStartX: Line segment end point_x;
    //* dLineStartY: Line segment end point_y;
    //* l_Color:     Color;

    CRect rc2;
    g_pict1.GetClientRect(rc2);

    CRgn rgn2;
    rgn2.CreateRectRgnIndirect(rc2);
    g_memDC2.SelectObject(rgn2);

    CPen pen2, *oldPen2;
    pen2.CreatePen(PS_SOLID, 1, l_Color);
    oldPen2 = g_memDC2.SelectObject(&pen2);

    g_memDC2.MoveTo(DtoP2(dLineStartX, true), DtoP2(dLineStartY, false));
    g_memDC2.LineTo(DtoP2(dLineEndX, true), DtoP2(dLineEndY, false));


    ///////////////////////////////////////////////
    rgn2.DeleteObject();

    g_memDC2.SelectObject(oldPen2);
    pen2.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}

//* Dotted line
BOOL CDrawFunc::P_LineD2(double dLineStartX, double dLineStartY,
                  double dLineEndX, double dLineEndY, long l_Color)
{
    //* dLineStartX: Line segment start point_x;
    //* dLineStartY: Line segment start point_y;
    //* dLineStartX: Line segment end point_x;
    //* dLineStartY: Line segment end point_y;
    //* l_Color:     Color;

    CRect rc2;
    g_pict1.GetClientRect(rc2);

    CRgn rgn2;
    rgn2.CreateRectRgnIndirect(rc2);
    g_memDC2.SelectObject(rgn2);

    CPen pen2, *oldPen2;
    pen2.CreatePen(PS_SOLID, 1, l_Color);
    oldPen2 = g_memDC2.SelectObject(&pen2);

    g_memDC2.SetBkMode(TRANSPARENT);
    g_memDC2.MoveTo(DtoP2(dLineStartX, true), DtoP2(dLineStartY, false));
    g_memDC2.LineTo(DtoP2(dLineEndX, true), DtoP2(dLineEndY, false));


    ///////////////////////////////////////////////
    rgn2.DeleteObject();

    g_memDC2.SelectObject(oldPen2);
    pen2.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}

//* Set the characters Q and Q'
BOOL CDrawFunc::P_Char_Set2(CString strContents, CString strFontName, int iFontSize, double dPosCharX, double dPosCharY, long l_Color)
{
    //* strContents: Character to be displayed
    //* strFontName: Font to use
    //* strContents: Dont size
    //* dPosCharX:   Character set_x;
    //* dPosCharY:   Character set_x;
    //* l_Color:     Color;

    CRect rc2;
    g_pict1.GetClientRect(rc2);

    CRgn rgn2;
    rgn2.CreateRectRgnIndirect(rc2);
    g_memDC2.SelectObject(rgn2);

    CFont font2, *oldFont2;
    font2.CreateFont(iFontSize, 0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, strFontName);
    oldFont2 = g_memDC2.SelectObject(&font2);
    g_memDC2.SetBkMode(TRANSPARENT);
    g_memDC2.SetTextColor(l_Color);
    g_memDC2.TextOut(DtoP2(dPosCharX, true), DtoP(dPosCharY, false), strContents);

    g_memDC2.SelectObject(oldFont2);
    font2.DeleteObject();

    ///////////////////////////////////////////////
    rgn2.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}


BOOL CDrawFunc::P_Rectangle2(double dLineStartX, double dLineStartY,
                  double dLineEndX, double dLineEndY, long l_Color1, long l_Color2)
{
    //* dLineStartX: Rectangle start point_x;
    //* dLineStartY: Rectangle start point_y;
    //* dLineStartX: Rectangle end point_x;
    //* dLineStartY: Rectangle end point_y;
    //* l_Color1:    Border Color;
    //* l_Color2:    Fill Color;

    CRect rc2;
    g_pict1.GetClientRect(rc2);

    CRgn rgn2;
    rgn2.CreateRectRgnIndirect(rc2);
    g_memDC2.SelectObject(rgn2);

    CPen pen2, *oldPen2;
    pen2.CreatePen(PS_SOLID, 1, l_Color1);
    oldPen2 = g_memDC2.SelectObject(&pen2);

    CBrush brsh2;
    CBrush* oldBrsh2;
    brsh2.CreateSolidBrush(l_Color2);
    oldBrsh2 = g_memDC2.SelectObject(&brsh2);

    ///////////////////////////////////////////////

    g_memDC2.Rectangle(DtoP2(dLineStartX, true), DtoP2(dLineStartY, false),
          DtoP2(dLineEndX, true),  DtoP2(dLineEndY, false));


    ///////////////////////////////////////////////
    rgn2.DeleteObject();

    g_memDC2.SelectObject(oldBrsh2);
    brsh2.DeleteObject();

    g_memDC2.SelectObject(oldPen2);
    pen2.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}

BOOL CDrawFunc::P_FloodFill2(double dFillPosX, double dFillPosY, long l_Color1, long l_Color2)
{
    //* d_S_x:     Fill specified point_x;
    //* dFillPosX: Fill specified point_y;
    //* l_Color1:  Border Color;
    //* l_Color2:  Fill Color;

    CRect rc2;
    g_pict1.GetClientRect(rc2);

    CRgn rgn2;
    rgn2.CreateRectRgnIndirect(rc2);
    g_memDC2.SelectObject(rgn2);

    CPen pen2, *oldPen2;
    pen2.CreatePen(PS_SOLID, 1, l_Color1);
    oldPen2 = g_memDC2.SelectObject(&pen2);

    CBrush brsh2;
    CBrush* oldBrsh2;
    brsh2.CreateSolidBrush(l_Color2);
    oldBrsh2 = g_memDC2.SelectObject(&brsh2);

    g_memDC2.FloodFill(DtoP2(dFillPosX, true), DtoP2(dFillPosY, false), l_Color1);


    ///////////////////////////////////////////////
    rgn2.DeleteObject();

    g_memDC2.SelectObject(oldBrsh2);
    brsh2.DeleteObject();

    g_memDC2.SelectObject(oldPen2);
    pen2.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}

BOOL CDrawFunc::P_Circle2(double dCircCenterX, double dCircCenterY, double dCircRadius, double dCircStartAngle, double dCircEndAngle, long l_Color)
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

    dDDI = dDDI / 36.0;

    double dCircStartAngleTmp;
    dCircStartAngleTmp = dCircStartAngle;

    double dx;
    double dy;
    dx = dCircRadius * cos(dCircStartAngleTmp);
    dy = dCircRadius * sin(dCircStartAngleTmp);

    CRect rc2;
    g_pict1.GetClientRect(rc2);

    CRgn rgn2;
    rgn2.CreateRectRgnIndirect(rc2);
    g_memDC2.SelectObject(rgn2);

    CPen pen2, *oldPen2;
    pen2.CreatePen(PS_SOLID, 1, l_Color);
    oldPen2 = g_memDC2.SelectObject(&pen2);

    int ix;
    int iy;
    ix = DtoP2(dx + dCircCenterX, true);
    iy = DtoP2(dy + dCircCenterY, false);
    g_memDC2.MoveTo(ix, iy);

    for(int i = 0; i < 36; i++) {
        dCircStartAngleTmp = dCircStartAngleTmp + dDDI;

        dx = dCircRadius * cos(dCircStartAngleTmp);
        dx = YukouNum(dx);
        dy = dCircRadius * sin(dCircStartAngleTmp);
        dy = YukouNum(dy);

        ix = DtoP2(dx + dCircCenterX, true);
        iy = DtoP2(dy + dCircCenterY, false);
        g_memDC2.LineTo(ix, iy);

    }


    ///////////////////////////////////////////////
    rgn2.DeleteObject();

    g_memDC2.SelectObject(oldPen2);
    pen2.DeleteObject();
    ///////////////////////////////////////////////

    return TRUE;
}

