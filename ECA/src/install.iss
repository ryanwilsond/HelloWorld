#define APPNAME "ECA"

; x.x.x = major version . major feature . each commit relevant to ccc
#define APPVERSION "0.1.46"
#define BUILDT1 "version : ECA-WOS32-builds-"
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

[Files]
Source: "./../LICENSE"; DestDir: "{app}"; DestName: "LICENSE"
Source: "./../bin\ccc.exe"; DestDir: "{app}\bin"; DestName: "ccc.exe"
; Source: "./../bin\eas.exe"; DestDir: "{app}\bin"; DestName: "eas.exe"
Source: "./../docs\Usingccc.md"; DestDir: "{app}\docs"; DestName: "Usingccc.md"
Source: "./../lib\w64-eca\include\test.inc"; DestDir: "{app}\lib\w64-eca\include"; DestName: "test.inc"
Source: "./../lib\wos32-eca32\include\test.inc"; DestDir: "{app}\lib\wos32-eca32\include"; DestName: "test.inc"

[CustomMessages]
BuildT1Txt={#BUILDT1}
BuildT2Txt={#BUILDT2}
BuildT3Txt={#BUILDT3}
AppVerTxt={#APPVERSION}
DateTimeTxt={#DATETIME}

[Code]
var
    buildInfoTxt: string;
    sspos: TSetupStep;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  buildInfoTxt := CustomMessage('BuildT1Txt') + CustomMessage('AppVerTxt') + #13#10 + CustomMessage('BuildT2Txt') + CustomMessage('DateTimeTxt') + #13#10 + CustomMessage('BuildT3Txt') + ExpandConstant('{app}') + #13#10;
  if CurStep = ssPostInstall then
    SaveStringToFile(ExpandConstant('{app}') + '\build_info.txt', buildInfoTxt, False);
end;
