run: all
	./test.sh

run_debug: debug
	./test.sh
all:
	$(MAKE) -C ./protocol
	$(MAKE) -C ./agent 
	$(MAKE) -C ./client 
	$(MAKE) -C ./server 
debug:
	$(MAKE) -C ./protocol debug
	$(MAKE) -C ./agent Debug
	$(MAKE) -C ./client Debug
	$(MAKE) -C ./server Debug

.PHONY: all
