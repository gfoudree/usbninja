Todo
----------------------------
- add syncDB that syncs sqlite3 and mysql DB
- optimize code for SQL (inheritance)
- usbninja service status (pid etc..)
- inserted usb, popup (temporarly authorize or fully authorize?)
- Run service on startup (win32 service on startup watchdog)
- Fix usbninja serial in GUI app

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
