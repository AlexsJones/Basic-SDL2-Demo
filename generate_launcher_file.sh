##Generates am application file that launches the game, for Linux/Unix.
#!/bin/sh
Name="Plane of Craftiness"
FileName="poc"
Version=.1
Type=Application
Encoding=UTF-8
Path=$PWD
Exec=./$FileName
Icon=$Path/icon.png
Categories="Game;ActionGame;"
Comment="2D Massively Multiplayer Online Role Playing Strategic Defense and Conquer Game"
StartupNotify=false
Terminal=false

exec echo -e -n [Desktop Entry]\\nName=$Name\\nVersion=$Version\\nType=$Type\\nEncoding=$Encoding\\nPath=$Path\\nExec=$Exec\\nIcon=$Icon\\nCategories=$Categories\\nComment=$Comment\\nStartupNotify=$StartupNotify\\nTerminal=$Terminal > $FileName.desktop
