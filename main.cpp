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
public:
    int type;
    char op_value;
    int num_value;
    std::string type_str;  
};

const std::string INT_TYPE = "Integer";
const std::string OP_TYPE = "Operator";

Token current_token;
int current_pos = 0;
int operand;
char op;
int result;

void set_value(int a_type, char a_op_value, int a_num_value, const std::string& a_type_str){
    current_token.type = a_type;
    current_token.op_value = a_op_value;
    current_token.num_value = a_num_value;
    current_token.type_str = a_type_str;
}

bool is_digit(char& c){
    return (c >= '0' && c <= '9');
}

bool is_whitespace(char& c){
    return (c == ' ');
}

void get_next_token(std::string content){
    char c;
    c = content[current_pos];
    
    while(is_whitespace(c)){
        current_pos++;
        c = content[current_pos];
    }

    if (is_digit(c)){
        int current_num = c - '0';
        current_pos++;
        while(is_digit(content[current_pos])){
            current_num = (current_num * 10) + (content[current_pos] - '0');
            current_pos++;
        }

        set_value(INT, '_', current_num, INT_TYPE);
    }
    else{
        set_value(OPERATOR, c, 0, OP_TYPE);
        current_pos++;
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

void eval(){
    if(op == '+'){
        result += operand;
    }
    else if (op == '-'){
        result -= operand;
    }
    else{
        std::cout << "Error during evaluation. Invail operator input." << std::endl;
    }
}

void parser(int type){
    std::string type_str = get_token_type(type);
    if(current_token.type != type){
        std::cout << "Syntax Error : Expected " << type_str << " instead got " << current_token.type_str;
        exit(0);
    }
}

void interpret(std::string& content){
    get_next_token(content);
    parser(INT);
    result = current_token.num_value;

    int str_len = content.length();

    while(current_pos < str_len){
        get_next_token(content);
        parser(OPERATOR);
        op = current_token.op_value;

        get_next_token(content);
        parser(INT);
        operand = current_token.num_value;

        eval();        
    }

}

int main() {

    std::string content;

    while(true){
        current_pos = 0;
        LOG(">>> ");
        std::getline(std::cin, content);
        if(content == "exit"){
            exit(0);
        }
        interpret(content);
        std::cout << result << std::endl;
    }

    return 0;
}