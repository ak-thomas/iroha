add_library(simulator
    impl/simulator.cpp
    )

target_link_libraries(simulator
    model
    rxcpp
    optional
    ametsuchi
    logger
    )
