#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#include "types.h"
#include "elfdef.h"
#include "reg.h"

#define fatalf(fmt, ...) (fprintf(stderr, "Fatal: %s:%d " fmt "\n", __FILE__, __LINE__, __VA_ARGS__), exit(1))
#define fatal(msg) fatalf("%s", msg)
#define unreachable() (fatal("unreachable"), __builtin_unreachable())

#define ROUNDDOWN(x, k) ((x) & -(k))
#define ROUNDUP(x, k)   (((x)) + (k)-1 & -(k))
#define MIN(x, y)       ((y) > (x) ? (x) : (y))
#define MAX(x, y)       ((y) < (x) ? (x) : (y))

#define GUEST_MEMORY_OFFSET 0x088800000000ULL

#define TO_HOST(addr) (addr + GUEST_MEMORY_OFFSET)
#define TO_GUST(addr) (addr - GUEST_MEMORY_OFFSET)

/**
 * decode.c
*/
enum insn_type_t {
    insn_addi,
    num_insns,
};

typedef struct {
    i8 rd;
    i8 rs1;
    i8 rs2;
    i32 imm;
    enum insn_type_t type;
    bool rvc;
    bool cont; /* continue */
} insn_t;
void insn_decode(insn_t *, u32);

/**
 * mmu.c
*/
typedef struct {
    u64 entry;
    u64 host_alloc;
    u64 alloc;
    u64 base;
} mmu_t;
void mmu_load_elf(mmu_t *, int);

/**
 * state.c
*/
enum exit_reason_t {
    none,
    direct_branch,      //编译时就知道
    indirect_branch,    //运行时才知道
    ecall,
};
typedef struct {
    enum exit_reason_t exit_reason;
    u64 gp_regs[32];
    u64 pc;
} state_t;

/** 
 * machine.c
*/
typedef struct {
    state_t state;
    mmu_t mmu;
} machine_t;
void machine_load_program(machine_t *, char *);
enum exit_reason_t machine_step(machine_t *);

/*
 * interp.c
*/
void exec_block_interp(state_t *);