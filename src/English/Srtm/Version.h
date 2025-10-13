
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


#pragma once

//* major version  0: no double buffering
//*                1: double buffering without class
//*                2: double buffering with class
//* minor version  Addressing concerns
//* build version  There is no limit, so it is fixed at 1
//* revision       This is endless...

#define VERSION             2,22,1,1
#define STR_VERSION        "2.22.1.1"

//* When the year changes, change the year number.
#define STR_COPYRIGHT    "Copyright (C) 2025 Kazuo Kawamura"

class CVersion
{
public:
    CVersion();
    ~CVersion();
};

