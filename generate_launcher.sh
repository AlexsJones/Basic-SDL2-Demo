##Generates an application file that launches the game, for Linux/Unix.
#!/bin/sh
Name="Plane of Craftiness"
Version=.07
FileName="poc"
FileType="desktop"
Path=$PWD
Icon=$Path/icon.png
Categories="Game;ActionGame;"
Comment="2D Massively Multiplayer Online Role Playing Strategic Defense and Conquer Game"

##	Generate the file for Linux.
OS=`uname -s`
##	I don't know if Mac OS X if supports '.desktop' files, but this will generate them anyway.
if [ $OS == "Linux" || "Darwin" ]
	then
	echo -e -n 							\
	[Desktop Entry]\\n					\
	Name=$Name\\n						\
	Version=$Version\\n					\
	Path=$Path\\n						\
	Exec=./$FileName\\n					\
	Icon=$Icon\\n						\
	Comment=$Comment\\n					\
	Categories=$Categories\\n			\
	Type=Application\\n					\
	Encoding=UTF-8\\n					\
	StartupNotify=false\\n				\
	Terminal=false 						> $FileName.$FileType

	chmod +x $FileName.$FileType
	if [ -x "$FileName.$FileType" ]
		then
		echo "Error, failed to set the file to be executable."
		echo "You can do this manually by typing 'chmod +x $FileName.$FileType' or enabling it in the properties of the file."
	fi
	cp $FileName.$FileType ~/.local/share/applications

else 
	echo "Sorry, this script only support Linux at this time."
	echo "To run the game, double-click 'poc' or type './poc'."
fi
