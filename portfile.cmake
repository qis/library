vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_configure_cmake(SOURCE_PATH ${CURRENT_PORT_DIR}
  PREFER_NINJA OPTIONS_DEBUG -DINSTALL_HEADERS=OFF)

vcpkg_install_cmake()
vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/${PORT})
vcpkg_copy_pdbs()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/share)
file(INSTALL ${CURRENT_PORT_DIR}/license.txt DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
