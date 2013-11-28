diana-gui
=========

gui for remote rover control

777777777777777777777777ZO$Z?I77I7I?~~~~~~~~~~~~~~~~~+??I+I7I?=?7~:::::::??,:::=
777777777777777777777:77ZO77+OZ8O$$~~~~~~~~~~~~~~~~~~+??I+I7I=+++~:::::::::,I::=
7777777777777777??777777~7~ZOOZ8O$$~~~~~~~~~~~~~~~~~~+??I+I7?:=++~:::::::::,:7:=
7777777777777777~I77777777$ZOOZ8O$$~~~~~~~~~~~~~~~~~~+??I+I=+?=++~:::::::::,::7=
777777777777777777??=7777O$ZOOZ8O$$~~~~~~~~~~~~~~~~~~+??I+I7I?=++~:::::::::,::I=
DDDDDDDDNN8777777$DDD7?77O$ZOONDDI$~~~~~~~~DDN~~~~~~~+DDN++7I?=++~:8DDD::::,::+I
DDNNNNNNDDDD$7777$DDD7I77O$ZOODDDD$~~~~~~~~DDDD7~~~~~+DDN+?7I?=++~?DDDD7:::,::?7
DD77777777NDN7777$DDD7777O$Z7DDINDD~~~~~~~~DDDDD8~~~~+DDN?I7II??+~NDDNDN:::,::7?
DD777777777DDD777$DDD77I77$ZNDD87DD$~~~~~~~DDNDDDN=~~+ODN77I777I?8DN::NDN::,:?7=
DD777777777NDN777$DDD77777+8DNZ8ONDN~~~~=~~DDN~+NDDD~=ZDN77777777DD?::7DDZ:,I7~~
DD777777777NDN777$DDD777Z777N$Z8O$DDD~==~~~DDN~~~NDDNIZDN777777INDD~~~~NDD?77~:=
DD77777777IDDD777$DDD777ZODI777?II$ZI7~~~~~DDN~~~~$DDN7DNI?+??7777I?I+I?I77?::~I
DD7777777ZDDN7777$DDD777Z?DDOOI?II$NDD?~~~~DDN~~~~~~NDDDN?+=+?IDD7I7777I7NDO,~I7
DDNNNNDDDDDN=7777$DDD777ZND?OOZ8O$Z$NDN++++DDN+++++?7NDDN?+=+?DDO77I????,NDD=I77
DDDDDDDDNND777777$DDD777ODNZOOZ8O$ZOODDZ???DDN??????77ZDN=?=+DDN?777????,:DDN777
+++++++++?????????+++??????????????????????+++??????7I?++????+++?III??????++7777
OO7MMZNNN7N7NZM7N7788IM7Z7$MOMZNNONO7OOOIN?7?M7?NNN7$7II8IIIZ?NOO$Z77M+N?NI77777
8ZZ7ZO77D7DIOZ$$$Z7O8ZZ7?D?ZIZZD77DD+ZZZOO+I+8O$N+ZZZ77ZO+IID$ZZ?77$OZ+~?ZZO7$7I



Project Diana

Graphical application for rover remote control

-- Build Instruction -- 

necessary libs:
Qt5
SDL

Qutty (provided as submodule, see 'Git submodule')

-------------------------
mkdir build && cd build
qmake ..
make
make install
-------------------------

-- Troubleshotting -- 
o Remember to always read the logs, look for missing files inside the logs.
o There is still a problem with the build system: it doesn't copy the configurations
of the app. This file can be copied manually or using 'make install'. See
 'Config Files'.

-- Git submodule --
Download the qutty submodule with

git submodule init
git submodule update

-- Config Files --
defaults/electronicDataView.csv
  this file contains all the details of the data to be shown over the drawing
  of the rover. If this file is missing, no data is shown.
