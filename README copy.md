# WuName99

WuName99 is a lightweight C++ command-line tool that generates
Wu-Tang–inspired usernames in the format:

```bash
AdjectiveNoun##
```

Example output:

```
MightyScholar47
IronMonk82
SilentShadow15
```

---

## Features

- Generates usernames in the format `AdjectiveNoun##`
- Simple CLI options:
  - `--N` to generate multiple names
  - `--copy` to copy the result to clipboard
  - `--help` to display usage
- No dependencies at runtime
- Portable (macOS, Linux, Windows)

---

## Build from Source

```bash
git clone https://github.com/<yourusername>/WuName99.git
cd WuName99
g++ -std=c++17 -O2 wuname99.cpp -o wuname99
```

Optionally install globally:

```bash
sudo mv wuname99 /usr/local/bin/
```

Then run it:

```bash
wuname99
```

---

## Usage

### Generate one random name

```bash
wuname99
```

### Generate multiple names

```bash
wuname99 --5
```

### Copy last generated name to clipboard

```bash
wuname99 --copy
```

Clipboard utilities used:

- macOS → `pbcopy`
- Linux → `xclip` or `xsel` (must be installed)
- Windows → `clip`

### Help

```bash
wuname99 --help
```

---

## Example

```bash
$ wuname99 --3 --copy
IronTiger17
CrimsonRogue88
ShadowScribe35 (copied to clipboard)
```

---

## Word Lists

The adjectives and nouns are stored in `words.h`.  
Modify these lists to customize the name style — for example:

```cpp
std::vector<std::string> adjectives = {"Mighty", "Silent", "Iron", "Clever"};
std::vector<std::string> nouns = {"Monk", "Shadow", "Scholar", "Blade"};
```

---

## License

MIT License — feel free to modify and distribute.
