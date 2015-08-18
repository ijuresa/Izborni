#!/bin/bash
# Convert wav to raw
for file in *.wav
do
 wav2raw +s $file
done

# Convert raw to short
for file in *.raw
do
 x2x +s $file > ${file%.raw}.short
done

# Convert short to float
for file in *.short
do
 x2x +sf $file > ${file%.short}.f
done

# Calculating lpc
for file in *.f
do 
 frame < $file | frame -l 400 -p 80 | window -l 400 |\lpc -l 400 -m 20 > ${file%.f}.lpc
done

# Calculating mfcc
for file in *.f
do
 frame -l 640 -p 160 $file |\mfcc -l 640 -m 12 -s 16 -E > ${file%.f}.mfc
done

