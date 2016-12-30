Buffer.o: Buffer.cpp Buffer.h libjb/cpp.h libjb/macros.h
Button.o: Button.cpp Button.h Font.h libjb/JBDim.h Window.h XData.h \
  libjb/xcb.h config.h libjb/cpp.h util.h
Font.o: Font.cpp Font.h libjb/JBDim.h libjb/xcb.h
Options.o: Options.cpp Options.h libjb/cpp.h libjb/log.h
Toolbar.o: Toolbar.cpp Toolbar.h Button.h Font.h libjb/JBDim.h Window.h \
  XData.h config.h libjb/cpp.h
Window.o: Window.cpp Window.h libjb/xcb.h config.h XData.h
XData.o: XData.cpp XData.h Window.h libjb/xcb.h
XStatus.o: XStatus.cpp XStatus.h Font.h libjb/JBDim.h Options.h Toolbar.h \
  Button.h Window.h XData.h libjb/log.h libjb/util.h libjb/xcb.h \
  battery.h clock.h config.h load.h status_file.h temperature.h util.h
battery.o: battery.cpp battery.h Font.h libjb/JBDim.h libjb/log.h \
  libjb/macros.h config.h util.h XData.h Window.h
clock.o: clock.cpp clock.h Font.h libjb/JBDim.h XData.h Window.h \
  libjb/log.h libjb/xcb.h Buffer.h config.h Renderer.h
load.o: load.cpp load.h Font.h libjb/JBDim.h Buffer.h config.h Renderer.h \
  XData.h Window.h
main.o: main.cpp config.h Options.h XStatus.h Font.h libjb/JBDim.h \
  Toolbar.h Button.h Window.h XData.h
status_file.o: status_file.cpp status_file.h Font.h libjb/JBDim.h \
  Buffer.h config.h Renderer.h XData.h Window.h
temperature.o: temperature.cpp temperature.h Font.h libjb/JBDim.h \
  config.h Buffer.h Renderer.h XData.h Window.h util.h
util.o: util.cpp util.h Font.h libjb/JBDim.h libjb/xcb.h
