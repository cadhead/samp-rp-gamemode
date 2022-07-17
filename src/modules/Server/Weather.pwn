#include <YSI_Coding\y_hooks>

static
  WeatherTimer              = 0,
  Weather                   = 10,
  WeathersIDList[7]         = { 1, 7, 8, 13, 15, 17, 10 };

Weather_Get() {
  return Weather;
}

Weather_Set(value) {
  Weather = value;
}

task GlobalWeather[1000]() {
  DynamicWeather();

  return 1;
}

static DynamicWeather() {
  if (gettimestamp() >= WeatherTimer) {
    WeatherTimer = gettimestamp() + 6000;

    new
      thour;

    gettime(thour);

    if (thour >= 6 && thour <= 20) {
      new RandomWeatherID;
      RandomWeatherID = randomEx(0,6);

      SetWeather(WeathersIDList[RandomWeatherID]);
      Weather_Set(WeathersIDList[RandomWeatherID]);
    } else if (thour >= 21 && thour <= 5) {
      SetWeather(10);
      Weather_Set(10);
    }
  }
}

hook OnGameModeInit() {
  SetWeather(10);
  Weather_Set(10);
}
