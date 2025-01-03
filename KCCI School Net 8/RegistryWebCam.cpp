#include "stdafx.h"

#include "Registry.h"
#include "BaseRegistry.h"

int GetDefaultWebCam()
{
	int x = ReadRegistry("DefaultWebCam");
	if(x < 0) x = 0;
	return x;
}

int GetWebCamUpdateInterval()
{
	int x = ReadRegistry("WebCamUpdateInterval");
	if(x < 0) x = 5;
	return x;
}

int SetDefaultWebCam(int x)
{
	return WriteRegistry("DefaultWebCam", x);
}

int SetWebCamUpdateInterval(int x)
{
	return WriteRegistry("WebCamUpdateInterval", x);
}

