# interpolator

Add environment interpolation to any YAML, JSON or TOML config file in any
Linux, Mac, Windows, FreeBSD, OpenBSD, NetBSD, BIOS based system leveraging
Cosmopolitan.

## Usage

You can use `interpolator` to interpolate using stdin:

```sh
cat config.yaml | ./interpolate > interpolated_config.yaml
```

or you can use it to interpolate files:

```sh
./interpolate config.yaml interpolated_config.yaml
```

## Motivation

A simple cross platform way to wholesale interpolate environment variables
in config files for software that doesn't support it natively.
