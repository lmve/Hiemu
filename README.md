# Risc-V High-Performance emulator
## 简介
这个项目主要记录模拟器的学习过程。因为最终实现一个 Risc-v 下的高性能模拟器，故取名 Hiemu。想深入学习可以看这里[手搓 RISC-V 高性能模拟器](https://ksco.cc/rvemu/)👀  


本项目通过解析 ELF 文件（通常是可执行文件格式）， 加载内容到模拟的内存空间，通过解释器（interp.c）、内存管理单元（mmu.c）等模块模拟 cpu 的指令执行过程，实现类似 qemu 的二进制模拟功能。

## 工作流程
1. ELF解析 解析文件头、程序头、节区头等，提取代码段、数据段等信息。
2. 初始化 初始化机器状态、将 ELF 文件内容加载到模拟内存空间。
3. 指令解释与执行 解释并执行指令流，模拟 CPU 的行为。
```
int main(int argc, char *argv[]) {
    // 1. 解析命令行参数，获取 ELF 文件路径
    // 2. 初始化寄存器和内存
    // 3. 加载 ELF 文件到模拟内存
    // 4. 设置入口点（PC）
    // 5. 进入主循环，解释执行指令
}
```

## 参考资料
[ELF文件](https://ctf-wiki.org/executable/elf/structure/basic-info/)  
[risc-v](http://staff.ustc.edu.cn/~llxx/cod/reference_books/RISC-V-Reader-Chinese-v2p12017.pdf)