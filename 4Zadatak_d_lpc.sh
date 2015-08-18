#Plotting spectral estimates from LPC coefficients
#Analysis order: 20
for file in *.lpc
do
 bcut +f -n 20 -s 10 -e 135 < $file |\spec -l 512 -n 20 | grlogsp -l 512 -x 8 | xgr
done
