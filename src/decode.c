/*
 * 主要做指令解码工作
 *  while(true){
 *    raw = fetch(pc)
 *    insn = decode(raw)
 *    exec(insn)
 *    
 *    pc += rvc ? 2 : 4
 * }
 *
*/

#include "Hiemu.h"

#define QUADRANT(data) (((data) >> 0) & 0x3)       // 下限 判断是否是压缩指令

void insn_decode(insn_t *insn, u32 data) {
    u32 quadrant = QUADRANT(data);
    switch (quadrant) {
        case 0x0: fatal("unimplemented instruction"); 
        case 0x1: fatal("unimplemented instruction");
        case 0x2: fatal("unimplemented instruction");
        case 0x3: fatal("unimplemented instruction");
        default: unreachable();
    }

}