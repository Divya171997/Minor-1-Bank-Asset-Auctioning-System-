# Bank Asset Auction System

A console application that brings banks and prospective bidders together for auctions of bank-held property. Banks list properties, registered customers place bids, and the highest bidder is declared the winner.

B.Tech. Computer Science and Engineering (IBM specialisation in Banking, Financial Services and Insurance), University of Petroleum and Energy Studies, Dehradun. Minor Project I, October 2017, by Divya Arora and Shailendra, supervised by Dr Hitesh Kumar Sharma.

## Features

- **Manager window:** login, then insert, display, search, update and delete property records (property number, name, quantity, price range).
- **Customer window:** registration and login, with three attempts before lock-out.
- **Bidding window:** customers enter a name and bid; the program tracks the current highest bid and announces the winner.
- **Bank module:** create accounts, view accounts, deposit and withdraw.
- Terms and conditions displayed from `termscon.c`, a text file read at runtime.
- Records are stored in flat files written with `fwrite`/`fread`. The text UI is drawn with Windows console cursor positioning.

## Repository contents

| Path | Description |
|---|---|
| `MINOR 1.rar` | Original project archive: sources, executable, report, slides, ER diagrams |
| `source/copy.c` | Main program (about 1,200 lines of C), extracted unchanged from the archive |
| `source/termscon.c` | Auction terms and conditions shown by the program, extracted unchanged |
| `docs/er-diagram.png`, `docs/er-diagram-draft.png` | Entity-relationship diagrams, extracted from the archive |
| `README.md` | Original title-only README |

The archive also contains `report.docx` (project report), `minor project.pptx` (slides), `copy.exe` and an earlier module, `bidding.c`. `bidding.c` cannot be recovered: its compressed data in the uploaded archive is truncated, and both `unar` and 7-Zip fail on that one entry. Everything else extracts cleanly.

## Building

The program uses `<windows.h>` and `conio`-style input, so it targets Windows:

```bash
# on Windows with MinGW
gcc -o auction.exe source/copy.c
# or cross-compile from Linux
x86_64-w64-mingw32-gcc -o auction.exe source/copy.c
```

Run it from the `source/` folder so it can find `termscon.c` and create its data files there.

## Known issues

`source/copy.c` still compiles with MinGW-w64 (checked November 2026). Compiling with `-Wall` reports these defects, left unchanged so the extracted source matches the archive:

- In the deposit and withdraw functions (lines 156–158 and 201–203), `fscanf` receives integer values instead of their addresses, and reads text-formatted lines from a file that `create()` writes in binary. Deposits and withdrawals therefore do not update balances reliably.
- `scanf("%s", &array)` passes a pointer-to-array where `char *` is expected. This is harmless in practice but technically undefined behaviour.
- `getch`, `avlno` and `avln` are called without prior declarations.
