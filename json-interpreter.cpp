//Including the necessary libraries
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//Defining the enums for tokens
enum TokenType{
    CURLY_OPEN = 0,
    CURLY_CLOSE,
    STRING,
    COLON,
    COMMA,
    INT
};

//Token class. Each "word" will have a type (int) (from the enum),
//a string with the name of the type and the actual char value
struct Token{
    int type;
    std::string type_str;
    std::string char_val;
};

//Defining and initializing all the essential variables
std::string Keys[1000];
std::string Value[1000];
int key_pos = 0;
int value_pos = 0;
bool is_key = true;
int current_pos = 0;
Token current_token;

//Initializing the string that will contain types
const std::string INT_TYPE = "Integer";
const std::string STR_TYPE = "String";
const std::string CURLY_OPEN_TYPE = "Curly Brackets Open";
const std::string CURLY_CLOSE_TYPE = "Curly Brackets Close";
const std::string QUOTES_TYPE = "Quotes (\")";
const std::string COLON_TYPE = "Colon (:)";
const std::string COMMA_TYPE = "Comma (,)";

//Function to set the Token object easily
void set_token_value(int a_type, const std::string& a_type_str, std::string a_c){
    current_token.type = a_type;
    current_token.type_str = a_type_str;
    current_token.char_val = a_c;
}

//A bunch of functions to check stuff
bool is_whitespace(char c){
    return (c == ' ');
}

bool is_next_line(char c){
    return (c == '\n');
}

bool is_digit(char& c){
    return (c >= '0' && c <= '9');
}

//Takes in enum type and returns string type
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
    else if(type == COLON){
        return COLON_TYPE;
    }
    else if(type == COMMA){
        return COMMA_TYPE;
    }
    else if(type == STRING){
        return STR_TYPE;
    }
    else{
        return "Error";
    }
}

//Takes in the whole string from the file and then sets the current token object
void get_next_token(std::string& content){
    char c;
    c = content[current_pos];
    
    //skips white spaces and next line (\n) end sequence 
    while(is_whitespace(c) || is_next_line(c)){
        current_pos++;
        c = content[current_pos];
    }

    //if it is a digit, we go through it and add it in current_num 
    //until content[current_pos] (current element being checked) is not a number anymore
    if(is_digit(c)){
        std::string current_num = "";
        current_num += c;
        current_pos++;
        while(is_digit(content[current_pos])){
            current_num += content[current_pos];
            current_pos++;
        }
        set_token_value(INT, INT_TYPE, current_num);
    }
    //if it is a \", we go through it and add it in current_str
    //until content[current_pos] (current element being checked) is a \" again
    else if(c == '\"'){
        std::string current_str = "";
        current_pos++;
        c = content[current_pos];
        while(c != '\"'){
            current_str += c;
            current_pos++;
            c = content[current_pos];
        }
        set_token_value(STRING, STR_TYPE, current_str);
    }
    //Checks for the other unimportant stuff
    else if(c == '{'){
        set_token_value(CURLY_OPEN, CURLY_OPEN_TYPE, "_");
    }
    else if(c == '}'){
        set_token_value(CURLY_CLOSE, CURLY_CLOSE_TYPE, "_");
    }
    else if(c == ':'){
        set_token_value(COLON, COLON_TYPE, "_");
    }
    else if(c == ','){
        set_token_value(COMMA, COMMA_TYPE, "_");
    }
    current_pos++;
}

/*
    The parser is present to check the syntax of the.json file.
    if the type given is NOT equal to the type of current token object,
    then the syntax is wrong and an error message is displayed.
*/
void parser(int type){
    std::string type_str = get_token_type(type);
    if(current_token.type != type){
        std::cout << "Syntax Error : Expected " << type_str << " instead got " << current_token.type_str;
        exit(0);
    }
}

//Sets the current token as the key
void set_key(){
    if(!(current_token.char_val == "_")){
        Keys[key_pos] = current_token.char_val;
        key_pos++;
    }
}

//Sets the current token as the value
void set_value(){
    if(!(current_token.char_val == "_")){
        Value[value_pos] = current_token.char_val;
        value_pos++;
    }
}

/*
    This function returns true when the interpretation is done.
    it gets the next token --> checks if the syntax is correct --> set key/value.
*/
bool interpret(std::string& content){
    get_next_token(content);
    parser(CURLY_OPEN);

    int len = content.length();

    while (current_pos < len){
        get_next_token(content);
        if(current_token.type == CURLY_CLOSE){
            std::cout << "JSON parsing completed" << std:: endl;
            break;
        }

        if(current_token.type == COMMA){
            is_key = true;
        }
        else if (current_token.type == COLON){
            is_key = false;
        }

        if(is_key){
            set_key();
        }
        else{
            set_value();
        }
    }
    return true;
}

//This is the get function to get the value from the value array
std::string get(std::string& key, std::string& content){
    int pos = 0;
    for(int x = 0; x < content.length(); x++){
        if(Keys[x] == key){
            pos = x;
        }
    }
    return Value[pos];
}

int main(){
    std::string filename = "Json.json";
    //std::cout << "Input file name" << std::endl;
    //std::getline(std::cin, filename);

    std::ifstream file("Json.json");

    if (!file.is_open()){
        std::cout << "File failed to open";
        exit(0);
    }
    
    std::ostringstream buff;
    buff <<file.rdbuf();
    std::string content = buff.str();

    bool is_interpreter_done = false;

    is_interpreter_done = interpret(content);
    
    std::string get_key;

    //This is the part displayed to the user.
    if(is_interpreter_done){
        std::cout << "What \'Key\' do you want to get the value of? : ";
        std::cin >> get_key;
        std::cout <<  get(get_key, content) << std::endl;
    }

    return 0;
}