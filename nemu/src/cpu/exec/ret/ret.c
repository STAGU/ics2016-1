#include "cpu/exec/helper.h"

extern CPU_state cpu;

make_helper(ret_w)
{
	cpu.ip=swaddr_read(cpu.esp,2);
	cpu.esp+=2;
	cpu.eip=cpu.eip&0x0000FFFF;
	print_asm("ret");
	return 0;
}

make_helper(ret_l)
{
	cpu.eip=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
	print_asm("ret");
	return 0;
}

make_helper(ret_i_w)
{
	decode_i_w(eip);
	int16_t a=op_src->val;
	cpu.esp+=2;
	cpu.esp+=a;
	print_asm("ret imm16");
	return 0;
}

make_helper_v(ret)