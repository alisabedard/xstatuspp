Buffer.o: Buffer.cpp Buffer.h libjb/cpp.h libjb/macros.h
Button.o: Button.cpp Button.h Font.h libjb/JBDim.h Window.h XData.h \
  libjb/xcb.h config.h libjb/cpp.h util.h
Font.o: Font.cpp Font.h libjb/JBDim.h libjb/xcb.h
Options.o: Options.cpp Options.h libjb/cpp.h libjb/log.h
Toolbar.o: Toolbar.cpp Toolbar.h Button.h Font.h libjb/JBDim.h Window.h \
  XData.h config.h libjb/cpp.h
Widget.o: Widget.cpp Widget.h Buffer.h Font.h libjb/JBDim.h Window.h \
  XData.h
Window.o: Window.cpp Window.h libjb/xcb.h config.h XData.h
XData.o: XData.cpp XData.h Window.h libjb/xcb.h
XStatus.o: XStatus.cpp XStatus.h Buffer.h Font.h libjb/JBDim.h load.h \
  BufferWidget.h Widget.h Window.h XData.h Options.h Toolbar.h Button.h \
  battery.h config.h clock.h libjb/cpp.h libjb/log.h libjb/xcb.h \
  libjb/util.h status_file.h temperature.h util.h
battery.o: battery.cpp battery.h Font.h libjb/JBDim.h libjb/log.h \
  libjb/macros.h config.h util.h XData.h Window.h
clock.o: clock.cpp clock.h Font.h libjb/JBDim.h XData.h Window.h config.h \
  Widget.h Buffer.h
