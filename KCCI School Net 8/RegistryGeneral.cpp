#include "stdafx.h"
#include <winreg.h>

#include "KCCI.h"
#include "Registry.h"
#include "BaseRegistry.h"

/* SetAtStartup - Sets the registry key so that this runs when Windows starts or logs in */

bool SetAtStartup()
{
	HKEY key;
	extern CKCCIApp theApp;
	char appName[1024];

	GetModuleFileName(GetModuleHandle(NULL), appName, 1024);

	if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, & key) != ERROR_SUCCESS)
		return false;

	RegSetValueEx(key, "KCCI", 0, REG_SZ, (const unsigned char *)appName, strlen(appName));

	RegCloseKey(key);

	return true;
}

/* RemoveStartup - Removes the registry entry that allows this to run at startup */

bool RemoveStartup()
{
	HKEY key;
	const char * appName = AfxGetAppName();

	if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, & key) != ERROR_SUCCESS)
		return false;

	RegDeleteValue(key, "KCCI");

	RegCloseKey(key);

	return true;
}

/* Retrieves whether this program is set to run at startup */

bool GetStartup()
{
	HKEY key;
	long regError;

	if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, & key) != ERROR_SUCCESS)
		return false;

	regError = RegQueryValueEx(key, "KCCI", NULL, NULL, NULL, NULL);
	RegCloseKey(key);

	if(regError == ERROR_SUCCESS) return true;
	return false;
}

int GetDefaultView()
{
	int x = ReadRegistry("DefaultView");
	if(x < 0) x = 0;
	return x;
}

int SetDefaultView(int value)
{
	return WriteRegistry("DefaultView", value);
}

int GetControlPanelLocation()
{
	int x = ReadRegistry("ControlPanel");
	if(x < 0) x = 2;
	return x;
}

int SetControlPanelLocation(int value)
{
	return WriteRegistry("ControlPanel", value);
}
