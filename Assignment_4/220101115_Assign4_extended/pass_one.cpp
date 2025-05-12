#include "top.h"



void pass1()
{
    cout << "Started Pass 1" << endl;
    ifstream input("sample_input.txt");
    ofstream intermediate("intermediate.txt");
    ofstream symtab("symtab.txt");

    string label, opcode, operand;
    string line = "";
    getline(input, line);
    vs temp1 = splitLine(0,line);
    assign(temp1, label, opcode, operand);

    if (opcode == "START")
    {

        LOCCTR = hexToInt(operand);
        startingAddress = LOCCTR;
        addSpacesEnd(operand, 7);
        operand += line;
        intermediate << operand << endl;

        getline(input, line);
        temp1 = splitLine(0,line);
        assign(temp1, label, opcode, operand);
    }
    else
    {
        LOCCTR = 0;
    }

    while (opcode != "END")
    {

        if (label != "." and label != "")
        {
            if (SYMTAB.find(label) != SYMTAB.end())
            {
                cout << "Duplicate Label found \n";
            }
            else
            {
                SYMTAB[label] = LOCCTR;
            }
        }
        else if (label == ".")
        {
            intermediate << line << endl;
            getline(input, line);
            temp1 = splitLine(0,line);
            assign(temp1, label, opcode, operand);
            continue;
        }

        string temp = intToHex(LOCCTR);
        if (OPTAB.find(opcode) != OPTAB.end())
        {
            LOCCTR += 3;
        }
        else if (opcode == "WORD")
        {
            LOCCTR += 3;
        }
        else if (opcode == "BYTE")
        {
            LOCCTR += byteOperandLength(operand); // byteOperandLength returns the length of constant in bytes(if X(hex), then each bit is equivalent to 4bits and if it is C(char), then each char is 1 byte)
        }
        else if (opcode == "RESW")
        {
            LOCCTR += 3 * stoi(operand);
        }
        else if (opcode == "RESB")
        {
            LOCCTR += stoi(operand);
        }
        else
        {
            cout << opcode << endl;
            cout << "Error: Invalid opcode" << endl;
        }

        addSpacesEnd(temp, 7);
        temp += line;
        intermediate << temp << endl;

        getline(input, line);
        temp1 = splitLine(0,line);
        assign(temp1, label, opcode, operand);
    }

    addSpacesEnd(operand, 7);
    operand += line;
    intermediate << line << endl;
    programLength = LOCCTR - startingAddress;

    for (auto i = SYMTAB.begin(); i != SYMTAB.end(); i++)
    {
        string tmp = i->first;
        appendEnd(tmp, 10, ' ');
        if (i == SYMTAB.begin())
        {
            symtab << tmp << "     " << intToHex(i->second);
        }
        else
        {
            symtab << "\n"
                   << tmp << "     " << intToHex(i->second);
        }
    }

    input.close();
    intermediate.close();
    symtab.close();
    cout << "PAss 1 completed" << endl;
}
