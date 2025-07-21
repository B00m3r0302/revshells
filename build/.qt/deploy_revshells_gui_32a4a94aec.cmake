include(/home/kali/Documents/revshells/build/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/revshells-gui-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/kali/Documents/revshells/build/src/ui/revshells-gui
    GENERATE_QT_CONF
)
