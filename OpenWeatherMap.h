// OpenWeatherMap.h
// Patrick Dobbie, Feb. 24, 2016
//
// Defines the OpenWeatherMap object, data for
// which is obtained from openweathermap.org.
// The data is received in XML format.
/////////////////////////////////////////////////
#ifndef OpenWeatherMap_H
#define OpenWeatherMap_H

#include <string>

struct CityCoord {std::string lon; std::string lat;};
struct CitySun {std::string rise; std::string set;};
struct City {
    std::string id;
    std::string name;
    struct CityCoord coord;
    std::string country;
    struct CitySun sun;
};
struct Temperature {
    std::string value;
    std::string min;
    std::string max;
    std::string unit;
};
struct Humidity {std::string value; std::string unit;};
struct Pressure {std::string value; std::string unit;};
struct WindSpeed {std::string value; std::string name;};
struct WindDirection {std::string value; std::string code; std::string name;};
struct Wind {
    struct WindSpeed speed;
    struct WindDirection direction;
};
struct Clouds {std::string value; std::string name;};
struct Visibility {std::string value;};
struct Precipitation {std::string value; std::string mode;};
struct Weather {std::string number; std::string value; std::string icon;};
struct Lastupdate{std::string value;};

class OpenWeatherMapClass {
public:
    struct City city;
    struct Temperature temperature;
    struct Humidity humidity;
    struct Pressure pressure;
    struct Wind wind;
    struct Clouds clouds;
    struct Visibility visibility;
    struct Precipitation precipitation;
    struct Weather weather;
    struct Lastupdate lastupdate;
	void   update(std::string str);
};

#endif
/////////////////////////////////////////////////
//EOF
