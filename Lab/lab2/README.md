<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 2<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ПИ-б-о-203(1)<br>Сайдалиев Артур Ридванович<br>
направления подготовки 09.03.04 "Программная инженерия"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center">Симферополь, 2020</p>
<hr>

## Цель
1. Получить представления о структуре post-запроса;
2. Изучить webhooks как метод взаимодействия web-приложений;

## Постановка задачи

Разработать и зарегистрировать навык для Алисы на сервисе Яндекс.Диалоги;

В качестве backend-a для навыка реализовать приложение на языке С++ выполняющее следующие функции:

- Составление продуктовой корзины:
    - Добавление продукта в корзину;
    - Удаление продукта из корзины;
    - Очистка корзины;
    - Вывод списка товаров в корзине;
    - Подсчёт стоимости товаров в корзине.

- Вывод справочной информации по навыку;

- Регистрацию webhook-ов сторонних сервисов;

- Отправку данных на сторонние сервисы.

В качестве стороннего сервиса реализовать приложение на языке Python, выполняющее следующие функции:
    Ожидание данных о покупке;
    Сохранение поступивших данных в excel-документ.

## Выполнение работы

В начале работы был создан навык на странице яндекса. Название было выбрано лаконичное, чётко отражающее суть навыка -- "Корзина".

