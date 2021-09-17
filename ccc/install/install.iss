#define APPNAME "ccc"
#define APPVERSION "0.1.43"

[Setup]
AppName={#APPNAME}
; x.x.x = major version . major feature . each commit relevant to ccc
AppVersion={#APPVERSION}
AppVerName={#APPNAME} {#APPVERSION}
WizardStyle=modern
DefaultDirName={autopf}\ccc
DefaultGroupName=ccc
UninstallDisplayIcon={app}\ccc.exe
OutputDir="."
OutputBaseFilename="ccc_setup"
LicenseFile="LICENSE"
Compression=lzma2
SolidCompression=yes
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64
AppPublisher=EMD

[Files]
Source: "bin\ccc.exe"; DestDir: "{app}\bin"; DestName: "ccc.exe"
Source: "include\test.inc"; DestDir: "{app}\include"; DestName: "test.inc"
