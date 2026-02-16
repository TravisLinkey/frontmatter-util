# frontmatter-util

Updates YAML frontmatter in Markdown files. Supports the keys **Subject**, **Tag**, and **Type**.

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
./main.o Key=Value [file_path]
```

| Argument   | Description |
|-----------|-------------|
| **Key=Value** | Frontmatter key and value (e.g. `Subject=Software Engineering`, `Tag=reviewed`). Key must be `Subject`, `Tag`, or `Type`. Quote the argument if the value contains spaces. |
| **file_path** | File or directory to process. Optional; default is the current directory (`.`). |

Examples:

```bash
# Current directory
./main.o "Subject=Software Engineering"
./main.o Tag=reviewed

# Specific path
./main.o "Subject=Software Engineering" ./notes
./main.o Type=concept /path/to/markdown
```

With the `fu` alias:

```bash
fu "Subject=Software Engineering"
fu Tag=reviewed ./notes
```
