#include "Hiemu.h"
int main(int argc, char *argv[]) {
    assert(argc > 1);

    machine_t machine = {0};
    machine_load_program(&machine, argv[1]);
    printf("Entry: %lx\n", machine.mmu.entry);
    printf("machine address: 0x%lx\n", (u64)&machine);
    printf("Entry: 0x%llx\n", TO_HOST(machine.mmu.entry));
    return 0;
}