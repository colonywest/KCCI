#include "stdafx.h"

#include "LinkedList.h"
#include "SString.h"
#include "Token.h"
#include "KCCISchoolNet.h"

/* Parses through the School Net station list and sends it into a linked list */

void ParseSchoolNetStationList(const char * stationList, LinkedList & output)
{
	KCCIStationList * pNode;
	Token * token; Token * lineToken; SString tokenString;

	token = new Token(stationList, "\n");

	/* The first line, the header line, can be discarded */

	token->nextToken(tokenString);
	output.reset();
	
	/* Each subsequent line is the station list */

	while(token->moreTokens())
	{
		token->nextToken(tokenString);
		lineToken = new Token(tokenString, ",");
		pNode = new KCCIStationList;

		/* Two parts to this token */

		lineToken->nextToken(pNode->stationID);
		lineToken->nextToken(pNode->stationName);

		output.addElement(pNode);

		delete lineToken;
	}

	delete token;
}

KCCICameraList * DowntownDesMoines()
{
	KCCICameraList * pNode = new KCCICameraList;
	pNode->stationID = "IASCN1";
	pNode->stationName = "Downtown Des Moines";
	pNode->stationURL = "http://images.ibsys.com/des/images/weather/auto/towercam3_320x240.jpg";
	return pNode;
}

KCCICameraList * DesMoinesAirport()
{
	KCCICameraList * pNode = new KCCICameraList;
	pNode->stationID = "IASCN2";
	pNode->stationName = "Des Moines International Airport";
	pNode->stationURL = "http://images.ibsys.com/des/images/weather/auto/towercam4_320x240.jpg";
	return pNode;
}

KCCICameraList * DesMoinesEast()
{
	KCCICameraList * pNode = new KCCICameraList;
	pNode->stationID = "IASCN3";
	pNode->stationName = "Des Moines - East";
	pNode->stationURL = "http://images.ibsys.com/des/images/weather/auto/towercam2_320x240.jpg";
	return pNode;
}

KCCICameraList * DesMoinesWest()
{
	KCCICameraList * pNode = new KCCICameraList;
	pNode->stationID = "IASCN4";
	pNode->stationName = "Des Moines - West";
	pNode->stationURL = "http://images.ibsys.com/des/images/weather/auto/towercam1_320x240.jpg";
	return pNode;
}

/* Parses the list of web cameras into a linked list */

void ParseCameraList(const char * cameraList, LinkedList & output)
{
	KCCICameraList * pNode;
	Token * token; Token * lineToken; SString tokenString;

	SString temp = cameraList; temp.trim();
	token = new Token(temp, "\n");

	/* The first line is a header line and can be discarded */

	token->nextToken(tokenString);
	output.reset();

	/* The first four lines will be for the Iowa SkyCam network */

	output.addElement(DowntownDesMoines());
	output.addElement(DesMoinesAirport());
	output.addElement(DesMoinesEast());
	output.addElement(DesMoinesWest());

	/* Parse through the camera list and add the remaining elements */

	while(token->moreTokens())
	{
		token->nextToken(tokenString);
		lineToken = new Token(tokenString, ",");

		pNode = new KCCICameraList;

		lineToken->nextToken(pNode->stationID);
		lineToken->nextToken(pNode->stationURL);
		lineToken->nextToken(pNode->stationName);

		pNode->stationURL = "http://mesonet.agron.iastate.edu/data/camera/stills/";
		pNode->stationURL += pNode->stationID;

		output.addElement(pNode);

		delete lineToken;
	}

	delete token;
}

/* Parses the School Net weather data into a linked list */

void ParseSchoolNetData(const char * data, LinkedList & output)
{
	KCCISchoolNetData * pNode;
	Token * token, * lineToken; SString tokenString, temp;

	token = new Token(data, "\n");

	/* Again, the first line is a header line */

	token->nextToken(tokenString);
	output.reset();

	/* Parse through the next lines to get the data */

	while(token->moreTokens())
	{
		token->nextToken(tokenString);
		lineToken = new Token(tokenString, ",");

		pNode = new KCCISchoolNetData;

		/* Station ID */

		lineToken->nextToken(temp);
		strcpy(pNode->stationID, temp);

		/* Time stamp */

		lineToken->nextToken(temp);
		pNode->timestamp = atol(temp);

		/* Temperature in F */

		lineToken->nextToken(temp);
		pNode->tempFahrenheit = atoi(temp);

		/* Dewpoint in F */

		lineToken->nextToken(temp);
		pNode->dewpointFahrenheit = atoi(temp);

		/* Relative humidity */

		lineToken->nextToken(temp);
		pNode->relativeHumidity = atoi(temp);

		/* Feels like */

		lineToken->nextToken(temp);
		pNode->feelsLike = atoi(temp);

		/* Altimeter - Barometric pressure */

		lineToken->nextToken(temp);
		pNode->altimeter = atof(temp);

		/* Altimeter trend */

		lineToken->nextToken(temp);
		pNode->altimeterTrend = temp[0];

		/* Wind direction, text */

		lineToken->nextToken(temp); temp.trim();
		strcpy(pNode->windDirection, temp);

		/* Wind speed */

		lineToken->nextToken(temp);
		pNode->windSpeed = atoi(temp);

		/* Wind speed - knots */

		lineToken->nextToken(temp);
		pNode->windSpeedKnots = atoi(temp);

		/* Wind direction - angle */

		lineToken->nextToken(temp);
		pNode->windDirectionAngle = atoi(temp);

		/* Gust over 20 minutes */

		lineToken->nextToken(temp);
		pNode->gust20min = atoi(temp);

		/* Gust in MPH */

		lineToken->nextToken(temp);
		pNode->gustMPH = atoi(temp);

		/* Gust time */

		lineToken->nextToken(temp);
		pNode->gustTime = atoi(temp);

		/* Precip for day */

		lineToken->nextToken(temp);
		pNode->precipDay = atof(temp);

		/* Precip for month */

		lineToken->nextToken(temp);
		pNode->precipMonth = atof(temp);

		/* Low temperature in F */

		lineToken->nextToken(temp);
		pNode->lowTempFahrenheit = atoi(temp);

		/* High temperature in F */

		lineToken->nextToken(temp);
		pNode->highTempFahrenheit = atoi(temp);

		/* Max wind in knots */

		lineToken->nextToken(temp);
		pNode->maxWindKnots = atoi(temp);

		/* Max wind direction - angle */

		lineToken->nextToken(temp);
		pNode->angleMaxWind = atoi(temp);

		/* Max wind in MPH */

		lineToken->nextToken(temp);
		pNode->maxWindMPH = atoi(temp);

		/* Max wind direction - text */

		lineToken->nextToken(temp); temp.trim();
		strcpy(pNode->maxWindDirection, temp);

		/* Max solar radiation */

		lineToken->nextToken(temp);
		pNode->maxSolarRad = atoi(temp);

		output.addElement(pNode);

		delete lineToken;
	}

	delete token;
}
