/**
 * MIT License
 * Copyright (c) 2026 [AlexBo/My3DEngine]
 * * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 */

#pragma once

 // EN: Forward declaration to avoid heavy includes.
class Scene;

/**
 * Description:
 * EN: Interface for the Command design pattern. Encapsulates an action or user input to be executed on the scene.
 */
class ICommand
{
public:
    virtual ~ICommand() = default;

    /**
     * Description:
     * EN: Executes the encapsulated command, modifying the scene state if necessary
     *
     * Arguments:
     * scene (IO) - EN: The target scene to apply the command to | UA: Цільова сцена, до якої застосовується команда
     */
    virtual void execute(Scene& scene) = 0;
};