# Analog-Weather-Station
A weather station which mimics an analog style and uses a Particle Photon microcontroller to get weather data from OpenWeatherMap.org.
The station utilizes stepper motors to control dials which display weather information. The steppers are set up such that they share common coil connections, and are each individually switched on using a transistor array.

In order to properly use this code, the Particle.publish() and Particle.subscribe() functions in "ParticleFunctions.h" should be updated to fit the webhook you have created for your project.
