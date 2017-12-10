@echo This batch file will link the game data folder to the Android and NaCl build folders
@echo --

pushd GameEmptyReplaceMe\Game\SourceAndroid\AndroidStudio\app\src\main
mkdir assets
cd assets
mklink /J "Data" "../../../../../../Data"
popd

pushd GameEmptyReplaceMe\Game\SourceNaCL\Web
mklink /J "Data" "../../Data"
popd

pause
