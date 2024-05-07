# interpolator

Add environment interpolation to any YAML, JSON or TOML config file in any
Linux, Mac, Windows, FreeBSD, OpenBSD, NetBSD, BIOS based system leveraging
Cosmopolitan.

## Usage

`interpolator` is designed to replace all matched values with those
defined in the environment. If a match in the environment is not found, no
substitution will occur.

The interpolation tag for `interpolator` is `${SOME_ENV_VAR}`.

You can use `interpolator` to interpolate using stdin:

```sh
cat config.yaml | ./interpolate > interpolated_config.yaml
```

or you can use it to interpolate files:

```sh
./interpolate config.yaml interpolated_config.yaml
```

use inline environment variables:

```sh
SOME_ENV_VAR=foo cat config.yaml | ./interpolate > interpolated_config.yaml
```

## Motivation

A simple cross platform way to wholesale interpolate environment variables
in config files for software that doesn't support it natively.
