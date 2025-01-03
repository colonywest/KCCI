#include "BinaryString.h"
#include "SString.h"
#include "LinkedList.h"

#ifndef KCCISCHOOLNET_H
#define KCCISCHOOLNET_H

struct KCCISchoolNet
{
	BinaryString schoolNetStations;
	BinaryString schoolNetData;
	BinaryString cameraList;
	BinaryString radarImage;
	BinaryString forecastImage;
};

class KCCIStationList : public Node
{
public:
	SString stationID;
	SString stationName;
};

class KCCISchoolNetData : public Node
{
public:
	char stationID [7];
	long timestamp;
	short tempFahrenheit;
	short dewpointFahrenheit;
	short relativeHumidity;
	short feelsLike;
	float altimeter;
	char altimeterTrend;
	char windDirection [4];
	short windSpeed;
	short windSpeedKnots;
	short windDirectionAngle;
	short gust20min;
	short gustMPH;
	short gustTime;
	float precipDay;
	float precipMonth;
	short lowTempFahrenheit;
	short highTempFahrenheit;
	short maxWindKnots;
	short angleMaxWind;
	short maxWindMPH;
	char maxWindDirection [4];
	int maxSolarRad;
};

class KCCICameraList : public Node
{
public:
	SString stationID;
	SString stationName;
	SString stationURL;
};

void ParseSchoolNetStationList(const char *, LinkedList &);
void ParseCameraList(const char *, LinkedList &);
void ParseSchoolNetData(const char *, LinkedList &);

#endif
