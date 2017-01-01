Battery.o: Battery.cpp Battery.h Font.h libjb/JBDim.h Widget.h Buffer.h \
  Window.h XData.h libjb/log.h libjb/macros.h config.h util.h
Buffer.o: Buffer.cpp Buffer.h libjb/cpp.h libjb/macros.h
Button.o: Button.cpp Button.h Font.h libjb/JBDim.h Window.h XData.h \
  libjb/xcb.h config.h libjb/cpp.h util.h
Clock.o: Clock.cpp Clock.h BufferWidget.h Widget.h Buffer.h Font.h \
  libjb/JBDim.h Window.h XData.h config.h
Font.o: Font.cpp Font.h libjb/JBDim.h libjb/xcb.h
Load.o: Load.cpp Load.h BufferWidget.h Widget.h Buffer.h Font.h \
  libjb/JBDim.h Window.h XData.h config.h
Options.o: Options.cpp Options.h libjb/cpp.h libjb/log.h
Statusbar.o: Statusbar.cpp Statusbar.h BufferWidget.h Widget.h Buffer.h \
  Font.h libjb/JBDim.h Window.h XData.h config.h
Temperature.o: Temperature.cpp Temperature.h BufferWidget.h Widget.h \
  Buffer.h Font.h libjb/JBDim.h Window.h XData.h config.h util.h
Toolbar.o: Toolbar.cpp Toolbar.h Button.h Font.h libjb/JBDim.h Window.h \
  XData.h config.h libjb/cpp.h
Widget.o: Widget.cpp Widget.h Buffer.h Font.h libjb/JBDim.h Window.h \
  XData.h
Window.o: Window.cpp Window.h libjb/xcb.h config.h XData.h
XData.o: XData.cpp XData.h Window.h libjb/xcb.h
XStatus.o: XStatus.cpp XStatus.h Options.h Toolbar.h Button.h Font.h \
  libjb/JBDim.h Window.h XData.h Battery.h Widget.h Buffer.h config.h \
  Clock.h BufferWidget.h libjb/cpp.h libjb/log.h libjb/xcb.h \
  libjb/util.h Load.h Statusbar.h Temperature.h util.h
main.o: main.cpp config.h Options.h XStatus.h Toolbar.h Button.h Font.h \
  libjb/JBDim.h Window.h XData.h
util.o: util.cpp util.h Font.h libjb/JBDim.h libjb/xcb.h
