# Networking

## IP
```sh
$ ifconfig

# Check IP address
$ ifconfig | grep inet
```
## Check open port

```sh
$ netstat
$ sudo netstat -p
$ sudo netstat -lptu | grep :http
$ sudo netstat -lptun | grep :80
$ sudo lsof -i :80
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

## wget
```sh
wget www.example.com
```

## curl
```sh
curl www.example.com -o filename
```

## httpie
```sh
$ http www.examle.com
$ http -d www.example.com
```
