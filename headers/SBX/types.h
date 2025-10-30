#ifndef SBX_TYPES_H
#define SBX_TYPES_H

// Project headers
#include <SBX/window.h>

// LibC headers
#include <stdint.h>

typedef struct SBXWindowReport SBX_window_report_t;
typedef struct SBXWindow       SBX_window_t;

typedef uint16_t               SBX_bit_flags_t;
typedef int                    SBX_window_dimensions_t;
typedef int                    SBX_window_position_t;
typedef const char*            SBX_string_t;

#endif // SBX_TYPES_H
