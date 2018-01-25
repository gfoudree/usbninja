from Crypto.PublicKey import RSA
from Crypto.Hash import SHA256
from Crypto.Signature import PKCS1_v1_5
from random import randint

class UsbSerial:
    def genKey(self, outFile):
      self.key = RSA.generate(4096)
      hFile = open(outFile, 'w')
      hFile.write(self.key.exportKey('PEM'))
      hFile.close()

    def readKey(self, inFile):
        self.key = RSA.importKey(open(inFile, 'r').read())

    def signData(self, data):
        if not self.key:
            raise "Keypair not initalized!"
        hsh = SHA256.new(data)
        return PKCS1_v1_5.new(self.key).sign(hsh)

    def verifyData(self, data, signature):
        hsh = SHA256.new(data)
        if PKCS1_v1_5.new(self.key).verify(hsh, signature):
            return True
        else:
            return False

    def generateSerial(self, length = 16):
        serial = ''
        for i in range(0, length):
            serial += str(randint(0,9))
        return serial
