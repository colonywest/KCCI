#include "stdafx.h"

#include "KCCI.h"

#include "KCCISchoolNet.h"
#include "Registry.h"

#include "xImage.h"
#include "LinkedList.h"
#include "SString.h"

#define FontSize(x) -MulDiv(x, GetDeviceCaps(cDC->m_hDC, LOGPIXELSY), 72)

void LoadWindDirection(CxImage & wind, const char * windDirection)
{
	SString speed = windDirection;
	UINT resourceID;

    if(speed == "") return;

	if(speed == "E") resourceID = IDR_WindE;
	else if(speed == "ENE") resourceID = IDR_WindENE;
	else if(speed == "ESE") resourceID = IDR_WindESE;
	else if(speed == "N") resourceID = IDR_WindN;
	else if(speed == "NE") resourceID = IDR_WindNE;
	else if(speed == "NNE") resourceID = IDR_WindNNE;
	else if(speed == "NNW") resourceID = IDR_WindNNW;
	else if(speed == "NW") resourceID = IDR_WindNW;
	else if(speed == "S") resourceID = IDR_WindS;
	else if(speed == "SE") resourceID = IDR_WindSE;
	else if(speed == "SSE") resourceID = IDR_WindSSE;
	else if(speed == "SSW") resourceID = IDR_WindSSW;
	else if(speed == "SW") resourceID = IDR_WindSW;
	else if(speed == "W") resourceID = IDR_WindW;
	else if(speed == "WNW") resourceID = IDR_WindWNW;
	else if(speed == "WSW") resourceID = IDR_WindWSW;
	else resourceID = 0;

	wind.LoadResource(FindResource(NULL,MAKEINTRESOURCE(resourceID), "GIF"), CXIMAGE_FORMAT_GIF);
}

void SetTransparency(CxImage & image)
{
	RGBQUAD transColor;

	memset(&transColor, 0, sizeof(RGBQUAD));

	image.SetTransIndex(0);
	image.SetTransColor(transColor);
}

void GetTextExtent(CDC * cDC, const char * textString, int size, CSize & s)
{
	CFont font, * oldFont;
	
	font.CreatePointFont(size * 10, "Arial", cDC);
	oldFont = cDC->SelectObject(&font);
	s = cDC->GetTextExtent(textString, strlen(textString));
	cDC->SelectObject(oldFont); font.DeleteObject();
}

long GetTextDescent(CDC * cDC)
{
	TEXTMETRIC textMetric;
	cDC->GetTextMetrics(& textMetric);
	return textMetric.tmDescent;
}

void RenderStationName(CDC * cDC, CxImage & station, const char * stationName)
{
	CSize size;
	RGBQUAD fontColor;

	fontColor.rgbBlue = fontColor.rgbGreen = fontColor.rgbRed = 255;
	fontColor.rgbReserved = 0;

	GetTextExtent(cDC, stationName, 12, size);

	/* For the station name, the x coordinate is not important, but the y is to determine
	 * how far up from the bottom to render
	 */

	station.Create(192, 18, 24); station.Clear();
	SetTransparency(station);
	station.DrawString(cDC->m_hDC, 0, 18 - GetTextDescent(cDC), stationName, fontColor, "Arial", FontSize(12));
}

void RenderPeakWind(CDC * cDC, CxImage & image, const char * textString)
{
	CSize size;
	RGBQUAD fontColor;
	short fontSize;

	fontColor.rgbBlue = fontColor.rgbGreen = fontColor.rgbRed = 255;
	fontColor.rgbReserved = 0;

	/* Attempt to render the string at the normal 28 point font size, but if it is too large,
	 * then substitute a smaller font size.
	 */

	fontSize = 28;
	GetTextExtent(cDC, textString, fontSize, size);

	while(size.cx > image.GetWidth())
	{
		fontSize -= 1;
		GetTextExtent(cDC, textString, fontSize, size);
	}

	/* Render the text centered according to the size returned by GetTextExtent */

	image.DrawString(cDC->m_hDC, (image.GetWidth() - size.cx) / 2, (image.GetHeight() + size.cy) / 2, textString, fontColor, "Arial", FontSize(fontSize));
}

void RenderElements(CDC * cDC, CxImage & image, const char * textString)
{
	CSize size;
	RGBQUAD fontColor;
	long x;

	fontColor.rgbBlue = fontColor.rgbGreen = fontColor.rgbRed = 255;
	fontColor.rgbReserved = 0;

	GetTextExtent(cDC, textString, 28, size);

	/* Render the text centered according to the size returned by GetTextExtent */
	
	x = image.DrawString(cDC->m_hDC, (image.GetWidth() - size.cx) / 2, image.GetHeight(), textString, fontColor, "Arial", FontSize(28));
}

