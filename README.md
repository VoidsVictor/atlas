# Autonomous Network

## Setting Up

1. Install OpenSSL

```shell
    sudo apt update
    sudo apt install openssl libssl-dev
```

2. Configure GTest

```shell
    sudo apt update
    sudo apt install libgtest-dev cmake
    cd /usr/src/gtest
    sudo cmake .
    sudo make
    sudo cp lib/*.a /usr/lib
```

3. Install `emscripten` by following the official [guide](https://emscripten.org/docs/getting_started/downloads.html)

## Structure of the Data Section

- Data section is basically a string
- The value can be a JSON object but it must serialised to string

## TODOs

### v0.0.1 (Pre-Alpha 0)

- [ ] Make the Smart Contract System (SCS)
    - [ ] Implement a generalised DHT with Kademlia
- [ ] Make the Peer Discovery System (PDS)
- [ ] Make the service
- [ ] Make the human interface
- [x] Develop the Blockchain
- [x] Implement Block
    - [x] Change data part to json or dynamic string
    - [x] Make the merkle root implementation
    - [x] Fix the deprecated openssl component
- [x] Develop a basic Makefile
- [x] Implement a test system

### v0.0.2 (Pre-Alpha 1)

- [ ] Fix inconsistencies and security issues
- [ ] Refactor the code
- [ ] Implement concurency and parallel processing
- [ ] Make the data section robust by making it a class
    - [ ] Have the ability to store transactional data