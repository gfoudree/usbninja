Usbninja Security Software
===================
Security software to monitor your PC for USB removable media insertion. Provides the ability to white-list USB drives by burning a serial to them and blocking all un-authorized devices from mounting.

- Background

  Malware and worms love to use USB flash drives as an easy vector for PC infection. In addition, sensitive
data can be leaked easily (and nearly anonymously) through the use of flash drives. Some organizations
have completely banned flash drives for the reasons above but there is a better solution. UsbNinja. 

- How it works

  Instead of banning the use of flash drives completely, an administrator can "authorize" each individual flash drive
for use with a computer. This can be used to assign company-only drives and ban personal drives from being
used in the work place. In addition, each device plugged in is logged with a time-stamp. Data leaks and computer
infection can be matched with the logs to reveal the culprit. Administrators can authorize as many or as little drives
as they choose. All non-authorized drives are blocked by default. 

For example: Joe's PC can be programmed to only allow Joe's flash drive and the administrator's to be used. If
Sally tries to plug in her drive (which is only authorized for her PC) she won't be able to use it on Joe's computer.

Usb Drive plugged in -> UsbNinja verifies if it's authorized -> Ejected or permitted to access computer
