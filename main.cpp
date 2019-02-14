/*
 * Copyright (c) 2019, CATIE
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mbed.h"

#include "zest-sensor-camera/zest-sensor-camera.h"

using namespace sixtron;

namespace {
#define TIMEOUT_MS     1000 // timeout capture sequence in milliseconds
#define BOARD_VERSION  "v2.1.0"
#define START_PROMPT   "\r\n*** Zest Sensor Camera Example ***\r\n"\
                       "camera version board: "\
                       BOARD_VERSION
#define PROMPT         "\r\n> "
#define POWER_ON_DELAY 50 // hardware power up delay needed to start camera
#define CAPTURE_COUNT  1 // capture image count
#define INTERVAL_TIME  500 // delay between each capture, used if the CAPTURE_COUNT is bigger than one
#define FLASH_ENABLE   1 // state of led flash during the capture
}

// Prototypes
bool capture_sequence(int capture_count, int interval_time, bool flash_enable);
void jpeg_processing(int jpeg_index, uint8_t *data);
void application_setup(void);
void application(void);

// Peripherals
RawSerial pc(SERIAL_TX, SERIAL_RX);
static DigitalOut led1(LED1);
static InterruptIn button(BUTTON1);
static DigitalOut camera_pwr(GPIO15);
static DigitalOut camera_reset(WKUP);
ZestSensorCamera camera_device(GPIO14);

// RTOS
Thread thread_application;

// Variables
bool frame_detected = false;

static void camera_frame_handler(void)
{
    frame_detected = true;
}

static void button_handler(void)
{
    thread_application.signal_set(0x1);
}

bool capture_sequence(int capture_count, int interval_time, bool flash_enable)
{
    bool res = false;
    int timeout_ms;
    int capture_index = 0;

    while (capture_index != capture_count) {
        timeout_ms = TIMEOUT_MS;
        // clear flag frame ready
        frame_detected = false;
        // setup led flash
        if (flash_enable == true) {
            camera_device.lm3405().turn_on();
        }
        // start ov5640 camera capture
        camera_device.ov5640().start_capture();
        // wait frame ready
        do{
            wait_ms(1);
            timeout_ms--;
            if (timeout_ms <= 0) {
                break;
            }
        } while(frame_detected != true);

        // turn off led flash
        if (flash_enable == true) {
            camera_device.lm3405().turn_off();
        }
        // resume DCMI camera
        camera_device.ov5640().resume();
        // if no timeout occurred
        if (timeout_ms > 0) {
            res = true;
            // increment index
            capture_index++;
            // check if the jpeg mode is enable
            if (camera_device.ov5640().jpeg_mode() == OV5640::JpegMode::ENABLE) {
                jpeg_processing(capture_index, ov5640_camera_data());
            }
            // set interval capture time
            if (interval_time != 0) {
                wait_ms(interval_time);
            }
        } else {
            camera_device.ov5640().stop();
            // error
            res = false;
            break;
        }
    }

    return res;
}

void jpeg_processing(int jpeg_index, uint8_t *data)
{
    size_t i = 0;
    uint32_t jpgstart = 0;
    bool  head = false;
    uint8_t  *base_address = NULL;
    uint32_t length = 0;

    for (i=0; i < OV5640_JPEG_BUFFER_SIZE; i++)
    {
        //search for 0XFF 0XD8 0XFF and 0XFF 0XD9, get size of JPG
        if ((data[i] == 0xFF) && (data[i+1] == 0xD8) && (data[i+2] == 0xFF)) {
            base_address = &data[i];
            jpgstart=i;
            head=1; // Already found  FF D8
        }
        if ((data[i] == 0xFF) && (data[i+1] == 0xD9) && head) {
            // set jpeg length
            length = i - jpgstart + 2;
            break;
        }
    }

    //end of traitment: back to base address of jpeg
    data = base_address;

    // print data to serial port
    pc.printf(PROMPT);
    pc.printf("JPEG %d stored in RAM: %ld bytes", jpeg_index, length);

}

void application_setup(void)
{
    // camera power on
    camera_pwr = 1;
    wait_ms(POWER_ON_DELAY);
    camera_reset = 0;
    // power up led flash
    camera_device.lm3405().power_on();
    // set user button handler
    button.fall(button_handler);
}

void application(void)
{
    // application setup
    application_setup();

    // init ov5640 sensor: 15fps VGA resolution, jpeg compression enable and capture mode configured in snapshot mode
    if (camera_device.ov5640().iniatilize(OV5640::Resolution::VGA_640x480, OV5640::FrameRate::_15_FPS, OV5640::JpegMode::ENABLE, OV5640::CameraMode::SNAPSHOT)){
        pc.printf(PROMPT);
        pc.printf("Omnivision sensor ov5640 initialized");
        // attach frame complete callback
        camera_device.ov5640().attach(camera_frame_handler);
        pc.printf(PROMPT);
        pc.printf("Press the button to start the snapshot capture...");
    } else {
        pc.printf(PROMPT);
        pc.printf("Error: omnivision sensor ov5640 initialization failed");
        return;
    }

    // process: wait an user button event to start the capture
    while (true) {
        // wait semaphore
        Thread::signal_wait(0x1);
        if (capture_sequence(CAPTURE_COUNT, INTERVAL_TIME, FLASH_ENABLE)) {
            pc.printf(PROMPT);
            pc.printf("Complete camera acquisition");
        } else {
            pc.printf(PROMPT);
            pc.printf("Camera acquisition error");
        }
    }
}

// main() runs in its own thread in the OS
// (note the calls to Thread::wait below for delays)
int main()
{
    pc.printf(START_PROMPT);

    //set priority thread application
    thread_application.set_priority(osPriorityHigh);
    // start thread
    thread_application.start(application);
}
