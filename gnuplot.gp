
set terminal qt

set terminal qt size 1400,600

set multiplot layout 1,2 rowsfirst

plot "amplituden.dat" with linespoints title "Amplituden"


 # "speakingProb.dat" with linespoints title "Speaking probability" , \
 # "silenceProb.dat" with linespoints title "SIlence probability" , \

plot "energy.dat" with linespoints title "Energy" , \
  "isSpeaking.dat" with linespoints title "Is Speaking"

pause -1

unset multiplot