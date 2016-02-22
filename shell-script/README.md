## Shell

### Basic condition
```sh
cmd1 && cmd2        cmd2 execute if cmd1 success.
cmd1 || cmd2        cmd2 execute if cmd1 fail.

if command is successful; then
  execute command
elif command is successful; then
  execute command
else
  execute command
fi

for variables in list; do
  command
done

while condition is true; do
  command
done

case expression in
esac
```
