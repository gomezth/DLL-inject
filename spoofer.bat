@echo off
title GBZ
color 6
echo spoofing...
color 4
ipconfig /realease
ipconfig /flushdns
ipconfig /renew
ping localhost -n 3 >nul
exit