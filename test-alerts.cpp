#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}


TEST_CASE("sendToController) 
{
  BreachType breachType = TOO_LOW;
  const unsigned short expectedHeader = 0xfeed;

  std::stringstream outputStream;
  std::streambuf* originalOutputBuffer = std::cout.rdbuf();
  std::cout.rdbuf(outputStream.rdbuf());

  sendToController(breachType);

  std::cout.rdbuf(originalOutputBuffer);

  std::string output = outputStream.str();
  std::stringstream expectedOutput;
  expectedOutput << std::hex << expectedHeader << " : " << std::hex << breachType << "\n";

  REQUIRE(output == expectedOutput.str());
}

TEST_CASE("sendToEmail") 
{
  BreachType breachType = TOO_LOW;
  const char* expectedRecipient = "a.b@c.com";
  const char* expectedMessage = "Hi, the temperature is too low\n";

  std::stringstream outputStream;
  std::streambuf* originalOutputBuffer = std::cout.rdbuf();
  std::cout.rdbuf(outputStream.rdbuf());

  sendToEmail(breachType);
  std::cout.rdbuf(originalOutputBuffer);

  std::string output = outputStream.str();

  REQUIRE(output.find(expectedRecipient) != std::string::npos);
  REQUIRE(output.find(expectedMessage) != std::string::npos);
}


