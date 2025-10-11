
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* 本ソースコードは MIT License に基づき配布されています。
//*
//* 詳細については LICENSE ファイルを参照してください。


#include "stdafx.h"
#include "Ransu.h"


Ransu::Ransu()
{
}


Ransu::~Ransu()
{
}

int Ransu::RansuGet1()
{
    int iRslt;
    // メルセンヌ・ツイスター法による擬似乱数生成器を、
    // ハードウェア乱数をシードにして初期化
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    // [-100, 99] の範囲の一様分布器を生成
    std::uniform_int_distribution<int> dist1(0, 199);
    iRslt = dist1(engine) - 100;

    return(iRslt);
}

int Ransu::RansuGet2()
{
    int iRslt;
    // メルセンヌ・ツイスター法による擬似乱数生成器を、
    // ハードウェア乱数をシードにして初期化
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    // [-15, 14] の範囲の一様分布器を生成
    std::uniform_int_distribution<int> dist1(0, 29);
    iRslt = dist1(engine) - 15;

    return(iRslt);
}

