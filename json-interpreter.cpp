#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

enum TokenType{
    CURLY_OPEN = 0,
    CURLY_CLOSE,
    QUOTES,
    COLON,
    COMMA,
    INT,
    STRING
};

struct Token{
    int type;
    int num_val;
    std::string type_str;
    std::string char_val;
};

std::string Keys[1000];
std::string Value[1000];
bool is_key = true;
int current_pos = 0;
Token current_token;
const std::string INT_TYPE = "Integer";
const std::string STR_TYPE = "String";
const std::string CURLY_OPEN_TYPE = "Curly Brackets Open";
const std::string CURLY_CLOSE_TYPE = "Curly Brackets Close";
const std::string QUOTES_TYPE = "Quotes (\")";
const std::string COLON_TYPE = "Colon (:)";
const std::string COMMA_TYPE = "Comma (,)";


void set_value(int a_type, const std::string& a_type_str, std::string a_c, int a_num_value){
    current_token.type = a_type;
    current_token.type_str = a_type_str;
    current_token.char_val = a_c;
    current_token.num_val = a_num_value;
}

bool is_whitespace(char c){
    return (c == ' ');
}

bool is_next_line(char c){
    return (c == '\n');
}

bool is_digit(char& c){
    return (c >= '0' && c <= '9');
}

std::string get_token_type(int type){
    if(type == INT){
        return INT_TYPE;
    }
    else if(type == CURLY_OPEN){
        return CURLY_OPEN_TYPE;
    }
    else if(type == CURLY_CLOSE){
        return CURLY_CLOSE_TYPE;
    }
    else if(type == QUOTES){
        return QUOTES_TYPE;
    }
    else if(type == COLON){
        return COLON_TYPE;
    }
    else if(type == COMMA){
        return COMMA_TYPE;
    }
    else if(type == STRING){
        return STR_TYPE;
    }
    return "Error";
}

void get_next_token(std::string& content){
    char c;
    c = content[current_pos];
    
    while(is_whitespace(c) || is_next_line(c)){
        current_pos++;
        c = content[current_pos];
    }

    if(is_digit(c)){
        int current_num = c - '0';
        current_pos++;
        while(is_digit(content[current_pos])){
            current_num = (current_num * 10) + (content[current_pos] - '0');
            current_pos++;
        }
        set_value(INT, INT_TYPE, "_", current_num);
    }
    else if(c == 34){
        std::string current_str = "";
        current_str  += c;
        while(c != 34){
            current_pos++;
            c = content[current_pos];
            current_str += c;
        }
        current_str += '\"';
        set_value(STRING, STR_TYPE, current_str, -1);
    }
    else if(c == '{'){
        set_value(CURLY_OPEN, CURLY_OPEN_TYPE, "_", -1);
    }
    else if(c == '}'){
        set_value(CURLY_CLOSE, CURLY_CLOSE_TYPE, "_", -1);
    }
    else if(c == '\"'){
        set_value(QUOTES, QUOTES_TYPE, "_", -1);
    }
    else if(c == ':'){
        set_value(COLON, COLON_TYPE, "_", -1);
    }
    else if(c == ','){
        set_value(COMMA, COMMA_TYPE, "_", -1);
    }
    else{
        std::cout << "Invalid character at " << current_pos << std::endl;
    }
    current_pos++;
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
    parser(CURLY_OPEN);
}

int main(){
    std::string filename = "Json.json";
//     std::cout << "Input file name" << std::endl;
//     std::getline(std::cin, filename);

    std::ifstream file("Json.json");

    if (!file.is_open()){
        std::cout << "File failed to open";
        exit(0);
    }
    
    std::ostringstream buff;
    buff <<file.rdbuf();
    std::string content = buff.str();

    interpret(content);

    return 0;
}