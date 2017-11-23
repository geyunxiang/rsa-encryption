#include <iostream>
#include <chrono>
#include <ctime>
#include <random>

#include "BigInt.hpp"
#include "myRSA.hpp"
#include "TestSuits.hpp"

int main(int argc, char const *argv[]) {
    test_RSAStringEncryptionDecryption();
    return 0;
}
