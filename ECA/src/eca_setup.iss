#define APPNAME "ECA"

; ---- Installer Setup ----
; x.x.x = major version . major feature . each commit relevant to ccc
#define APPVERSION "0.1.46"
#define BUILDT1 "version : ECA-WOS32-WIN64-builds-"
#define BUILDT2 "date    : "
#define BUILDT3 "path    : "
#define DATETIME GetDateTimeString('dd/mm/yyyy hh:nn:ss am/pm', '.', ':')

[Setup]
AppName={#APPNAME}
AppVersion={#APPVERSION}
AppVerName={#APPNAME} {#APPVERSION}
WizardStyle=modern
DefaultDirName={autopf}\ECA
DefaultGroupName=ECA
UninstallDisplayIcon={app}\ccc.exe
OutputDir="./../"
OutputBaseFilename="eca_setup"
LicenseFile="./../LICENSE"
Compression=lzma2
SolidCompression=yes
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64
AppPublisher=EMD

; ---- Files ----
[Files]
; General files and executables
Source: "./../help.txt"; DestDir: "{app}"; DestName: "help.txt"
Source: "./../LICENSE"; DestDir: "{app}"; DestName: "LICENSE"
Source: "./../bin/release/ecc.exe"; DestDir: "{app}\bin"; DestName: "ecc.exe"
Source: "./../docs/Usingecc.md"; DestDir: "{app}\docs"; DestName: "Usingecc.md"
; G language libraries
Source: "./../lib/w64/g/w64.gh"; DestDir: "{app}\lib\w64\g"; DestName: "w64.gh"
Source: "./../lib/w32/g/w32.gh"; DestDir: "{app}\lib\w32\g"; DestName: "w32.gh"
Source: "./../lib/wos32/g/wos32.gh"; DestDir: "{app}\lib\wos32\g"; DestName: "wos32.gh"
Source: "./../lib/share/g/test.gh"; DestDir: "{app}\lib\share\g"; DestName: "test.gh"
; EAS libraries
Source: "./../lib/wos32/asm/test.ein"; DestDir: "{app}\lib\wos32\asm"; DestName: "test.ein"

; ---- Build Info ----
[CustomMessages]
BuildT1Txt={#BUILDT1}
BuildT2Txt={#BUILDT2}
BuildT3Txt={#BUILDT3}
AppVerTxt={#APPVERSION}
DateTimeTxt={#DATETIME}

[Code]
var
    buildInfoTxt: string;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  buildInfoTxt := CustomMessage('BuildT1Txt') + CustomMessage('AppVerTxt') + #13#10 + CustomMessage('BuildT2Txt') + CustomMessage('DateTimeTxt') + #13#10 + CustomMessage('BuildT3Txt') + ExpandConstant('{app}') + #13#10;
  if CurStep = ssPostInstall then
    SaveStringToFile(ExpandConstant('{app}') + '\build_info.txt', buildInfoTxt, False);
end;
