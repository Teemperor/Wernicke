
set terminal qt

set terminal qt size 1400,600

set multiplot layout 1,2 rowsfirst

plot "/home/teemperor/Dokumente/ASE/ubung3/amplituden.dat" with linespoints title "Amplituden"


 # "/home/teemperor/Dokumente/ASE/ubung3/speakingProb.dat" with linespoints title "Speaking probability" , \
 # "/home/teemperor/Dokumente/ASE/ubung3/silenceProb.dat" with linespoints title "SIlence probability" , \

plot "/home/teemperor/Dokumente/ASE/ubung3/energy.dat" with linespoints title "Energy" , \
  "/home/teemperor/Dokumente/ASE/ubung3/isSpeaking.dat" with linespoints title "Is Speaking"

pause -1

unset multiplot