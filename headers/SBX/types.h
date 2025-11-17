#ifndef SBX_TYPES_H
#define SBX_TYPES_H

// Dependency headers
#include <cglm/struct.h>

// LibC headers
#include <stdint.h>
#include <stdbool.h>

typedef struct SBXReport        SBX_report_t;
typedef bool                    SBX_bool_t;
typedef uint64_t                SBX_bit_flags_t;
typedef const char*             SBX_string_t;
typedef vec3s                   SBX_color_t;

typedef struct SBXWindow        SBX_window_t;
typedef int                     SBX_window_dimensions_t;
typedef int                     SBX_window_position_t;

typedef struct SBXBox           SBX_box_t;
typedef uint16_t                SBX_box_dimensions_t;

typedef struct SBXPlockType     SBX_plock_type_t;
typedef uint8_t                 SBX_plock_type_id_t;
typedef struct SBXPlock         SBX_plock_t;
typedef uint32_t                SBX_plock_count_t;
typedef uint32_t                SBX_plock_id_t;
typedef long double             SBX_plock_temperature_t;

#define SBX_MAX_PLOCK_COUNT     UINT32_MAX

#define SBX_COLOR_UNSET         ((SBX_color_t){-1.0f, -1.0f, -1.0f})
#define SBX_POINTER_UNSET       NULL
#define SBX_DIMENSION_UNSET     0
#define SBX_PLOCK_TYPE_ID_UNSET 0
#define SBX_PLOCK_ID_UNSET      0
#define SBX_TEMPERATURE_UNSET   -1000.0f

#endif // SBX_TYPES_H
