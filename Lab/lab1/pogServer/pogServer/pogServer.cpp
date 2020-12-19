// pogServer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
	std::cout << request;
	

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
	std::string str;
	json new_inf;
	json ti = json::parse(time_infa());
	json pi;
	std::ifstream file_read("INFAoPOGODE.json");
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
	std::cout << "yes";

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
	std::cout << "Server...OK";
	svr.listen("localhost", 2020);
}

