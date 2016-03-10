# Analog-Weather-Station
Patrick Dobbie, Mar. 9, 2016

A weather station which mimics an analog style and uses a Particle Photon microcontroller to get weather data from OpenWeatherMap.org.
The station utilizes stepper motors to control dials which display weather information. The steppers are set up such that they share common coil connections, and are each individually switched on using a transistor array.

In order to properly use this code, the Particle.publish() and Particle.subscribe() functions in "ParticleFunctions.h" should be updated to fit the webhook you have created for your project.

This project makes use of the "PowerShield.h" and "PowerShield.cpp" files, based on the original library published by Luca Dentella (http://www.lucadentella.it), and modified by Mohit Bhoite @ Particle Industries, Inc. July 2015.

OpenWeatherMap API: http://openweathermap.org/api

Particle Photon Documentation: https://docs.particle.io/guide/getting-started/intro/photon/

Power Shield Documentation: http://docs.particle.io/photon/shields/#power-shield

MAX17043 datasheet: http://datasheets.maximintegrated.com/en/ds/MAX17043-MAX17044.pdf
