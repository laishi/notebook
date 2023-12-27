# 仅进行预处理，生成预处理后的源代码文件
gcc -E source.c -o output.i

# 进行预处理和汇编，生成汇编代码文件
gcc -S source.c -o output.s

# 进行预处理、汇编和编译，生成目标文件
gcc -c source.c -o output.o

