## Session 1 - 31/10/18
- Decided to create a ~20 x ~30 grid of LEDs, with each LED having a width/height of ~3.33 cm. After cost and size considerations, resized to 16 x 32 LEDs, at 30 LEDs / m.
- Decided to prioritize programming Tetris over pong and images/gifs. Method of playing Tetris (app/website/physical controller) still undecided.
- Decided to have few or no meetings in December based on limited availability of 3-4 people a week.
- Decided to organize optional teaching sessions related to this project next semester due to strong interest. Topics include:
    - Basic computer graphics and colour theory
    - Web programming on the ESP8266
    - WS2812B LED strip in-depth


## Session 2 - 17/01/19
- Breadboarded circuit for connecting WeMos D1 Mini (also referred to as ESP8266, Arduino) to LED strip for testing. Circuit did not work and we could not debug why.
- Discussed enclosure structure for project.
    - Mounting in the lobby, on the pillar on the other side of the sofas from the TV. Measurements of wall are 57 cm wide and >3 m high
    - Enclosure width between 53.5 cm (width of 16 LEDs) and 57 cm
    - Height approx 110 cm (approx twice length of 32 LEDs)
- Acrylic for 3.3 cm square found to diffuse well at distance of 2 cm from LED at half brightness.


## Session 3 - 22/01/19
- Plywood bought over the weekend with measurements
    - 56 cm x 115 cm (1)
    - 2.3 cm x 115 cm (4)
    - 2.3 cm x 56 cm (6)
    - 7 cm x 56 cm (2)
- Breadboard circuit works after remove 470 ohm resistor on data line. Reasons unknown.
- Tested all LED strips, found 1 defective LED. Cut strips into rows of 32.
- Measured out columns 3.3 cm on plywood.
- Pasted LED strips on to board in snake configuration.
