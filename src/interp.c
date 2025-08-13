/**
 *  解释型模拟器
 *  整体架构  解释执行 + JIT 执行
 */

#include "Hiemu.h"

typedef void (func_t) (state_t *, insn_t *);

static func_t *funcs[100] = {NULL};

void exec_block_interp(state_t *state) {
    static insn_t insn = {0};
    while(true) {
        u32 data = *(u32 *)TO_HOST(state->pc);
        insn_decode(&insn, data);

        funcs[insn.type](state, &insn);
        state->gp_regs[zero] = 0;

        if(insn.cont) break;

        state->pc += insn.rvc ? 2 : 4;
    }
}
