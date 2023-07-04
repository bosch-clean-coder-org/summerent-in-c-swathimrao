#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>
#include <sstream>
#include "test/catch.hpp"
#include "typewise-alert.h"
#include <algorithm>
#include <cctype>

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}


TEST_CASE("sendToController") 
{
    BreachType breachType = TOO_LOW;
    std::stringstream outputStream;
    std::streambuf *originalOutputBuffer = std::cout.rdbuf();
    std::cout.rdbuf(outputStream.rdbuf());
    sendToController(breachType);
    std::cout.rdbuf(originalOutputBuffer);
    std::string output = outputStream.str();
    std::string expectedOutput = "feed : 1\n";
    REQUIRE(toLowercase(output) == toLowercase(expectedOutput));

    // breachType = TOO_HIGH;
    // expectedOutput = "feed : 2\n";
    // sendToController(breachType);
    // std::cout.rdbuf(originalOutputBuffer);
    // output = outputStream.str();
    // REQUIRE(output == expectedOutput);
    
}

TEST_CASE("sendToEmail") 
{
  BreachType breachType = TOO_LOW;
  std::string expectedOutput = "To: a.b@c.com\nHi, the temperature is too low\n";
  std::stringstream outputStream;
  std::streambuf* originalOutputBuffer = std::cout.rdbuf();
  std::cout.rdbuf(outputStream.rdbuf());
  sendToEmail(breachType);
  std::cout.rdbuf(originalOutputBuffer);
  std::string output = outputStream.str();
  REQUIRE(toLowercase(output) == toLowercase(expectedOutput));
  

  // breachType = TOO_LOW;
  // expectedOutput = "To: a.b@c.com\nHi, the temperature is too high\n";
  // sendToEmail(breachType);
  // std::cout.rdbuf(originalOutputBuffer);
  // output = outputStream.str();
  // REQUIRE(output == expectedOutput);
  
}


