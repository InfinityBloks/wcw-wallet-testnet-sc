project(wcwwallettestnet)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( wcwwallettestnet wcwwallettestnet wcwwallettestnet.cpp )
target_include_directories( wcwwallettestnet PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( wcwwallettestnet ${CMAKE_SOURCE_DIR}/../ricardian )