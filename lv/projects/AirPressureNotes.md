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
> - I2C pins
> - Adequete software support
> - Still in stock and manufactured
> - Absolute pressure type, board mount to mirror previous application capacity and ability to be connected in an array

