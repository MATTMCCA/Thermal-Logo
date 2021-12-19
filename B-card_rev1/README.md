


# Thermal Logo Business Card
A business card that "prints" the company logo on thermal paper.


# Possible Issues with the Design
- The `TPS61097A-33` can handle voltages from 0.9 - 5.5, that's fine, but as the voltage on the input sags, the effective output current also sags. Will < 200mA be enough to power the MCU? (I suspect not)
- The super cap used to hold vin high will deplete too quickly based on the projected current consumption of the design. However, since the heaters wont have a contentious draw on the battery, this might actually work.... I hope
- The 'supply' battery I have in mind can do a contentious 1A, I'm really going to be pushing the limits of the battery. The heaters are an effective short, were talking .9 ohms - 1.9 ohms. @ 3.3v, that's almost 2A. I only performed test at 5v current limited at 2A, 'this' supply may be too weak to handle the load.
- I have a feeling parts of this design will fail due to spec.
- Giving out business cards that heat up and run the risk of failure could be bad.... seconds thoughts about the project...