![](https://sun9-71.userapi.com/impg/UHQ_fIUmVZ4icMhTO1Fz9645LbCUsM-OSNqt_A/ZM1OK4BqowU.jpg?size=1920x1080&quality=96&proxy=1&sign=7122f94582a238fbaa4017869330eecc&type=album)Рис 1 создание навыка

<br>

<p>
	Далее я сделал логику для Алисы. <br>
	После каждой команды, Алиса отправляет post запрос на указаный webhook url ,в зависимости от команды Алиса отвечает пользовотелю
</p>

![](https://sun9-48.userapi.com/impg/KFt5DvbWXdkPPT7dErpWGJDp1UE4l61Qs-wb1g/WQtd69dBCCU.jpg?size=1374x649&quality=96&proxy=1&sign=1ecbd292e23edefa51d3491fd05a8214&type=album)Рис 2 проверка работоспособности Алисы

Проводим проверку работы Алисы в разделе тестирование.

![](https://sun9-11.userapi.com/impg/NsDnH_GxwifgAKTkFU1bN_hqGzF0xWUYVhflsw/nGhdHKk234Y.jpg?size=1371x612&quality=96&proxy=1&sign=6926492e5a614c8bf12482e092f4849b&type=album)Рис 3 проверка работоспособности Алисы

<p>
	Далее я создаю сайт для регистрации Webhook ,находиться он по пути "/Webhooks" .Регистриру. на сайте клиенское приложение.
</p>

![](https://sun9-74.userapi.com/impg/O9t0vPzJYobIDB_8pQEBw8C4j2NlISc3zRxgiA/DH5yWtniI5k.jpg?size=1920x1080&quality=96&proxy=1&sign=e21ea37ead116d4731b81e67b13c365a&type=album)Рис 4 сайт с Webhook


<p>
	При работе клиенского приложения ,был создан exel-файл ,он находится в папку с клиенским приложением .
</p>

<br><hr>
	Исходный код серверного приложения:

```cpp

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>

int mode = 0;
bool tts_bool = true;
int i = 0;






using json = nlohmann::json;

using namespace httplib;


json config() {
    std::ifstream conf_file("config.json");
    json conf;
    std::string str;
    if (conf_file.is_open())
    {
        getline(conf_file, str, '\0');
        conf = json::parse(str);
        conf_file.close();

    }
    return conf;
}


int count() {
    json conf = config();
    int c = 0;
    bool flag = true;
    while (flag)
    {
        if (to_string(conf["webhooks"][c]) != "null") {
            c++;
        }
        else
        {
            flag = false;
        }

    }
    return c;
}

std::string File_parse(std::string FileName) {
    std::ifstream file_html(FileName);
    std::string str;
    if (file_html.is_open()) {
        getline(file_html, str, '\0');
        file_html.close();
    }
    return str;
}

void delet(std::string link) {
    json conf = config();



    int leng = count();
    for (int i = 0; i < leng; i++)
    {
        if ('"'+link+'"' == to_string(conf["webhooks"][i])) {
            conf["webhooks"].erase(conf["webhooks"].begin() + i);
            std::ofstream conf_file("config.json");
            conf_file << conf;
        }
    }

}

void Sett(std::string set) {
    json conf = config();

    std::ofstream File_config("config.json");


    conf["webhooks"].push_back(set);

    File_config <<  conf;

}

std::string FileHtml() {
    std::string in = File_parse("index.html");
    std::string link = "http://localhost:1234/Webhooks?del=";
    std::string n;
    std::string ad = File_parse("add.html");
    json conf = config();

    int num = in.find("{webhooks_list}");
    in.replace(num, 15, "");
    if (to_string(conf["webhooks"][0]) == "null") {
    }
    else
    {
        for (int i = 0; i < count(); i++)
        {
            n = ad;
            int f = n.find("{Webhook URL}");
            n.replace(f, 13, conf["webhooks"][i]);

            int s = n.find("?{webhook_URL}}");
            n.replace(s, 15, conf["webhooks"][i]);

            in.replace(num, 0, n);
        }
    }
    return in;
}

std::string basket(json req) {
    i += 1;
    json j = json::parse(File_parse("check.json"));
    j["user_id"] = req["session"]["user"]["user_id"];
    json s = {
        {"item", req["request"]["nlu"]["tokens"][3]},
        {"price", req["request"]["nlu"]["entities"][0]["value"]}
       };
    j["check"].push_back(s);
    std::ofstream Check_File("check.json");

    Check_File << j;

    return "";
}

std::string del(json req) {
    json check = json::parse(File_parse("check.json"));
    std::string ret = "no";
    for (int s = 0; s < i; s++)
    {
        if (check["check"][s]["item"] == req["request"]["nlu"]["tokens"][3])
        {
            ret = "ok";
            check["check"].erase(check["check"].begin() + s);
        }
    }
    std::ofstream Check_File("check.json");

    Check_File << check;
    i -= 1;
    return ret;
}

void clear() {
    i = 0;
    json j = json::parse(File_parse("check.json"));
    j["check"] = {};
    std::ofstream Check_File("check.json");
    Check_File << j;

}

int summ() {
    json j = json::parse(File_parse("check.json"));
    int sum = 0;
    for (int s = 0; s < i; s++)
    {
        sum += j["check"][s]["price"];
    }
    return sum;
}

std::string propert(){
    json j = json::parse(File_parse("check.json"));

    std::string str;
    for (int s = 0; s < i; s++)
    {
        str += to_string(j["check"][s]["item"]) + '\t' + to_string(j["check"][s]["price"]) + '\n';
    }
    return str;
}

void end_of_purchase() {
    json conf = config();
    json check = json::parse(File_parse("check.json"));

    std::string str;
    int c = count();
    for (int i = 0; i < c; i++)
    {
        str = conf["webhooks"][i];
        Client cli(str.c_str());
        auto res = cli.Post("/85d9efd0-eec7-4f11-9bdc-1b290298c0ef", to_string(check), "application/json");
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
            auto err = res.error();
            std::cout << "Error code: " << err << std::endl;
        }
    }

}


std::string answer(std::string command , json req) {
    json answere = json::parse(File_parse("hello.json"));
    std::string tts;
    std::string text;
    json help_state_buttons = {

    {
        {"title", u8"Корзина"},
        {"hide", true}
    },
    {
        {"title", u8"Выйти из этого режима"},
        {"hide", true}
    }
    };
    json talk_no = {

   {
       {"title", u8"Помощь"},
       {"hide", true}
   },
   {
       {"title", u8"Говорить"},
       {"hide", true}
   }
    };
    json button_basket = {
        {
            {"title",u8"Очистить корзину"},
            {"hide",true}
        },
        {
            {"title",u8"Что в корзине"},
            {"hide",true}
        },
        {
            {"title",u8"сумма"},
            {"hide",true}
        },
        {
            {"title",u8"завершить покупку"},
            {"hide",true}
        },
        {

            {"title", u8"Выйти из этого режима"},
            {"hide", true}
        }
    };


    if (command == u8"выйти из этого режима")
    {
        text = u8"Что-то не так?";
        if (tts_bool) {
            tts = u8"Что-то не так?";
        }
        else {
            answere["response"]["buttons"] = talk_no;
            tts = "";
        }
        answere["response"]["text"] = text;
        answere["response"]["tts"] = tts;

        mode = 0;
    }
    else if (command == u8"молчать") {
        text = u8"Молчу,молчу";
        tts = u8"";
        answere["response"]["text"] = text;
        answere["response"]["tts"] = tts;
        answere["response"]["buttons"] = talk_no;
        tts_bool = false;
    }
    else if (command == u8"говорить") {
        text = u8"ОК";
        tts = u8"ok";
        answere["response"]["text"] = text;
        answere["response"]["tts"] = tts;
        tts_bool = true;
    }
    else if ( mode == 0 && command == u8"помощь") {
        text = u8"Корзина. Поможет организовать покупки";
        if (tts_bool) {
            tts = u8"Корзина. Поможет организовать покупки";
        }
        else {
            tts = "";
        }
        answere["response"]["text"] = text;
        answere["response"]["tts"] = tts;
        answere["response"]["buttons"] = help_state_buttons;
        mode += 1;
    }
    else if(mode == 1 && command == u8"корзина")
    {
        text = u8"Чтобы что-нибудь добавить в корзину \nНужно написать команду 'Добавь в корзину' \nНапример \n'Добавь в корзину огурцы 20 рублей' \nЧтобы что-нибудь удалить из корзины \nНужно написать команду 'Удалить из корзины' \nНапример \n'удалить из корзины огурцы'";
        if (tts_bool) {
            tts = u8"Чтобы что-нибудь добавить в корзину \nНужно написать команду 'Добавь в корзину' \nНапример \n'Добавь в корзину огурцы 20 рублей' \nЧтобы что-нибудь удалить из корзины \nНужно написать команду 'Удалить из корзины' \nНапример \n'удалить из корзины огурцы'";
        }
        else {
            tts = "";
        }
        answere["response"]["text"] = text;
        answere["response"]["tts"] = tts;
        answere["response"]["buttons"] = button_basket;
        mode += 1;
    }   
    else if(mode == 2)
    {
        if (req["request"]["nlu"]["tokens"][0] == u8"добавь") {

            basket(req);
            text = u8"Добавлено";
            if (tts_bool) {
                tts = u8"добавлено";
            }
            else
            {
                tts = "";
            }

        }
        else if (req["request"]["nlu"]["tokens"][0] == u8"удалить")
        {
            if (i != 0) {
                std::string d = del(req);
                if (d == "ok") {
                    text = u8"Удалено";
                    if (tts_bool) {
                        tts = u8"удалено";
                    }
                    else
                    {
                        tts = "";
                    }
                }
                else
                {
                    text = u8"Товара в корзине нет";
                    if (tts_bool) {
                        tts = u8"Товара в корзине нет";
                    }
                    else
                    {
                        tts = "";
                    }
                }
            }
            else
            {
                text = u8"Корзина и так пуста";
                if (tts_bool) {
                    tts = u8"Корзина и так пуста";
                }
                else
                {
                    tts = "";
                }
            }


        }
        else if (command == u8"очистить корзину") {
            clear();
            text = u8"Корзина пуста";
            if (tts_bool) {
                tts = u8"корзина пуста";
            }
            else
            {
                tts = "";
            }
        }
        else if (command == u8"сумма") {
            if (i != 0) {
                std::string sum = std::to_string(summ());
                text = sum;
                if (tts_bool) {
                    tts = sum;
                }
                else
                {
                    tts = "";
                }
            }
            else
            {
                text = u8"Корзина пуста";
                if (tts_bool) {
                    tts = u8"Корзина пуста";
                }
                else
                {
                    tts = "";
                }
            }
        }
        else if (command == u8"что в корзине") {
            if (i != 0) {
                std::string prop = propert();
                text = prop;
                if (tts_bool) {
                    tts = prop;
                }
                else
                {
                    tts = "";
                }
            }
            else
            {
                text = u8"Корзина пуста";
                if (tts_bool) {
                    tts = u8"Корзина пуста";
                }
                else
                {
                    tts = "";
                }
            }
        }
        else if (command == u8"завершить покупку") {
            end_of_purchase();
            text = u8"OK";
            if (tts_bool) {
                tts = u8"OK";
            }
            else
            {
                tts = "";
            }
            clear();
        }
        else {
            text = u8"Такой команды нет";
            if (tts_bool) {
                tts = u8"такой команды нет";
            }
            else {
                tts = "";
            }
        }

        answere["response"]["text"] = text;
        answere["response"]["tts"] = tts;
        answere["response"]["buttons"] = button_basket;
    }
    else
    {
        text = u8"Такой команды нет";
        if (tts_bool) {
            tts = u8"такой команды нет";
        }
        else {
            answere["response"]["buttons"] = talk_no;
            tts = "";
        }
        answere["response"]["text"] = text;
        answere["response"]["tts"] = tts;
    }
    return to_string(answere);
}

void gen_response(const Request& req, Response& res) {
    res.set_content(FileHtml(), "text/html; charset=UTF-8");
}

void gen_response_webhooks(const Request& req, Response& res){

    if (req.has_param("del")) {
        delet(req.get_param_value("del"));
    }
    else if (req.has_param("set"))
    {
        Sett(req.get_param_value("set"));
    }
    res.set_content(FileHtml(), "text/html; charset=UTF-8");
}

void post_respons(const Request& req, Response& res) {
    // Выводим на экран тело запроса
    std::string str = "";
    // Отправляем ответ
    json j = json::parse(req.body.c_str());
    if (j["session"]["new"]) {
        str = File_parse("hello.json");
        mode = 0;


        json j = json::parse(File_parse("check.json"));
        j["user_id"] = "";
        j["check"] = {};
        std::ofstream Check_File("check.json");
        Check_File << j;


    }
    else
    {

        str = answer(j["request"]["command"], j);

    }
     res.set_content(str, "application/json; charset=UTF-8");
}

void test() {
    json j = json::parse(File_parse("check.json"));
    j["user_id"] = "svsvd";
    json s = { {"id","sdvsddsdsdv"} };
    j["check"].push_back(s);
    std::ofstream Check_File("check.json");

    Check_File << j;
}

int main() {
     Server svr;
     svr.Get("/Webhooks", gen_response);
     svr.Post("/Webhooks", gen_response_webhooks);
     svr.Post("/", post_respons);
     std::cout << "Start server... OK\n";
     svr.listen("localhost", 1234);
}
```


	Исходный код клиентского приложения:
```python
import openpyxl
import datetime
import json
import os.path
from flask import Flask, request

app = Flask(__name__)

def write_from_buf():
    global buf, next_line
    book = openpyxl.load_workbook('data.xlsx')
    sheet = book.active

    for line in buf:
        for i in range(5):
            sheet.cell(next_line, i + 1).value = line[i]
        next_line += 1

    sheet.cell(1, 6).value = next_line - 1
    book.save('data.xlsx')
    book.close
    buf.clear()

@app.route('/', methods = ['POST'])
def index():
    global next_id, buf
    req_time = datetime.datetime.now().time()

    req_j = request.get_json()
    for item in req_j['cart']:
        line = [
            next_id,
            req_j['user_id'],
            req_time,
            item['item'],
            item['price']
        ]
        next_id += 1
        buf.append(line)

    if len(buf) > 1000:
        write_from_buf()

    return 'OK'

if __name__ == "__main__":
    global buf, next_id, next_line
    next_id   = 1
    next_line = 2
    buf       = []

    if not os.path.exists('data.xlsx'):
        book = openpyxl.Workbook()
        sheet = book.active
        sheet.cell(1,1).value = 'N'
        sheet.cell(1,2).value = 'User ID'
        sheet.cell(1,3).value = 'Datetime'
        sheet.cell(1,4).value = 'Item'
        sheet.cell(1,5).value = 'Price'
        sheet.cell(1,6).value = 1
        book.save('data.xlsx')
        book.close
    else:
        book = openpyxl.load_workbook('data.xlsx')
        sheet = book.active

        next_id = int(sheet.cell(1,6).value)
        next_line = next_id + 1

        book.close

    app.run()
```

## Вывод

Я научился работать с системой навыков Яндекс, читать из файлов, работать с системами по принципу REST, писать файлы excel из Python и прокачал знания и навыки
работы в обоих языках программирования.
