cmake_minimum_required (VERSION 3.5.1)

project (stravaV10)

# On inclut notre bibliothèque dans le processus de CMake
# add_subdirectory(source/routes)
add_subdirectory(TDD/sd/fatfs)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

add_definitions(-DTDD)
add_definitions(-D__HEAP_SIZE=150000)
add_definitions(-D_USE_MATH_DEFINES)
#add_definitions(-DLOC_SOURCE_GPS)
#add_definitions(-DTDD_RANDOMIZE)
#add_definitions(-DLS027_GUI)

set(CMAKE_C_FLAGS  "-fno-builtin --short-enums -nostdlib -MMD -nostdlib -ffunction-sections -fdata-sections -fno-strict-aliasing")
set(CMAKE_CXX_FLAGS  "-g -std=gnu++0x -rdynamic -felide-constructors -fno-exceptions -fno-rtti -fpermissive")


# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/TDD/main_tdd.h.in"
  "${PROJECT_BINARY_DIR}/main_tdd.h"
  )
 
# add the binary tree to the search path for include files

include_directories(
    ./
	TDD
	TDD/sd
	TDD/sd/fatfs/src
	TDD/drivers
	TDD/timer
	TDD/sensors
	TDD/scheduler
	libraries/AdafruitGFX
    libraries/AdafruitGFX/Fonts
	libraries/AltiBaro
	libraries/GlobalTop
	libraries/utils
    libraries/filters
    libraries/komoot
	libraries/TinyGPSPlus
	rf
    source
    source/routes
	source/model
	source/vue
	source/parsers
	source/display
	source/sensors
    )

# Cree des variables avec les fichiers à compiler
set(SRCS
    main_tdd.cpp
    segger_wrapper.c
    GUI_connector.cpp
    scheduler/task_scheduler.c
    unit_testing.cpp
	Model_tdd.cpp
    Simulator.cpp
	millis_tdd.c
	order1_filter_tdd.c
	sd/sd_functions.cpp
	sd/sd_hal.c
	rf/ant_device_manager.cpp
	timer/timer.c
    sensors/GPSMGMT.cpp
    sensors/STC3100.cpp
    sensors/fxos.cpp
    sensors/bme280.c
	drivers/uart_tdd.c
	drivers/ant_tdd.c
	drivers/gpio_tdd.cpp
	drivers/ls027_tdd.cpp
	drivers/neopixel_tdd.c
	libraries/utils/WString.cpp
	libraries/AdafruitGFX/Adafruit_GFX.cpp
	libraries/AdafruitGFX/Print.cpp
	libraries/AltiBaro/AltiBaro.cpp
	libraries/utils/utils.c
    libraries/komoot/komoot_nav.c
	libraries/GlobalTop/EPONmeaPacket.cpp
	libraries/TinyGPSPlus/TinyGPS++.cpp
	source/display/SegmentManager.cpp
	source/display/Zoom.cpp
	source/display/notifications.c
    source/routes/ListePoints.cpp
	source/routes/Parcours.cpp
	source/routes/Points.cpp
	source/routes/Segment.cpp
	source/routes/Vecteur.cpp
    source/sensors/fram.c
	source/parsers/file_parser.cpp
	source/model/Attitude.cpp
	source/model/Boucle.cpp
	source/model/BoucleCRS.cpp
	source/model/BoucleFEC.cpp
	source/model/Locator.cpp
	source/model/PowerZone.cpp
	source/model/SufferScore.cpp
	source/model/UserSettings.cpp
	source/vue/Screenutils.cpp
	source/vue/Menuable.cpp
    source/vue/MenuObjects.cpp
	source/vue/Vue.cpp
	source/vue/VueCRS.cpp
	source/vue/VueDebug.cpp
	source/vue/VueGPS.cpp
	source/vue/VuePRC.cpp
	source/vue/VueFEC.cpp
    )
    
set(HEADERS
    main_tdd.h
    Simulator.h
    )
 
# add the executable
add_executable(StravaV10 ${SRCS} ${HEADERS})

# Et pour que l'executable fonctionne, il faut lui indiquer la bibliothèque dont il dépend
target_link_libraries(StravaV10 fatfs)
# target_link_libraries(StravaV10 routes)
