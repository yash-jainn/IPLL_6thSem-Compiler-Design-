#include "helper.cpp"
#include "pass_one.cpp"
#include "pass_two.cpp"

using namespace std;

void GenerateOptab() {
    // cout<<"OPTAB"<<endl;
    ifstream optab("optab.txt");
    string data="",temp= "";
    int i=0;
    
    while(getline(optab, data)){
        i=0;
        // cout<<data<<endl;
        while(data[i]!=' '){
            temp+=data[i];
            i++;
        }
        while(data[i]==' '){
                i++;
        }
        i--;
        // cout<<temp<<endl;
        OPTAB[temp] = data.substr(i+1);
        temp="";
        // cout<<OPTAB[temp]<<endl;
    }
    
    return;
}

vector<string> splitLine(int index, string& data) {
     int ctr = 0;
    vector<string> ret(3, "");
    if (data[0] == '.')
    {
        ret[0] = ".";
        return ret;
    }

    f(i, index , data.size())
    {

        if (data[i] == ' ')
        {
            while (data[i] == ' ')
            {
                i++;
                if (i == data.size())
                {
                    break;
                }
            }
            ctr++;
            i--;
        }
        else
        {
            ret[ctr] += data[i];
        }
    }
    return ret;
}

string constObjCode(string operand) {
    string res = "";
    
    // Case for character operand (e.g., 'A')
    if ((operand[0] == 'C' || operand[0] == 'c') && operand[1] == '\'') {
        for (int i = 2; i < operand.size(); i++) {
            if (operand[i] == '\'') {
                break;
            }
            res += intToHex(int(operand[i]));
        }
        return res;
    }
    
    // Case for hexadecimal operand (e.g., X'FF')
    if ((operand[0] == 'X' || operand[0] == 'x') && operand[1] == '\'') {
        for (int i = 2; i < operand.size(); i++) {
            if (operand[i] == '\'') {
                break;
            }
            res += operand[i];
        }
        return res;
    }
    
    // Case for numeric operand (e.g., 1234)
    res = intToHex(convertToInt(operand));
    appendStart(res, 6, '0');
    return res;
}

int byteOperandLength(string& s) {
    int length = 0;
    char quoteChar = '\'';
    
    // Hexadecimal case: Each pair of hex digits represents one byte (4 bits each)
    if ((s[0] == 'x' || s[0] == 'X') && s[1] == quoteChar) {
        for (int i = 2; i < s.size(); i += 2) {
            if (s[i] == quoteChar) {
                break;
            } else {
                length += 1;
            }
        }
    }
    // Character case: Each character represents one byte (1 byte per char)
    else if ((s[0] == 'c' || s[0] == 'C') && s[1] == quoteChar) {
        for (int i = 2; i < s.size(); i++) {
            if (s[i] == quoteChar) {
                break;
            } else {
                length += 1;
            }
        }
    }
    
    return length;
}

int main() {
    GenerateOptab();
    pass1();
    pass2();
}












