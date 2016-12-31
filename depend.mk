Buffer.o: Buffer.cpp Buffer.h libjb/cpp.h libjb/macros.h
Button.o: Button.cpp Button.h Font.h libjb/JBDim.h Window.h XData.h \
  libjb/xcb.h config.h libjb/cpp.h util.h
Font.o: Font.cpp Font.h libjb/JBDim.h libjb/xcb.h
Load.o: Load.cpp Load.h BufferWidget.h Widget.h Buffer.h Font.h \
  libjb/JBDim.h Window.h XData.h config.h
Options.o: Options.cpp Options.h libjb/cpp.h libjb/log.h
Toolbar.o: Toolbar.cpp Toolbar.h Button.h Font.h libjb/JBDim.h Window.h \
  XData.h config.h libjb/cpp.h
Widget.o: Widget.cpp Widget.h Buffer.h Font.h libjb/JBDim.h Window.h \
  XData.h
Window.o: Window.cpp Window.h libjb/xcb.h config.h XData.h
XData.o: XData.cpp XData.h Window.h libjb/xcb.h
