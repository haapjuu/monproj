import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev
import datetime

GPIO.setmode(GPIO.BCM)

pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1], [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]

radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0, 26)

radio.setPayloadSize(32)
radio.setChannel(0x74)
radio.setDataRate(NRF24.BR_250KBPS)
radio.setPALevel(NRF24.PA_MIN)

radio.setAutoAck(True)
radio.enableDynamicPayloads()
radio.enableAckPayload()

radio.openReadingPipe(1, pipes[1])
radio.printDetails()
radio.startListening()

while True:
    ackPL = [1]
    while not radio.available(0):
        time.sleep(0.01)

    receivedMessage = []
    radio.read(receivedMessage, radio.getDynamicPayloadSize())
    print("Received: {}".format(receivedMessage))

    print("Translating the receivedMessage into unicode characters")
    string = ""
    for n in receivedMessage:
        if (n >= 32 and n <= 126):
            string += chr(n)
    print("Our received message decodes to: {}".format(string))
    radio.writeAckPayload(1, ackPL, len (ackPL))
    print("Loaded payload reply of {}".format(ackPL))

    now = datetime.datetime.now()
    f= open("logs.txt", "a+")
    f.write(now.strftime("%Y-%b-%d %H:%M")+" "+"{}".format(string)+"\n")
    f.close()
