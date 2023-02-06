
#pragma once

struct [[eosio::table, eosio::contract(CONTRACT_NAME)]] config_s {
    name wallet_suffix = "wamtn"_n;
    public_key wallet_key;
    uint32_t ram_bytes = 5120;
    asset stake_net = asset(50000000, symbol("WAX", 8));
    asset stake_cpu = asset(100000000, symbol("WAX", 8));
    asset faucet_amount = asset(1000000000, symbol("WAX", 8));
    string faucet_memo = string("WAX Cloud Wallet testnet faucet. Check https://all-access.waxtest.net for more info");
    // explicit serialization macro is not necessary, used here only to improve compilation time
    // EOSLIB_SERIALIZE( config_s, (wallet_index) )
};
typedef singleton <name("config"), config_s> config_t;
typedef multi_index <name("config"), config_s> config_t_for_abi;