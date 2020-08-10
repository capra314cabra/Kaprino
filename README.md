<div align="center">
  <h1>Kaprino <i>- A language of mathematical thinking</i></h1>
</div>

[![Latest release](https://img.shields.io/github/v/release/kaprino-lang/kaprino?include_prereleases)](https://github.com/kaprino-lang/kaprino/releases)
[![CI](https://github.com/kaprino-lang/kaprino/workflows/CI/badge.svg)](https://github.com/kaprino-lang/kaprino/actions?query=workflow%3ACI)

This is a strongly-typed programming language that tastes like a mathematics.

## Code snippets 📝

![Code example](https://raw.githubusercontent.com/kaprino-lang/kaprino/master/img/code_example1.png)

## How to run 💻

Write a code and save it with the extension, `.kpr`.  
Now, you can compile it by executing the following command:  
("kprc" is the shorteness of "kaprino compiler".)

```
$ kprc some-source.kpr
```

kprc will generate an executable.

If you are tired to set your environment, you can use [Kaprino Online Compiler](https://kaprino.herokuapp.com/).

## Installation 💿

### Download from release page 💾

Download achievements from [Release Page](https://github.com/kaprino-lang/kaprino/releases) and add the directory path put it into to PATH.  
Here is the table of available environments.

|OS|Available|
|---|:---:|
|Linux x64| ✔️ |
|Windows x64| ✔️ |
|MacOS x64| ✔️ |

### Build from sources 🔨

Please read [How to build](https://github.com/kaprino-lang/kaprino/blob/master/HowToBuild.md).

### Run kaprino using Docker 🐳

You can use a docker image which is already installed kaprino.

```
docker run --rm -it kaprino/kaprino:latest
```

## Requirements

- Clang (>=9.0.1)

## License

[MIT license](https://github.com/kaprino-lang/kaprino/blob/master/LICENSE)
