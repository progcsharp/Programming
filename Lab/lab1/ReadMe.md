<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 1<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ПИ-б-о-203(1)<br>
Сайдалиев Артур Ридванович<br>
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

<!-- ![](./image/pic1.png) -->
## Цель:

1. Закрепить навыки разработки многофайловыx приложений;
2. Изучить способы работы с API web-сервиса;
3. Изучить процесс сериализации/десериализации данных в/из json;
4. Получить базовое представление о сетевом взаимодействии приложений;

## Постановка задачи
Разработать сервис предоставляющий данные о погоде в городе Симферополе на момент запроса. В качестве источника данных о погоде использовать: http://openweathermap.org/. В состав сервиса входит: серверное приложение на языке С++ и клиентское приложение на языке Python.
Серверное приложение (далее Сервер) предназначенное для обслуживания клиентских приложений и минимизации количества запросов к сервису openweathermap.org. Сервер должен обеспечивать возможность получения данных в формате JSON и виде html виджета (для вставки виджета на страницу будет использоваться iframe).
Клиентское приложение должно иметь графический интерфейс отображающий сведения о погоде и возможность обновления данных по требованию пользователя.

## Выполнение работы
API ключ по-умолчанию созданный сервисом:<br>d9bdc7022a03819090040e7e05691e2c

Запрос, созданный к серверу погоды включает в себя широту и долготу места, для которого необходимо получить погоду, исключить все типы прогноза кроме почасового, ключ API, метрические единицы изменения (цельсий) и описание на русском языке:

api.openweathermap.org/data/2.5/onecall?lat=45.0522222222&lon=33.9744444444&exclude=current,minutely,daily,alerts&appid=d9bdc7022a03819090040e7e05691e2c&units=metric&lang=ru

Запрос для сервера погоды включает в себя город, время которого необходимо получить: http://worldtimeapi.org/api/timezone/Europe/Simferopol

Исходный код сервера:
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include "cpp_httplib/httplib.h"
using namespace httplib;
#include "nlohmann/json.hpp"
using json = nlohmann::json;
Client owm("http://api.openweathermap.org");
std::string latitude = "45.0522222222";
std::string longitude = "33.9744444444";
std::string exclude = "current,minutely,daily,alerts";
std::string lang = "ru";
std::string units = "metric";
std::string appid = "d9bdc7022a03819090040e7e05691e2c";
std::string informarion() {
	std::string request = "/data/2.5/onecall?lat=" + latitude + "&lon=" + longitude +
		"&exclude=" + exclude + "&appid=" + appid + "&units=" + units + "&lang=" + lang;
	auto result = owm.Get(request.c_str());
	if (!result) {
		return "err";
	}
	int status_code = result->status;
	if (status_code < 200 || status_code >= 300) {
		return std::to_string( status_code);
	}
	return result->body;
}
std::string time_infa() {
	Client cli("http://worldtimeapi.org");
	auto res = cli.Get("/api/timezone/Europe/Simferopol");
	if (res)
	{
		if (res->status == 200) {
			// В res->body лежит string с ответом сервера
			return res->body;
		}
		else {
			return "is not 200";
		}
	}
	else
	{
		return "err";
	}
}
std::string parascha() {
	json ti = json::parse(time_infa());
	json pi;
	std::ifstream file_read("INFAoPOGODE.json");
	std::string str;
	json new_inf;
	if (file_read.is_open()) {
		getline(file_read, str, '\0');
		pi = json::parse(str);
		for (int i = 0;i < pi["hourly"].size();i++) {
			if (ti["unixtime"] > pi["hourly"][i]["dt"] && ti["unixtime"] < pi["hourly"][i + 1]["dt"])
			{
				new_inf.push_back({
					{"temp",pi["hourly"][i]["temp"] },
					{"description",pi["hourly"][i]["weather"][0]["description"]},
					{"icon",pi["hourly"][i]["weather"][0]["icon"]}
					});
				break;
			}
		}
	}
	if (new_inf.size() > 0) {
		return to_string(new_inf);
	}
	else
	{
		pi = json::parse(informarion());
		std::ofstream file_write("INFAoPOGODE.json");
		file_write << pi;
		new_inf.push_back({
					{"temp",pi["hourly"][0]["temp"] },
					{"description",pi["hourly"][0]["weather"][0]["description"]},
					{"icon",pi["hourly"][0]["weather"][0]["icon"]}
			});
		return to_string(new_inf);
	}
}
std::string htmlsran() {
	json j = json::parse(parascha());
	std::ifstream file_html("index.html");
	std::string str;
	if (file_html.is_open()) {
		getline(file_html, str, '\0');
		file_html.close();
	}
	int d = str.find("{hourly[i].weather[0].description}");
	str.replace(d, 34, to_string(j[0]["description"]));
	int t1 = str.find("{hourly[i].temp}");
	str.replace(t1, 16, to_string(j[0]["temp"]));
	int t2 = str.find("{hourly[i].temp}");
	str.replace(t2, 16, to_string(j[0]["temp"]));
	int i = str.find("{hourly[i].weather[0].icon}");
	str.replace(i, 27, j[0]["icon"]);
	return str;
}
void get_response_raw(const Request& req, Response& res) {
	res.set_content(parascha(), "text/json");
}
void get_response(const Request& req, Response& res) {
	res.set_content(htmlsran(), "text/html");
}
int main() {
	Server svr;
	svr.Get("/", get_response);
	svr.Get("/raw", get_response_raw);
	svr.listen("localhost", 2020);
}
```

Код клиента:
```python
from tkinter import *
import json
import requests

