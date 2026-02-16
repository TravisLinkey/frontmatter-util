# frontmatter-util

Updates YAML frontmatter in Markdown files. Supports the keys **Subject**, **Tag**, **Type**, and **Filter**.

## Compiling

From the project root:

```bash
make
```

Builds `main.o` with `clang++` (C++17). On macOS, use `make` or `clang++`; `g++` may not find the system C++ headers.

Clean rebuild:

```bash
make clean && make
```

## Running

```text
./main.o Key=Value [Key=Value ...] [file_path]
```

| Argument   | Description |
|-----------|-------------|
| **Key=Value** | One or more frontmatter key/value pairs (e.g. `Subject="Software Engineering"`, `Tag=reviewed`, `Filter=concept`). Key must be `Subject`, `Tag`, `Type`, or `Filter`. Quote the value if it contains spaces. |
| **file_path** | File or directory to process. Optional; default is the current directory (`.`). Must not contain `=`; the first argument without `=` is treated as the path. |

Examples:

```bash
# Single key, current directory
./main.o Subject="Software Engineering"
./main.o Tag=reviewed

# Multiple keys (both applied to each file)
./main.o Subject="Software Engineering" Filter=concept
./main.o Type=concept Tag=reviewed

# With path
./main.o Subject="Software Engineering" ./notes
./main.o Subject="OS" Filter=concept ./notes
```

With the `fu` alias:

```bash
fu Subject="Software Engineering"
fu Subject="Software Engineering" Filter=concept ./notes
```
