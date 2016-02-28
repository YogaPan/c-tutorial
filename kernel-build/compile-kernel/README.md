## Challenge2

# How to do?
```sh
$ git clone https://github.com/torvalds/linux.git && cd linux
$
$ make localmodconfig   # All your settings will in .config
$ vim .config           # change CONFIG_LOCALVERSION_AUTO=y

$ make -jx              # x means how many cpus you have
$ make modules_install install
$
$ dmesg | head -n 2
$ uname -a
```
