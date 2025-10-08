//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once


class CoreEvents
{
public:
    virtual ~CoreEvents() = default;
    virtual void OnRender() {}
    virtual void OnTick() {}
};
