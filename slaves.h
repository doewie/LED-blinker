#ifndef DOEWIE_SLAVES_H
#define DOEWIE_SLAVES_H

int slaves[10]; // space for max 10 scanned I2C-slaves
unsigned short int slaveCounter = 0; 

// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

void scanActiveSlaves(){
    
// copied from pico-examples blink , I2C, ....

    for (int addr = 0; addr < (1 << 7); ++addr) {

        // Perform a 1-byte dummy read from the probe address. If a slave
        // acknowledges this address, the function returns the number of bytes
        // transferred. If the address byte is ignored, the function returns
        // -1.

        // Skip over any reserved addresses.
        int ret;
        uint8_t rxdata;
        if (reserved_addr(addr))
            ret = PICO_ERROR_GENERIC;
        else
            ret = i2c_read_blocking(i2c0, addr, &rxdata, 1, false);

        if (ret >= 0) {
            slaves[slaveCounter] = addr;
            slaveCounter++;
        }    
    }

}

#endif