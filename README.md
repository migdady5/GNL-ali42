# migdady5

# Get Next Line

A C project that implements `get_next_line`, a function that reads one line at a time from a file descriptor.

## What it covers

- Buffered reading with a configurable `BUFFER_SIZE`
- Preserving unread data between calls
- Handling files, standard input, EOF, and errors
- Supporting multiple file descriptors in the bonus version

## Build

Compile the source with your own program:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

This activity has been created as part of the 42 curriculum by amigdadi.