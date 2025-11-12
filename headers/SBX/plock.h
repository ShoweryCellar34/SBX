#ifndef SBX_PLOCK_H
#define SBX_PLOCK_H

// Project headers
#include <SBX/types.h>
#include <SBX/report.h>

/// @brief Structure used by SBXPlockType fuctions to store color, physics type, and more data to represent a plock type
struct SBXPlockType {
    SBX_color_t color;
};

SBX_report_t SBXPlockTypeCreate(SBX_plock_type_t** plockType, SBX_color_t color);

SBX_report_t SBXPlockTypeDestroy(SBX_plock_type_t* plockType);

struct SBXPlock {
    SBX_plock_type_id_t     type;
    SBX_plock_temperature_t temperature;
};

#endif // SBX_PLOCK_H
