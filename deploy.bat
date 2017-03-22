SET DIRPROJECT="%~dp0"
set CPU=x86
rem set CPU=x64
set DEPROY_VER=QuickViewer-0.1.9-%CPU%

if %CPU%==x64 (
	set ENV_BUILD=build-QVproject-Desktop_Qt_5_7_0_MSVC2015_64bit
	set ENV_QT=msvc2015_64
) else (
	set ENV_BUILD=build-QVproject-Desktop_Qt_5_7_0_MSVC2015_32bit
	set ENV_QT=msvc2015
)

set DIR_RELEASE="..\%ENV_BUILD%-Release\QuickViewer\release"
rem set DIR_DEPLOY="C:\Users\hanakawa2\Desktop\amazon.com\%DEPROY_VER%"
set DIR_DEPLOY="%~dp0%DEPROY_VER%"
set DEPLOYQT="E:\local\gnu\Qt-5.7\5.7\%ENV_QT%\bin\windeployqt.exe"
set EXECTABLE=QuickViewer.exe
set MS_RUNTIMES=concrt140.dll msvcp140.dll vccorlib140.dll vcruntime140.dll
set DIR_MS_RUNTIME="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\redist\%CPU%\Microsoft.VC140.CRT"

mkdir %DIR_DEPLOY%
copy %DIR_RELEASE%\%EXECTABLE% %DIR_DEPLOY%

cd /D %DIR_MS_RUNTIME%
copy *.dll %DIR_DEPLOY%

cd /D %DIR_DEPLOY%

%DEPLOYQT% --release --compiler-runtime %EXECTABLE%

cd /D %DIRPROJECT%

copy QuickViewer\translations\quickviewer_ja.qm %DIR_DEPLOY%\translations
copy README.md %DIR_DEPLOY%

pause
