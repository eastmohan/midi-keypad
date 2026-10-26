# midi-keypad
A compact, custom-designed USB MIDI controller built around the Waveshare ESP32-S3-ZERO. It has 7 key inputs, a daisy-chained chain of addressable RGB LEDs for visual feedback, and a rotary encoder with a push-button for volume control.
<img width="623" height="507" alt="image" src="https://github.com/user-attachments/assets/780d3ef9-7d97-4904-ba97-bc60fe44c494" />

Components
Microcontroller (U1): Waveshare ESP32-S3-ZERO (providing native USB support for direct MIDI communication).
EC11 Rotary Encoder
8*SK6812 Mini-e LEDs
PCB

<img width="603" height="514" alt="image" src="https://github.com/user-attachments/assets/e0e16498-e1f7-4209-afa3-4237d989aeb0" />
<img width="890" height="736" alt="image" src="https://github.com/user-attachments/assets/49915bf9-3570-4a08-83bd-571cdb51b672" />


Key Inputs (J1): Set as a pin header in the schematic, but actually connects to a custom footprint of exposed pads (conductive keys):
<img width="1198" height="605" alt="image" src="https://github.com/user-attachments/assets/928fa24e-0e69-439b-827c-1dce7754889c" />

Rotary Encoder (SW1): Incremental rotary encoder with an integrated push switch (rcswitch) for navigation or volume adjustment.

Addressable LEDs (D1–D8): 8x SK6812MINI-E RGB LEDs wired in a serial data chain.
