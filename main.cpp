#include <iostream>
#include <string>

#define LOG(x) std::cout << x;

enum TokenType{
    INT = 0, OPERATOR
};

struct Token{
    int type;
    char op_value;
    int num_value;
};

int current_pos = 0;

void interpret(std::string& content){
    std::string content_ptr = content;
    char c;
    c = content_ptr[current_pos];
    Token current_tokken;
    
    if (c >= '0' && c <= '9'){
        current_tokken.type = INT;
        current_tokken.num_value = c - '0';
    }
    else{
        current_tokken.type = OPERATOR;
        current_tokken.op_value = c;
    }

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