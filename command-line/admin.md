# Basic command

## User
```sh
$ passwd                     # change your password
$ sudo adduser username           # add new user
$ sudo adduser username groupname # Add group to user
$ sudo adduser yogapan sudo       # Add yogapan sudoer
```

## Cron
| command    | descrption       |
|------------|------------------|
| crontab -e | edit cron        |
| crontab -r | remove cron      |
| crontab -l | list cron        |
| crontab -u | change cron user |

minute | hour | day  | month | week | user | command
-------|------|------|-------|------|------|--------------
 0~59  | 0~23 | 1~31 | 1~12  | 0~6  | user | /usr/bin/xxxx

**Example**
```cron
*/5 * * * * root /usr/libexec/atrun      # Every 5 minutes
0 1 1-20 * * root /usr/libexec/atrun     # At day 1~20's one o'clock
*/5 8-16 * * * root /usr/libexec/atrun
@reboot root /usr/libexec/atrun
```

Cron command
```sh
$ sudo service cron status
$ sudo service cron start
$ sudo service cron stop
$ sudo service cron restart
```

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

## Process
```sh
$ ps aux                  # All process detail
$ ps aux | grep root      # Use pipe
$ ps -u root              # Process belongs to root
$ ps -e                   # Initial process
```

```sh
$ kill 1234
$ kill -9 1234            # Force
```

## Apache2

All your web page in /var/www/html
```sh
sudo service apache2 status
sudo service apache2 start
sudo service apache2 stop
sudo service apache2 restart
```

## Update time
```sh
sudo ntpdate -s time.stdtime.gov.tw
```

## LINK
- [the-art-of-command-line](https://github.com/jlevy/the-art-of-command-line)
- [TLDR pages](http://tldr-pages.github.io/)
- [explainshell](http://explainshell.com/)
