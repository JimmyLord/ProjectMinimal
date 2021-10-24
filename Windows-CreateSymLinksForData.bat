@echo This batch file will link the game data folder to the Android and NaCl build folders
@echo --

rem pushd GameMinimalReplaceMe\Game\SourceAndroid\AndroidStudio\app\src\main
rem mkdir assets
rem cd assets
rem mklink /J "Data" "../../../../../../Data"
rem popd

pushd GameMinimalReplaceMe\Game\SourceNaCL\Web
mklink /J "Data" "../../Data"
popd

pause
