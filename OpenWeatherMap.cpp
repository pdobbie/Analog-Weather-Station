// OpenWeatherMap.cpp
// Patrick Dobbie, Feb. 24, 2016
//
// Defines the OpenWeatherMap functions.
// The data is received in XML format and this
// will update all fields of the OpenWeatherMap
// object.
/////////////////////////////////////////////////s
#include "OpenWeatherMap.h"
#include <string>
using namespace std;

string tryExtractString(string str, string category, string value) {
    // Find specified category
    int p0 = str.find("<"+category);
    if (p0 == string::npos) {return "";}
    p0 += category.length()+2;

    // Find end to category if specified by a value of "*"
    if (value == "*") {
        int p1 = str.find("</"+category+">");
        if (p1 == string::npos) {return "";}
        return str.substr(p0,p1-p0);
    }

    // Find specified value
    int p1 = str.find(value+"=", p0);
    if (p1 == string::npos) {return "";}
    p1 += value.length()+2;

    int p2 = str.find("\"", p1);
    if (p2 == string::npos) {return "";}

    return str.substr(p1,p2-p1);
}

void OpenWeatherMapClass::update(string str) {
	string cityStr = tryExtractString(str,"city","*");
	OpenWeatherMapClass::city.id = tryExtractString(str,"city","id");
	OpenWeatherMapClass::city.name = tryExtractString(str,"city","name");
	OpenWeatherMapClass::city.coord.lon = tryExtractString(cityStr,"coord","lon");
	OpenWeatherMapClass::city.coord.lat = tryExtractString(cityStr,"coord","lat");
	OpenWeatherMapClass::city.country = tryExtractString(str,"city","country");
	OpenWeatherMapClass::city.sun.rise = tryExtractString(cityStr,"sun","rise");
	OpenWeatherMapClass::city.sun.set = tryExtractString(cityStr,"sun","set");

	OpenWeatherMapClass::temperature.value = tryExtractString(str,"temperature","value");
	OpenWeatherMapClass::temperature.min = tryExtractString(str,"temperature","min");
	OpenWeatherMapClass::temperature.max = tryExtractString(str,"temperature","max");
	OpenWeatherMapClass::temperature.unit = tryExtractString(str,"temperature","unit");

	OpenWeatherMapClass::humidity.value = tryExtractString(str,"humidity","value");
	OpenWeatherMapClass::humidity.unit = tryExtractString(str,"humidity","unit");

	OpenWeatherMapClass::pressure.value = tryExtractString(str,"pressure","value");
	OpenWeatherMapClass::pressure.unit = tryExtractString(str,"pressure","unit");

	string windStr = tryExtractString(str,"wind","*");
	OpenWeatherMapClass::wind.speed.value = tryExtractString(windStr,"speed","value");
	OpenWeatherMapClass::wind.speed.name = tryExtractString(windStr,"speed","name");
	OpenWeatherMapClass::wind.direction.value = tryExtractString(windStr,"speed","value");
	OpenWeatherMapClass::wind.direction.code = tryExtractString(windStr,"speed","code");
	OpenWeatherMapClass::wind.direction.name = tryExtractString(windStr,"speed","name");

	OpenWeatherMapClass::clouds.value = tryExtractString(str,"clouds","value");
	OpenWeatherMapClass::clouds.name = tryExtractString(str,"clouds","name");

	OpenWeatherMapClass::visibility.value = tryExtractString(str,"visibility","value");

	OpenWeatherMapClass::precipitation.value = tryExtractString(str,"precipitation","value");
	OpenWeatherMapClass::precipitation.mode = tryExtractString(str,"precipitation","mode");

	OpenWeatherMapClass::weather.number = tryExtractString(str,"weather","number");
	OpenWeatherMapClass::weather.value = tryExtractString(str,"weather","value");
	OpenWeatherMapClass::weather.icon = tryExtractString(str,"weather","icon");

	OpenWeatherMapClass::lastupdate.value = tryExtractString(str,"lastupdate","value");
}
/////////////////////////////////////////////////
//EOF