void RenderTimestamp(CDC * cDC, CxImage & image, int timeStamp)
{
	CSize size;
	RGBQUAD fontColor;
	long x;

	CTime cTime = timeStamp; CTime hourOld = CTime::GetCurrentTime();
	CTimeSpan timeSpan(0,GetTimeRed(),0,0); hourOld -= timeSpan;
	CString timeString = cTime.Format("%b %d, %Y - %#I:%M:%S %p");

	if(cTime < hourOld) { fontColor.rgbRed = 255; fontColor.rgbGreen = 0; fontColor.rgbBlue = 0; }
	else fontColor.rgbRed = fontColor.rgbBlue = fontColor.rgbGreen = 255;

	fontColor.rgbReserved = 0;

	GetTextExtent(cDC, timeString, 12, size);

	/* Render the text centered according to the size returned by GetTextExtent */
	
	x = image.DrawString(cDC->m_hDC, (image.GetWidth() - size.cx) / 2, image.GetHeight(), timeString, fontColor, "Arial", FontSize(12));
}

void RenderTempBar(CxImage & bar, int temp)
{
	/* The bottom of the image is -20 degrees with it being about 1.5 pixels per degree.
	 * The bar is 8 pixels wide.
	 */

	int x, tempLength;
	RGBQUAD color;

	color.rgbBlue = 3; color.rgbGreen = 5; color.rgbRed = 137; color.rgbReserved = 0;

	tempLength = (temp + 20) * 202 / 140;

	for(x = 0; x < 8; x++) bar.DrawLine(x, x, 0, tempLength, color);
}

void RenderSchoolNetData(CDC * cDC, CxImage & image, const char * stationName, KCCISchoolNetData & data)
{
	CxImage background, wind;
	CxImage windspeed, station;
	CxImage temp, peak;
	CxImage rainfall, feelsLike, pressure;
	CxImage humidity;
	CxImage tempBar;
	CxImage timeStamp;

	char tempString[25];

	/* Load the background image */

	background.LoadResource(FindResource(NULL,MAKEINTRESOURCE(IDR_Background), "JPG"), CXIMAGE_FORMAT_JPG);

	/* Load the wind direction */

	LoadWindDirection(wind, data.windDirection);

	/* Set the station name in an image */

	RenderStationName(cDC, station, stationName);

	/* Render each of the other elements into their own images.  Begin by setting up each image
	 * for their size, clearing them out, and giving them some transparency.
	 */

	windspeed.Create(146, 42, 24); windspeed.Clear(); SetTransparency(windspeed);
	temp.Create(98, 42, 24); temp.Clear(); SetTransparency(temp);

	peak.Create(146, 42, 24); peak.Clear();	SetTransparency(peak);
	rainfall.Create(146, 42, 24); rainfall.Clear(); SetTransparency(rainfall);

	feelsLike.Create(146, 42, 24); feelsLike.Clear(); SetTransparency(feelsLike);
	pressure.Create(146, 42, 24); pressure.Clear(); SetTransparency(pressure);
	humidity.Create(146, 42, 24); humidity.Clear(); SetTransparency(humidity);

	timeStamp.Create(250, 42, 24); timeStamp.Clear(); SetTransparency(timeStamp);

	tempBar.Create(8, 224, 24); tempBar.Clear(); SetTransparency(tempBar);

	/* Render each image */

	sprintf(tempString, "%i %s", data.maxWindMPH, data.maxWindDirection);
	RenderPeakWind(cDC, peak, tempString);

	sprintf(tempString, "%i", data.tempFahrenheit);
	RenderElements(cDC, temp, tempString);

	sprintf(tempString, "%i", data.windSpeed);
	RenderElements(cDC, windspeed, tempString);

	sprintf(tempString, "%.2f\"", data.precipDay);
	RenderElements(cDC, rainfall, tempString);

	sprintf(tempString, "%i", data.feelsLike);
	RenderElements(cDC, feelsLike, tempString);

	sprintf(tempString, "%.2f%c", data.altimeter, data.altimeterTrend);
	RenderElements(cDC, pressure, tempString);

	sprintf(tempString, "%i%%", data.relativeHumidity);
	RenderElements(cDC, humidity, tempString);

	RenderTimestamp(cDC, timeStamp, data.timestamp);
	RenderTempBar(tempBar, data.tempFahrenheit);

	/* Mix each together */

	background.MixFrom(station, 336, 480 - 56 - station.GetHeight());
	background.MixFrom(temp, 71, 480 - 368 - temp.GetHeight());
	background.MixFrom(wind, 222, 480 - 75 - wind.GetHeight());
	background.MixFrom(windspeed, 218, 480 - 123 - windspeed.GetHeight());
	background.MixFrom(peak, 218, 480 - 288 - peak.GetHeight());
	background.MixFrom(rainfall, 218, 480 - 368 - rainfall.GetHeight());
	background.MixFrom(humidity, 412, 480 - 210 - humidity.GetHeight());
	background.MixFrom(feelsLike, 412, 480 - 288 - feelsLike.GetHeight());
	background.MixFrom(pressure, 412, 480 - 368 - pressure.GetHeight());
	background.MixFrom(timeStamp, 195, 480 - 425 - timeStamp.GetHeight());
	background.MixFrom(tempBar, 115, 480 - 72 - tempBar.GetHeight());

	image.Copy(background);
}
