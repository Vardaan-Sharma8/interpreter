#include <iostream>

#define LOG(x) std::cout << x << std::endl;

void interpret(char& content){
    
}

int main() {

    char content;

    while(true){
        LOG(">>>");
        std::cin >> content;
        interpret(content);
    }

    return 0;
}