#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <string.h>

//recreating lsusb in C
//©MxBit2020

int main(){

    libusb_device_handle    *handle = NULL;
    libusb_context          *ctx    = NULL;
    libusb_device            **devs;

    int devNumber = 4;

    int result = libusb_init(&ctx);
    if( result < 0){printf("error: ", stderr, "\n", result);}

    ssize_t cnt = 0;
    ssize_t i;

    cnt = libusb_get_device_list(ctx, &devs);
    if(cnt < 0) {printf("Error in get_device_list");}
    printf("Device Number %d of %d:\n\n",devNumber,cnt);

    libusb_device *devices[cnt];

    struct libusb_device_descriptor desc;
    
    //get device handler to run -> open
    unsigned char data[255] = {};
    int resultDescr = libusb_get_device_descriptor(devs[3],&desc);
    
    handle = libusb_open_device_with_vid_pid(ctx,(int)desc.idVendor,(int)desc.idProduct);
    
    //int r = libusb_get_string_descriptor_ascii(handle,desc.bDescriptorType, data, sizeof(data));
    //causes segmentation core dump -> want to extract detailed ascii names of usb data 


    printf("%s StringDescriptorAscii\n",data);
    printf("%d VendorID\n",(int)desc.idVendor);
    printf("%d ProductID\n",(int)desc.idProduct);
    printf("%d Product\n",( int )desc.iSerialNumber);
    printf("%d Descriptor Type\n", (int)desc.bDescriptorType);
    printf("%d Descriptor Conf.\n", (int)desc.bNumConfigurations);
    // printf("%s Device\n",desc.bcdDevice);
    // names ..

//Looping each device
/*
    for(i=0; i < cnt; i++){
        printf( devs[i] +'/n');
    }
*/

    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
    return 0;
}
