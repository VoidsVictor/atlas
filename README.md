# Atlas  

> This project is in its early stages of development and highly experimental. Expect frequent architectural changes and updates.  

## Present Overview  

Atlas, in its current form, is a **partially autonomous multi-chain network** designed for high developer accessibility while ensuring security through contract containerization. The core idea is to **investigate and develop an autonomous network that is self-governing, self-optimizing, self-healing, self-securing, and ultimately self-sustaining.** The architecture will evolve accordingly.  

At present, Atlas leverages **WASMedge** for smart contract execution and aims to provide a seamless, developer-friendly environment for deploying and managing decentralized applications.  

## Features: Implemented & Planned  

**Note: The features listed here correspond to Pre-Alpha 0.**  

### Implemented  

1. **Core Blockchain:** Foundation established with Merkle root integration.  
2. **Smart Contract Execution:** WASMedge successfully integrated for contract execution.  
3. **Basic Makefile & Test System:** Initial build automation and testing framework in place.  

### Planned  

1. **Colossus (Decentralized Contract Execution):** Designing a decentralized execution framework for contracts.  
2. **Emissary (Cross-Chain Communication):** Enabling interoperability across multiple blockchains.  
3. **Smart Contract System (SCS):** Implementing a generalized Distributed Hash Table (DHT) with Kademlia.  

## Potential Use Cases
- **Decentralized Finance (DeFi):** Secure smart contract execution with multi-chain support.
- **Autonomous Systems:** Self-optimizing, self-healing networks.
- **Cross-Chain Applications:** Interoperability between different blockchain ecosystems.


## Setting Up  

1. Install OpenSSL:  

   ```shell
   sudo apt update
   sudo apt install openssl libssl-dev
   ```  

2. Configure GTest:  

   ```shell
   sudo apt update
   sudo apt install libgtest-dev cmake
   cd /usr/src/gtest
   sudo cmake .
   sudo make
   sudo cp lib/*.a /usr/lib
   ```  

3. Install `emscripten` by following the official [guide](https://emscripten.org/docs/getting_started/downloads.html).  

4. Install WASMedge.  

## Smart Contract Compilation  

Compile C++ smart contracts to WebAssembly using **Emscripten**:  

```sh
emcc contract.cpp -o contract.wasm -sSTANDALONE_WASM -Wl,--no-entry
```  

## Structure of the Data Section  

- The **data section** is essentially a string.  
- The value can be a JSON object but must be serialized to a string.  

## TODOs  

### v0.0.1 (Pre-Alpha 0)  

- [ ] **Develop the Smart Contract System (SCS)**  
  - [ ] Implement a generalized DHT with Kademlia  
  - [ ] Design the Context API  
- [ ] **Implement Emissary** – Cross-chain communication  
- [ ] **Implement Colossus** – Decentralized contract execution  
  - [ ] Evaluate node performance  
  - [ ] Advertise node performance  
  - [ ] Receive smart contracts  
  - [ ] Return contract output to the system  
  - [x] Execute smart contracts with WASMedge Runtime  
- [ ] **Develop the Peer Discovery System (PDS)**  
- [ ] **Develop the network service**  
- [ ] **Develop the human interface**  
- [x] **Develop the Blockchain**  
- [x] **Implement Block**  
  - [x] Change data part to JSON or dynamic string  
  - [x] Implement Merkle root  
  - [x] Fix deprecated OpenSSL component  
- [x] **Develop a basic Makefile**  
- [x] **Implement a test system**  

### v0.0.2 (Pre-Alpha 1)  

- [ ] Fix inconsistencies and security issues  
- [ ] Refactor the code  
- [ ] Implement concurrency and parallel processing  
- [ ] Improve the data section by converting it into a class  
  - [ ] Enable transactional data storage  
