// Bounce.pde
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2012 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>
#include <Encoder.h>
#define ENCODER_STEPS 500
#define STEPPER_STEPS 200
// Define an encoder and the pins it will use
Encoder encoder(2,3);
// define a function that returns the real position
long realPos() 
{
  // get real position from encoder
  long enc = encoder.read()%ENCODER_STEPS;
  long pos = enc*STEPPER_STEPS/ENCODER_STEPS;
  
  return pos;
}
// Define a stepper and the pins it will use
AccelStepper stepper(realPos, AccelStepper::DRIVER,4,5); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5


void setup()
{  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(40);
  stepper.setAcceleration(20);
  stepper.moveTo(500);
}

void loop()
{
    // If at the end of travel go to the other end
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());
    stepper.run();
}