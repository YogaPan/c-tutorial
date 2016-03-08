# Basic command

## Install
```sh
sudo apt-get update
sudo apt-get upgrade

sudo apt-get install package-name
sudo apt-get remove package-name
sudo apt-get autoremove

dpkg --get-selections | grep -v deinstall
apt --installed list
```

## Shutdown
```sh
sudo shutdown -h now  # Halt now
sudo shutdown -r +5   # Reboot 5 minutes later
```

## User
```sh
passwd username                 # change your password
sudo adduser username           # add new user
sudo adduser username groupname # Add group to user
sudo adduser yogapan sudo       # Add yogapan sudoer

usermod -l newUsername oldUsername
usermod -d /home/newHomeDir -m newUsername

sudo deluser temporary
sudo rm -r /home/temporary
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

## Apache2

All your web page in /var/www/html
```sh
sudo service apache2 status
sudo service apache2 start
sudo service apache2 stop
sudo service apache2 restart
```

## Nginx

All your web page in /usr/share/nginx/html  
/etc/nginx/nginx.conf
```sh
sudo service nginx status
sudo service nginx start
sudo service nginx stop
sudo service nginx restart
```

https://www.linode.com/docs/websites/nginx/how-to-configure-nginx

## Update time
```sh
sudo ntpdate -s time.stdtime.gov.tw
```
