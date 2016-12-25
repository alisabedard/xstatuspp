battery.o: battery.cpp battery.h config.h libjb/log.h libjb/macros.h \
 libjb/util.h util.h libjb/xcb.h xdata.h xstatus.h font.h libjb/JBDim.h
button.o: button.cpp button.h config.h font.h libjb/JBDim.h libjb/xcb.h \
 xdata.h window.h
clock.o: clock.cpp clock.h xdata.h config.h font.h libjb/JBDim.h \
 libjb/log.h libjb/xcb.h
font.o: font.cpp font.h libjb/JBDim.h libjb/log.h libjb/xcb.h
load.o: load.cpp load.h xdata.h config.h font.h libjb/JBDim.h
main.o: main.cpp config.h xstatus.h
status_file.o: status_file.cpp status_file.h config.h font.h \
 libjb/JBDim.h libjb/file.h libjb/util.h xdata.h
temperature.o: temperature.cpp temperature.h config.h font.h \
 libjb/JBDim.h util.h libjb/xcb.h xdata.h
toolbar.o: toolbar.cpp toolbar.h button.h config.h libjb/log.h
util.o: util.cpp util.h libjb/xcb.h xdata.h font.h libjb/JBDim.h \
 libjb/file.h
window.o: window.cpp window.h config.h libjb/xcb.h xdata.h
xdata.o: xdata.cpp xdata.h libjb/xcb.h
xstatus.o: xstatus.cpp libjb/log.h libjb/xcb.h xstatus.h battery.h \
 clock.h xdata.h config.h load.h status_file.h temperature.h toolbar.h \
 font.h libjb/JBDim.h window.h util.h
