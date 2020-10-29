#include <iostream>
#include <cstdlib>
#include <ctime> 

int main()
{
    setlocale(LC_ALL, "RUS");
    std::cout << "{Приветственное сообщение от игры} \n";
    int a, b, c, h;
checkpoint:
    std::cout << "уровень сложность \n1) 0-10 \n2) 0-100 \n 3) 0-1000 \n";
    std::cin >> b;
    if (b == 1) a = rand() % 11;
    else if (b == 2) a = rand() % 101;
    else a = rand() % 1001;
    std::cout << "{игра началась}" << "\n {введите число} \n";
    for (int i = 0; i < 5;i++) {
        std::cin >> c;
        if (c < a) std::cout << "нужно больше \n";
        else if (c > a) std::cout << "меньше \n";
        else if (c == a) {
            std::cout << "красава \n" << a;
            break;
        }
    }
    std::cout << "еще раз? \n" << "1)да \n" << "2)нет \n";
    std::cin >> h;
    if (h == 1) goto checkpoint;
}
