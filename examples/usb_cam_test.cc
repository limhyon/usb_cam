#include <iostream>
#include <stdio.h>
#include <usb_cam/usb_cam.h>
#include <sstream>
#include <unistd.h>

int main(int argc, char** argv) {
  usb_cam::UsbCam cam_;

  std::string io_method_name_;
  std::string pixel_format_name_;
  std::string video_device_name_;

  int image_width_, image_height_, framerate_;

  // params setting
  io_method_name_ = std::string("mmap");
  pixel_format_name_ = std::string("yuyv");
  //pixel_format_name_ = std::string("yuvstereo10");
  video_device_name_ = std::string("/dev/video0");
  image_width_ = 640;
  image_height_ = 480;
  framerate_ = 30;

  usb_cam::UsbCam::io_method io_method = usb_cam::UsbCam::io_method_from_string(io_method_name_);
  if(io_method == usb_cam::UsbCam::IO_METHOD_UNKNOWN) {
    fprintf(stderr, "Unknown IO method %s", io_method_name_.c_str());
    return -1;
  }

  // set the pixel format
  usb_cam::UsbCam::pixel_format pixel_format = usb_cam::UsbCam::pixel_format_from_string(pixel_format_name_);
  if(pixel_format == usb_cam::UsbCam::PIXEL_FORMAT_UNKNOWN) {
    fprintf(stderr,"Unknown pixel format '%s'", pixel_format_name_.c_str());
    return -1;
  }

  cam_.start(video_device_name_.c_str(), io_method, pixel_format, image_width_, image_height_, framerate_);
  char buf[0xff];
  for(int i = 0; i < 10; i++) {
    cam_.grab_image(buf);
    sleep(1);
  }
  
  cam_.shutdown();

  return 0;
}
