# Hard Disk

## swap

Create a 500 MB swapfile:
```sh
$ sudo dd if=/dev/zero of=/swapfile bs=1024 count=524288
$ sudo mkswap /swapfile
$ sudo swapon /swapfile
```

Check out all swap and memory status
```sh
$ sudo swapon -s
$ free -m
```

This will add swapfile every time you restart computer.
In **/etc/fstab** add:
```
/swapfile none swap sw 0 0
```

## dd
```sh
dd if=/dev/random of=/dev/sda
mkfs.ext3 /dev/sda
```
