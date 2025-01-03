#include "stdafx.h"

#include "Registry.h"
#include "BaseRegistry.h"

/* Retrieves the radar update interval from the registry */

int GetRadarUpdateInterval()
{
	int x = ReadRegistry("RadarUpdate");
	if(x < 0) x = 5;
	return x;
}

int SetRadarUpdateInterval(int value)
{
	int x = WriteRegistry("RadarUpdate", value);
	return x;
}

/* Retrieves the default radar image from the registry */

int GetDefaultRadarImage()
{
	int x = ReadRegistry("RadarImage");
	if(x < 0) x = 0;
	return x;
}

int SetDefaultRadarImage(int value)
{
	int x = WriteRegistry("RadarImage", value);
	return x;
}

int GetDisableRadarUpdate()
{
	int x = ReadRegistry("DisableRadarUpdate");
	if(x < 0) x = 0;
	return x;
}

int SetDisableRadarUpdate(int value)
{
	return WriteRegistry("DisableRadarUpdate", value);
}

int GetDisableRadarWhenMinimized()
{
	int x = ReadRegistry("DisableRadarUpdateWhenMinimized");
	if(x < 0) x = 0;
	return x;
}

int SetDisableRadarWhenMinimized(int value)
{
	int x = WriteRegistry("DisableRadarUpdateWhenMinimized", value);
	return x;
}

