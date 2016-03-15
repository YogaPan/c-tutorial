all:
	make -C system-call
	make -C standard-library
	make -C data-structure
	make -C socket
	make -C asm
	make -C macro
	make -C algorithm

tags:
	make -C system-call tags
	make -C standard-library tags
	make -C data-structure tags
	make -C socket tags
	make -C asm tags
	make -C macro tags
	make -C algorithm tags

clean:
	make -C system-call clean
	make -C standard-library clean
	make -C data-structure clean
	make -C socket clean
	make -C asm clean
	make -C macro clean
	make -C algorithm clean
