//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once


class IDisposable
{
public:
    virtual ~IDisposable() = default;
    virtual void Dispose() = 0;
};
