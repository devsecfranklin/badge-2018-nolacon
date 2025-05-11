# Artwork

- pull bmp into fusion 360
- save bmp as dxf
- run import_dxf_polygons.ulp
  - use scale of 7.8
  - import to unused layer (like 50)
- run copy-wire-to-any-layer.ulp
  - copy from 50 to 20

## eagle

Use these settings for art import.

- import bmp 0.085 MM
- import bmp 0.0425 MM nola_layered_NEW.bmp

## Generate byte array

- [image2cpp is a simple tool to change images into byte arrays](http://javl.github.io/image2cpp/)
  (or arrays back into an images) for use with (monochrome) displays such as OLEDs on
  your Arduino or Raspberry Pi.
