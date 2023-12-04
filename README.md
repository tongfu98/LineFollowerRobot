# Line Follower Robot That Perform Olympic-themed Sensing and Calculation


This year’s Integrated Design Challenge requires five autonomous bots to act as judges for the BOE-lympics. Each individual bot first has to follow a black ring around their object to be sensed. The bots then must use sensors to take measurements such as the color, size, slope, distance, and magnetic strength of an object. Based on the measurements taken, each bot will then transmit a 0, 1, or 2 to the other bot based on what object it senses. The bots will add together the values it receives, in addition to its own value, and take the modulus of 3 of that number. When the remainder is a 2, the bots have to perform a song using a piezoelectric speaker. When the remainder is 1, the bots will perform a light show using LEDs or an LCD display. When the remainder is 0, the bots will perform a dance using servo motors.

Our group’s bot is the weightlifting bot. The three objects the bot could have to sense are a Bronze medal weight, which is white and has no magnet, the Silver medal weight, which is gray and has a small magnet, or the Gold medal weight, which is black and has a large magnet. The bot first must 

1) use QTI sensors to provide information to the Arduino, which will communicate to the servo motors and follow the ring around the course. Once the bot completes a circle, it must
2) orient itself and move close to the weights, so that the Hall-effect sensor, a sensor that measures the strength of a magnetic field, can work effectively. Once the bot makes its measurement, it must
3) save this data for the calculation later, and then use an XBee module to communicate with the other bots.
4) It will send the value it senses, and listen for the values that other groups send. Once it receives a message from each group, the bot will calculate the remainder of the sum of the numbers it receives, and then perform its song, light show, or dance.

Our Bot only had one mistake, a miscalculation of the final remainder.
