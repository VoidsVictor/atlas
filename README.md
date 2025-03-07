# Autonomous Network

## Setting Up

1. Install OpenSSL

```shell
    sudo apt update
    sudo apt install openssl libssl-dev
```

2. Setup GTest

```shell
    sudo apt update
    sudo apt install libgtest-dev cmake
    cd /usr/src/gtest
    sudo cmake .
    sudo make
    sudo cp lib/*.a /usr/lib
```

## Structure of the Data Section

- Data section is basically an ordered map
- The key and value both are string
- The value can be a JSON object but it must serialised to string
- This can be done with the `serialise` function in `utils.cpp`

## TODO

### v0.0.1 (Pre-Alpha)

- [ ] Implement Block
    - [ ] Change data part to ordered map or json
    - [ ] Make the merkle root implementation
    - [x] Fix the deprecated openssl component
- [ ] Develop the Blockchain
- [ ] Make the Peer Discovery System (PDS)
- [ ] Make the service
- [ ] Make the human interface
- [x] Develop a basic Makefile
- [x] Implement a test system
