#include <iostream>
#include <stack>
#include <string>
#include <stdio.h>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);


    std::stack <Bracket> opening_brackets_stack;
    int error=0;
    for (int position = 0; position < text.length(); position++) {
        char next = text[position];
        Bracket* tmp = new Bracket(next, position+1);

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            opening_brackets_stack.push(*tmp);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.empty()){
                error=position+1;
                break;
            }

            else if (opening_brackets_stack.top().Matchc(next))
                opening_brackets_stack.pop();
            else{
                error=position+1;
                break;
            }
                
        }
        delete tmp;
    }

    // Printing answer, write your code here
    if (error==0 && opening_brackets_stack.size()==0)
        std::cout<<"Success"<<std::endl;
    else if (error==0 && opening_brackets_stack.size()!=0)
        printf("%d\n",opening_brackets_stack.top().position);
    else printf("%d\n", error);


    return 0;
}
