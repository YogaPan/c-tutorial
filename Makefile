all:
	make -C syscall
	make -C basic/struct_padding
	make -C basic/stdlib
	make -C data-structure
	make -C socket
	make -C asm
	make -C basic/macro
	make -C algorithm

tags:
	make -C syscall tags
	make -C basic/struct_padding tags
	make -C basic/stdlib tags
	make -C data-structure tags
	make -C socket tags
	make -C asm tags
	make -C basic/macro tags
	make -C algorithm tags

clean:
	make -C syscall clean
	make -C basic/struct_padding clean
	make -C basic/stdlib clean
	make -C data-structure clean
	make -C socket clean
	make -C asm clean
	make -C basic/macro clean
	make -C algorithm clean

format:
	astyle --style=linux --indent=tab --pad-oper --pad-header --suffix=none *.[ch]
