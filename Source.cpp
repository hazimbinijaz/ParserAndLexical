#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<fstream>
#include<algorithm>
using namespace std;
//----------------LEXICAL Global Variable-------------
struct SymbolTable
{
public:
	string keyword;
	string type;

	void insert(string kw, string t)
	{
		keyword = kw;
		type = t;
	}
	bool ismatch(string kw)
	{
		int s = kw.length();
		if (kw.length() != keyword.length())
			return false;
		for (int i = 0; i < s; i++)
		{
			if (kw[i] != keyword[i])
				return false;
		}
		return true;
	}
	void print(int i)
	{
		cout << i << "\t" << type << " " << keyword << "\n";
	}
};
int CurrentState = 0;
int TT[62][24];
int Map[128][1];
int FinalStates[26][1];
string ReservedWords[60][1];
string Code[10];
const int symbolTableSize = 500;
struct SymbolTable stable[symbolTableSize];

//----------------Parser Global Variables-------------
class Stack
{
	string strs[300];
public:

	int sindex = 0;
	bool IsEmpty()
	{
		return sindex == 0;
	}
	bool IsFull()
	{
		return sindex == 300;
	}
	void Push(string s)
	{
		if (IsFull())
		{
			cout << "Stack Full.\n";
			exit(1);
		}
		else
		{
			strs[sindex] = s;
			sindex++;
		}
	}
	string Pop()
	{
		sindex--;
		string s = strs[sindex];
		strs[sindex] = '\0';
		return s;
	}

	string Top()
	{
		return strs[sindex - 1];
	}
	void output()
	{
		cout << "----------------- Stack ---------------------\n";
		for (int i = 0; i < sindex; i++)
			cout << i << "-" << strs[i] << endl;
	}
};
int TokenNumber = 1;
int PT[34][27];
string NTMap[34] = { "\0" };;
string TMap[27] = { "\0" };
char HT[70][70] = { '\0' };
Stack ParsingStack;
string Tokens[50] = { "\0" };
int RuleNumber = 0;

//----------------LEXICAL Functions-------------
struct Token 
{
	int id;
	string name;
	string TheTokenItself;
};

vector<Token> ListOfTokens;

bool CheckIfFinalState()
{
	for (int i = 0; i < 26; i++)
	{
		if(CurrentState==FinalStates[i][0])
			return true;
	}
	return false;
}

void InitializationFunction()
{
	
	ifstream Take;
	Take.open("TT.txt");
	int rows = 0, cols = 0;
	//TT Initialization
	do
	{
		Take >> TT[rows][cols];
		cols++;
		if (cols == 24)
		{
			rows++;
			cols = 0;
		}
	} while (!Take.eof());
	Take.close();
	//Map Initialization
	
	Take.open("Map.txt");
	rows = 0;
	do
	{
		Take >> Map[rows][0];
		rows++;
	} while (!Take.eof());
	Take.close();
	
	//Reserved Words Initialization
	rows = 0;
	Take.open("ReservedWords.txt");
	do
	{
		Take >> ReservedWords[rows][0];
		rows++;
	} while (!Take.eof());
	Take.close();
	
	//Code Initialization
	rows = 0;
	Take.open("Code.txt");
	do
	{
		getline(Take, Code[rows]);
		rows++;
	
	} while (!Take.eof());
	Take.close();

	//FinalStates Initialization
	rows = 0;
	Take.open("FinalStates.txt");
	do
	{
		Take >> FinalStates[rows][0];
		rows++;
	} while (!Take.eof());
	Take.close();
	
}

bool CheckIfReservedWords(string ToSearch)
{
	for (int i = 0; ReservedWords[i] != '\0'; i++)
	{
		if (ReservedWords[i][0].compare(ToSearch) == 0)
			return true;
	}
	return false;
}

