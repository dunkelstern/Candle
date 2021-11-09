$env:PATH += ";${env:QTDIR}\bin"
$env:PATH += ";C:\Program Files (x86)\NSIS"
$QT_VERSION = "Qt_5_15_2"
$COMPILER = "MSVC2019"
$MODE = "release"

$ARCH = "64bit"

$BUILD_DIR = "build-candle-Desktop_${QT_VERSION}_${COMPILER}_${ARCH}-${MODE}"

# Switch to build dir
Set-Location -Path "..\..\..\${BUILD_DIR}"

# Create directory structure
Remove-Item "bin" -Recurse -Force -Confirm:$false
Remove-Item "dist" -Recurse -Force -Confirm:$false
New-Item -Name "bin" -ItemType "directory" -Force
#New-Item -Path "bin" -Name "plugins" -ItemType "directory" -Force
New-Item -Path "bin" -Name "script" -ItemType "directory" -Force
New-Item -Name "dist" -ItemType "directory" -Force

# Gather dependencies
windeployqt.exe --dir bin --${MODE} --force src\candle\release\Candle.exe
Copy-Item "src\candle\release\Candle.exe" "bin"

# Move redist files toplevel
Remove-Item "vc_redist.*.exe" -Force -Confirm:$false
Move-Item "bin\vc_redist.*.exe" "."

# Scripting plugins
Copy-Item "src\scriptbindings\qtbindings\plugins\script\*.dll" ".\bin\script\"

# Custom Widgets
Copy-Item "src\designerplugins\customwidgetsplugin\${MODE}\*.dll" ".\bin\"

# Plugins
Copy-Item -Recurse "..\Candle\src\candleplugins" ".\bin\plugins"
Remove-Item "bin\plugins\camera" -Recurse -Force -Confirm:$false  # Camera plugin does not work
Remove-Item "bin\plugins\candleplugins.pro" -Force -Confirm:$false # Remove project file

# Build installer
Copy-Item "..\Candle\build_scripts\windows-nsis\installer_${ARCH}.nsis" "installer.nsis" -Force
makensis.exe /X"SetCompressor /FINAL lzma" installer.nsis