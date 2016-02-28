# Git

## Install and check version
```sh
$ sudo add-apt-repository ppa:git-core/ppa -y
$ sudo apt-get update
$ sudo apt-get install git
$ git --version
```

## Basic config
```sh
git config --global user.name "yourname"
git config --global user.email "username@gmail.com"
git config --global list | grep -e user.name -e user.email
```

```sh
git init
git clone url

git add -A
git commit -v

git push origin master
git pull origin master
git fetch origin master
git merge origin/master

git branch
git branch -a
git branch -r
git branch new-branch

git checkout new-branch
git checkout -b new-branch

git status
git log

git format-patch
git am

git remote -v
git remote add
```
