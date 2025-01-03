// Detailed.cpp : implementation file
//

#include "stdafx.h"
#include "KCCI.h"
#include "Detailed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDetailed dialog


CDetailed::CDetailed(CWnd* pParent /*=NULL*/)
	: CDialog(CDetailed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDetailed)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDetailed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDetailed)
	DDX_Control(pDX, IDC_View, m_View);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDetailed, CDialog)
	//{{AFX_MSG_MAP(CDetailed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetailed message handlers

unsigned long streamProgress;

DWORD __stdcall StreamInCallback(DWORD dwCookie, LPBYTE lpBuff, LONG cb, LONG * pcb)
{
	const char * psBuffer = (const char *) dwCookie;

	psBuffer += streamProgress;
	if(cb <= strlen(psBuffer))
	{
		memcpy(lpBuff, psBuffer, cb);
		streamProgress += cb;
		* pcb = cb;
	}
	else
	{
		memcpy(lpBuff, psBuffer, strlen(psBuffer));
		* pcb = strlen(psBuffer);
		streamProgress += * pcb;
	}

	return 0;
}

void spellWind(const char * dirText, CString & out)
{
	if(strcmp(dirText, "N") == 0) out = "North";
	else if(strcmp(dirText, "NNE") == 0) out = "North-Northeast";
	else if(strcmp(dirText, "NE") == 0) out = "Northeast";
	else if(strcmp(dirText, "ENE") == 0) out = "East-Northeast";
	else if(strcmp(dirText, "E") == 0) out = "East";
	else if(strcmp(dirText, "ESE") == 0) out = "East-Southeast";
	else if(strcmp(dirText, "SE") == 0) out = "Southeast";
	else if(strcmp(dirText, "SSE") == 0) out = "South-Southeast";
	else if(strcmp(dirText, "S") == 0) out = "South";
	else if(strcmp(dirText, "SSW") == 0) out = "South-Southwest";
	else if(strcmp(dirText, "SW") == 0) out = "Southwest";
	else if(strcmp(dirText, "WSW") == 0) out = "West-Southwest";
	else if(strcmp(dirText, "W") == 0) out = "West";
	else if(strcmp(dirText, "WNW") == 0) out = "West-Northwest";
	else if(strcmp(dirText, "NW") == 0) out = "Northwest";
	else if(strcmp(dirText, "NNW") == 0) out = "North-Northwest";
}

void spellTrend(char trend, CString & out)
{
	switch(trend)
	{
	case 'R': out = "rising"; break;
	case 'S': out = "holding steady"; break;
	case 'F': out = "falling"; break;
	}
}

BOOL CDetailed::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CTime time = data->timestamp;
	CString stationName; int hour;

	CString temp; EDITSTREAM editStream; CHARFORMAT charFormat;
	CString text = "Current conditions at ";
	text += station->stationName; text += ":\n\n";

	text += "Currently the temperature is ";
	temp.Format("%i%cF", data->tempFahrenheit, 0xB0);
	text += temp; text +=" with a ";
	spellWind(data->windDirection, temp); text += temp;
	text += " wind of "; temp.Format("%i MPH", data->windSpeed); text += temp;
	text += " and a wind gust of ";
	temp.Format("%i MPH ", data->gustMPH);
	text += temp; text += " reached at ";

	hour = (data->gustTime / 100) % 12; if(hour == 0) hour = 12;
	temp.Format("%i:%0.2i %s", hour, data->gustTime % 100, (data->gustTime > 1200) ? "PM" : "AM");
	text += temp; text += ". The relative humidity is ";
	temp.Format("%i%%", data->relativeHumidity);
	text += temp; text += " and the dewpoint is at ";
	temp.Format("%i%cF.", data->dewpointFahrenheit, 0xB0); text += temp;
	text += " The barometric pressure is ";
	temp.Format("%0.2f", data->altimeter); text += temp;
	text += " and "; spellTrend(data->altimeterTrend, temp); text += temp;
	text += ". Currently it feels like ";
	temp.Format("%i%cF.\n\n", data->feelsLike, 0xB0); text += temp;

	text += "Since 12:00AM, there has been a high temperature of ";
	temp.Format("%i%cF", data->highTempFahrenheit, 0xB0); text += temp;
	text += " and a low temperature of ";
	temp.Format("%i%cF", data->lowTempFahrenheit, 0xB0); text += temp;
	text += ". The maximum wind since 12:00 AM was out of the ";
	spellWind(data->maxWindDirection, temp);
	text += temp; text += " at "; temp.Format("%i MPH.\n\n", data->maxWindMPH); text += temp;

	text += "Rainfall for the day since 12:00 AM has totaled ";
	temp.Format("%0.2f\"", data->precipDay); text += temp;
	text += ". Rainfall for the month has totaled ";
	temp.Format("%0.2f\".\n\n", data->precipMonth); text += temp;

	text += "Weather information as reported ";
	temp = time.Format("%b %d, %Y at %#I:%M:%S %p.");
	text += temp;

	editStream.dwCookie = (unsigned long )(const char *)text;
	editStream.pfnCallback = StreamInCallback;
	streamProgress = 0;

	strcpy(charFormat.szFaceName, "Courier");
	charFormat.yHeight = 200;
	charFormat.dwMask = CFM_SIZE | CFM_FACE;
	charFormat.cbSize = sizeof(CHARFORMAT);

	m_View.SetDefaultCharFormat(charFormat);
	m_View.StreamIn(SF_TEXT, editStream);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDetailed::OnOK() 
{
	// TODO: Add extra validation here

	PostMessage(WM_QUIT);
	
//	CDialog::OnOK();
}
