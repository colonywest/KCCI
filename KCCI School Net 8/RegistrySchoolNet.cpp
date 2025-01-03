#include "stdafx.h"
#include <winreg.h>

#include "Registry.h"
#include "BaseRegistry.h"

// Sets the default School Net station in the registry

bool SetDefaultStation(const char * stationID)
{
	HKEY key;
	unsigned long disposition;

	if(RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\KCCI", 0, NULL, 0, KEY_WRITE, NULL, & key, & disposition) != ERROR_SUCCESS)
		return false;

	RegSetValueEx(key, "DefaultStation", 0, REG_SZ, (const unsigned char *)stationID, strlen(stationID));

	RegCloseKey(key);
	return true;
}

// Retrieves the default School Net station from the registry

bool GetDefaultStation(CString & stationID)
{
	HKEY key;
	unsigned long data;
	unsigned long regError;
	unsigned char * station;

	if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\KCCI", 0, KEY_READ, & key) != ERROR_SUCCESS)
		return false;

	regError = RegQueryValueEx(key, "DefaultStation", NULL, NULL, NULL, &data);

	station = new unsigned char[data];
	regError = RegQueryValueEx(key, "DefaultStation", NULL, NULL, station, &data);

	RegCloseKey(key);

	if(regError == ERROR_SUCCESS)
	{
		stationID = (char *)station;
		delete [] station;
		return true;
	}

	delete station;
	return false;
}

/* Retrieves the School Net update interval from the registry */

int GetSchoolNetUpdateInterval()
{
	int x = ReadRegistry("SchoolNetUpdate");
	if(x < 0) x = 1;
	return x;
}

int SetSchoolNetUpdateInterval(int value)
{
	int x = WriteRegistry("SchoolNetUpdate", value);
	return x;
}

int GetTimeRed()
{
	int x = ReadRegistry("TimeRed");
	if(x < 0) x = 1;
	return x;
}

int SetTimeRed(int value)
{
	return WriteRegistry("TimeRed", value);
}

int GetDataPlotUpdateInterval()
{
	int x = ReadRegistry("DataPlotUpdate");
	if(x < 0) x = 30;
	return x;
}

int SetDataPlotUpdateInterval(int value)
{
	return WriteRegistry("DataPlotUpdate", value);
}