# Reverse

## File
Determine file type
```sh
file filename
```

## Strings
Find printable strings in an object file or binary
```sh
# Print all strings in a binary
strings file

# Limit results to strings at least  characters long:
strings -n length file

# Prefix each result with its offset within the file:
strings -t d file

# Prefix each result with its offset within the file in hexadecimal:
strings -t x file
```

## Strace
```sh
strace command

# Start tracing a specific process by its PID:
strace -p pid

# Trace a process and filter output by system call:
strace -p pid -e system-call-name

# Count time, calls, and errors for each system call and report a
summary on program exit:
strace -p pid -c

# Show the time spent in every system call:
strace -p pid -T
```

## Objdump
```sh
```

## nm
```sh
```
