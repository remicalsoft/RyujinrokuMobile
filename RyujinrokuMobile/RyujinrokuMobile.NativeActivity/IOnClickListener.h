#pragma once

#include "View.h"

class IOnClickListener
{
public:
    IOnClickListener() = default;
    virtual ~IOnClickListener() = default;
    virtual void onClick(View view) = 0;
};

