
//* Copyright (c) 2025 Kazuo Kawamura
//*
//* This source code is distributed under the MIT License.
//*
//* Please see the LICENSE file for details.


#pragma once

//* major version  0: Constructing in Visual Basic
//*                1: Ported from Visual Basic
//*                2: double buffering with class
//* minor version  Addressing concerns
//* patch version  There is no limit, so it is fixed at 0

#define VERSION             2,27,0
#define STR_VERSION        "2.27.0"

//* When the year changes, change the year number.
#define STR_COPYRIGHT    "Copyright (C) 2025 Kazuo Kawamura"

class CVersion
{
public:
    CVersion();
    ~CVersion();
};