def reload_data(event=None):
	try:
		response = requests.get('http://localhost:3000/raw').content.decode("utf8")
		forecast_j = json.loads(response)

		desc.config(text=str(forecast_j["description"]))
		temp.config(text=str(forecast_j["temp"]) + "°C")
	except requests.exceptions.ConnectionError:
		pass

root = Tk()
root.title("Погода")
root.pack_propagate(0)
root.bind("<Button-1>", reload_data)

_yellow = "#ffb84d"
_white = "#ffffff"
_w = 100
_h = 30

top_frame =    Frame(root, bg=_yellow, width=_w, height=_h)
middle_frame = Frame(root, bg=_white,  width=_w, height=_h*3)
bottom_frame = Frame(root, bg=_yellow, width=_w, height=_h)

top_frame.pack(side=TOP, fill=X)
middle_frame.pack(expand=True, fill=BOTH)
bottom_frame.pack(side=BOTTOM, fill=X)

city = Label(top_frame, font=("Calibri Bold", 12), text="Симферополь", bg=_yellow)
desc = Label(top_frame, font=("Calibri", 12), bg=_yellow)
temp = Label(middle_frame, font=("Impact", 48), bg=_white)

city.pack(pady=0)
desc.pack(pady=0)
temp.pack(expand=True)

reload_data()
root.mainloop()
```

скриншот клиента:

![](https://sun9-65.userapi.com/impg/g2XS8MqF-N1R7nEkR4QAS3djpMpaJvEed5GfGw/8Jy7DzTkpv8.jpg?size=211x283&quality=96&proxy=1&sign=9e6e33dcfab6e872d0605eab21c4cc37)

Рис 1 окно клиента



скриншот сервера:

![](https://sun9-5.userapi.com/impg/2gWEbG5ue3jJLxDU4PKWKjnddNN21atjG2ODOg/PqfQad8NddI.jpg?size=445x183&quality=96&proxy=1&sign=12e7a35a5119746304018174e991a0de)

Рис 2 скриншот работы сервера

## Вывод по работе.
Цель работы была успешно достигнута. Было выполнено:
- Создание сервера на языке С++, обращающегося к openweathermap.com и возвращающий виджет или описание и температуру в формате json
- Приложение с графическим интерфейсом, написанное на языке Python с использованием библиотеки Tkinter, получающее и обрабатывающее данные из сервера.
