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

#include <vector>
#include <memory>



 // Forward declarations для мінімізації включень
class ICommand;
struct EngineEvent;

/**
 * Description:
 * EN: Static utility class responsible for mapping hardware input events to engine commands.
 * UA: Статичний допоміжний клас, що відповідає за мапінг апаратних подій вводу у команди рушія.
 */
class InputHandler final
{
public:
    // EN: Prevent instantiation. This is a purely static/utility class.
    // UA: Запобігаємо створенню екземплярів. Це суто статичний/допоміжний клас.
    InputHandler() = delete;
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;

    /**
     * Description:
     * EN: Processes raw input events and generates corresponding executable commands * deltaTime .
     *
     * Arguments:
     * events      (I) - EN: Queue of engine-agnostic events  
     * deltaTime   (I)   deltaTime wich multiply on out value
     * outCommands (O) - EN: Buffer to store created commands 
     * 
     */
 
    static void handleInput(
        const std::vector<EngineEvent>& events,
        float deltaTime,
        std::vector<std::unique_ptr<ICommand>>& outCommands
        
    );
};