# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)
add_compile_definitions(LWIP_MQTT=1)
# Must set these FIRST
set(PICO_BOARD pico_w)
set(PICO_CYW43_ARCH "pico_cyw43_arch_lwip_threadsafe_background")

# Global settings (before project/sdk init)
set(__USE_PICO_STATIC_ASSERT 1)
set(PICO_CYW43_ARCH_LWIP 1)
set(PICO_CYW43_ARCH_ENABLE_BT 1)  # Only if you need Bluetooth

include(${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk/external/pico_sdk_import.cmake)
project(wifi C CXX ASM)

set(__USE_PICO_STATIC_ASSERT 1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICOTOOL_FORCE_FETCH_FROM_GIT OFF)
set(PICO_TOOLCHAIN_PROGRAMMING_VERSION 2.1.1)

pico_sdk_init()

add_compile_definitions(
    LWIP_MQTT=1
    LWIP_TCP=1
    LWIP_IPV4=1
)


add_subdirectory(pico-sdk pico-sdk-build)

# Copy firmware files to build directory
file(COPY ${PICO_SDK_PATH}/lib/cyw43-driver/firmware/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/firmware)

add_executable(wifi
 src/main.c
 src/buzzer.c
 src/wifi.c
 src/datetime.c
 src/led.c
 src/ultrasonic.c
 src/lcd.c)


pico_set_program_name(wifi "wifi")

# Now that 'main' target exists, we can configure it
target_compile_definitions(wifi PRIVATE
    __USE_PICO_STATIC_ASSERT
    CYW43_LWIP=1
    CYW43_WIFI_NVRAM_INCLUDE_FILE="wifi_nvram_43439.h"
)

target_compile_definitions(wifi PRIVATE
    CYW43_HAL_GET_MAC_DEFINED=1  # Prevent redefinition
)

# Lägg till nödvändiga bibliotek för GPIO
target_link_libraries(wifi PRIVATE 
	pico_stdlib 
	hardware_pwm
	hardware_gpio)


target_include_directories(wifi PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PICO_SDK_PATH}/include
    ${PICO_SDK_PATH}/lib/cyw43-driver/firmware
    ${PICO_SDK_PATH}/lib/cyw43-driver/src
    ${PICO_SDK_PATH}/lib/cyw43-driver/include
    ${PICO_SDK_PATH}/lib/lwip/src/include
    ${PICO_SDK_PATH}/lib/lwip/src/include/lwip
    ${PICO_SDK_PATH}/lib/lwip/contrib/ports/rp2040/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_driver
    ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_arch/include/pico
    ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_driver/include
    ${PICO_SDK_PATH}/src/common/pico_stdlib/include
    #${PICO_SDK_PATH}/src/common/pico_base/include
    #${PICO_SDK_PATH}/src/common/pico_time/include
    #${PICO_SDK_PATH}/src/common/pico_types/include
    #${PICO_SDK_PATH}/src/common/pico_sync/include
    #${PICO_SDK_PATH}/src/common/pico_util/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_uart/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_spi/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_i2c/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_pwm/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_adc/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_rtc/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_flash/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_pll/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_vreg/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_clocks/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_watchdog/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_xosc/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_irq/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_pio/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_dma/include
    #${PICO_SDK_PATH}/src/rp2_common/hardware_claim/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_platform/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_printf/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_bit_ops/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_bootrom/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_divider/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_double/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_int64_ops/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_float/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_malloc/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_mem_ops/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_standard_link/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_stdio/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_stdio_usb/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_unique_id/include
    #${PICO_SDK_PATH}/src/rp2_common/pico_runtime/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(wifi PRIVATE
    pico_cyw43_arch_lwip_threadsafe_background
    pico_stdlib
    pico_lwip
    hardware_i2c
    hardware_dma
    hardware_irq
    pico_time
    pico_lwip_mqtt
)

pico_enable_stdio_usb(wifi 1)
pico_enable_stdio_uart(wifi 0)
pico_add_extra_outputs(wifi)
