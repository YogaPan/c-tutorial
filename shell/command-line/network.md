# Networking

## IP
```sh
ifconfig

# Check IP address
ifconfig | grep inet
```
## Check open port

```sh
netstat
sudo netstat -p
sudo netstat -lptu | grep :http
sudo netstat -lptun | grep :80

sudo netstat -lntp
sudo netstat -luntp

sudo netstat -an | grep EST    # Check who connected to you
sudo lsof -i :80
```

# iptables
```sh
sudo iptables -I INPUT -p tcp --dport 80 -j ACCEPT
sudo iptables -A INPUT -j REJECT

# Enable apt-get
iptables -F OUTPUT  # remove your existing OUTPUT rule which becomes redundant
iptables -A OUTPUT -m state --state RELATED,ESTABLISHED -j ACCEPT
iptables -A OUTPUT -p tcp --dport 80 -m state --state NEW -j ACCEPT
iptables -A OUTPUT -p tcp --dport 53 -m state --state NEW -j ACCEPT
iptables -A OUTPUT -p udp --dport 53 -m state --state NEW -j ACCEPT

iptables -A INPUT -m state --state RELATED,ESTABLISHED -j ACCEPT
```

## Ping
```sh
ping host
ping -c count host
ping -i seconds host
ping -n host   # Ping host without trying to lookup symbolic names for addresses.
```

## ssh and scp
```sh
ssh username@192.168.0.1   # And then enter your password

scp local_file username@192.168.0.1:/path/to/dir
scp -r local_dir username@192.168.0.1:/path/to/dir

scp username@192.168.0.1:/path/to/file /path/to/local
scp -r username@192.168.0.1:/path/to/dir /path/to/local

```

## Login without password
```sh
ssh-keygen -t rsa
scp ~/.ssh/*.pub remote:~/.ssh/
ssh remote
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
exit
eval `ssh-agent -s`
ssh-add
```
http://blog.faq-book.com/?p=1375

## Telnet
- quit
- CTRL + ]
```sh
telnet ip_address port
```

## netcat
```sh
# Is port open?
nc -v -w1 www.google.com 80

# Port Scanning
nc -vnz -w1 192.168.233.208 1-1000 2000-3000

# Simple server
while true; do sudo nc -l 80 < index.html; done

# Simple client
echo -ne "GET / HTTP/1.0\r\n\r\n" | nc www.google.com 80

# Copy file
nc -l 5000 > my.jpg          # Server
nc hostB.com 5000 < my.jpg   # Client

# Copy directory
nc -l 5000 | tar xvf -                      # Server
tar cvf - /path/to/dir | nc hostB.com 5000  # Client
```
http://blogger.gtwang.org/2014/02/linux-utility-netcat-examples.html

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
http www.examle.com
http -d www.example.com
```
