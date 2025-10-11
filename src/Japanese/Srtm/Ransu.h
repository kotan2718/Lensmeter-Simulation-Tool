
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#pragma once

#include <random>
#include <initializer_list>

class Ransu
{
public:
    Ransu();
    ~Ransu();

    //* 乱数を求める
    int RansuGet1();
    int RansuGet2();

};

