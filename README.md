anos
====

>anos is a toy operating system.

Setup Development Environment
---

###Install bochs

```
$ wget http://bochs.sourceforge.net/svn-snapshot/bochs-20140628.tar.gz
$ tar xzvf bochs-20140628.tar.gz
$ cd bochs-20140628
$ ./configure --enable-disasm --enable-gdb-stub --with-x11
$ make
$ sudo make install
```

Build
---

```
$make all
```

Run and Debug
---

###Run

```
$bochs -q
```

###Debug

```
$bochs -q -f bochsrc.gdb
```

Then open a new terminal and run gdb.

```
$gdb
>target remote :1234
>br *0x7c00
>c
```