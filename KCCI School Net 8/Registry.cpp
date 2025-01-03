#include "stdafx.h"

#include <winreg.h>

#include "KCCI.h"
#include "Registry.h"

/* ReadRegistry - Attempts to read a specified integer key value from the registry */

int ReadRegistry(const char * keyValue)
{
	HKEY key;
	unsigned long type;
	unsigned long dataSize;
	char * data; unsigned long * p;
	int retValue;

	if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\KCCI", 0, KEY_READ, & key) != ERROR_SUCCESS)
		return -1;

	if(RegQueryValueEx(key, keyValue, NULL, & type, NULL, & dataSize) != ERROR_SUCCESS)
	{
		RegCloseKey(key);
		return -1;
	}

	data = new char [dataSize + 1];
	RegQueryValueEx(key, keyValue, NULL, & type, (unsigned char * )data, & dataSize);

	RegCloseKey(key);

	p = (unsigned long *) data;

	retValue = * p;
	delete [] data;

	return retValue;
}

/* WriteRegistry - Attempts to write a specified integer value to the registry */

int WriteRegistry(const char * keyValue, unsigned long valueToWrite)
{
	HKEY key;
	unsigned long disposition;

	/* If opening the key fails, create it */

	if(RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\KCCI", 0, NULL, 0, KEY_WRITE, NULL, & key, & disposition) != ERROR_SUCCESS)
		return -1;

	RegSetValueEx(key, keyValue, 0, REG_DWORD, (const unsigned char *)& valueToWrite, sizeof(unsigned long));

	RegCloseKey(key);

	return 0;
}

/* SetDefaults - Sets the default options */

void SetDefaults()
{
	HKEY key;
	int k = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\KCCI", 0, KEY_READ, & key);
	RegCloseKey(key);

	if(k != ERROR_SUCCESS)
	{
		SetAtStartup();
		SetCheckNewerVersion(1);
	}
}