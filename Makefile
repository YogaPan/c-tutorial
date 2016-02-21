all:
	make -C system-call
	make -C data-structure
	make -C asm

tags:
	make -C system-call tags
	make -C data-structure tags
	make -C asm tags

clean:
	make -C system-call clean
	make -C data-structure clean
	make -C asm clean
