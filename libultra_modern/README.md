# libultra_modern

This repo contains a decompilation of libultra version 2.0L. It is intended to facilitate updating of libultra and allow the Modern SDK to be a complete open book for people to edit as they see fit.

## Build dependencies

The Modern SDK is required. Install it [here](https://crashoveride95.github.io/n64hbrew/modernsdk/index.html)

The build process additionally requires the following packages:

- build-essential
- python3

Under Debian / Ubuntu you can install them with the following commands:

```bash
sudo apt update
sudo apt install build-essential python3
```

## Building

- `make`

- `make all` if wanting to build all versions (libultra, libultra_d, libultra_rom) at once
