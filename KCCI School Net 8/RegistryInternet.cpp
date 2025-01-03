#include "stdafx.h"

#include "Registry.h"
#include "BaseRegistry.h"

int GetDefaultTimeout()
{
	int x = ReadRegistry("NetworkTimeout");
	if(x < 0) x = 30;
	return x;
}

int SetDefaultTimeout(int value)
{
	int x = WriteRegistry("NetworkTimeout", value);
	return x;
}

int GetCheckConnection()
{
	int x = ReadRegistry("CheckConnection");
	if(x < 0) x = 5;
	return x;
}

int SetCheckConnection(int value)
{
	return WriteRegistry("CheckConnection", value);
}

int GetCheckNewerVersion()
{
	int x = ReadRegistry("CheckNewerVersion");
	if(x < 0) x = 1;
	return x;
}

int SetCheckNewerVersion(int value)
{
	return WriteRegistry("CheckNewerVersion", value);
}

int GetUseProxy()
{
	int x = ReadRegistry("UseProxy");
	if(x < 0) x = 0;
	return x;
}

int SetUseProxy(int value)
{
	int x = WriteRegistry("UseProxy", value);
	return x;
}

int GetProxyPort()
{
	int x = ReadRegistry("ProxyPort");
	return x;
}

int SetProxyPort(int value)
{
	int x = WriteRegistry("ProxyPort", value);
	return x;
}

bool GetProxyServer(CString & server)
{
	HKEY key;
	unsigned long data;
	unsigned long regError;
	unsigned char * station;

	if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\KCCI", 0, KEY_READ, & key) != ERROR_SUCCESS)
		return false;

	regError = RegQueryValueEx(key, "ProxyServer", NULL, NULL, NULL, &data);

	station = new unsigned char[data];
	regError = RegQueryValueEx(key, "ProxyServer", NULL, NULL, station, &data);

	RegCloseKey(key);

	if(regError == ERROR_SUCCESS)
	{
		server = (char *)station;
		delete station;
		return true;
	}

	delete station;
	return false;
}

bool SetProxyServer(const char * server)
{
	HKEY key;
	unsigned long disposition;

	if(RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\KCCI", 0, NULL, 0, KEY_WRITE, NULL, & key, & disposition) != ERROR_SUCCESS)
		return false;

	RegSetValueEx(key, "ProxyServer", 0, REG_SZ, (const unsigned char *)server, strlen(server));

	RegCloseKey(key);
	return true;
}
