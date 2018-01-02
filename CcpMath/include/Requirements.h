#pragma once

#ifdef _WIN32
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#define NOMINMAX
#include <Windows.h>
#endif
#endif

#include <algorithm>
#include <cstdint>
#include <utility>
#include <cmath>