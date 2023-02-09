#include <wcwwallettestnet.hpp>

ACTION wcwwallettestnet::init() {
    require_auth(_self);
    rule_check(!config.exists(), "Smart contract already init");
    config.get_or_create(_self, config_s{});
}

ACTION wcwwallettestnet::setwalletkey(public_key key) {
    require_auth(_self);
    rule_check(config.exists(), "Init smart contract first");
    auto configs = config.get();
    configs.wallet_key = key;
    
    config.set(configs, _self);
}

ACTION wcwwallettestnet::regaccount(name wallet, public_key key) {
    require_auth(_self);
    rule_check(config.exists(), "Init smart contract first");
    auto configs = config.get();
    rule_check(configs.wallet_key != public_key(), "Must set wallet key first");
    const string VALID_SUFFIX = "." + configs.wallet_suffix.to_string();
    string wallet_str = wallet.to_string();
    auto is_valid_wallet = wallet_str.size() > VALID_SUFFIX.size() && ends_with(wallet_str, VALID_SUFFIX);
    rule_check(is_valid_wallet, ("Wallet must end with " + std::string { VALID_SUFFIX }).c_str());
    auto not_exists_wallet = !is_account(wallet);
    rule_check(not_exists_wallet, ("Wallet " + wallet_str + " already exists").c_str());
    permission_level_weight managed_perm = {.permission = {"manage.waxtn"_n, "active"_n}, .weight = 1};
    permission_level_weight cosign_perm = {.permission = {"manage.waxtn"_n, "cosign"_n}, .weight = 1};
    // key_weight wallet_key = {.key = configs.wallet_key, .weight = 1};
    key_weight wallet_key = {.key = key, .weight = 1};
    authority owner = {.threshold = 1, .keys = {}, .accounts = {managed_perm}, .waits = {}};
    authority active = {.threshold = 2, .keys = {wallet_key}, .accounts = {cosign_perm}, .waits = {}};
    
    //create account
    action(permission_level{ "wamtn"_n, "newaccount"_n }, "eosio"_n, "newaccount"_n,
          std::make_tuple( "wamtn"_n, wallet, owner, active) ).send();
    
    //buy ram
    action(
        {"wamtn"_n, "newaccount"_n}, "eosio"_n, "buyrambytes"_n,
        make_tuple(
            "wamtn"_n,
            wallet,
            configs.ram_bytes
        )
    ).send();

    //stake CPU & NET
    action(
        {"wamtn"_n, "newaccount"_n}, "eosio"_n, "delegatebw"_n,
        make_tuple(
            "wamtn"_n,
            wallet,
            configs.stake_net,
            configs.stake_cpu,
            true
        )
    ).send();

    //wax faucet
    action(
        {"wamtn"_n, "newaccount"_n}, "eosio.token"_n, "transfer"_n,
        make_tuple(
            "wamtn"_n,
            wallet,
            configs.faucet_amount,
            configs.faucet_memo
        )
    ).send();
}