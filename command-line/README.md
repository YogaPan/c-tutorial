# Basic command

## User
```sh
$ passwd                     # change your password
$ adduser username           # add new user
$ adduser username groupname # Add group to user
$ adduser yogapan sudo       # Add yogapan sudoer
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

Example
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

## LINK
- [the-art-of-command-line](https://github.com/jlevy/the-art-of-command-line)
- [TLDR pages](http://tldr-pages.github.io/)
- [explainshell](http://explainshell.com/)
