# 定义编译器标志，包括优化级别、警告和错误处理
CFLAGS=-O3 -Wall -Werror -Wimplicit-fallthrough 
# 自动获取所有源文件路径
SRCS=$(wildcard src/*.c)
# 自动获取所有头文件路径
HDRS=$(wildcard src/*.h)
# 将源文件路径转换为目标文件路径
OBJS=$(patsubst src/%.c, obj/%.o, $(SRCS))
# 指定使用的编译器
CC=gcc

# 最终目标是构建Hiemu可执行文件，依赖于所有目标文件
Hiemu: $(OBJS)
# 使用clang编译器、指定的编译器标志、链接数学库，生成可执行文件
	$(CC) $(CFLAGS) -lm -o $@ $^ $(LDFLAGS) 

# 目标文件的构建规则，依赖于对应的源文件和所有头文件
$(OBJS): obj/%.o: src/%.c $(HDRS)
# 在构建之前，确保目标文件所在目录存在
	@mkdir -p $$(dirname $@)
# 使用clang编译器和指定的编译器标志编译源文件为对象文件
	$(CC) $(CFLAGS) -c -o $@ $<

# 定义clean目标，用于清理构建产生的文件
clean:
# 删除Hiemu可执行文件和obj目录下的所有目标文件
	rm -rf Hiemu obj/

# 指定clean目标为伪目标，即不生成实际文件
.PHONY: clean