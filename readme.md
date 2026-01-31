
**Sign Of Affection — 3‑Color eInk Photo Frame**

![image1](/readmeAssets/banner.jpg)

- **Project:** A compact 3‑color eInk photo frame that cycles a different photo every 4 hours.
- **Made as:** One‑day challenge project.

**Overview**
- **What it is:** A low‑power photo frame using a 3‑color (black/white/red or black/white/yellow) 2.9" eInk display and an ESP32‑S3 DevKit C1. The frame shows a new image on a 4‑hour schedule and sleeps between updates to conserve battery.

Please note that this readme is generated since I did not feel like writing one :0.

**Features**
- **Power efficient:** Uses deep sleep between updates.
- **Battery powered:** Single 18650 Li‑ion cell with onboard charger.
- **Simple build:** 3D printed enclosure and a small parts list.

**Required Parts**
- **3D printed parts:** Frame, bezel, back cover (STL files included in `cad/3d print stl/`).
- **MCU:** ESP32‑S3 DevKit C1.
- **Display:** 2.9" 3‑color eInk display (black/white/third color).
- **Power:** Step‑down regulator to 3.3V (from battery/charger output).
- **Charger:** TP4056 Li‑ion charger module (commonly called 4056).
- **Battery:** 18650 Li‑ion cell.
- **Wires, connectors, and small hardware:** JST wires (optional), screws, double‑sided tape.

**Files & Where to Look**
- **Firmware:** See [code/src/main.cpp](code/src/main.cpp) and [code/platformio.ini](code/platformio.ini).
- **3D models:** See `cad/3d print stl/` for printable STL files.
- **Images for tutorial:** See `tools/images/` (image1 → image6) used below.

**Quick Build Tutorial (use images 1–6)**
- **Step 1 — Print & prepare parts:** Print the frame, bezel, and back cover. Remove supports and test fit the eInk display in the bezel.
- **Step 2 — Mount the display:** Seat the 2.9" eInk display into the bezel, secure with the small screws or tape supplied with your display. Ensure the display flex cable has clear access to the electronics area. (See [tools/images/image2.jpg](tools/images/image2.jpg))
- **Step 3 — Solder modules and wires while loose (recommended):** Before permanently mounting anything, solder all required connections with the parts loose on the bench:
	- Solder the eInk display SPI wires (SCK, MOSI, MISO, CS, DC, RST, BUSY) to a header or directly to the ESP32 wires.
	- Solder the TP4056 battery connections (B+ / B‑) and the OUT+ / OUT‑ to the step‑down regulator input.
	- Solder the regulator output (3.3V) to the ESP32 `3V3` pin and connect common ground to `GND`.
	- Keep wires long enough to tuck into the enclosure, and use heat‑shrink or insulation on exposed joints.
	- Test the wiring on the bench: connect battery or USB (through TP4056) and verify the regulator provides 3.3V and the ESP32 powers up before mounting. (See [tools/images/image3.jpg](tools/images/image3.jpg))
- **Step 4 — Charger & battery placement:** Place the TP4056 module and the 18650 battery in the cavity after testing. Place the charger module near the enclosure opening so the micro‑USB remains accessible. Secure the battery safely in the cavity (use foam or a holder). (See [tools/images/image4.jpg](tools/images/image4.jpg))
- **Step 5 — Mount the MCU & regulator:** With soldering and bench tests complete, mount the ESP32‑S3 DevKit and the step‑down regulator in the electronics cavity and tuck the wires neatly. (See [tools/images/image5.jpg](tools/images/image5.jpg))
- **Step 6 — Final assembly & test:** Load firmware (see below), insert an initial picture set, close the back cover, and test the power and display sequence. Confirm the photo changes after 4 hours (or shorten the interval while debugging). (See [tools/images/image6.jpg](tools/images/image6.jpg))

**Wiring Summary**
- **Battery → TP4056:** Battery connected to B+ and B‑ (confirm polarity).
- **TP4056 OUT → Step‑down input:** Module OUT+ to regulator VIN, OUT‑ to regulator GND.
- **Step‑down 3.3V → ESP32 3V3:** Regulator output to `3V3` pin on the ESP32; common ground to `GND`.
- **ESP32 SPI → eInk display:** Use the display's SPI pins (SCK, MOSI, CS, DC, RST, BUSY). Match MOSI/MISO according to your display module docs.
- **TP4056 micro‑USB:** Use for charging; remove USB power before working on battery wiring.

**Software / Firmware**
- **Platform:** PlatformIO is configured in [code/platformio.ini](code/platformio.ini).
- **Main code:** See [code/src/main.cpp](code/src/main.cpp). The firmware handles:
	- loading images from onboard storage (SPIFFS/LittleFS) or embedded arrays,
	- updating the display, and
	- entering deep sleep for energy savings and waking on a timed schedule (4 hours by default).
- **Build & flash (quick):**
```bash
cd code
platformio run --target upload
```

**Preparing Images**
- Resize your photos to the display resolution and convert to the display's color format (1‑bit or 2‑bit per plane depending on your module). Tools/scripts may be included in `tools/` to help convert images; check `tools/convert_images_to_h.py` for a simple converter.
- Upload images to the filesystem used by the firmware (SPIFFS/LittleFS) or include them in the firmware binary.

**Safety & Tips**
- **Battery safety:** Always respect Li‑ion battery polarity. Do not short the battery. Use the TP4056 correctly and avoid leaving the battery connected during long DIY bench work without supervision.
- **Testing:** During early testing, shorten the 4‑hour interval so you can confirm behavior quickly.
- **Enclosure:** Use non‑conductive spacers where the PCB faces the printed parts to avoid shorts.

**Customization Ideas**
- Add a light sensor to switch to a night mode or disable updates in darkness.
- Add a simple RTC if you want reliable timekeeping without relying on network updates.

**Credits & License**
- **Author:** Project completed as a one‑day challenge.
- **License:** MIT — feel free to reuse and adapt.

If you want, I can also:
- add a wiring diagram image to the repo,
- adapt the firmware to use an SD card for images, or
- prepare automated image conversion scripts.
