#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

#include "./assets/adalogo.h"
#include "./assets/adaqr.h"

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

void printTestPage() {
    printer.setDefault(); // Restore printer to defaults
    // Test inverse on & off
    printer.inverseOn();
    printer.println(F("Inverse ON"));
    printer.inverseOff();

    // Test character double-height on & off
    printer.doubleHeightOn();
    printer.println(F("Double Height ON"));
    printer.doubleHeightOff();

    // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
    printer.justify('R');
    printer.println(F("Right justified"));
    printer.justify('C');
    printer.println(F("Center justified"));
    printer.justify('L');
    printer.println(F("Left justified"));

    // Test more styles
    printer.boldOn();
    printer.println(F("Bold text"));
    printer.boldOff();

    printer.underlineOn();
    printer.println(F("Underlined text"));
    printer.underlineOff();

    printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
    printer.println(F("Large"));
    printer.setSize('M');
    printer.println(F("Medium"));
    printer.setSize('S');
    printer.println(F("Small"));

    printer.justify('C');
    printer.println(F("normal\nline\nspacing"));
    printer.setLineHeight(50);
    printer.println(F("Taller\nline\nspacing"));
    printer.setLineHeight(); // Reset to default
    printer.justify('L');

    // Barcode examples:
    // CODE39 is the most common alphanumeric barcode:
    printer.printBarcode("ADAFRUT", CODE39);
    printer.setBarcodeHeight(100);
    // Print UPC line on product barcodes:
    printer.printBarcode("123456789123", UPC_A);

    // Print the 75x75 pixel logo in adalogo.h:
    printer.printBitmap(adalogo_width, adalogo_height, adalogo_data);

    // Print the 135x135 pixel QR code in adaqrcode.h:
    printer.printBitmap(adaqr_width, adaqr_height, adaqr_data);
    printer.println(F("Adafruit!"));
    printer.feed(2);
    printer.setDefault(); // Restore printer to defaults
}