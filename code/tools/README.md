Image conversion tools
======================

Simple helper to convert images into C header arrays for embedded displays.

Usage
-----

1. Put source images in a folder (e.g. `images/`).
2. Run the converter, specifying output folder and target resolution:

```bash
```

Options
-------
- `--mode rgb565` (default) or `--mode mono` for 1-bit packed bytes.
- `--progmem` will add `PROGMEM` (for AVR) in the generated headers.
2. Run the converter, specifying output folder and target resolution.

Example (color / RGB565):

```bash
python tools/convert_images_to_h.py -i images -o include/generated -W 240 -H 320 --mode rgb565
```

Example (3-color e-ink: black/red/white) for your 296x128 panel:

```bash
python tools/convert_images_to_h.py -i images -o include/generated -W 296 -H 128 --mode tri
```

Face-focus notes
----------------
- If backgrounds are dominating, use `--focus face` to crop around the detected face so the person fills the frame better. This requires `opencv-python`.
- Control how much surrounding area is kept with `--focus-margin` (default `1.8`). Larger values zoom out (less crop). Example:

```bash
python tools/convert_images_to_h.py -i images -o include/generated -W 296 -H 128 --mode tri --focus face --focus-margin 2.8
```

Person-focus (HOG) notes
------------------------
- Use `--focus person` to detect the whole person using HOG and ensure the entire person fits in the cropped image. The script will also attempt to detect a face inside the person bbox and center the crop on the face.
- The crop will include at least `--top-margin` pixels above the detected head (default `20`).
- Example (person focus, keep 20px above head):

```bash
python tools/convert_images_to_h.py -i images -o include/generated -W 296 -H 128 --mode tri --focus person --top-margin 20
```

------
Per-image `.h` files and an `images_index.h` that includes all generated headers
and an array of entries you can iterate over on the device.


Output details for `tri` mode
-----------------------------
- Each generated header now contains a packed 2-bit-per-pixel gray plane `<name>_gray` (4 gray levels: 0=white..3=black) and a packed 1-bit red mask `<name>_red`.
- `images_index.h` defines an `ImageTri` struct with `{ gray, red, w, h }` and an `images[]` array you can iterate at runtime.
- Packing: `gray` plane packs 4 pixels per byte (bits: g0 g1 g2 g3 as 2-bit fields, MSB first). `red` packs 8 pixels per byte (MSB first).
- The generated C arrays are plain; adjust `PROGMEM` usage per your target.
