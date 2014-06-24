#ifdef SIMU
#ifndef AS_DAC_H
#define AS_DAC_H

#include <stdint.h>

extern "C"
{


#define AS_MAX5821_TYPE "max5821"

	struct as_dac_device *as_dac_open(const char *aDacType, int aBusNumber,
			int aAddress, int aVRef);

	int32_t as_dac_set_value_in_millivolts(struct as_dac_device *aDev,
	                                       int aChannel,
	                                       int aValue);

	int32_t as_dac_close(struct as_dac_device *aDev);
}
#endif
#endif
