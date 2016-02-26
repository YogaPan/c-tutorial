# Networking

## IP
```sh
$ ifconfig
$ ifconfig | grep inet
```
## Check open port

```sh
$ netstat
$ netstat -p
$ netstat -lptu | grep :http
$ netstat -lptun | grep :80
$ lsof -i :80
```

## Ping
```sh
$ ping host
$ ping -c count host
$ ping -i seconds host
$ ping -n host   # Ping host without trying to lookup symbolic names for addresses.
```

## nslookup
```sh
nslookup host
```

## route
```sh
traceroute host
```
