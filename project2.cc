#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include "fraction.h"
#include "dictionary.h"
#include "stack.h"

using namespace std;

struct Operand{
    string name;
    Fraction val;
};

Stack<Operand> numStack;
Stack<char> opStack;

Dictionary _Dictionary = Dictionary();

bool hasPrecedence(char a, char b){
    if (b == '*' or b == '/')
        return true;
    else if ((b == '+' or b == '-')&&(a != '*' and a != '/' and a != '$'))
    	return true;
    else
        return false;
}


void DoOp(char s) {
    Operand 
        rhs, lhs, res;
    Fraction
        num;
    char
        x;

    rhs = numStack.pop();
    lhs = numStack.pop();
    x = s;
    
    if (!rhs.name.empty()) {
    	rhs.val = _Dictionary.search(rhs.name);
    	numStack.push(rhs);
    }
    if ((x != '=') && (!lhs.name.empty())) {
    	lhs.val = _Dictionary.search(lhs.name);
    	numStack.push(lhs);
	}
    if (x == '='){
        _Dictionary.add(lhs.name, rhs.val);
        lhs.val = rhs.val;
        numStack.push(lhs);
    }
    if (x == '+') {
        num = lhs.val + rhs.val;
        res.val = num;
        numStack.push(res);
    }
    if (x == '-') {
        num = lhs.val - rhs.val;
        res.val = num;
        numStack.push(res);
    }
    if (x == '*') {
        num = lhs.val * rhs.val;
        res.val = num;
        numStack.push(res);
    }
    if (x == '/') {
        num = lhs.val / rhs.val;
        res.val = num;
        numStack.push(res);
    }

}

void Evaluate(string s){
    numStack.clear();
    opStack.clear();
    opStack.push('$');
    uint32_t first = 0;
    Operand temp;
    
    while (first < s.length()){
        if(isdigit(s[first])){
            string number = "";
            while (isdigit(s[first]) && first < s.length()){
                number = number + s[first];
                first++;
            }
            temp.val = Fraction(stoi(number), 1);
            temp.name = "";
            numStack.push(temp);
        }
        else if (isalpha(s[first])) {
            string variable = "";
            while (isalpha(s[first]) && first < s.length()) {
                variable = variable + s[first];
                first ++;
            }
            temp.name = variable;
            temp.val = -1;
            numStack.push(temp);
        }
        else if (s[first] == '(') {
            opStack.push('(');
            first++;
        }
        else if (s[first] == ')') {
        	while(opStack.peek() != '('){
                	DoOp(opStack.pop());
                }
            	opStack.pop();
           	first++;
        }
        else if ((s[first] == '+') || (s[first] == '-') || (s[first] == '*') || (s[first] == '/') || (s[first] == '=')){
            	if (hasPrecedence(opStack.peek(), s[first])) {
            		opStack.push(s[first]);
            		first++;
            		if(isdigit(s[first])){
           		string number = "";
            		while (isdigit(s[first]) && first < s.length()){
                		number = number + s[first];
                		first++;
            		}
            		temp.val = Fraction(stoi(number), 1);
            		temp.name = "";
            		numStack.push(temp);
            		DoOp(opStack.pop());
        		}
        		else if (isalpha(s[first])) {
            		string variable = "";
            		while (isalpha(s[first]) && first < s.length()) {
                		variable = variable + s[first];
                		first ++;
            		}
            		temp.name = variable;
            		temp.val = -1;
            		numStack.push(temp);
            		DoOp(opStack.pop());
        		}
        		else{
        			first++;
        		}
           	}
           	else{
           		opStack.push(s[first]);
           		first++;
           	}
           	
        }
        else{
        	first++;
        }
    }
    while(opStack.peek(	) != '$'){
        DoOp(opStack.pop());
    }
        if ((s[first] != '=') && (!numStack.isEmpty())) {
        temp = numStack.pop();
    	temp.val = _Dictionary.search(temp.name);
    	numStack.push(temp);
	}
    cout << numStack.pop().val << endl;
}

void Debugger(string s){
    numStack.clear();
    opStack.clear();
    uint32_t first = 0;


    while (first < s.length()){
        if(isdigit(s[first])){
            string number = "";
            while (isdigit(s[first]) && first < s.length()){
                number = number + s[first];
                first++;
            }
            cout << Fraction(stoi(number), 1) << endl;
        }
        else if (isalpha(s[first])) {
            string variable = "";
            while (isalpha(s[first]) && first < s.length()) {
                variable = variable + s[first];
                first++;
            }
            cout << variable << endl;
        }
        else if (s[first] == '(') {
            cout << '(' << endl;
            first++;
        }
        else if (s[first] == ')') {
            cout << ')' << endl;
            first++;
        }
        else if (s[first] == '+'){
            cout << '+' << endl;
            first++;
        }
        else if (s[first] == '-') {
        	cout << '-' << endl;
        	first++;
        }
        else if (s[first] == '*') {
        	cout << '*' << endl;
        	first++;
        }
        else if (s[first] == '/') {
        	cout << '/' << endl;
        	first++;
        }
        else if (s[first] == '=') {
        	cout << '=' << endl;
        	first++;
        }
        else{
        first++;
        }
    }
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

    do{
        cout << "calc: ";
        getline(cin, expression);
;

        if(expression != "#") {
            if (debug == false) {
                Evaluate(expression);
            }
            else{
                Debugger(expression);
            }
        }
    }
    while (expression != "#");
    
        return 0;
}
