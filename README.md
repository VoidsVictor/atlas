# Autonomous Network

## Compile Command

```shell
    g++ -std=c++17 -Iinclude src/Block.cpp src/utils.cpp main.cpp
```

## Setting Up

1. Install OpenSSL

```shell
    sudo apt update
    sudo apt install openssl libssl-dev
```

## TODO

- [ ] Implement Block
    - [x] Fix the deprecated openssl component
    - [ ] Change data part to ordered map
    - [ ] Make the merkle root implementation
- [ ] Develop the Makefile