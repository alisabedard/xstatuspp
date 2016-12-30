Buffer.o: Buffer.cpp Buffer.h libjb/macros.h
Options.o: Options.cpp Options.h libjb/cpp.h libjb/log.h
battery.o: battery.cpp battery.h font.h libjb/JBDim.h libjb/log.h \
  libjb/macros.h config.h util.h xdata.h window.h
button.o: button.cpp button.h font.h libjb/JBDim.h window.h xdata.h \
  libjb/log.h libjb/xcb.h config.h util.h
clock.o: clock.cpp clock.h font.h libjb/JBDim.h xdata.h window.h \
  libjb/log.h libjb/xcb.h Buffer.h config.h Renderer.h
font.o: font.cpp font.h libjb/JBDim.h libjb/xcb.h
load.o: load.cpp load.h font.h libjb/JBDim.h Buffer.h config.h Renderer.h \
  xdata.h window.h
main.o: main.cpp config.h Options.h xstatus.h font.h libjb/JBDim.h \
  toolbar.h button.h window.h xdata.h
status_file.o: status_file.cpp status_file.h font.h libjb/JBDim.h \
  Buffer.h config.h Renderer.h xdata.h window.h
temperature.o: temperature.cpp temperature.h font.h libjb/JBDim.h \
  config.h Buffer.h Renderer.h xdata.h window.h util.h
toolbar.o: toolbar.cpp toolbar.h button.h font.h libjb/JBDim.h window.h \
  xdata.h libjb/log.h config.h
util.o: util.cpp util.h font.h libjb/JBDim.h libjb/xcb.h
window.o: window.cpp window.h libjb/xcb.h config.h xdata.h
xdata.o: xdata.cpp xdata.h window.h libjb/xcb.h
xstatus.o: xstatus.cpp xstatus.h font.h libjb/JBDim.h Options.h toolbar.h \
  button.h window.h xdata.h libjb/log.h libjb/util.h libjb/xcb.h \
  battery.h clock.h config.h load.h status_file.h temperature.h util.h
