objs=util.o main.o Font.o XData.o Button.o Options.o
objs+=clock.o load.o status_file.o Window.o Toolbar.o
objs+=battery.o temperature.o XStatus.o Buffer.o Widget.o
include config.mk
cflags+=-std=c++11
cflags+=-D_XOPEN_SOURCE=700
cflags+=-D_DEFAULT_SOURCE
cflags+=-D_BSD_SOURCE
ldflags+=-lxcb -lxcb-cursor
ldlags+=${LDFLAGS}
cflags+=${CFLAGS}
CXXFLAGS=${cflags}
PREFIX=/usr
exe=xspp
installdir=${DESTDIR}${PREFIX}
${exe}: libjb/libjb.a ${objs}
	${CXX} ${cflags} ${ldflags} ${objs} ${static} -o $@
	strip -s -o xstatus_stripped ${exe}
	ls -l xstatus_stripped >> sz.log
	rm -f xstatus_stripped
	tail sz.log
libjb/libjb.a:
	cd libjb && ${MAKE} libjb.a
include depend.mk
clean:
	rm -f ${exe} *.o
distclean: clean
	cd libjb && ${MAKE} clean
	rm -f config.mk
install:
	install -d ${installdir}/bin
	install -s ${exe} ${installdir}/bin
depend:
	${CC} -E -MM *.cpp > depend.mk
cppcheck:
	cppcheck --enable=all --inconclusive --std=c++11 \
                . 2> cppcheck.log
	echo 'Results written to cppcheck.log'
#EOF
