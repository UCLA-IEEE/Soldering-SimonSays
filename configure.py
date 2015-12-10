#!/usr/bin/python

from ninja_syntax import Writer
import os, sys

source_dirs = [
        ".",
        "/home/kbalke/Tools/Atmel/avr8-gnu-toolchain-linux_x86_64/avr/include"]

include_dirs = [
        ]

libraries = [
        "/home/kbalke/Tools/Atmel/avr8-gnu-toolchain-linux_x86_64/avr/lib/avr25/libc.a",
        "/home/kbalke/Tools/Atmel/avr8-gnu-toolchain-linux_x86_64/avr/lib/avr25/libm.a",
        "/home/kbalke/Tools/Atmel/avr8-gnu-toolchain-linux_x86_64/avr/lib/avr25/libattiny84a.a",
        ]

defines = [
        "F_CPU=1000000"
        ]

def subst_ext(fname, ext):
    return os.path.splitext(fname)[0] + ext

def get_sources():
    fnames = []
    for d in source_dirs:
        for f in os.listdir(d):
            fnames.append(os.path.join(d, f))
    return fnames

def get_includes():
    return " ".join(map(lambda x : "-I"+x, source_dirs + include_dirs))

def get_libs():
    return " ".join(libraries)
    #return "-Wl,-rpath," + (":".join(library_dirs))

def get_defines():
    return " ".join(map(lambda x : "-D"+x, defines))

with open("build.ninja", "w") as buildfile:
    n = Writer(buildfile)

    # Variable declarations
    n.variable("cflags", "-funsigned-char -funsigned-bitfields -DDEBUG -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=attiny84a -c -std=gnu99 " + get_includes() + " " +  get_defines())
    n.variable("lflags", " -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=attiny84a")
    n.variable("libs", get_libs())

    # Rule declarations
    n.rule("cxx",
           command = "avr-g++ $cxxflags -c $in -o $out")

    n.rule("cc",
           command = "avr-gcc $cflags -c $in -o $out")

    n.rule("cl",
           command = "avr-gcc -o $out $in $libs $lflags")

    n.rule("och",
           command = "avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature $in $out")

    n.rule("oceep",
           command = "avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex $in $out")

    n.rule("od",
           command = "avr-objdump -h -S $in > $out")

    n.rule("ocsrec",
           command = "avr-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature $in $out")

    n.rule("cdb",
           command = "ninja -t compdb cc > compile_commands.json")

    n.rule("cscf",
            command = "find " + " ".join(set(source_dirs + include_dirs)) + " -regex \".*\\(\\.c\\|\\.h\\|.cpp\\|.hpp\\)$$\" -and -not -type d > $out")

    n.rule("cscdb",
           command = "cscope -bq")

    # Build rules
    n.build("compile_commands.json", "cdb")
    n.build("cscope.files", "cscf")
    n.build(["cscope.in.out", "cscope.po.out", "cscope.out"], "cscdb", "cscope.files")

    objects = []

    def cc(name):
        ofile = subst_ext(name, ".o")
        n.build(ofile, "cc", name)
        objects.append(ofile)
    def cxx(name):
        ofile = subst_ext(name, ".o")
        n.build(ofile, "cxx", name)
        objects.append(ofile)
    def cl(oname, ofiles):
        n.build(oname, "cl", ofiles)

    sources = get_sources()
    map(cc, filter(lambda x : x.endswith(".c"), sources))
    map(cxx, filter(lambda x : x.endswith(".cxx"), sources))

    cl("main.elf", objects)

    n.build("main.hex", "och", "main.elf")
    n.build("main.eep", "oceep", "main.elf")
    n.build("main.lss", "od", "main.elf")
    n.build("main.srec", "ocsrec", "main.elf")
