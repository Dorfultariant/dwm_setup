
xrandr --output DP-0 --primary --auto
xrandr --output HDMI-0 --auto --right-of DP-0
xrandr --output DP-2 --auto --left-of DP-0


/usr/local/bin/slstatus &

exec dwm 


