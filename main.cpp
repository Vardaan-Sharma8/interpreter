#include <iostream>
#include <string>

#define LOG(x) std::cout << x << std::endl;

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

int current_pos_str = 0;
int current_pos_arr = 0;
Token token_arr[1000];
int token_num;

bool is_digit(char& c){
    return (c >= '0' && c <= '9');
}

void get_next_token(std::string content){
    char c;
    c = content[current_pos_str];
        
    if (is_digit(c)){
        token_arr[current_pos_arr].type = INT;
        token_arr[current_pos_arr].num_value = c - '0';
        token_arr[current_pos_arr].op_value = '_';
        token_arr[current_pos_arr].type_str = INT_TYPE;
    }
    else{
        token_arr[current_pos_arr].type = OPERATOR;
        token_arr[current_pos_arr].op_value = c;
        token_arr[current_pos_arr].num_value = -1;
        token_arr[current_pos_arr].type_str = OP_TYPE;
    }
    current_pos_str++;
}

std::string get_token_type(int& type){
    if(type == 0){
        return "Integer";
    }
    else if(type == 1){
        return "Operator";
    }
    else{
        return "Error";
    }
}

void parser(int type){
    std::string type_str = get_token_type(type);
    if(token_arr[current_pos_arr].type != type){
        std::cout << "Syntax Error : Expected " << type_str << " instead got " << token_arr[current_pos_arr].type_str << std::endl;
        exit(0);
    }
}

void interpret(std::string& content){
    for(int x = 0; x < token_num; x++){
        get_next_token(content);
        current_pos_arr++;
    }
}

int main() {

    std::string content;

    while(true){
        std::cout << ">>> ";
        std::getline(std::cin, content);
        token_num = content.size();
        interpret(content);
    }

    return 0;
}