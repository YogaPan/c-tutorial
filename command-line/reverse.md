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

## Objdump
```sh
```
