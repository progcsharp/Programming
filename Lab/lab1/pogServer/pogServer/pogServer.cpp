// pogServer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <cpp_httplib/httplib.h>
using namespace httplib;


int main() {
    // Создаём клиент и привязываем к домену. Туда пойдут наши запросы
    Client cli("http://openweathermap.org/");
    // Отправляем get-запрос и ждём ответ, который сохраняется в переменной res
    auto res = cli.Get("/data/2.5/onecall?lat=44.952116&lon=34.102411&units=metric&lang=ru&exlude=current&appid=d9bdc7022a03819090040e7e05691e2c&dt=1605698376&dt=1605712642");
    // res преобразуется в true, если запрос-ответ прошли без ошибок
    if (res) {
        // Проверяем статус ответа, т.к. может быть 404 и другие
        if (res->status == 200) {
            // В res->body лежит string с ответом сервера
            std::cout << res->body << std::endl;
        }
        else {
            std::cout << "Status code: " << res->status << std::endl;
        }
    }
    else {
        
        std::cout << res.error()    ;
    }
 
}