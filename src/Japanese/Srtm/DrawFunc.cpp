
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#include "stdafx.h"
#include "DrawFunc.h"
#include "GlobalDef.h"


CDrawFunc::CDrawFunc()
{
}


CDrawFunc::~CDrawFunc()
{
}

//* 計算値がゼロに近いときの有効数字の処理
//* sin(KK_PI / 180.0 * deg) などで，deg = 180.0 とした場合に
//* 小数第10位以降にゴミが残るので，その処理
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
    //* VC++は座標系をピクセル座標系としてとらえているようなので
    //* 直交座標系で計算したデータを描画する際，ピクセル座標に変換する。

    //* 問題は，ピクチャーボックスの Width, Height が取得出来ないことで...
    //* 本当はここにピクチャーボックスの Width と Height の値を取得したいのだが...
    //* SRTLMDlg.cpp の OnInitDialog に記述することで解決。

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
    case true: //* x座標: 直交座標系->ピクセル座標系に
        iNumericalValue = int(double(g_lPictureBoxSizeX) / awx * awxl + dNumericalValue * double(g_lPictureBoxSizeX) / awx);
        break;
    case false: //* y座標: 直交座標系->ピクセル座標系に
        iNumericalValue = int(double(g_lPictureBoxSizeY) / awy * awyt - dNumericalValue * double(g_lPictureBoxSizeY) / awy);
        break;
    }

    return(iNumericalValue);
}

//* 点を描画する
BOOL CDrawFunc::P_Pset(double dPsetX, double dPsetY, long l_Color)
{
    //* dPsetX:  点_x;
    //* dPsetY:  点_y;
    //* l_Color: カラー;

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
    //* dLineStartX: 線分開始点_x;
    //* dLineStartY: 線分開始点_y;
    //* dLineStartX: 線分終了点_x;
    //* dLineStartY: 線分終了点_y;
    //* l_Color:     カラー;

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

//* 破線
BOOL CDrawFunc::P_LineD(double dLineStartX, double dLineStartY,
    double dLineEndX, double dLineEndY, long l_Color)
{
    //* dLineStartX:  線分開始点_x;
    //* dLineStartY:  線分開始点_y;
    //* dLineStartX:  線分終了点_x;
    //* dLineStartY:  線分終了点_y;
    //* l_Circ_Color: カラー;

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


//* Q, Q' のキャラクタをセット
BOOL CDrawFunc::P_Char_Set(CString strContents, CString strFontName, int iFontSize, double dPosCharX, double dPosCharY, long l_Color)
{
    //* strContents:  表示を希望するキャラクタ
    //* strFontName:  使用するフォント
    //* strContents:  フォントのサイズ
    //* dPosCharX:    キャラクタセット_x;
    //* dPosCharY:    キャラクタセット_x;
    //* l_Color:      カラー;

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
    //* dLineStartX:   矩形開始点_x;
    //* dLineStartY:   矩形開始点_y;
    //* dLineStartX:   矩形終了点_x;
    //* dLineStartY:   矩形終了点_y;
    //* l_Circ_Color1: 境界線カラー;
    //* l_Circ_Color2: 塗りつぶしカラー;

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
    //* d_S_x:     塗りつぶし指定点_x;
    //* dFillPosX: 塗りつぶし指定点_y;
    //* l_Color1:  境界線色;
    //* l_Color2:  塗りつぶしカラー;

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
    //* dCircCenterX:    円の中心_x;
    //* dCircCenterY:    円の中心_y;
    //* dCircRadius:     半径;
    //* dCircStartAngle: 開始角;
    //* dCircEndAngle:   終了角;
    //* l_Circ_Color:    カラー;

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

