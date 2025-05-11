#include "Hiemu.h"

void mmu_load_elf(mmu_t *mmu, int fd) {
    u8 buf[sizeof(elf64_ehdr_t)];
    FILE *file = fdopen(fd, "rb");
    if(fread(buf, 1, sizeof(elf64_ehdr_t), file) != sizeof(elf64_ehdr_t)) {
        fatal("file too small.");
    }

    elf64_ehdr_t *ehdr = (elf64_ehdr_t *)buf;

    if(*(u32 *)ehdr != *(u32 *)ELFMAG) {
        fatal("invalid elf file.");
    }

    if(ehdr->e_ident[EI_CLASS] != ELFCLASS64 || ehdr->e_machine != EM_RISCV) {
        fatal("Only support ELF64 and RISC-V.");
    }
    mmu->entry = (u64)ehdr->e_entry;
}