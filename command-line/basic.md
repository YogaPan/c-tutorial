# Basic command line

## ls
```sh
$ ls

# List files one per line
$ ls -1

# List all files, including hidden files
$ ls -a

# Long format list (permissions, ownership, size and modification date) of all
# file.
$ ls -la
```

## pwd
```sh
# Print the current directory
$ pwd
```

## cd
```sh
# Go to the given directory
$ cd /path/to/directory

# Go to home directory of current user
$ cd

# Go up to the parent of the current directory
$ cd ..

# Go to the previously chosen directory
$ cd -
```

## mkdir

```sh
# Create a directory in current folder or given path
$ mkdir path

# Create directories recursively (useful for creating nested dirs)
$ mkdir -p path

```

## touch
```sh
# Create a new empty file(s)
$ touch filename
```

## rm
```sh
# Remove files from arbitrary locations
$ rm /path/to/file

# Remove recursively a directory and all it's subdirectories
$ rm -r /path/to/folder

# Remove directory without prompt
$ rm -rf /path/to/folder

# Prompt before every removal
$ rm -i
```

## user

```sh
$ chmod u+x file
$ chmod a+rw file
$ chmod o=g file
$ chmod 755 file


$ chown user path/to/file
$ chown user:group path/to/file
$ chown -R user path/to/dir

$ chgrp yogapan file
```

# Date

```sh
# CST Sun 2016-02-28 21:45:23
$ date +"%Z %a %Y-%m-%d %H:%M:%S"

# Display a calendar for the current month
$ cal
$ cal -3
$ cal -y

# Display a calendar for a specific month
$ cal -m month_number

# Display a 12 month calendar for a specific year
$ cal 2016

```
