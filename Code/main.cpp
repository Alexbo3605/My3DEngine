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

#include "Application.h"
#include <iostream>
#include <cstdlib>
#include <exception>

 /**
  * Description:
  * EN: Application entry point. Initializes the engine, runs the main loop, and provides global exception handling.
  *
  * Returns:
  * EN: EXIT_SUCCESS on normal termination, EXIT_FAILURE on crash/exception.
  */
int main()
{
    try
    {
        Application app;
        app.run();
    }
    catch (const std::exception& e)
    {
        // EN: Catch any standard C++ or SFML-derived exceptions
        // UA: Перехоплення будь-яких стандартних винятків C++ або похідних від SFML
        std::cerr << "[FATAL ERROR] Engine crashed: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (...)
    {
        // EN: Catch-all for non-standard exceptions (e.g., thrown integers or raw strings)
        // UA: Перехоплення нестандартних винятків (наприклад, кинутих цілих чисел або рядків)
        std::cerr << "[FATAL ERROR] Engine crashed due to an unknown exception!\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}