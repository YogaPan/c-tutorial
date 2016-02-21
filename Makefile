all:
	make -C system-call
	make -C data-structure

clean:
	make -C system-call clean
	make -C data-structure clean
