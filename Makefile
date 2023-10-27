# To configure exlaunch, edit config.mk.
include $(shell pwd)/config.mk

all:
	cmake -DLOGGER_IP=$(LOGGER_IP) -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain.cmake -S . -B build -G Ninja

send:
	cmake --toolchain=cmake/toolchain.cmake -DFTP_IP=$(FTP_IP) -DLOGGER_IP=$(LOGGER_IP) -DDEBUGMOD=$(DEBUGMOD) -S . -B build && $(MAKE) -C build subsdk_npdm
	
clean:
	rm -r build

log:
	python3 misc/scripts/tcpServer.py