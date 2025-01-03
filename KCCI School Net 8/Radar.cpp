#include "stdafx.h"

void GetRadarURL(int index, CString & output)
{
	if(index == 8)
	{
		output = "http://www.keloland.com/Weather/Files_Forecast/KELOLAND_WXTYPE_STILL.jpg";
		return;
	}

	output = "http://images.ibsys.com/";

	if(index < 6) output += "des";
	else if(index == 6) output += "oma";
	else if(index == 7) output += "kc1";

	output += "/images/weather/auto/";

	switch(index)
	{
	case 1: output += "metro"; break;
	case 2: output += "northwest_"; break;
	case 3: output += "northeast_"; break;
	case 4: output += "southwest_"; break;
	case 5: output += "southeast_"; break;
	default: break;
	}

	output += "radar_640x480.jpg";
}
