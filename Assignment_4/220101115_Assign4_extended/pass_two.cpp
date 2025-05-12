#include "top.h"

// Function to simulate the second pass of the assembler
void pass2()
{
    cout << "Started PASs 2" << endl;
    
    ifstream intermediate("intermediate.txt");
    ofstream final("final.txt");
    ofstream outputObj("output.o");
    ofstream readableFile("readable_output.txt");
    
    string line;
    
    // Read first line to initialize the process
    getline(intermediate, line);
    string objectCode = "";
    string locCounter = line.substr(0, 4);
    vs temp = splitLine(7, line);
    
    string label, opcode, operand;
    assign(temp, label, opcode, operand);

    string textRecord, startLoc;
    string readableHeader = " ^     ^ ", readableLine = readableHeader;
    
    // Process the first opcode, handle 'START' case
    if (opcode == "START")
    {
        final << line << endl;
        appendEnd(label, 6, ' ');
        appendStart(operand, 6, '0');
        string length = intToHex(programLength);
        appendStart(length, 6, '0');
        outputObj << "H" << label << operand << length << endl;
        readableFile << "H" << label << operand << length << endl;
        readableFile << " ^     ^     ^" << endl;
        startLoc = operand;
        textRecord = ""; // Initialize textRecord
    }

    // Start processing lines after the first one
    while (getline(intermediate, line))
    {
        locCounter = line.substr(0, 4);
        temp = splitLine(7, line);
        assign(temp, label, opcode, operand);

        // Continue until "END" opcode is encountered
        if (opcode == "END") 
        {
            break;
        }

        if(label == "."){
            final << line << endl;
            continue;
        }
        
        if (label != ".") // Skip comment lines
        {
            if (OPTAB.find(opcode) != OPTAB.end())
            {
                if (true)
                {
                    // If operand exists, find its object code from SYMTAB
                    if (SYMTAB.find(operand) != SYMTAB.end())
                    {
                        objectCode = OPTAB[opcode] + intToHex(SYMTAB[operand]);
                    }
                    else if (operand[operand.size() - 1] == 'X' && operand[operand.size() - 2] == ',')
                    {
                        operand.pop_back();
                        operand.pop_back();
                        objectCode = OPTAB[opcode] + intToHex(SYMTAB[operand] + hexToInt("8000"));
                    }
                    else
                    {
                        objectCode = OPTAB[opcode];
                        appendEnd(objectCode, 6, '0');
                    }
                }
            }
            else if (opcode == "BYTE" || opcode == "WORD")
            {
                // Handle BYTE or WORD cases
                objectCode = constObjCode(operand);
            }
            else if (opcode == "RESW" || opcode == "RESB")
            {
                // Handle RESW and RESB: These should not generate object code
                objectCode = "";
            }

            appendEnd(line, 35, ' ');
            line += objectCode;
            final << line << endl;
            
            if (startLoc.empty() && !objectCode.empty())
            {
                startLoc = locCounter;
            }

            if (objectCode.empty() || textRecord.size() + objectCode.size() > 60)
            {
                // If text record exceeds limit, finalize it and start a new one
                if (!textRecord.empty())
                {
                    appendStart(startLoc, 6, '0');
                    string hexSize = intToHex(textRecord.size() / 2);
                    appendStart(hexSize, 2, '0');
                    textRecord = "T" + startLoc + hexSize + textRecord;
                    outputObj << textRecord << endl;
                    readableFile << textRecord << endl;
                    readableFile << readableLine << endl;
                }
                textRecord = objectCode;
                readableLine = readableHeader;
                startLoc.clear();
                if (!objectCode.empty())
                {
                    startLoc = locCounter;
                    readableLine.push_back('^');
                    appendEnd(readableLine, readableLine.size() + objectCode.size() - 1, ' ');
                }
            }
            else if (!objectCode.empty())
            {
                // Continue appending to current textRecord
                textRecord += objectCode;
                readableLine.push_back('^');
                appendEnd(readableLine, readableLine.size() + objectCode.size() - 1, ' ');
            }
        }
    }

    // Finalize the last record after the loop ends
    final << line << endl;
    if (!textRecord.empty())
    {
        appendStart(startLoc, 6, '0');
        string hexSize = intToHex(textRecord.size() / 2);
        appendStart(hexSize, 2, '0');
        textRecord = "T" + startLoc + hexSize + textRecord;
        outputObj << textRecord << endl;
        readableFile << textRecord << endl;
        readableFile << readableLine << endl;
    }

    // Write the final "E" record
    string end = intToHex(startingAddress);
    appendStart(end, 6, '0');
    textRecord = "E" + end;
    outputObj << textRecord << endl;
    readableFile << textRecord << endl;
    readableFile << " ^" << endl;

    // Close all files
    intermediate.close();
    final.close();
    outputObj.close();
    readableFile.close();
    
    cout << "Completed PASs 2" << endl;
}
