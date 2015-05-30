@echo This batch file will link a data folder from Engine to GameEmptyReplaceMe/Game
@echo --

cd GameMinimalReplaceMe/Game

cd SourceAndroid/AndroidApk
mkdir assets
cd assets
mklink /J "Data" "../../../Data"

pause