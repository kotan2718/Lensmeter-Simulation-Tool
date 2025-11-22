
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#pragma once

//* major version  0: Constructing in Visual Basic
//*                1: Ported from Visual Basic
//*                2: double buffering with class
//* minor version  懸念事項の対応
//* patch version  きりがないので0で固定

#define VERSION             2,27,0
#define STR_VERSION        "2.27.0"

//* 年が変わったら、年号を変更する
#define STR_COPYRIGHT    "Copyright (C) 2025 Kazuo Kawamura"

class CVersion
{
public:
    CVersion();
    ~CVersion();
};

