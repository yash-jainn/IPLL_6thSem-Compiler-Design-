# Running `setA_7.asm` Using NASM and GCC
(Similar as this for setA_11.asm and for setB_3.asm)

This guide explains how to assemble, link, and execute `setA_7.asm` using NASM and GCC.

## Prerequisites

Ensure the following tools are installed:

- **NASM**
- **LD**

Check installation with:

```bash
nasm -v
ld --version
```

## Steps to Run

1. **Assemble with NASM**

   ```bash
    nasm -f elf32 setA_7.asm -o setA_7.o
   ```

   - `-f elf32`: Specifies 32-bit format.
   - `-o setA_7.o`: Output object file.

   
2. **Link with LD**

   ```bash
   ld -m elf_i386 setA_7.o -o setA_7
   ```

   - `setA_7.o`: Input object file.
   - `-o setA_7`: Output executable.

3. **Run the Executable**

   ```bash
   ./setA_7
   ```

## Example Workflow

```bash
nasm -f elf32 -o setA_7.o setA_7.asm
ld -m elf_i386 setA_7.o -o setA_7
./setA_7
```




# Running `setB_11.asm` Using NASM and GCC

This guide explains how to assemble, link, and execute `setB_11.asm` using NASM and GCC.

## Prerequisites

Ensure the following tools are installed:

- **NASM**
- **GCC**

Check installation with:

```bash
nasm -v
gcc --version
```

## Steps to Run

1. **Assemble with NASM**

   ```bash
   nasm -f elf32 setB_11.asm -o setB_11.o
   ```

   - `-f elf32`: Specifies 32-bit format.
   - `-o setB_11.o`: Output object file.

2. **Link with GCC**

   ```bash
   gcc -m32 -no-pie setB_11.o -o setB_11
   ```

   - `setB_11.o`: Input object file.
   - `-o setB_11`: Output executable.

3. **Run the Executable**

   ```bash
   ./setB_11
   ```

## Example Workflow

```bash
nasm -f elf32 setB_11.asm -o setB_11.o
gcc -m32 -no-pie setB_11.o -o setB_11
./setB_11
```
