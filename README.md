# xmgt

Extract magnet links from a website page. Used for aria2c, for example. `Linux only`.


## Compile & Install

```
  $ make && make install
```

## Usage

```
  $ xmgt https://openpirate.org/top/48h207 | xargs aria2c -j 999
```

## Required Library

- libcurl

Enjoy!
