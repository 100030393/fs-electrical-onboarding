Sensor example: https://www.digikey.com/en/products/detail/bosch-sensortec/BMP180/2688259
> Specifications (from DigiKey and datasheet from Bosch)
> - BMP180
> - Pressure range: 300 - 1100hPa (+9000m - -500m)
> - Supply voltage: 1.8V - 3.6V (VDD), 1.62V - 3.6V (VDDIO)
> - Dimensions: 3.6mm x 3.8mm x 0.93mm
> - Two wire I2C interface
> - Board mount
> - Absolute pressure type
> - Accuracy: +-2%
> - Termination style: SMD (SMT) tab

> Pros
> - MEMS (micro-electro mechanical system), used to measure pressure
> - Commonly used with Arduinos, so there is a lot of support software-wise
> - I2C compatibility
> Cons
> - Out of production, difficult to source
> - "Decent" (mediocre?) resolution
> - Difficult to interface multiple units with a single microcontroller due to a lack of address pins for I2C

> Goals
> - Resolution equal to or better than the original
> - Communication or output interface that allows it to be banked with more pressure sensors
> - Adequete software support
> - Still in stock and manufactured
> - Absolute pressure type, board mount to mirror previous application capacity and ability to be connected in an array

Candidates
Following filters:
- Pressure type: Absolute
- Accuracy: >=2%
- Applications: Board mount
- Product status: Active

MS561101BA03-50
- Initially promising because of its significantly better pressure range, compact size, and accuracy of the sensor
- It also utilized SMD tab termination and the same voltage supply range, allowing its integration to be similar to its predecessor 
- While it does have I2C support, it does not have the capacity to change addresses due to a lack of the relevant pins (according to its datasheet, it can only be used with other sensors on the same bus if they have different addresses, which would not be the case for duplicate sensors)
- It does have SPI communication, although despite its higher pin count, does not natively support address-based communication and would require more GPIO from the microcontroller to support each additional sensor

BMP390
- A successor to the BMP180, it shares the same implementation style and a moderately improved
- While it is still actively produced, it was out of stock as of 10/12. May or may not be an issue
- It has both I2C and SPI communication, the former of which has a total of... two possible addresses, depending on the SDO connection, making it not ideal for an array of pressure sensors

Following these failures, I went back to research I2C and found some interesting information. While I2C does have support for custom addresses in the form of address setting pins (A0-2 typically), most pressure sensors are in fact too small to have this be an option. Instead, they have what I observed with the BMP390, which is having the ability to change a single bit in the address, allowing for two of the same sensor in the same I2C bus. From this approach, comes a few intruiging options:

- Have multiple buses, each one with two sensors. The upside is flexibility with sensor choices, although the rather severe downside of requiring one pin for each sensor (although it is two sensors per bus, as far as I understand you would still need two pins per bus, resulting in 1:1 pin to sensor ratio for the microcontroller). This is also likely a hassle on the software side
- Use multiple different sensor with their own addresses all on the I2C bus. While technically possible, processing the data from each one would be nightmareish as they would have their own respective ranges and accuracies, introducing too much variability to the end result of the information
- I2C multiplixers are something that came up during this research, which suggested the possibility of having a secondary board connected to the microcontroller that would allow for multiple I2C sensors to be connected in the same bus, they would just need to be wired to the multiplixer, and the multiplexer would then be wired to the original microcontroller. The benefit is a significantly larger array of the same sensor on the same bus, but with the downside that there is now an additional board that needs to be accounted for in the layout of wherever the microcontroller is located. The most popular example is the TCA9548A (https://www.digikey.com/en/products/detail/adafruit-industries-llc/2717/5604376), which has 8 interfacing channels. These channels would then allow for 8 sensors with the same address to be connected to one microcontroller. With two-addresssolutions like the aforementioned BMP390, this opens up the possibility for 16 individual pressure sensors on the same I2C bus, which can be further expanded by either having multiple I2C buses or wiring multiplexers in series
