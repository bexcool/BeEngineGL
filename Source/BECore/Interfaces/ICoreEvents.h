//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once


class ICoreEvents
{
public:
    virtual ~ICoreEvents() = default;
    virtual void OnRender() = 0;
    virtual void OnTick() = 0;
};
