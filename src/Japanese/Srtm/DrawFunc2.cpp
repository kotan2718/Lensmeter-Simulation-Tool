
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


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
    case true:  //* x座標: 直交座標系->ピクセル座標系に
        iNumericalValue = int(double(g_lPictureBoxSizeX2) / awx * awxl + dNumericalValue * double(g_lPictureBoxSizeX2) / awx);
        break;
    case false: //* y座標: 直交座標系->ピクセル座標系に
        iNumericalValue = int(double(g_lPictureBoxSizeY2) / awy * awyt - dNumericalValue * double(g_lPictureBoxSizeY2) / awy);
        break;
    }

    return(iNumericalValue);
}

//* 点を描画する
BOOL CDrawFunc::P_Pset2(double dPsetX, double dPsetY, long l_Color)
{
    //* dPsetX:  点_x;
    //* dPsetY:  点_y;
    //* l_Color: カラー;

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

//* ピクチャー2
BOOL CDrawFunc::P_Line2(double dLineStartX, double dLineStartY,
                  double dLineEndX, double dLineEndY, long l_Color)
{
    //* dLineStartX: 線分開始点_x;
    //* dLineStartY: 線分開始点_y;
    //* dLineStartX: 線分終了点_x;
    //* dLineStartY: 線分終了点_y;
    //* l_Color:     カラー;

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

//* 破線
BOOL CDrawFunc::P_LineD2(double dLineStartX, double dLineStartY,
                  double dLineEndX, double dLineEndY, long l_Color)
{
    //* dLineStartX: 線分開始点_x;
    //* dLineStartY: 線分開始点_y;
    //* dLineStartX: 線分終了点_x;
    //* dLineStartY: 線分終了点_y;
    //* l_Color:     カラー;

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

//* Q, Q' のキャラクタをセット
BOOL CDrawFunc::P_Char_Set2(CString strContents, CString strFontName, int iFontSize, double dPosCharX, double dPosCharY, long l_Color)
{
    //* strContents: 表示を希望するキャラクタ
    //* strFontName: 使用するフォント
    //* strContents: フォントのサイズ
    //* dPosCharX:   キャラクタセット_x;
    //* dPosCharY:   キャラクタセット_x;
    //* l_Color:     カラー;

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
    //* dLineStartX:   矩形開始点_x;
    //* dLineStartY:   矩形開始点_y;
    //* dLineStartX:   矩形終了点_x;
    //* dLineStartY:   矩形終了点_y;
    //* l_Circ_Color1: 境界線カラー;
    //* l_Circ_Color2: 塗りつぶしカラー;

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
    //* d_S_x:     塗りつぶし指定点_x;
    //* dFillPosX: 塗りつぶし指定点_y;
    //* l_Color1:  境界線色;
    //* l_Color2:  塗りつぶしカラー;

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
    //* dCircCenterX:    円の中心_x;
    //* dCircCenterY:    円の中心_y;
    //* dCircRadius:     半径;
    //* dCircStartAngle: 開始角;
    //* dCircEndAngle:   終了角;
    //* l_Circ_Color:    カラー;

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

