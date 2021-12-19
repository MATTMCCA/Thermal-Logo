



# Thermal Logo Business Card
A business card that "prints" the company logo on thermal paper.


# Possible Issues with the Design
- The `TPS61097A-33` can handle voltages from 0.9 - 5.5, that's fine, but as the voltage on the input sags, the effective output current also sags. Will < 200mA be enough to power the MCU? (I suspect not)
- The super cap used to hold vin high will deplete too quickly based on the projected current consumption of the design. However, since the heaters wont have a contentious draw on the battery, this might actually work.... I hope
- The 'supply' battery I have in mind can do a contentious 1A, I'm really going to be pushing the limits of the battery. The heaters are an effective short, were talking .9 ohms - 1.9 ohms. @ 3.3v, that's almost 2A. I only performed tests at 5v current limited at 2A, 'this' supply may be too weak to handle the load.
- I have a feeling parts of this design will fail due to spec.
- Giving out business cards that heat up and run the risk of failure could be bad.... seconds thoughts about the project...

# Low Voltage Test

Turns out running at 3.3 with the current choked @ 2 Amps dose heat up the nickle chromium wire to the point of activation, it just takes longer due to the lower effective wattage ~100ms. A possible solution may be to preheat the wire, thus reducing the time needed to reach the activation temperature.

Something to note, during the life of the battery, as the battery becomes depleted, the time needed to activate the paper will become greater. I may be-able to measure vbat during runtime and compensate for delta time.

A safety mechanism may be needed, the paper will act as a heat sink. If the elements are active without paper contact they may prematurely fail.

And a power switch may come in handy, but the likelihood of a client actually building the device is un-probable, this is more of a show piece.
