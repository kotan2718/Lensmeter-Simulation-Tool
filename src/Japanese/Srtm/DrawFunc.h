
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#pragma once
class CDrawFunc
{
public:
    CDrawFunc();
    ~CDrawFunc();

    //* 点の描画
    BOOL P_Pset(double dPsetX, double dPsetY, long l_Color);

    //* 線分の描画
    BOOL P_Line(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color);

    //* 破線
    BOOL P_LineD(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color);

    //* キャラクタをセット
    BOOL P_Char_Set(CString strContents, CString strFontName, int iFontSize,
        double dPosCharX, double dPosCharY, long l_Color);

    //* 円弧の描画
    BOOL P_Circle(double dCircCenterX, double dCircCenterY,
        double dCircRadius, double dCircStartAngle, double dCircEndAngle, long l_Color);

    //* 矩形塗りつぶし
    BOOL P_Rectangle(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color1, long l_Color2);


    //* 塗りつぶしの指定
    BOOL P_FloodFill(double dFillPosX, double dFillPosY, long l_Color1, long l_Color2);


    //* 指定した点を直交座標系からピクセル座標系に変換
    //* DoubleToPixel
    int DtoP(double dNumericalValue, bool bNumValXYFlg);
    int iNumericalValue;
    //* dNumericalValue: 直交座標系の x or y 成分
    //* bNumValXYFlg: true-> x 成分を指定, false -> y 成分を指定

    //* ピクチャー2
    //* 点の描画
    BOOL P_Pset2(double dPsetX, double dPsetY, long l_Color);

    //* 線分の描画
    BOOL P_Line2(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color);

    //* 折れ線の描画
    BOOL P_LineOre2(bool bStart, int iPointX, int iPointY, long l_Color);

    //* 破線の描画
    BOOL P_LineD2(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color);

    //* キャラクタをセット
    BOOL P_Char_Set2(CString strContents, CString strFontName, int iFontSize,
        double dPosCharX, double dPosCharY, long l_Color);

    //* 円弧の描画
    BOOL P_Circle2(double dCircCenterX, double dCircCenterY,
        double dCircRadius, double dCircStartAngle, double dCircEndAngle, long l_Color);

    //* 矩形塗りつぶし
    BOOL P_Rectangle2(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color1, long l_Color2);


    //* 塗りつぶしの指定
    BOOL P_FloodFill2(double dFillPosX, double dFillPosY, long l_Color1, long l_Color2);


    //* 指定した点を直交座標系からピクセル座標系に変換
    //* DoubleToPixel
    int DtoP2(double dNumericalValue, bool bNumValXYFlg);

    //* ================================================
    //* 有効数字
    double YukouNum(double x);
    //* ================================================

private:

};

