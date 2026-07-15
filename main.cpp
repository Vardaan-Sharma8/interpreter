#include <iostream>
#include <string>
#include <cmath>

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
char op;
int token_num;
int number[2] = {0, 0};

bool is_digit(char& c){
    return (c >= '0' && c <= '9');
}

int create_number(int pos, Token& current_token){
    int temp;
    int c = 0;
    for(int x = 0; x < pos; x++){
        current_token.num_value = current_token.num_value * (std::pow(10, (pos - x)));
        number[c] += current_token.num_value;
    }
    temp = number[c];
    c++;
    op = token_arr[pos + 1].op_value;
    return temp;
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

void parser(){
    int ptr_pos = 0;
    int op_pos;
    Token current_token;
    for(ptr_pos = 0; ptr_pos < token_num; ptr_pos++){
        current_token = token_arr[ptr_pos];
        if(current_token.type == OPERATOR){
            op_pos = ptr_pos;
            create_number(op_pos, token_arr[ptr_pos - 1]);
        }
    }
}

void interpret(std::string& content){
    for(int x = 0; x < token_num; x++){
        get_next_token(content);
        current_pos_arr++;
    }
    
    if(token_arr[0].type != INT){
        std::cout << "Syntax Error : Input starts with wrong type"; //Add more information in this error message!
        exit(0);
    }    

}

int main() {

    std::string content;

    while(true){
        std::cout << ">>> ";
        std::getline(std::cin, content);
        token_num = content.size();
        if(content == "exit"){
            exit(0);
        }
        interpret(content);
    }

    return 0;
}