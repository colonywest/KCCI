# Microsoft Developer Studio Project File - Name="KCCI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=KCCI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "KCCI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "KCCI.mak" CFG="KCCI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KCCI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "KCCI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KCCI - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\CxImage\CxImage" /I "..\BinaryString" /I "..\SString" /I "..\LinkedList" /I "..\HttpComm" /I "..\AshSysTray" /I "..\PPToolTip" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wsock32.lib ..\CxImage\CxImage\CxImageDLL\Release\cximage.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\CxImage\CxImage\CxImageDLL\Release"

!ELSEIF  "$(CFG)" == "KCCI - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\CxImage\CxImage" /I "..\BinaryString" /I "..\SString" /I "..\LinkedList" /I "..\HttpComm" /I "..\AshSysTray" /I "..\PPToolTip" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wsock32.lib ..\CxImage\CxImage\CxImageDLL\Debug\cximaged.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"c:\CxImage\CxImage\CxImageDLL\Debug"

!ENDIF 

# Begin Target

# Name "KCCI - Win32 Release"
# Name "KCCI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CheckNewerVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\DataPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\DataPlotThread.cpp
# End Source File
# Begin Source File

SOURCE=.\Detailed.cpp
# End Source File
# Begin Source File

SOURCE=.\DetailedThread.cpp
# End Source File
# Begin Source File

SOURCE=.\FeaturetteProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\Initialize.cpp
# End Source File
# Begin Source File

SOURCE=.\KCCI.cpp
# End Source File
# Begin Source File

SOURCE=.\KCCI.rc
# End Source File
# Begin Source File

SOURCE=.\KCCIDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveControls.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsInternet.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsRadar.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsSchoolNet.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsThread.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsWebCam.cpp
# End Source File
# Begin Source File

SOURCE=.\ParseData.cpp
# End Source File
# Begin Source File

SOURCE=.\PopulateLists.cpp
# End Source File
# Begin Source File

SOURCE=.\Radar.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryInternet.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryRadar.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistrySchoolNet.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryWebCam.cpp
# End Source File
# Begin Source File

SOURCE=.\RenderSchoolNet.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\AshSysTray\Traynot.cpp
# End Source File
# Begin Source File

SOURCE=.\Update.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateData.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateSchoolNetData.cpp
# End Source File
# Begin Source File

SOURCE=.\WebCam.cpp
# End Source File
# Begin Source File

SOURCE=.\WebCamThread.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CheckConnection.h
# End Source File
# Begin Source File

SOURCE=.\DataPlot.h
# End Source File
# Begin Source File

SOURCE=.\DataPlotThread.h
# End Source File
# Begin Source File

SOURCE=.\Detailed.h
# End Source File
# Begin Source File

SOURCE=.\DetailedThread.h
# End Source File
# Begin Source File

SOURCE=.\FeaturetteProgress.h
# End Source File
# Begin Source File

SOURCE=.\Initialize.h
# End Source File
# Begin Source File

SOURCE=.\KCCI.h
# End Source File
# Begin Source File

SOURCE=.\KCCIDlg.h
# End Source File
# Begin Source File

SOURCE=.\KCCISchoolNet.h
# End Source File
# Begin Source File

SOURCE=.\MoveControls.h
# End Source File
# Begin Source File

SOURCE=.\OptionsGeneral.h
# End Source File
# Begin Source File

SOURCE=.\OptionsInternet.h
# End Source File
# Begin Source File

SOURCE=.\OptionsRadar.h
# End Source File
# Begin Source File

SOURCE=.\OptionsSchoolNet.h
# End Source File
# Begin Source File

SOURCE=.\OptionsSheet.h
# End Source File
# Begin Source File

SOURCE=.\OptionsThread.h
# End Source File
# Begin Source File

SOURCE=.\OptionsWebCam.h
# End Source File
# Begin Source File

SOURCE=.\PopulateLists.h
# End Source File
# Begin Source File

SOURCE=.\Radar.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\Render.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\AshSysTray\Traynot.h
# End Source File
# Begin Source File

SOURCE=.\Update.h
# End Source File
# Begin Source File

SOURCE=.\UpdateData.h
# End Source File
# Begin Source File

SOURCE=.\WebCam.h
# End Source File
# Begin Source File

SOURCE=.\WebCamThread.h
# End Source File
# Begin Source File

SOURCE=..\CxImage\CxImage\ximage.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\base640.jpg
# End Source File
# Begin Source File

SOURCE=.\res\KCCI.ico
# End Source File
# Begin Source File

SOURCE=.\res\KCCI.rc2
# End Source File
# Begin Source File

SOURCE=.\SMAI4.bmp
# End Source File
# Begin Source File

SOURCE=.\splash.bmp
# End Source File
# Begin Source File

SOURCE=.\wind_E.gif
# End Source File
# Begin Source File

SOURCE=.\wind_ENE.gif
# End Source File
# Begin Source File

SOURCE=.\wind_ESE.gif
# End Source File
# Begin Source File

SOURCE=.\wind_N.gif
# End Source File
# Begin Source File

SOURCE=.\wind_NE.gif
# End Source File
# Begin Source File

SOURCE=.\wind_NNE.gif
# End Source File
# Begin Source File

SOURCE=.\wind_NNW.gif
# End Source File
# Begin Source File

SOURCE=.\wind_NW.gif
# End Source File
# Begin Source File

SOURCE=.\wind_S.gif
# End Source File
# Begin Source File

SOURCE=.\wind_SE.gif
# End Source File
# Begin Source File

SOURCE=.\wind_SSE.gif
# End Source File
# Begin Source File

SOURCE=.\wind_SSW.gif
# End Source File
# Begin Source File

SOURCE=.\wind_SW.gif
# End Source File
# Begin Source File

SOURCE=.\wind_W.gif
# End Source File
# Begin Source File

SOURCE=.\wind_WNW.gif
# End Source File
# Begin Source File

SOURCE=.\wind_WSW.gif
# End Source File
# End Group
# Begin Group "NewMenu"

# PROP Default_Filter ".cpp, .h"
# Begin Source File

SOURCE=.\NewMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\NewMenu.h
# End Source File
# End Group
# Begin Group "PPToolTip"

# PROP Default_Filter ".cpp, .h"
# Begin Source File

SOURCE=..\PPToolTip\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=..\PPToolTip\CeXDib.h
# End Source File
# Begin Source File

SOURCE=..\PPToolTip\PPDrawManager.cpp
# End Source File
# Begin Source File

SOURCE=..\PPToolTip\PPDrawManager.h
# End Source File
# Begin Source File

SOURCE=..\PPToolTip\PPHtmlDrawer.cpp
# End Source File
# Begin Source File

SOURCE=..\PPToolTip\PPHtmlDrawer.h
# End Source File
# Begin Source File

SOURCE=..\PPToolTip\PPTooltip.cpp
# End Source File
# Begin Source File

SOURCE=..\PPToolTip\PPTooltip.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\splash.png
# End Source File
# Begin Source File

SOURCE=.\splash2.png
# End Source File
# End Target
# End Project
