cmake_minimum_required(VERSION 3.19)

project(vet_server LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    HttpServer
    Sql
)

qt_standard_project_setup()

qt_add_executable(vet_server
    main.cpp
    database/database.h database/database.cpp
    server/server.h server/server.cpp
    auth/authservice.h auth/authservice.cpp
    database/models.h

)

target_link_libraries(vet_server
    PRIVATE
        Qt6::Core
        Qt6::HttpServer
        Qt6::Sql
)

install(TARGETS vet_server
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)