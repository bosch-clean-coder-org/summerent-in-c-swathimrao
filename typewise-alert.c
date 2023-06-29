#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;

  int limit[3] = {35, 45, 40};
  upperLimit = limit[coolingType];
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void sendAlert(AlertTarget alertTarget, BreachType breachType)//dont foget to declare
{
  if (alertTarget == TO_CONTROLLER)
    sendToController(breachType);
    
  if (alertTarget == TO_EMAIL)
    sendToEmail(breachType);
  
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );
 sendAlert(alertTarget, breachType);

}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}


void sendToEmail(BreachType breachType) {
  const char* recipient = "a.b@c.com";
  printf("To: %s\n", recipient);

  if (breachType == TOO_LOW)
    printf("Hi, the temperature is too low\n");
  else if (breachType == TOO_HIGH)
    printf("Hi, the temperature is too high\n");
}

