#ifndef REGISTRY_H
#define REGISTRY_H

void SetDefaults();

/* School Net related Options */

int GetSchoolNetUpdateInterval();
int SetSchoolNetUpdateInterval(int );

bool GetDefaultStation(CString &);
bool SetDefaultStation(const char * );

int GetDataPlotUpdateInterval();
int SetDataPlotUpdateInterval(int );

int GetTimeRed();
int SetTimeRed(int );

/* General Options */

int GetDefaultView();
int SetDefaultView(int );

int GetControlPanelLocation();
int SetControlPanelLocation(int );

bool SetAtStartup();
bool RemoveStartup();
bool GetStartup();

/* Radar Options */

int GetRadarUpdateInterval();
int SetRadarUpdateInterval(int );

int GetDefaultRadarImage();
int SetDefaultRadarImage(int );

int GetDisableRadarUpdate();
int SetDisableRadarUpdate(int );

int GetDisableRadarWhenMinimized();
int SetDisableRadarWhenMinimized(int );

/* Web Cam Options */

int GetDefaultWebCam();
int SetDefaultWebCam(int );

int GetWebCamUpdateInterval();
int SetWebCamUpdateInterval(int );

/* Internet Options */

int GetDefaultTimeout();
int SetDefaultTimeout(int );

int GetUseProxy();
int SetUseProxy(int );

bool GetProxyServer(CString & );
bool SetProxyServer(const char * );

int GetProxyPort();
int SetProxyPort(int );

int GetCheckConnection();
int SetCheckConnection(int );

int GetCheckNewerVersion();
int SetCheckNewerVersion(int );

#endif
