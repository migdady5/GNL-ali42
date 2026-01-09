*This activity has been created as part of the 42 curriculum by amigdadi.*

# get_next_line

## Description
`get_next_line` is a C function that reads from a file descriptor (`fd`) and returns **one line per call**.
- The returned line includes `\n` if present (except the last line at EOF if it does not end with `\n`).
- Returns `NULL` when there is nothing left to read or an error occurs.
- Works with both files and standard input.

## Instructions
**Prototype:** `char *get_next_line(int fd);`

**Files:**
- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

**Allowed:** `read`, `malloc`, `free`  
**Forbidden:** `libft`, `lseek`, global variables

**Compile (example):**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
Note: Must compile with and without -D BUFFER_SIZE=n.

Algorithm (explanation & justification)

Since read() returns chunks (size BUFFER_SIZE) and not full lines, the function uses a static stash to keep leftover data between calls.

Read and append to stash until '\n' is found or EOF/error occurs.

Return the first line from stash (including '\n' if present; last line may not).

Keep what remains after that line in stash for the next call; if nothing remains, set stash to NULL.

This reads as little as possible, returns one line per call, and works for any BUFFER_SIZE (small or large).

Resources
- [get_next_line subject]
- [42 Network get_next_line page]|
- [Network discussion on get_next_line]