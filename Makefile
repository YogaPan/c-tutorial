all:
	make -C system-call
	make -C standard-library
	make -C data-structure
	make -C socket
	make -C asm

tags:
	make -C system-call tags
	make -C data-structure tags
	make -C socket tags
	make -C asm tags

clean:
	make -C system-call clean
	make -C data-structure clean
	make -C socket clean
	make -C asm clean
