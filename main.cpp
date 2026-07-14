#include <iostream>
#include <string>

#define LOG(x) std::cout << x;

//Number will have '0' token type
//Operators will have '1' token type
enum TokenType{
    INT = 0, OPERATOR
};

//Objects of this structure will be the indivisual characters in the user input
struct Token{
    int type;
    char op_value;
    int num_value;
    std::string type_str;
};
const std::string INT_TYPE = "Integer";
const std::string OP_TYPE = "Operator";

Token current_token;
int current_pos = 0;

bool is_digit(char& c){
    return (c >= '0' && c <= '9');
}

void get_next_token(std::string content){
    char c;
    c = content[current_pos];
        
    if (is_digit(c)){
        current_token.type = INT;
        current_token.num_value = c - '0';
        current_token.type_str = INT_TYPE;
    }
    else{
        current_token.type = OPERATOR;
        current_token.op_value = c;
        current_token.type_str = OP_TYPE;
    }
}

std::string get_token_type(int& type){
    if(type == 0){
        return "Integer";
    }
    else if(type == 1){
        return "Operator";
    }
    return "Error";
}

void parser(int type){
    std::string type_str = get_token_type(type);
    if(current_token.type != type){
        std::cout << "Syntax Error : Expected " << type_str << " instead got " << current_token.type_str;
        exit(0);
    }
}

void interpret(std::string& content){
    get_next_token(content); //expected to be integer
    parser(INT);
}

int main() {

    std::string content;

    while(true){
        LOG(">>> ");
        std::getline(std::cin, content);
        interpret(content);
    }

    return 0;
}