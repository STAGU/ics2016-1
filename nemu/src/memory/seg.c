#include "common.h"
#include "cpu/reg.h"
#include "memory/memory.h"

static void get_base_and_limit(uint8_t sreg,lnaddr_t *base,lnaddr_t * limit)
{
	uint32_t index_in_descripter_table=cpu.segment_reg[sreg].selector.index;

	uint32_t temp[2];

	/**
	 * little endian
	 */
	temp[0]=lnaddr_read(cpu.gdtr+index_in_descripter_table*8,4);
	temp[1]=lnaddr_read(cpu.gdtr+index_in_descripter_table*8+4,4);

	SegDesc sgds;
	memcpy(&sgds,temp,8);

	*base=sgds.base_15_0|(((uint32_t)sgds.base_23_16<<16))|(((uint32_t)sgds.base_31_24<<24));
	*limit=sgds.limit_15_0|((uint32_t)sgds.limit_19_16<<16);

#ifdef DEBUG
	Assert(sgds.present,"sgds failed");
#endif 

}



lnaddr_t seg_translate(swaddr_t addr, size_t len,uint8_t sreg)
{
	if(cpu.cr0.protect_enable==1)
	{
		
	    lnaddr_t base,limit;

	    get_base_and_limit(sreg,&base,&limit);
#ifdef DEBUG   
	    if (addr > limit || addr + len - 1 > limit) {
	    	panic("can't do segment-translation");
	    }
#endif
    	return base + addr;

	}
	else
		return addr;
}
