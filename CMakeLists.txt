cmake_minimum_required(VERSION 3.16)
project(PointAndClickSFML)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

#---- Fetch SFML, only works if you have git installed on your machine ----#

include(FetchContent)   # Allows fetching content remotely at configure time
FetchContent_Declare(   # Fetches SFML from github and puts it in the build directory
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b    # Makes sure to fetch SFML version 2.6.1
)

FetchContent_MakeAvailable(SFML)    # Makes sure SFML and its dependencies are avaiable for the project



#----- Fetch JSON Parser For Level Editor, only works if you have git installed on your machine ----#

FetchContent_Declare(
    json 
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG 9cca280a4d0ccf0c08f47a99aa71d1b0e52f8d03
)
FetchContent_MakeAvailable(json)

#---- File management & .exe creation ----#

set(SOURCE_DIR src/)
include_directories(src/)

set(SOURCE_FILES src/Core/main.cpp 
        src/Core/Data.h src/Core/Data.cpp
        src/Core/Game.h src/Core/Game.cpp 
        src/GameState/GameStateClass.h 
        src/GameState/GamePlay.h src/GameState/GamePlay.cpp 
        src/GameState/Menu.h src/GameState/Menu.cpp 
        src/GameState/Pause.h src/GameState/Pause.cpp  
        src/GameState/GameWin.h src/GameState/GameWin.cpp 
        src/GameObjects/GameObject.h src/GameObjects/GameObject.cpp 
        "src/GameObjects/Interactable/InteractableBase.h" 
        "src/GameObjects/Interactable/InteractableBase.cpp" 
        "src/GameObjects/Interactable/ItemDB.h" 
        "src/GameObjects/Interactable/AudioInteractable.cpp" 
        "src/GameObjects/Interactable/AudioInteractable.h"
        "src/Core/DeltaTime.cpp"
        "src/Core/DeltaTime.h" 
        "src/GameState/DebugState.h" 
        "src/GameState/DebugState.cpp" 
        "src/Room/BaseRoom.h"
        "src/Room/BaseRoom.cpp" 
        "src/Room/Rooms/Debug/DebugRoom.h" 
        "src/Room/Rooms/Debug/DebugRoom.cpp" 
        "src/GameObjects/Player.h" 
        "src/GameObjects/Player.cpp" 
        "src/GameObjects/AnimatedGameObject.h" 
        "src/GameObjects/AnimatedGameObject.cpp" 
        "src/GameObjects/PlayerAnimationController.h" 
        "src/GameObjects/PlayerAnimationController.cpp" 
        "src/Room/Rooms/Debug/DebugCorridor.h" 
        "src/Room/Rooms/Debug/DebugCorridor.cpp" 
        "src/Pathfinding/FindClosestPixel.h" 
        "src/Pathfinding/FindClosestPixel.cpp" 
        "src/Pathfinding/AStar.h" 
        "src/Pathfinding/AStar.cpp" 
        "src/Pathfinding/PathNode.h" 
        "src/Pathfinding/PathNode.cpp" 
        "src/Room/RoomManager.cpp" 
        "src/Room/RoomManager.h" 
        "src/Room/PlayerRoomSpawner.h" 
        "src/Room/PlayerRoomSpawner.cpp" 
        "src/GameObjects/Interactable/EditorInteractable.h"
        "src/GameObjects/Interactable/EditorInteractable.cpp"
        "src/GameObjects/Interactable/RoomTransitionInteractable.cpp" 
        "src/GameObjects/Interactable/RoomTransitionInteractable.h"  
        "src/Room/Rooms/RoomJail.h" "src/Room/Rooms/RoomJail.cpp" 
        "src/Room/Rooms/Beach/RoomBeach.h" "src/Room/Rooms/Beach/RoomBeach.cpp"   "src/GameObjects/Inventory.h" "src/GameObjects/Inventory.cpp" "src/GameObjects/Item.h" "src/GameObjects/Item.cpp" "src/GameObjects/Interactable/ItemAudioInteractable.h" "src/GameObjects/Interactable/ItemAudioInteractable.cpp" "src/Room/Rooms/Beach/RoomBeachDecide.h" "src/Room/Rooms/Beach/RoomBeachDecide.cpp" "src/Room/Rooms/Beach/RoomBeachDocks.h" "src/Room/Rooms/Beach/RoomBeachDocks.cpp" "src/Room/Rooms/Beach/RoomBeachMansion.h" "src/Room/Rooms/Beach/RoomBeachMansion.cpp" "src/Room/Rooms/Mansion/RoomMansionDecide.h" "src/Room/Rooms/Mansion/RoomMansionDecide.cpp" "src/Room/Rooms/Mansion/RoomMansionCorridor.h" "src/Room/Rooms/Mansion/RoomMansionCorridor.cpp" "src/Room/Rooms/Mansion/RoomMansionGarage.h" "src/Room/Rooms/Mansion/RoomMansionGarage.cpp" "src/Room/Rooms/Mansion/RoomMansionDining.h" "src/Room/Rooms/Mansion/RoomMansionDining.cpp" "src/Room/Rooms/Mansion/RoomMansionToilet.h" "src/Room/Rooms/Mansion/RoomMansionToilet.cpp" "src/Room/Rooms/Mansion/RoomMansionBase.h" "src/Room/Rooms/Mansion/RoomMansionBase.cpp" "src/GameObjects/Interactable/PowerInteractable.h" "src/GameObjects/Interactable/PowerInteractable.cpp" "src/GameObjects/Interactable/FirePlaceInteractable.h" "src/GameObjects/Interactable/FirePlaceInteractable.cpp")
add_executable(PointAndClickSFML ${SOURCE_FILES} "src/Core/main.cpp")  # Names the application and tells compiler which source files to use

target_link_libraries(PointAndClickSFML PRIVATE nlohmann_json::nlohmann_json sfml-graphics sfml-window sfml-system sfml-network sfml-audio) # Links the SFML libraries we need to our application
target_compile_features(PointAndClickSFML PRIVATE cxx_std_20)  # Defines which standard of C++ the compiler should use

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin/Data/)  # Copies data from source directory to build directory (so the executable can access it)

if(WIN32)
    add_custom_command(
        TARGET PointAndClickSFML
        COMMENT "Copy OpenAL DLL to build directory so app can have sound"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PointAndClickSFML>
        VERBATIM)
endif()
