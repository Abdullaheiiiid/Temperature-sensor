#include "bit.h"
#include "typedef.h"
#include "GIE_private.h"
#include "GIE_config.h"
#include "GIE_interface.h"

void GIE_VidEnable(){
	SETBIT(SREG,SREF_I);
}
void GIE_VidDisable(){
	CLEARBIT(SREG,SREF_I);
}