void Lexical()
{
	string RWtemp = { '\0' };
	Token temp;
	int index = 0;
	int rows = 0;
	ifstream Take;
	Take.open("Code.txt");
	ifstream ForRW;
	ForRW.open("Code.txt");
	ForRW >> RWtemp;



	do
	{
		string Arr = { '\0' };
		getline(Take, Arr);

		for (int i = 0; Arr[i]!='\0' + 1; i++)
		{
			if (Arr[i] == '\0')
			{
				if (CurrentState == 2)
					CurrentState = 3;

				else if (CurrentState == 4)
					CurrentState = 5;
				
				else if (CurrentState == 7)
					CurrentState = 8;

				else if (CurrentState == 10)
					CurrentState = 11;

				else if (CurrentState == 6)
					CurrentState = 9;

				else if (CurrentState == 13)
					CurrentState = 14;
				
				else if (CurrentState == 15)
					CurrentState = 16;
				
				else if (CurrentState == 20)
					CurrentState = 21;
				
				else if (CurrentState == 22)
					CurrentState = 23;

				else if (CurrentState == 24)
					CurrentState = 26;
				
				else if (CurrentState == 25)
					CurrentState = 26;

				else if(CurrentState==18)
					CurrentState = 19;

				else if (CurrentState == 29)
					CurrentState = 26;
				
				else if (CurrentState == 30)
					CurrentState = 31;

				else if (CurrentState == 32)
					CurrentState = 33;

				else if (CurrentState == 34)
					CurrentState = 35;

				else if (CurrentState == 36)
					CurrentState = 37;

				else if (CurrentState == 38)
					CurrentState = 39;
			
				else if (CurrentState == 40)
					CurrentState = 41;

				else if (CurrentState == 43)
					CurrentState = 44;

				else if (CurrentState == 46)
					CurrentState = 47;

				else if (CurrentState == 49)
					CurrentState = 50;
			
				else if (CurrentState == 51)
					CurrentState = 52;

				else if (CurrentState == 53)
					CurrentState = 54;

				else if (CurrentState == 55)
					CurrentState = 56;

				else if (CurrentState == 57)
					CurrentState = 58;

				else if (CurrentState == 59)
					CurrentState = 60;
				
				else if (CurrentState == 61)
					CurrentState = 62;
			
				else
				{
					
					if (CheckIfReservedWords(RWtemp))
					{
						CurrentState = 1234;
					}
					
				}
			}
			else
				CurrentState=TT[CurrentState][Map[Arr[i]][0]];
			
			if (CheckIfFinalState())
			{
				if (CurrentState == 1234)
				{
						//Make Token Of Reserved Words
						temp.id = 666;
						temp.name = "Reserved Word";
						temp.TheTokenItself = RWtemp;
						ListOfTokens.push_back(temp);
						CurrentState = 0;

						if (Arr[i] == '\0')
							break;
				}
				
				if (CurrentState == 19)
				{
					//Make Token Of ID
					temp.id = 6;
					temp.name = "Identifier";
					temp.TheTokenItself = "id";
					ListOfTokens.push_back(temp);
					CurrentState = 0;

					if (Arr[i] == '\0')
						break;
					
					
					
				}
				else if (CurrentState == 26)
				{
					//Make Token of Number
					temp.id = 7;
					temp.name = "Number";
					temp.TheTokenItself = "number";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}
				
				else if (CurrentState == 3)
				{
					//Make Token of ||
					temp.id = 0;
					temp.name = "Operator";
					temp.TheTokenItself = "||";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}
				
				else if (CurrentState == 5)
				{
					//Make Token of %
					temp.id = 1;
					temp.name = "Operator";
					temp.TheTokenItself = "%";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}
			
				else if (CurrentState == 8)
				{
					//Make Token of ++
					temp.id = 22;
					temp.name = "Operator";
					temp.TheTokenItself = "++";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}
				
				else if (CurrentState == 9)
				{
					//Make Token of +
					temp.id = 2;
					temp.name = "Operator";
					temp.TheTokenItself = "+";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}
				
				else if (CurrentState == 11)
				{
					//Make Token of +=
					temp.id = 23;
					temp.name = "Operator";
					temp.TheTokenItself = "+=";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}
			
				else if (CurrentState == 14)
				{
					//Make Token of ==
					temp.id = 33;
					temp.name = "Operator";
					temp.TheTokenItself = "==";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}
				
				else if (CurrentState == 16)
				{
					//Make Token of -
					temp.id = 4;
					temp.name = "Operator";
					temp.TheTokenItself = "-";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}
				
				else if (CurrentState == 21)
				{
					//Make Token of *
					temp.id = 8;
					temp.name = "Operator";
					temp.TheTokenItself = "*";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 23)
				{
					//Make Token of /
					temp.id = 9;
					temp.name = "Operator";
					temp.TheTokenItself = "/";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 31)
				{
					//Make Token of <
					temp.id = 11;
					temp.name = "Operator";
					temp.TheTokenItself = "<";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 33)
				{
					//Make Token of <=
					temp.id = 113;
					temp.name = "Operator";
					temp.TheTokenItself = "<=";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 35)
				{
					//Make Token of <<
					temp.id = 1111;
					temp.name = "Operator";
					temp.TheTokenItself = "<<";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 37)
				{
					//Make Token of >
					temp.id = 12;
					temp.name = "Operator";
					temp.TheTokenItself = ">";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 39)
				{
					//Make Token of >=
					temp.id = 123;
					temp.name = "Operator";
					temp.TheTokenItself = ">=";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 41)
				{
					//Make Token of >>
					temp.id = 1212;
					temp.name = "Operator";
					temp.TheTokenItself = ">>";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 44)
				{
					//Make Token of !=
					temp.id = 133;
					temp.name = "Operator";
					temp.TheTokenItself = "!=";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 47)
				{
					//Make Token of ::
					temp.id = 1414;
					temp.name = "Operator";
					temp.TheTokenItself = "::";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				

				else if (CurrentState == 50)
				{
					//Make Token of &&
					temp.id = 15;
					temp.name = "Operator";
					temp.TheTokenItself = "&&";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 52)
				{
					//Make Token of (
					temp.id = 18;
					temp.name = "Operator";
					temp.TheTokenItself = "(";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 54)
				{
					//Make Token of )
					temp.id = 19;
					temp.name = "Operator";
					temp.TheTokenItself = ")";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 56)
				{
					//Make Token of {
					temp.id = 20;
					temp.name = "Operator";
					temp.TheTokenItself = "{";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 58)
				{
					//Make Token of }
					temp.id = 21;
					temp.name = "Operator";
					temp.TheTokenItself = "}";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 60)
				{
					//Make Token of [
					temp.id = 59;
					temp.name = "Operator";
					temp.TheTokenItself = "[";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}

				else if (CurrentState == 62)
				{
					//Make Token of ]
					temp.id = 23;
					temp.name = "Operator";
					temp.TheTokenItself = "]";
					ListOfTokens.push_back(temp);
					CurrentState = 0;
					if (Arr[i] == '\0')
						break;
				}
			}
		}
	
	} while (!Take.eof());

	ofstream Give;
	Give.open("Tokens.txt");
	for (int i = 0; i < ListOfTokens.size(); i++)
	{
		Give << "<" << ListOfTokens[i].id << ", " << ListOfTokens[i].name<<", "<<ListOfTokens[i].TheTokenItself << ">" << endl;
	}
	ofstream Give1;
	Give1.open("TokenItSelf.txt");
	for (int i = 0; i < ListOfTokens.size(); i++)
	{
		Give1 << ListOfTokens[i].TheTokenItself << endl;
	}

	
	if (!CheckIfFinalState())
	{
		ofstream Error;
		Error.open("Errors.txt");
		Error << "Error has occured";
	}
}

//----------------PARSER Functions-------------
void InitializationFunctionParser()
{

	ifstream Take;
	Take.open("PT.txt");
	int rows = 0, cols = 0;
	//PT Initialization
	do
	{
		Take >> PT[rows][cols];
		cols++;
		if (cols == 27)
		{
			rows++;
			cols = 0;
		}
	} while (!Take.eof());
	Take.close();

	//NTMap Initialization

	Take.open("NTMap.txt");
	rows = 0;
	do
	{
		Take >> NTMap[rows];
		rows++;
	} while (!Take.eof());
	Take.close();

	//TMap Initialization

	Take.open("TMap.txt");
	cols = 0;
	do
	{
		Take >> TMap[cols];
		cols++;
	} while (!Take.eof());
	Take.close();

	//Hash Map Initialization
	Take.open("HT.txt");
	rows = 0, cols = 0;
	do
	{
		Take.getline(HT[rows], 70);
		rows++;
	} while (!Take.eof());
	Take.close();

	rows = 0;
	Take.open("TokenItSelf.txt");
	do
	{
		Take >> Tokens[rows];
		rows++;
	} while (!Take.eof());
	Take.close();

}

int GetIndex(string ToFind, bool check)
{
	if (check == 0)//Check Tmap
	{
		for (int i = 0; TMap[i] != "\0"; i++)
		{
			if (TMap[i].compare(ToFind) == 0)
				return i;
		}
	}
	else//check NTmap
	{
		for (int i = 0; NTMap[i] != "\0"; i++)
		{
			if (NTMap[i].compare(ToFind) == 0)
				return i;
		}
	}
	return -1;
}

string GetSString(string s1, int indx)
{
	if (s1[indx] == ' ')
		indx++;
	char s2[50] = "\0";
	int si = 0;
	for (int i = indx; ; i++)
	{
		if (s1[i] == ' ' || s1[i] == '\0')
		{
			return s2;
		}
		s2[si] = s1[i];
		si++;
	}
}

void PushGrammer(string str)
{
	for (int i = str.size() - 1; i != -1; i--)
		if (str[i] == ' ' || i == 0)
			ParsingStack.Push(GetSString(str, i));
}

//void SpaceSeparatedStackPusher(string ToPush)
//{
//	string SingleWord = { "\0" };
//	int k = 0;
//	for (int j = SingleWord.size-1; j!=0; j--)
//	{
//		if (ToPush[j] != ' ')
//		{
//			SingleWord[k] = ToPush[j];
//			k++;
//		}
//		else
//		{
//			SingleWord[k] = '\0';
//			ParsingStack.Push(SingleWord);
//
//		}
//			
//	}
//}

void Parser()
{
	int StackPointer = 0;
	ParsingStack.Push("$");
	ParsingStack.Push(NTMap[0]);
	StackPointer++;
	int NTMapIndex = 0, TMapIndex = 0, TokenPointer = 0;
	string temp = { "\0" };
	for (int i = 0; true; i++)
	{
		if (Tokens[TokenPointer] == "\0")
			break;
		if (ParsingStack.Top() == Tokens[TokenPointer])
		{
			ParsingStack.Pop();
			TokenPointer++;
			cout << "Token # " << TokenNumber << " is Valid!" << endl;
			TokenNumber++;
		}
		else
		{
			//Pop from stack and find the index in NTmap put in NTIndex
			NTMapIndex = GetIndex(ParsingStack.Top(), 1);

			//Pop from Tokens find index in Tmap put in TIndex
			TMapIndex = GetIndex(Tokens[TokenPointer], 0);

			//Check both index in PT like PT[NTIndex][TIndex]
			//The output from above line will be a number search that number in the HT and push the content of the index in stack
			temp = HT[PT[NTMapIndex][TMapIndex] - 1];
			RuleNumber = PT[NTMapIndex][TMapIndex];
			cout << "Rule # " << RuleNumber << " Fired!" << endl;
			//For Panic Mode
			if (PT[NTMapIndex][TMapIndex] == 68)//Pop
				ParsingStack.Pop();

			else if (PT[NTMapIndex][TMapIndex] == 69)//Skip Input
			{
				TokenPointer++;
				cout << "Token # " << TokenNumber << " is Valid!" << endl;
				TokenNumber++;
			}
			else
			{
				ParsingStack.Pop();
				PushGrammer(temp);
			}
			//Repeat this until tokens are finished
		}


	}
}




void main()
{
	InitializationFunction();
	InitializationFunctionParser();
	Lexical();
	Parser();

}