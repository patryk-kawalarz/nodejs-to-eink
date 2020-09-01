# NodeJS to E-Ink
Convert any NodeJS generated canvas to stream data which can be easily handled by Arduino based hardware (like ESP8266) and display it on the E-Ink display.

## About

I spent a lot of time figuring out how to convert a canvas object to a monochrome picture which can be ease transferred to my ESP8266. Converting canvas to bitmaps was too complicated for me. So finally I decided to prepare a chain of `0` and `1` as information about which pixel should be black. ESP8266 must know the dimensions of the upcoming image but for me, it's not a problem.I know that using strings as raw data is lost of bytes but it was the only way to handle it based on my knowledge. 

## Installation & usage

Download source code and run Node app server:

```bash
npm run live
```

Upload `display.ino` to your arduino hardware. 

Make sure that you have correct IP address of your Node app server. I tested it on localhost so I used my local IP address: `167.0.0.42`.

### My hardware
Tested on [Waveshare 5.83" E-Ink display](https://www.waveshare.com/wiki/5.83inch_e-Paper_HAT) and [NodeMCU v2](https://www.seeedstudio.com/NodeMCU-v2-Lua-based-ESP8266-development-kit.html).
