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

/// @brief Structure used by SBXPlock(s) functions to store plock type, temperature, and more data to represent a plock
struct SBXPlock {
    SBX_plock_type_id_t     type;
    SBX_plock_temperature_t temperature;
};

SBX_report_t SBXPlocksCreate(SBX_plock_t*** plocks, SBX_plock_count_t count);

SBX_report_t SBXPlocksRecreate(SBX_plock_t*** plocks, SBX_plock_count_t oldCount, SBX_plock_count_t newCount);

SBX_report_t SBXPlocksDestroy(SBX_plock_t** plocks, SBX_plock_count_t count);

#endif // SBX_PLOCK_H
