include("/home/kali/Documents/real_revshells/revshells/build/Desktop_Qt_6_9_1-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/revshells-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/kali/Documents/real_revshells/revshells/build/Desktop_Qt_6_9_1-Debug/revshells
    GENERATE_QT_CONF
)
