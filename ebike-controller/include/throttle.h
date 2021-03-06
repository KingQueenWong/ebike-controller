#ifndef _THROTTLE_H_
#define _THROTTLE_H_

#include "stm32f4xx.h"
#include "DavidsFOCLib.h"
#include "adc.h"

#define THROTTLE_START_TIME			1000
#define THROTTLE_START_DEADTIME		500
#define THROTTLE_RANGE_LIMIT		0.05f
#define THROTTLE_MIN_DEFAULT		0.85f
#define THROTTLE_MAX_DEFAULT		2.20f
#define THROTTLE_HYST_LOW			0.025f
#define THROTTLE_HYST_HIGH			0.030f
#define THROTTLE_DROPOUT			0.72f
// Limit the throttle climb rate to 50% / second
// The update rate is 1000Hz, so the rate limit is actually .125% per update
#define THROTTLE_SLEW_RATE  (0.00125f)

typedef struct
{
	uint8_t throttle_state;
	uint32_t throttle_startup_count;
	float throttle_min;
	float throttle_max;
	float throttle_scale_factor;
}Throttle_Type;
#define THROTTLE_DEFAULTS	{0, 0, 0.0f, 0.0f, 1.0f}

// Biquad filter: Fs = 1kHz, f0 = 2Hz, Q = 0.45
// Little bit sluggish response. Maybe feels safer?
#define THROTTLE_LPF_DEFAULTS  { \
                -1.972304f, \
                0.9724600f, \
                0.00003893429f, \
                0.00007786857f, \
                0.00003893429f, \
                0.0f, \
                0.0f, \
                0.0f, \
                0.0f }


float throttle_process(float raw_voltage);

#endif /* _THROTTLE_H_ */
