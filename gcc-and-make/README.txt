GNU Compiler Collection(GCC)
===========================

Options:
        -c         Compile and assembly but not link, this will generate *.o files.
        -o         Place the output input file.
        -w         Don't show any warnings.
        -Wall      Show all compile warnings.
        -g         This will let you use gdb to debug.
        -Os        Optimize level.
        -ansi      ansi C.
        -S         Compile only. This will generate *.S files.
        -E         Preprocessor only.
        -Idir      Add header files's search paths.
        -llibrary  Link library.
        -Ldir      Add librarys search paths.


LINK:

- http://a7419.pixnet.net/blog/post/57931682-gcc%E5%8F%83%E6%95%B8%E8%A9%B3%E8%A7%A3
- http://changhoward.blogspot.tw/2009/02/using-gcc-to-create-static-and-shared.html


Makefile
========

If VAR2 change, VAR1 will change too.

        VAR1 = VAR2

If VAR2 change, VAR1 will keep the origin value.

        VAR1 := VAR2

Set VAR1 default value to VAR2.

        VAR1 ?= VAR2

This will let you add string into VAR1.

        VAR1 += VAR2

You can use $(VAR) to get VAR's return value

        echo $(VAR2)

The basic format is

        target: prerequisites
            commands

Command will be executed if

        1. target not exist.
        2. prerequisites's mtime is newer than target's mtime.

SYMBOLS:

        $@              Target.
        $^              Prerequisites.
        $<              First Prerequisites.
        $?              Newer than target's prerequisites.


FUNCTIONS:
        $(warning message)
        $(error message)
        $(subst from,to,string)
