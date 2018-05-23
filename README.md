21st-Century-Examples
=====================

Dear Reader,

Here are all of the examples from the second edition of _21st Century C_ by Ben Klemens [ http://tinyurl.com/c-for-moderns-2 ]. You'll notice that the captions for all of the examples in the text end in a filename in parens, like (string_utilities.c); that name is referring to the file here.

* Each .c file has a note about how to compile it. Some involve a makefile, and some have a command or two to cut/paste onto your command line. dict_use.c includes an extensive script that runs autoconf on the system.

* Everything is UTF-8. If you are using Windows and the encoding becomes relevant, try
    iconv -f UTF-8 -t UTF-16 < unicode.c > unicode.16.c

* I assume you have the requisite libraries in place, including the GSL and GLib. If installing via package manager, don't forget the -dev or -devel packages. One or two of the examples require Apophenia (available from http://apophenia.info), CWEB, or other requisites which should be obvious from the header, and you can't run the Autotools examples without having Autoconf, Automake, and Libtool installed.

* All of the CFLAGS use the GCC's -std=gnu11 flag, requesting that GCC use the C11 standard. If you have an older copy of GCC that predates C11 support, you'll need to change every instance to -std=gnu99. There exist other compilers that don't understand this flag, and you'll need to delete it entirely.

Here's the GNU sed command to do the changes on every .c file in the current directory all at once:

    #For a version of GCC that predates C11:
    sed -i -e 's/-std=gnu11/-std=gnu99/g' *.c

    #For Clang and icc, which don't need the -std=... flag at all:
    sed -i -e 's/-std=gnu11//g' *.c

* If you get linker errors about resolving the (common but not C-standard) function asprintf, use the version provided as an example in asprintf.c, and the function declaration in that file. Or use the libiberty library, which means adding the -liberty flag to your LDLIBS. For example, MSYS includes libiberty as part of its development package.

Have fun with them,


Ben Klemens
July 2012
