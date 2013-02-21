Todo
----------------------------
- add USBserial reading function and member in USBLog struct
- add error handling for usbdevice.cpp functions

Notes
----------------------------
AuthorizedDrives.db
Fields:
- id
- dateAuthorized
- serial
- driveName
- driveSize

log.db
Fields:
- id
- action 		#accepted/rejected
- date
- user
- driveLetter
- driveName		#USB friendly name
- driveLabel
- driveSize
- driveSerial
- driveGUID
- usbninjaSerial
