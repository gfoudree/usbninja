Todo
----------------------------
- add syncDB that syncs sqlite3 and mysql DB
- usbninja service status (pid etc..)
- inserted usb, popup (temporarly authorize or fully authorize?)
- Run service on startup (win32 service on startup watchdog)
- Fix sql "id" conflict with local and remote DB

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
