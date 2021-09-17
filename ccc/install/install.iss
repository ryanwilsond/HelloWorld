[Setup]
AppName=ccc
AppVersion=0.1.0
WizardStyle=modern
DefaultDirName={autopf}\ccc
DefaultGroupName=ccc
; UninstallDisplayIcon={app}\ccc.exe
OutputDir="."
LicenseFile="LICENSE"
Compression=lzma2
SolidCompression=yes
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64

[Files]
Source: "bin\ccc.exe"; DestDir: "{app}\bin"; DestName: "ccc.exe"
Source: "include\test.inc"; DestDir: "{app}\include"; DestName: "test.inc"
