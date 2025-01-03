; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=KCCI School Net 8 Desktop Weather Client
AppVerName=KCCI School Net 8 Desktop Weather Client 2.4.1
AppVersion=2.4.1
AppPublisher=Kenneth Ballard
AppPublisherURL=http://kcci.kennethballard.com
AppSupportURL=http://kcci.kennethballard.com
AppUpdatesURL=http://kcci.kennethballard.com
DefaultDirName={pf}\KCCI School Net 8
DisableDirPage=yes
DefaultGroupName=KCCI School Net 8
DisableProgramGroupPage=yes
LicenseFile=.\KCCI School Net 8 Desktop Weather Client - License Agreement.rtf
OutputBaseFilename=KCCI School Net 8
Compression=lzma
SolidCompression=yes

AllowCancelDuringInstall=no
MinVersion=0,5.0
PrivilegesRequired=admin
AllowUNCPath=no
; InfoBeforeFile=info.rtf
AppId=8B3E3413-06CF-4a8e-900F-3748510B22D0

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\KCCI School Net 8\Release\KCCI.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\KCCI School Net 8\Release\cximage.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\Fonts\DigitaldreamFatnarrow.ttf"; DestDir: "{fonts}"; FontInstall: "Digital dream Fat Narrow";
; Source: "..\Fonts\bnkgothm.ttf"; DestDir: "{fonts}"; FontInstall: "Bank Gothic Medium BT";
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\KCCI School Net 8"; Filename: "{app}\KCCI.exe"
Name: "{group}\{cm:UninstallProgram,KCCI School Net 8}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\KCCI School Net 8"; Filename: "{app}\KCCI.exe"; Tasks: desktopicon
Name: "{commonappdata}\Microsoft\Internet Explorer\Quick Launch\KCCI School Net 8"; Filename: "{app}\KCCI.exe"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\KCCI.exe"; Description: "{cm:LaunchProgram,KCCI School Net 8 Desktop Weather Client}"; Flags: nowait postinstall skipifsilent

