#pragma once

#define CONTRACT_NAME "wcwwallettestnet"

#include <string>
#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/singleton.hpp>
#include <eosio/crypto.hpp>

using namespace eosio;
using namespace std;

#include <tables/structs.hpp>
#include <tables/config.hpp>

#include "utils.hpp"

using namespace utils;

CONTRACT wcwwallettestnet : public contract {
public:
    using contract::contract;
    ACTION init();
    ACTION setwalletkey(public_key key);
    ACTION regaccount(name wallet);
    
private:

    config_t config = config_t(_self, _self.value);
};
