#include <stdio.h>
#include <iostream>
#include <usb_cam/usb_cam.h>
#include <sstream>

int main(int argc, char** argv) {
  std::string io_method_name_;

  // params setting
  io_method_name_ = std::string("mmap");

  usb_cam::UsbCam::io_method io_method = usb_cam::UsbCam::io_method_from_string(io_method_name_);
  if(io_method == usb_cam::UsbCam::IO_METHOD_UNKNOWN) {
    fprintf(stderr, "Unknown IO method %s", io_method_name_.c_str());
    return -1;
  }

  return 0;
}
