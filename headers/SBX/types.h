#ifndef SBX_TYPES_H
#define SBX_TYPES_H

// Project headers
// #include <SBX/window.h>
// #include <SBX/box.h>
// #include <SBX/plock.h>

// Dependency headers
#include <cglm/struct.h>

// LibC headers
#include <stdint.h>
#include <stdbool.h>

typedef bool                   SBX_bool_t;
typedef uint16_t               SBX_bit_flags_t;
typedef const char*            SBX_string_t;
typedef vec3s                  SBX_color_t;

typedef struct SBXWindowReport SBX_window_report_t;
typedef struct SBXWindow       SBX_window_t;
typedef int                    SBX_window_dimensions_t;
typedef int                    SBX_window_position_t;

typedef struct SBXBoxReport    SBX_box_report_t;
typedef struct SBXBox          SBX_box_t;
typedef uint16_t               SBX_box_dimensions_t;

typedef struct SBXPlockReport  SBX_plock_report_t;
typedef struct SBXPlock        SBX_plock_t;
typedef uint8_t                SBX_plock_id_t;

#endif // SBX_TYPES_H
