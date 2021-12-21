
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

# Addendum

After going through half a roll of [cheap thermal stock](https://www.amazon.com/POS1-Thermal-Paper-diameter-CORELESS/dp/B0785M4982) I came to the conclusion that the 'current' design wont work. 

Solution: Use the `AP1509-50SG-13` to regulate an [rc battery](https://www.amazon.com/Blomiky-1500mAh-Battery-Charger-Helicopter/dp/B07DNCK7V2/) down to 5v@2A, this ic dose not state that there is over current protection, but rather **Current-Limit Protection** , so I think this might work. 

This allows me to nix the battery charger on the pcb, I'm still apprehensive about only supplying the mcu with 200ma, it *should* work, but the official numbers say otherwise. Actually, I could just nix the 3.3v regulator since I have an uber cap to keep the system up during brownout. Or use an LDO linear reg. uber down to 3.3v@300ma from 5v.... that might be ok.

# Addendum Part 2
Ok so... I guess the atmega32u4 can run down to 3v with a lethargic clock, so the need for the 3.3 vreg is void. Ill just run the 8Mhz clock at 5v ~4.8v. If the reservoir cap is charged at 5v, I can operate over a 1.7v sag. Plus! I found [this](https://www.digikey.com/en/products/detail/henlv-power/WRD05S05-10W/15780166) gem, Its through hole, but fits my power requirements. The datasheets in Chinese, so I don't know if it has over current protection, or if its limited. 

New game plan, nix the regulators, drop in a dc/dc power module. Now I don't have to worry about the vreg layout being perfect for maximum efficiency. I might be-able to socket the dc module so no leads stick out the bottom. If not, oh well.

### From [Datasheet](http://www.henlv.com.cn/kin/php/upload/20200924/1600919314377087.pdf) (wrong datasheet though)
`Have good shielding anti‑interference performance and electromagnetic compatibility, output overcurrent,
Overheating protection, Self‑recovery and other functions.`

...so I don't know if it will drop out or limit the current, I suspect it will drop out ("*self recovery*"), that's what most do (this could be problematic).
