clear
echo 
echo
echo
clear
echo Build script
rm -r bin_r
./build_vx.sh ../linux_sdk/linux_sdk ../fenix
echo Run
bin_r/vgg vgg.nb priors.dat 0.4 ../testImage/image.jpg #> output.txt
echo Finish
