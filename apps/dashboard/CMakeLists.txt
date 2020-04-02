
corrade_add_resource(TextExample_RESOURCES resources.conf)

add_executable(dashboard
        main.cpp
        base_ui_plane.cpp
        base_ui_plane.h
        ${TextExample_RESOURCES})

target_include_directories(dashboard
        PUBLIC
        include)

target_link_libraries(dashboard
        Magnum::Magnum
        Magnum::Application
        Magnum::GL
        Magnum::Shaders
        Magnum::Text
        MagnumPlugins::FreeTypeFont
        MagnumExtras::Ui)
