#include "dictionary.h"
#include "fraction.h"
#include "stack.h"

using namespace std;

struct operand {
    string name;
    Fraction num;
};

Stack<operand> NumStack;
Stack<char> OpStack;

Dictionary dict = Dictionary();

bool hasPrecedence(char a, char b) {//watch out for this
    return ((b == '*' || b == '/') || (b == '+' || b == '-')) && !(a == '*' || a == '/');
}

Fraction DoOp(Fraction a, char x, Fraction){//new addition, alter if fails
    if (x == '+') {
        return a + b;
    }
    if (x == '-') {
        return a - b;
    }
    if (x == '*') {
        return a * b;
    }
    if (x == '/') {
        return a / b;
    }
}
/*void DoOp() {//maybe adjust
	operand rhs, lhs, res;
	Fraction num;
	char x;
	
	rhs = NumStack.pop();
	lhs = NumStack.pop();
	x = OpStack.pop();
	
	if(x == '+') {
		num = lhs.num + rhs.num;
		res.num = num;
		NumStack.push(res);
	}
	if (x == '*') {
		num = lhs.num * rhs.num;
		res.num = num;
		NumStack.push(res);
	}
}*/


void Eval(string s) {
    NumStack.clear();
    OpStack.clear();
    OpStack.push('$');
    int first = 0;
    operand NumInstance;
    string wholeNumber = "";
    string wholeVariable = "";
    string assignment = "";
    Fraction a,b;

    while (first < s.length()) {
        if (isdigit(s[first])) {
        wholeNumber = "";
            while (isdigit(s[first]) && first < s.length()) {
                wholeNumber = wholeNumber + s[first];
                first++;
            }
            NumInstance.num = Fraction(stoi(wholeNumber), 1);
            NumInstance.name = "";
            NumStack.push(NumInstance);
            //first++;
        }
        else if (isalpha(s[first])) {
            wholeVariable = "";
            while (isalpha(s[first]) && first < s.length()) {
                wholeVariable = wholeVariable + s[first];
            first ++;
            }
            NumInstance.name = wholeVariable;
            NumInstance.num = Fraction();
            NumStack.push(NumInstance);
            //first++;
        }
        else if (s[first] == '(') {
            OpStack.push('(');
            first++;
        }
        else if (s[first] == ')') {
            while(OpStack.peek() != '(') {
                NumInstance = NumStack.pop();
                if (NumInstance.name != "") {
                    a = dict.search(NumInstance.name);
                }
                else{
                    a = NumInstance.num;
                }
                NumInstance = NumStack.pop();
                if (NumInstance.name != "") {
                    b = dict.search(NumInstance.name);
                }
                else {
                    b = NumInstance.num;
                }
                NumInstance.num = DoOp(b,OpStack.pop(), a);
                NumInstance.name = "";
                NumStack.push(NumInstance);
            }
            OpStack.pop();
            first++;
        }
        else if (s[first] == '+' || s[first] == '-' || s[first] == '*' || s[first] == '/') {
            while (hasPrecedence(OpStack.peek(), s[first])) {
                NumInstance = NumStack.pop();
                if (NumInstance.name != "") {
                    a = dict.search(NumInstance.name);
                }
                else{
                    a = NumInstance.num;
                }
                NumInstance = NumStack.pop();
                if (NumInstance.name != "") {
                    b = dict.search(NumInstance.name);
                }
                else {
                    b = NumInstance.num;
                }
                NumInstance.num = DoOp(b,OpStack.pop(), a);
                NumInstance.name = "";
                NumStack.push(NumInstance);
            
            }
            OpStack.push(s[first]);
            first++;
            }
        else if (s[first] == '=') {
            OpStack.push(s[first]);
            first++;
        }
        else{
        first++;
        }
    while(OpStack.peek() != '$') {
        NumInstance = NumStack.pop();
        if (NumInstance.name != "") {
                    a = dict.search(NumInstance.name);
                }
                else{
                    a = NumInstance.num;
                }
                NumInstance = NumStack.pop();
                if (NumInstance.name != "") {
                    b = dict.search(NumInstance.name);
                }
                else {
                    b = NumInstance.num;
                }
                if (OpStack.peek() == '=') {
                    assignment = NumInstance.name;
                    dict.add(assignment, a);
                    cout << a << endl;
                }
                NumInstance.num = DoOp(b,OpStack.pop(), a);
                NumInstance.name = "";
                NumStack.push(NumInstance);
            }
        if(NumStack.peek().name == "") {
            cout << NumStack.peek().num << endl;
        }
        else {
            cout << dict.search(NumStack.pop().name) << endl;
        }
    }
}
void Debugger(string s) {
    NumStack.clear();
    OpStack.clear();
    OpStack.push('$');
    int first = 0;
    operand NumInstance;
    string wholeNumber = "";
    string wholeVariable = "";
    string assignment = "";
    Fraction a,b;

    while (first < s.length()) {
        if (isdigit(s[first])) {
            wholeNumber = "";
            while (isdigit(s[first]) && first < s.length()) {
                wholeNumber = wholeNumber + s[first];
                first++;
            }
            NumInstance.num = Fraction(stoi(wholeNumber), 1);
            NumInstance.name = "";
            NumStack.push(NumInstance);
        }
        else if (isalpha(s[first])) {
            wholeVariable = "";
            while (isalpha(s[first]) && first < s.length()) {
                wholeVariable = wholeVariable + s[first];
                first ++;
            }
            NumInstance.name = wholeVariable;
            NumInstance.num = Fraction();
            NumStack.push(NumInstance);
        }
        else if (s[first] == '(') {
            OpStack.push('(');
            first++;
        }
        else if (s[first] == ')') {
            OpStack.push(')');
            first++;
        }
        else if (s[first] == '+' || s[first] == '-' || s[first] == '*' || s[first] == '/') {
            OpStack.push(s[first]);
            first++;
         }

        else if (s[first] == '=') {
            OpStack.push(s[first]);
            first++;
        }
        else {
            first++;//new addition
        }

    while(!OpStack.isEmpty()) {
        cout << OpStack.pop() << endl;
    }
    while(!NumStack.isEmpty()) {
        if(NumStack.peek().name != "") {
            cout << NumStack.pop().name << endl;
        }
        else{
        cout << NumStack.pop().num << endl;
        }
        }
    }
}

string spacerem(const string& input){
    string result;
    for (char c: input){
        if (!std::isspace(c)) {
            result = result + c;
        }
    }
    return result;
}

int main(int argc, char* argv[]) {

    int option;
    bool debug = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            debug = true;
            cout << "Debug" << endl;
        }
    }
    string expression = "";
    string result = "";

    do{
        cout << "calc: ";
        getline(cin, expression);

    result = spacerem(expression);

        if(expression != "#") {
            if (debug == false) {
                Eval(result);
            }
            else{
                Debugger(result);
            }
        }
    }
    while (result != "#");
    
        return 0;
}
