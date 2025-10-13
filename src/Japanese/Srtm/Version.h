
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#pragma once

//* major version  0: no double buffering
//*                1: double buffering without class
//*                2: double buffering with class
//* minor version  懸念事項の対応
//* build version  きりがないので1で固定
//* revision       これもきりがないなぁ...

#define VERSION             2,22,1,1
#define STR_VERSION        "2.22.1.1"

//* 年が変わったら、年号を変更する
#define STR_COPYRIGHT    "Copyright (C) 2025 Kazuo Kawamura"

class CVersion
{
public:
    CVersion();
    ~CVersion();
};

