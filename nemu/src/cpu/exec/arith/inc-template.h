#include "cpu/exec/template-start.h"

#define instr inc
static void do_execute () {
	
	DATA_TYPE_S src=op_src->val;
	DATA_TYPE_S des=1;

	DATA_TYPE_S result = op_src->val + 1;
	OPERAND_W(op_src, result);


 	CPU_AFFECT_CF(src,des,1)
 	CPU_AFFECT_ZF(src,des)
 	CPU_AFFECT_PF(src,des)
 	CPU_AFFECT_SF(src,des)
  	CPU_AFFECT_OF(src,des)
	/* TODO: Update EFLAGS. */
	//panic("please implement me");

	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
