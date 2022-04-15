# ~/.config/lxsession/LXDE-pi/
#sudo nano autostart
#@lxpanel --profile LXDE-pi
#@pcmanfm --desktop --profile LXDE-pi
#@xscreensaver -no-splash
#@point-rpi
#@bash /home/pi/Desktop/startup.sh

# echo "lets start"
cd /usr/local/lib/processing-3.4
./processing-java --sketch=/home/pi/Desktop/processing/network --run 
