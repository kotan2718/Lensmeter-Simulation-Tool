
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


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
    // Initialize the Mersenne Twister pseudorandom number generator
    // using a hardware random number as a seed.
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    // Generate a uniform random number generator with a range of [-100, 99].
    std::uniform_int_distribution<int> dist1(0, 199);
    iRslt = dist1(engine) - 100;

    return(iRslt);
}

int Ransu::RansuGet2()
{
    int iRslt;
    // Initialize the Mersenne Twister pseudorandom number generator
    // using a hardware random number as a seed.
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    // Generate a uniform random number generator with a range of [-15, 14].
    std::uniform_int_distribution<int> dist1(0, 29);
    iRslt = dist1(engine) - 15;

    return(iRslt);
}

