#pragma once
#include <cstdio>

#ifndef _WIN32
#error Only windows is supported!

#else
#include <Windows.h>

#endif

#ifdef _DEBUG
#define ASSERT(condition, msg) if(!(condition)){ fprintf(stderr, "[FractalViewer Assertion] %s\n", msg); __debugbreak(); }

#else
#define ASSERT(condition, msg) if(!(condition)) { MessageBoxA(GetConsoleWindow(), msg, "FractalViewer Assertion", NULL); }

#endif

#define UNUSED(x) (void)(x)


