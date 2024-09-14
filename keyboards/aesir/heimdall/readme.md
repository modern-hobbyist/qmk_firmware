# heimdall

![heimdall](imgur.com image replace me!)

Heimdall is the first keyboard in Project Aesir, my journey into creating custom keyboards to fill my needs. Heimdall aims to address my biggest gripes about working with a keyboard and a separate macro keypad, namely having to remove my hands from the keyboard to access the macros. 

I primarily work on a Mac, so the Valhalla keymap is arranged to have the Command key by the thumb rather than where the Windows key is (I've effectively switched Alt and GUI). Furthermore, I wanted to maximize the number of dedicated macro keys, so I skipped the up/down arrows and integrated them into the numpad, a decision I may come to regret. But hey! That's what it's all about!

* Keyboard Maintainer: [Charlie Steenhagen](https://github.com/modern-hobbyist)
* Hardware Supported: This keyboard runs on an STM32F072CBT6 and supports Cherry MX keys and WS2812b LEDS.
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make aesir/heimdall:default

Flashing example for this keyboard:

    make aesir/heimdall:default:flash
    
Make example for building this keyboard in the Valhalla (Mac) configuration:

    make aesir/heimdall:valhalla

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
