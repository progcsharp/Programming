// prigram.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

int main()
{
    int n;
    int x = 0;
    std::cin >> n;
    std::string str;
    std::cin >> str;
 
    for (int i = 0; i < n;i++) {
        if (str[0 + (10 * i)] == 'a' && str[4 + (10 * i)] == '5' && str[5 + (10 * i)] == '5' && str[6 + (10 * i)] == '6'
            && str[7 + (10 * i)] == '6' && str[8 + (10 * i)] == '1'){
            std::cout << str[0 + (10 * i)] << str[1 + (10 * i)] << str[2 + (10 * i)] << str[3 + (10 * i)] << str[4 + (10 * i)] << str[5 + (10 * i)]
                << str[6 + (10 * i)] << str[7 + (10 * i)] << str[8 + (10 * i)];
            x = 1;
        }
    }
    if (x == 0) {
        std::cout << -1;
    }
}
