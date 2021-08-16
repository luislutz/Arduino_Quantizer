# Arduino_Quantizer
Eurorack format Quantizer with Arduino Nano
(based on Hagiwo Modulars original Design)

Feature List:


Scale Modes:
The Scale is chosen by turning the Encoder Knob:

1. Chromatic
2. Major
3. Major Pentatonic
4. Major Pentatonic + 7
5. Natural Minor 
6. Minor Pentatonic
7. Octaves


Root Modes:
The Root-Note is Selected by turning the same Encoder Knob while held pressed down!
With the Rotate function All Scales are availiable from C, C-sharp, D, D-Sharp, E .... A, A-Sharp, B. So no need to transpose your oscillator anymore!
Every Scale Mode is availiable with every Root Note Selected!


CV-Modes:
The CV-Mode is chosen by double clicking (and holding) the encoder button and turning the knob while pressed!
CV-modes determin what the Mode CV input does:

1. Control Slide Function via CV (ON or OFF)
2. Control Slide Time via CV, in addition to what is set on the Slide Knob
3. Select the Scales via CV
4. Select the Root Note via CV
5. Transpose the incoming Pitch CV in Semitone-Steps
6. Transpose the incoming Pitch CV in Fifths (7 Semitones)
7. Transpose the incoming Pitch CV in Octaves (12 Semitones)


TB-303 type Slide Function with Knob!

Encoder with Switch to select everything

A RGB LED to indicate the selected Scale. And in addition the Root, and CV Mode, when it is in the corresponding select mode.

Pitch CV Input 
Mode CV Input for all the additional CV functions
Gate/Trigger Output
Quantized Pitch CV Output

Toggle Switch to activate and deactivate current selected CV_Mode

Buffered Output with Scale trimpot for calibraion!

Inputs safe for Eurorack levels.


