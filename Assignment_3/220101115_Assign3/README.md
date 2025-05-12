# Assignment 3 CS348
Submission by:
- Yash Jain (220101115)

The following dependencies were used:
- nasm
- gcc

I have coded a program in assembly language for 32 bit x86 architecture, and implemented the following:
- Creation of a binary tree.
- Provided the functionality for dynamic input insertion for constructing the binary tree.
- Performed inorder, preorder and postorder traversal of the binary tree.


## Input Format

- First, you have to insert the number of nodes in binary tree, n. We are assuming that nodes will be numbered from 1 to n and he maximum value of n is 100.
- Then, you have to insert the edges, line by line as shown in the example below.The format for each line will be x y z, where x = current node, y = left child and z = right child. Also, input should be given in ascending order i.e. x should be given in increasing order from 1 to n.
- For NULL child, you will have to insert 999.

### Running the code
1. Assembling the code to generate machine language code from assembly code:

```bash
nasm -f elf32 220101115_assign3.asm
```

2. Lnking the code:
```bash
gcc -m32 220101115_assign3.o -o output -no-pie
```
3. Running the executable file:
```bash
./output
```

#### Example output

Enter the number of nodes(max 100): 7
For each node, print x y z where x = current node, y=left child, z= right child (999 for NULL i.e. no child)
1 2 3
2 999 4
3 5 6
4 999 999
5 7 999
6 999 999
7 999 999
Inorder traversal is: 2 4 1 7 5 3 6 Preorder traversal is: 1 2 4 3 5 7 6 Postorder traversal is: 4 2 7 5 6 3 1


