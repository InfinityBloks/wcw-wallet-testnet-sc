struct pb_key {
    uint8_t        type;
    array<unsigned char,33> data;
};

struct permission_level_weight {
    permission_level permission;
    uint16_t weight;
};

struct wait_weight {
    uint32_t wait_sec;
    uint16_t weight;
};

struct key_weight {
    public_key key;
    uint16_t weight;
};

struct authority {
    uint32_t threshold = 0;
    vector<key_weight> keys;
    vector<permission_level_weight> accounts;
    vector<wait_weight> waits;
};