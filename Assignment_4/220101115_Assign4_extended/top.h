#ifndef assembler
#define assembler

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <array>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <cassert>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <bitset>
#include <chrono>
#include <random>
#include <fstream>
#include <iterator>
#include <complex>
#include <cstring>
#include <list>
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
// typedef tree<
//     pair<int, int>,
//     null_type,
//     less<pair<int, int>>,
//     rb_tree_tag,
// tree_order_statistics_node_update> ordered_multiset;


#define pq priority_queue
#define ya cout<<"YES"<<endl
#define na cout<<"NO"<<endl
#define pb push_back
#define in insert
#define vi vector <int>
#define vpi vector<pair<int,int>>
#define si set <int>
#define f(i,s,e) for(int i=s;i<e;i++)
#define fori for(int i=0;i<n;i++)
#define allv (v.begin(),v.end())
#define all(s) (s.begin(),s.end())
// #define int long long
#define yashu_doshi ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define log log10
#define pp pair<int,int>
#define mm map<int,int>
//vector<pp>movve={{0,-1},{-1,0},{1,0},{0,1},{1,1},{-1,-1},{1,-1},{-1,1}};

#define tc int t; cin>>t; while(t--)
#define vs vector<string>


int LOCCTR = 0;
int startingAddress = 0;
int programLength = 0;
map<string, int> SYMTAB; 
map<string, string> OPTAB; 

// vector<string> op{"ADD","AND","COMP","DIV","J","JEQ","JGT","JLT","JSUB","LDA","LDCH","LDL","LDX",
// "MUL","OR","RD","RSUB","STA","STCH","STL","STSW","STX","SUB","TD","TIX","WD"};

// vector<string> opc{"18","40","28","24","3C","30","34","38","48","00","50","08","04","20","44","D8","4C",
// "0C","54","14","E8","10","1C","E0","2C","DC"};

vector<string> splitLine( int index,string& data);
string constObjCode(string operand);
int byteOperandLength(string& s);

#endif