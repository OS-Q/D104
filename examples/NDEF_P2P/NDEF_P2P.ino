
#include "SPI.h"
#include "NDEF.h"

PN532_SPI pn532spi(SPI, 15);
SNEP nfc(pn532spi);
uint8_t ndefBuf[128];

void setup()
{
    Serial.begin(115200);
    Serial.println("Peer to Peer");
    delay(3000);
    Serial.println("qitas");
}

void loop()
{
#if 1
    Serial.println("Send a message to Android");
    NdefMessage message = NdefMessage();
    message.addUriRecord("http://www.OS-Q.com");
    int messageSize = message.getEncodedSize();
    if (messageSize > sizeof(ndefBuf)) {
        Serial.println("ndefBuf is too small");
        while (1) {
        }

    }

    message.encode(ndefBuf);
    if (0 >= nfc.write(ndefBuf, messageSize)) {
        Serial.println("Failed");
    } else {
        Serial.println("Success");
    }

    delay(3000);
#else
    Serial.println("Get a message from Android");
    int msgSize = nfc.read(ndefBuf, sizeof(ndefBuf));
    if (msgSize > 0) {
        NdefMessage msg  = NdefMessage(ndefBuf, msgSize);
        msg.print();
        Serial.println("\nSuccess");
    } else {
        Serial.println("failed");
    }
    delay(3000);
#endif
}
