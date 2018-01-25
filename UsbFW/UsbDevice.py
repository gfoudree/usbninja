import psutil, os

class UsbDevice:
    def __init__(self, deviceName):
        self.devName = deviceName
        hdisk = open(deviceName, 'rb')
        self.mbr = hdisk.read(512)

    def RawMBR(self):
        return self.mbr

    def GetFileSystem(self):
        '''if self.mbr[54:61] == ['F','A','T','1','6',' ',' ',' ']:
            return self.FAT16
        else if self.mbr[82:89] == ['F','A','T','3','2',' ',' ',' ']:
            return self.FAT32
        '''
        for fs in psutil.disk_partitions():
            rawDiskName = fs.device[0:len(fs.device) -1]
            if fs.device == self.devName:
                print(fs.fstype)
