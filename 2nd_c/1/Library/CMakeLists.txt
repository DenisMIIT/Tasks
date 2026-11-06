add_library(gai_library STATIC
    Date.cpp
    Owner.cpp
    Accident.cpp
    Vehicle.cpp
    PassengerCar.cpp
    Truck.cpp
    VehicleRegistry.cpp
)
target_include_directories(gai_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(gai_library PUBLIC cxx_std_17)
