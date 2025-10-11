
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


#pragma once

class CDrawFunc
{
public:
    CDrawFunc();
    ~CDrawFunc();

    //* Point
    BOOL P_Pset(double dPsetX, double dPsetY, long l_Color);

    //* Line segment
    BOOL P_Line(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color);

    //* Dashed line
    BOOL P_LineD(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color);

    //* Character
    BOOL P_Char_Set(CString strContents, CString strFontName, int iFontSize,
        double dPosCharX, double dPosCharY, long l_Color);

    //* Circular arc
    BOOL P_Circle(double dCircCenterX, double dCircCenterY,
        double dCircRadius, double dCircStartAngle, double dCircEndAngle, long l_Color);

    //* Fill rectangle
    BOOL P_Rectangle(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color1, long l_Color2);


    //* Specify fill
    BOOL P_FloodFill(double dFillPosX, double dFillPosY, long l_Color1, long l_Color2);


    //* Convert the specified point from the Cartesian coordinate system to the pixel coordinate system
    //* DoubleToPixel
    int DtoP(double dNumericalValue, bool bNumValXYFlg);
    int iNumericalValue;
    //* dNumericalValue: 'x' or 'y' component in the Cartesian coordinate system
    //* bNumValXYFlg: true-> Specify the 'x' component, false -> Specify the 'y' component

    //* Picture2
    //* Point
    BOOL P_Pset2(double dPsetX, double dPsetY, long l_Color);

    //* Line segment
    BOOL P_Line2(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color);

    //* Line chart
    BOOL P_LineOre2(bool bStart, int iPointX, int iPointY, long l_Color);

    //* Dashed line
    BOOL P_LineD2(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color);

    //* Character
    BOOL P_Char_Set2(CString strContents, CString strFontName, int iFontSize,
        double dPosCharX, double dPosCharY, long l_Color);

    //* Circular arc
    BOOL P_Circle2(double dCircCenterX, double dCircCenterY,
        double dCircRadius, double dCircStartAngle, double dCircEndAngle, long l_Color);

    //* Fill rectangle
    BOOL P_Rectangle2(double dLineStartX, double dLineStartY,
        double dLineEndX, double dLineEndY, long l_Color1, long l_Color2);


    //* Specify fill
    BOOL P_FloodFill2(double dFillPosX, double dFillPosY, long l_Color1, long l_Color2);


    //* Convert the specified point from the Cartesian coordinate system to the pixel coordinate system
    //* DoubleToPixel
    int DtoP2(double dNumericalValue, bool bNumValXYFlg);

    //* ================================================
    //* significant figures
    double YukouNum(double x);
    //* ================================================

private:

};

