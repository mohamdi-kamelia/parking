cmake_minimum_required(VERSION 3.0)

project(ParkingGame)

# Recherche de la bibliothèque SDL2
find_package(SDL2 REQUIRED)

# Inclusion des en-têtes SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Définition de la liste des fichiers source
set(SOURCES
    main.cpp
    Window.cpp
    
)

# Déclaration de l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Liaison avec les bibliothèques SDL2
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
