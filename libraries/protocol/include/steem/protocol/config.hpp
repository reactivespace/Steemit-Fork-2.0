/*
 * Copyright (c) 2016 Cloutit, Inc., and contributors.
 */
#pragma once
#include <clout/protocol/hardfork.hpp>

// WARNING!
// Every symbol defined here needs to be handled appropriately in get_config.cpp
// This is checked by get_config_check.sh called from Dockerfile

#ifdef IS_TEST_NET
#define CLOUT_BLOCKCHAIN_VERSION              ( version(0, 23, 0) )
#define CLOUT_NETWORK_TYPE                    "testnet"

#define CLOUT_INIT_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("init_key"))))
#define CLOUT_INIT_PUBLIC_KEY_STR             (std::string( clout::protocol::public_key_type(CLOUT_INIT_PRIVATE_KEY.get_public_key()) ))
#define CLOUT_CHAIN_ID (fc::sha256::hash("testnet"))
#define CLOUT_ADDRESS_PREFIX                  "TST"

#define CLOUT_GENESIS_TIME                    (fc::time_point_sec(1451606400))
#define CLOUT_MINING_TIME                     (fc::time_point_sec(1451606400))
#define CLOUT_CASHOUT_WINDOW_SECONDS          (60*60) /// 1 hr
#define CLOUT_CASHOUT_WINDOW_SECONDS_PRE_HF12 (CLOUT_CASHOUT_WINDOW_SECONDS)
#define CLOUT_CASHOUT_WINDOW_SECONDS_PRE_HF17 (CLOUT_CASHOUT_WINDOW_SECONDS)
#define CLOUT_SECOND_CASHOUT_WINDOW           (60*60*24*3) /// 3 days
#define CLOUT_MAX_CASHOUT_WINDOW_SECONDS      (60*60*24) /// 1 day
#define CLOUT_UPVOTE_LOCKOUT_HF7              (fc::minutes(1))
#define CLOUT_UPVOTE_LOCKOUT_SECONDS          (60*5)    /// 5 minutes
#define CLOUT_UPVOTE_LOCKOUT_HF17             (fc::minutes(5))


#define CLOUT_MIN_ACCOUNT_CREATION_FEE          0
#define CLOUT_MAX_ACCOUNT_CREATION_FEE          int64_t(1000000000)

#define CLOUT_OWNER_AUTH_RECOVERY_PERIOD                  fc::seconds(60)
#define CLOUT_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  fc::seconds(12)
#define CLOUT_OWNER_UPDATE_LIMIT                          fc::seconds(0)
#define CLOUT_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM 1

#define CLOUT_INIT_SUPPLY                     (int64_t( 250 ) * int64_t( 1000000 ) * int64_t( 1000 ))
#define CLOUT_CBD_INIT_SUPPLY                 (int64_t( 7 ) * int64_t( 1000000 ) * int64_t( 1000 ))

/// Allows to limit number of total produced blocks.
#define TESTNET_BLOCK_LIMIT                   (3000000)

#else // IS LIVE CLOUT NETWORK

#define CLOUT_BLOCKCHAIN_VERSION              ( version(0, 22, 1) )
#define CLOUT_NETWORK_TYPE                    "mainnet"

#define CLOUT_INIT_PUBLIC_KEY_STR             "STM8GC13uCZbP44HzMLV6zPZGwVQ8Nt4Kji8PapsPiNq1BK153XTX"
#define CLOUT_CHAIN_ID fc::sha256()
#define CLOUT_ADDRESS_PREFIX                  "STM"

#define CLOUT_GENESIS_TIME                    (fc::time_point_sec(1458835200))
#define CLOUT_MINING_TIME                     (fc::time_point_sec(1458838800))
#define CLOUT_CASHOUT_WINDOW_SECONDS_PRE_HF12 (60*60*24)    /// 1 day
#define CLOUT_CASHOUT_WINDOW_SECONDS_PRE_HF17 (60*60*12)    /// 12 hours
#define CLOUT_CASHOUT_WINDOW_SECONDS          (60*60*24*7)  /// 7 days
#define CLOUT_SECOND_CASHOUT_WINDOW           (60*60*24*30) /// 30 days
#define CLOUT_MAX_CASHOUT_WINDOW_SECONDS      (60*60*24*14) /// 2 weeks
#define CLOUT_UPVOTE_LOCKOUT_HF7              (fc::minutes(1))
#define CLOUT_UPVOTE_LOCKOUT_SECONDS          (60*60*12)    /// 12 hours
#define CLOUT_UPVOTE_LOCKOUT_HF17             (fc::hours(12))

#define CLOUT_MIN_ACCOUNT_CREATION_FEE           1
#define CLOUT_MAX_ACCOUNT_CREATION_FEE           int64_t(1000000000)

#define CLOUT_OWNER_AUTH_RECOVERY_PERIOD                  fc::days(30)
#define CLOUT_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  fc::days(1)
#define CLOUT_OWNER_UPDATE_LIMIT                          fc::minutes(60)
#define CLOUT_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM 3186477

#define CLOUT_INIT_SUPPLY                     int64_t(0)
#define CLOUT_CBD_INIT_SUPPLY                 int64_t(0)

#endif

/// Version format string.  The Clout binary will refuse to load a state file where this does not match the built-in version.
#define CLOUT_DB_FORMAT_VERSION               "1"

#define VESTS_SYMBOL  (clout::protocol::asset_symbol_type::from_asset_num( CLOUT_ASSET_NUM_VESTS ) )
#define CLOUT_SYMBOL  (clout::protocol::asset_symbol_type::from_asset_num( CLOUT_ASSET_NUM_CLOUT ) )
#define CBD_SYMBOL    (clout::protocol::asset_symbol_type::from_asset_num( CLOUT_ASSET_NUM_CBD ) )

#define CLOUT_BLOCKCHAIN_HARDFORK_VERSION     ( hardfork_version( CLOUT_BLOCKCHAIN_VERSION ) )

#define CLOUT_100_PERCENT                     10000
#define CLOUT_1_PERCENT                       (CLOUT_100_PERCENT/100)

#define CLOUT_BLOCK_INTERVAL                  3
#define CLOUT_BLOCKS_PER_YEAR                 (365*24*60*60/CLOUT_BLOCK_INTERVAL)
#define CLOUT_BLOCKS_PER_DAY                  (24*60*60/CLOUT_BLOCK_INTERVAL)
#define CLOUT_START_VESTING_BLOCK             (CLOUT_BLOCKS_PER_DAY * 7)
#define CLOUT_START_MINER_VOTING_BLOCK        (CLOUT_BLOCKS_PER_DAY * 30)

#define CLOUT_INIT_MINER_NAME                 "initminer"
#define CLOUT_NUM_INIT_MINERS                 1
#define CLOUT_INIT_TIME                       (fc::time_point_sec());

#define CLOUT_MAX_WITNESSES                   21

#define CLOUT_MAX_VOTED_WITNESSES_HF0         19
#define CLOUT_MAX_MINER_WITNESSES_HF0         1
#define CLOUT_MAX_RUNNER_WITNESSES_HF0        1

#define CLOUT_MAX_VOTED_WITNESSES_HF17        20
#define CLOUT_MAX_MINER_WITNESSES_HF17        0
#define CLOUT_MAX_RUNNER_WITNESSES_HF17       1

#define CLOUT_HARDFORK_REQUIRED_WITNESSES     17 // 17 of the 21 dpos witnesses (20 elected and 1 virtual time) required for hardfork. This guarantees 75% participation on all subsequent rounds.
#define CLOUT_MAX_TIME_UNTIL_EXPIRATION       (60*60) // seconds,  aka: 1 hour
#define CLOUT_MAX_MEMO_SIZE                   2048
#define CLOUT_MAX_PROXY_RECURSION_DEPTH       4
#define CLOUT_VESTING_WITHDRAW_INTERVALS_PRE_HF_16 104
#define CLOUT_VESTING_WITHDRAW_INTERVALS      13
#define CLOUT_VESTING_WITHDRAW_INTERVAL_SECONDS (60*60*24*7) /// 1 week per interval
#define CLOUT_MAX_WITHDRAW_ROUTES             10
#define CLOUT_SAVINGS_WITHDRAW_TIME        	(fc::days(3))
#define CLOUT_SAVINGS_WITHDRAW_REQUEST_LIMIT  100
#define CLOUT_VOTING_MANA_REGENERATION_SECONDS (5*60*60*24) // 5 day
#define CLOUT_MAX_VOTE_CHANGES                5
#define CLOUT_REVERSE_AUCTION_WINDOW_SECONDS_HF6 (60*30) /// 30 minutes
#define CLOUT_REVERSE_AUCTION_WINDOW_SECONDS_HF20 (60*15) /// 15 minutes
#define CLOUT_REVERSE_AUCTION_WINDOW_SECONDS_HF21 (60*5) /// 5 minutes
#define CLOUT_MIN_VOTE_INTERVAL_SEC           3
#define CLOUT_VOTE_DUST_THRESHOLD             (50000000)
#define CLOUT_DOWNVOTE_POOL_PERCENT_HF21      (25*CLOUT_1_PERCENT)

#define CLOUT_MIN_ROOT_COMMENT_INTERVAL       (fc::seconds(60*5)) // 5 minutes
#define CLOUT_MIN_REPLY_INTERVAL              (fc::seconds(20)) // 20 seconds
#define CLOUT_MIN_REPLY_INTERVAL_HF20         (fc::seconds(3)) // 3 seconds
#define CLOUT_MIN_COMMENT_EDIT_INTERVAL       (fc::seconds(3)) // 3 seconds
#define CLOUT_POST_AVERAGE_WINDOW             (60*60*24u) // 1 day
#define CLOUT_POST_WEIGHT_CONSTANT            (uint64_t(4*CLOUT_100_PERCENT) * (4*CLOUT_100_PERCENT))// (4*CLOUT_100_PERCENT) -> 2 posts per 1 days, average 1 every 12 hours

#define CLOUT_MAX_ACCOUNT_WITNESS_VOTES       30

#define CLOUT_DEFAULT_CBD_INTEREST_RATE       (10*CLOUT_1_PERCENT) ///< 10% APR

#define CLOUT_INFLATION_RATE_START_PERCENT    (978) // Fixes block 7,000,000 to 9.5%
#define CLOUT_INFLATION_RATE_STOP_PERCENT     (95) // 0.95%
#define CLOUT_INFLATION_NARROWING_PERIOD      (250000) // Narrow 0.01% every 250k blocks
#define CLOUT_CONTENT_REWARD_PERCENT_HF16     (75*CLOUT_1_PERCENT) //75% of inflation, 7.125% inflation
#define CLOUT_VESTING_FUND_PERCENT_HF16       (15*CLOUT_1_PERCENT) //15% of inflation, 1.425% inflation
#define CLOUT_PROPOSAL_FUND_PERCENT_HF0       (0)

#define CLOUT_CONTENT_REWARD_PERCENT_HF21     (65*CLOUT_1_PERCENT)
#define CLOUT_PROPOSAL_FUND_PERCENT_HF21      (10*CLOUT_1_PERCENT)

#define CLOUT_HF21_CONVERGENT_LINEAR_RECENT_CLAIMS (fc::uint128_t(0,503600561838938636ull))
#define CLOUT_CONTENT_CONSTANT_HF21           (fc::uint128_t(0,2000000000000ull))

#define CLOUT_MINER_PAY_PERCENT               (CLOUT_1_PERCENT) // 1%
#define CLOUT_MAX_RATION_DECAY_RATE           (1000000)

#define CLOUT_BANDWIDTH_AVERAGE_WINDOW_SECONDS (60*60*24*7) ///< 1 week
#define CLOUT_BANDWIDTH_PRECISION             (uint64_t(1000000)) ///< 1 million
#define CLOUT_MAX_COMMENT_DEPTH_PRE_HF17      6
#define CLOUT_MAX_COMMENT_DEPTH               0xffff // 64k
#define CLOUT_SOFT_MAX_COMMENT_DEPTH          0xff // 255

#define CLOUT_MAX_RESERVE_RATIO               (20000)

#define CLOUT_CREATE_ACCOUNT_WITH_CLOUT_MODIFIER 30
#define CLOUT_CREATE_ACCOUNT_DELEGATION_RATIO    5
#define CLOUT_CREATE_ACCOUNT_DELEGATION_TIME     fc::days(30)

#define CLOUT_MINING_REWARD                   asset( 1000, CLOUT_SYMBOL )
#define CLOUT_EQUIHASH_N                      140
#define CLOUT_EQUIHASH_K                      6

#define CLOUT_LIQUIDITY_TIMEOUT_SEC           (fc::seconds(60*60*24*7)) // After one week volume is set to 0
#define CLOUT_MIN_LIQUIDITY_REWARD_PERIOD_SEC (fc::seconds(60)) // 1 minute required on books to receive volume
#define CLOUT_LIQUIDITY_REWARD_PERIOD_SEC     (60*60)
#define CLOUT_LIQUIDITY_REWARD_BLOCKS         (CLOUT_LIQUIDITY_REWARD_PERIOD_SEC/CLOUT_BLOCK_INTERVAL)
#define CLOUT_MIN_LIQUIDITY_REWARD            (asset( 1000*CLOUT_LIQUIDITY_REWARD_BLOCKS, CLOUT_SYMBOL )) // Minumum reward to be paid out to liquidity providers
#define CLOUT_MIN_CONTENT_REWARD              CLOUT_MINING_REWARD
#define CLOUT_MIN_CURATE_REWARD               CLOUT_MINING_REWARD
#define CLOUT_MIN_PRODUCER_REWARD             CLOUT_MINING_REWARD
#define CLOUT_MIN_POW_REWARD                  CLOUT_MINING_REWARD

#define CLOUT_ACTIVE_CHALLENGE_FEE            asset( 2000, CLOUT_SYMBOL )
#define CLOUT_OWNER_CHALLENGE_FEE             asset( 30000, CLOUT_SYMBOL )
#define CLOUT_ACTIVE_CHALLENGE_COOLDOWN       fc::days(1)
#define CLOUT_OWNER_CHALLENGE_COOLDOWN        fc::days(1)

#define CLOUT_POST_REWARD_FUND_NAME           ("post")
#define CLOUT_COMMENT_REWARD_FUND_NAME        ("comment")
#define CLOUT_RECENT_RSHARES_DECAY_TIME_HF17    (fc::days(30))
#define CLOUT_RECENT_RSHARES_DECAY_TIME_HF19    (fc::days(15))
#define CLOUT_CONTENT_CONSTANT_HF0            (uint128_t(uint64_t(2000000000000ll)))
// note, if redefining these constants make sure calculate_claims doesn't overflow

// 5ccc e802 de5f
// int(expm1( log1p( 1 ) / BLOCKS_PER_YEAR ) * 2**CLOUT_APR_PERCENT_SHIFT_PER_BLOCK / 100000 + 0.5)
// we use 100000 here instead of 10000 because we end up creating an additional 9x for vesting
#define CLOUT_APR_PERCENT_MULTIPLY_PER_BLOCK          ( (uint64_t( 0x5ccc ) << 0x20) \
                                                        | (uint64_t( 0xe802 ) << 0x10) \
                                                        | (uint64_t( 0xde5f )        ) \
                                                        )
// chosen to be the maximal value such that CLOUT_APR_PERCENT_MULTIPLY_PER_BLOCK * 2**64 * 100000 < 2**128
#define CLOUT_APR_PERCENT_SHIFT_PER_BLOCK             87

#define CLOUT_APR_PERCENT_MULTIPLY_PER_ROUND          ( (uint64_t( 0x79cc ) << 0x20 ) \
                                                        | (uint64_t( 0xf5c7 ) << 0x10 ) \
                                                        | (uint64_t( 0x3480 )         ) \
                                                        )

#define CLOUT_APR_PERCENT_SHIFT_PER_ROUND             83

// We have different constants for hourly rewards
// i.e. hex(int(math.expm1( math.log1p( 1 ) / HOURS_PER_YEAR ) * 2**CLOUT_APR_PERCENT_SHIFT_PER_HOUR / 100000 + 0.5))
#define CLOUT_APR_PERCENT_MULTIPLY_PER_HOUR           ( (uint64_t( 0x6cc1 ) << 0x20) \
                                                        | (uint64_t( 0x39a1 ) << 0x10) \
                                                        | (uint64_t( 0x5cbd )        ) \
                                                        )

// chosen to be the maximal value such that CLOUT_APR_PERCENT_MULTIPLY_PER_HOUR * 2**64 * 100000 < 2**128
#define CLOUT_APR_PERCENT_SHIFT_PER_HOUR              77

// These constants add up to GRAPHENE_100_PERCENT.  Each GRAPHENE_1_PERCENT is equivalent to 1% per year APY
// *including the corresponding 9x vesting rewards*
#define CLOUT_CURATE_APR_PERCENT              3875
#define CLOUT_CONTENT_APR_PERCENT             3875
#define CLOUT_LIQUIDITY_APR_PERCENT            750
#define CLOUT_PRODUCER_APR_PERCENT             750
#define CLOUT_POW_APR_PERCENT                  750

#define CLOUT_MIN_PAYOUT_CBD                  (asset(20,CBD_SYMBOL))

#define CLOUT_CBD_STOP_PERCENT_HF14           (5*CLOUT_1_PERCENT ) // Stop printing CBD at 5% Market Cap
#define CLOUT_CBD_STOP_PERCENT_HF20           (10*CLOUT_1_PERCENT ) // Stop printing CBD at 10% Market Cap
#define CLOUT_CBD_START_PERCENT_HF14          (2*CLOUT_1_PERCENT) // Start reducing printing of CBD at 2% Market Cap
#define CLOUT_CBD_START_PERCENT_HF20          (9*CLOUT_1_PERCENT) // Start reducing printing of CBD at 9% Market Cap

#define CLOUT_MIN_ACCOUNT_NAME_LENGTH          3
#define CLOUT_MAX_ACCOUNT_NAME_LENGTH         16

#define CLOUT_MIN_PERMLINK_LENGTH             0
#define CLOUT_MAX_PERMLINK_LENGTH             256
#define CLOUT_MAX_WITNESS_URL_LENGTH          2048

#define CLOUT_MAX_SHARE_SUPPLY                int64_t(1000000000000000ll)
#define CLOUT_MAX_SATOSHIS                    int64_t(4611686018427387903ll)
#define CLOUT_MAX_SIG_CHECK_DEPTH             2
#define CLOUT_MAX_SIG_CHECK_ACCOUNTS          125

#define CLOUT_MIN_TRANSACTION_SIZE_LIMIT      1024
#define CLOUT_SECONDS_PER_YEAR                (uint64_t(60*60*24*365ll))

#define CLOUT_CBD_INTEREST_COMPOUND_INTERVAL_SEC  (60*60*24*30)
#define CLOUT_MAX_TRANSACTION_SIZE            (1024*64)
#define CLOUT_MIN_BLOCK_SIZE_LIMIT            (CLOUT_MAX_TRANSACTION_SIZE)
#define CLOUT_MAX_BLOCK_SIZE                  (CLOUT_MAX_TRANSACTION_SIZE*CLOUT_BLOCK_INTERVAL*2000)
#define CLOUT_SOFT_MAX_BLOCK_SIZE             (2*1024*1024)
#define CLOUT_MIN_BLOCK_SIZE                  115
#define CLOUT_BLOCKS_PER_HOUR                 (60*60/CLOUT_BLOCK_INTERVAL)
#define CLOUT_FEED_INTERVAL_BLOCKS            (CLOUT_BLOCKS_PER_HOUR)
#define CLOUT_FEED_HISTORY_WINDOW_PRE_HF_16   (24*7) /// 7 days * 24 hours per day
#define CLOUT_FEED_HISTORY_WINDOW             (12*7) // 3.5 days
#define CLOUT_MAX_FEED_AGE_SECONDS            (60*60*24*7) // 7 days
#define CLOUT_MIN_FEEDS                       (CLOUT_MAX_WITNESSES/3) /// protects the network from conversions before price has been established
#define CLOUT_CONVERSION_DELAY_PRE_HF_16      (fc::days(7))
#define CLOUT_CONVERSION_DELAY                (fc::hours(CLOUT_FEED_HISTORY_WINDOW)) //3.5 day conversion

#define CLOUT_MIN_UNDO_HISTORY                10
#define CLOUT_MAX_UNDO_HISTORY                10000

#define CLOUT_MIN_TRANSACTION_EXPIRATION_LIMIT (CLOUT_BLOCK_INTERVAL * 5) // 5 transactions per block
#define CLOUT_BLOCKCHAIN_PRECISION            uint64_t( 1000 )

#define CLOUT_BLOCKCHAIN_PRECISION_DIGITS     3
#define CLOUT_MAX_INSTANCE_ID                 (uint64_t(-1)>>16)
/** NOTE: making this a power of 2 (say 2^15) would greatly accelerate fee calcs */
#define CLOUT_MAX_AUTHORITY_MEMBERSHIP        40
#define CLOUT_MAX_ASSET_WHITELIST_AUTHORITIES 10
#define CLOUT_MAX_URL_LENGTH                  127

#define CLOUT_IRREVERSIBLE_THRESHOLD          (75 * CLOUT_1_PERCENT)

#define CLOUT_VIRTUAL_SCHEDULE_LAP_LENGTH  ( fc::uint128(uint64_t(-1)) )
#define CLOUT_VIRTUAL_SCHEDULE_LAP_LENGTH2 ( fc::uint128::max_value() )

#define CLOUT_INITIAL_VOTE_POWER_RATE (40)
#define CLOUT_REDUCED_VOTE_POWER_RATE (10)
#define CLOUT_VOTES_PER_PERIOD_SMT_HF (50)

#define CLOUT_MAX_LIMIT_ORDER_EXPIRATION     (60*60*24*28) // 28 days
#define CLOUT_DELEGATION_RETURN_PERIOD_HF0   (CLOUT_CASHOUT_WINDOW_SECONDS)
#define CLOUT_DELEGATION_RETURN_PERIOD_HF20  (CLOUT_VOTING_MANA_REGENERATION_SECONDS)

#define CLOUT_RD_MIN_DECAY_BITS               6
#define CLOUT_RD_MAX_DECAY_BITS              32
#define CLOUT_RD_DECAY_DENOM_SHIFT           36
#define CLOUT_RD_MAX_POOL_BITS               64
#define CLOUT_RD_MAX_BUDGET_1                ((uint64_t(1) << (CLOUT_RD_MAX_POOL_BITS + CLOUT_RD_MIN_DECAY_BITS - CLOUT_RD_DECAY_DENOM_SHIFT))-1)
#define CLOUT_RD_MAX_BUDGET_2                ((uint64_t(1) << (64-CLOUT_RD_DECAY_DENOM_SHIFT))-1)
#define CLOUT_RD_MAX_BUDGET_3                (uint64_t( std::numeric_limits<int32_t>::max() ))
#define CLOUT_RD_MAX_BUDGET                  (int32_t( std::min( { CLOUT_RD_MAX_BUDGET_1, CLOUT_RD_MAX_BUDGET_2, CLOUT_RD_MAX_BUDGET_3 } )) )
#define CLOUT_RD_MIN_DECAY                   (uint32_t(1) << CLOUT_RD_MIN_DECAY_BITS)
#define CLOUT_RD_MIN_BUDGET                  1
#define CLOUT_RD_MAX_DECAY                   (uint32_t(0xFFFFFFFF))

#define CLOUT_ACCOUNT_SUBSIDY_PRECISION      (CLOUT_100_PERCENT)

// We want the global subsidy to run out first in normal (Poisson)
// conditions, so we boost the per-witness subsidy a little.
#define CLOUT_WITNESS_SUBSIDY_BUDGET_PERCENT (125 * CLOUT_1_PERCENT)

// Since witness decay only procs once per round, multiplying the decay
// constant by the number of witnesses means the per-witness pools have
// the same effective decay rate in real-time terms.
#define CLOUT_WITNESS_SUBSIDY_DECAY_PERCENT  (CLOUT_MAX_WITNESSES * CLOUT_100_PERCENT)

// 347321 corresponds to a 5-day halflife
#define CLOUT_DEFAULT_ACCOUNT_SUBSIDY_DECAY  (347321)
// Default rate is 0.5 accounts per block
#define CLOUT_DEFAULT_ACCOUNT_SUBSIDY_BUDGET (797)
#define CLOUT_DECAY_BACKSTOP_PERCENT         (90 * CLOUT_1_PERCENT)

#define CLOUT_BLOCK_GENERATION_POSTPONED_TX_LIMIT 5
#define CLOUT_PENDING_TRANSACTION_EXECUTION_LIMIT fc::milliseconds(200)

#define CLOUT_CUSTOM_OP_ID_MAX_LENGTH        (32)
#define CLOUT_CUSTOM_OP_DATA_MAX_LENGTH      (8192)
#define CLOUT_BENEFICIARY_LIMIT              (128)
#define CLOUT_COMMENT_TITLE_LIMIT            (256)

/**
 *  Reserved Account IDs with special meaning
 */
///@{
/// Represents the current witnesses
#define CLOUT_MINER_ACCOUNT                   "miners"
/// Represents the canonical account with NO authority (nobody can access funds in null account)
#define CLOUT_NULL_ACCOUNT                    "null"
/// Represents the canonical account with WILDCARD authority (anybody can access funds in temp account)
#define CLOUT_TEMP_ACCOUNT                    "temp"
/// Represents the canonical account for specifying you will vote for directly (as opposed to a proxy)
#define CLOUT_PROXY_TO_SELF_ACCOUNT           ""
/// Represents the canonical root post parent account
#define CLOUT_ROOT_POST_PARENT                (account_name_type())
/// Represents the account with NO authority which holds resources for payouts according to given proposals
#define CLOUT_TREASURY_ACCOUNT                "clout.dao"
///@}

/// CLOUT PROPOSAL SYSTEM support

#define CLOUT_TREASURY_FEE                         (10 * CLOUT_BLOCKCHAIN_PRECISION)
#define CLOUT_PROPOSAL_MAINTENANCE_PERIOD          3600
#define CLOUT_PROPOSAL_MAINTENANCE_CLEANUP         (60*60*24*1) /// 1 day
#define CLOUT_PROPOSAL_SUBJECT_MAX_LENGTH          80
/// Max number of IDs passed at once to the update_proposal_voter_operation or remove_proposal_operation.
#define CLOUT_PROPOSAL_MAX_IDS_NUMBER              5


#define SMT_MAX_VOTABLE_ASSETS 2
#define SMT_VESTING_WITHDRAW_INTERVAL_SECONDS   (60*60*24*7) /// 1 week per interval
#define SMT_UPVOTE_LOCKOUT                      (60*60*12)   /// 12 hours
#define SMT_EMISSION_MIN_INTERVAL_SECONDS       (60*60*6)    /// 6 hours
#define SMT_EMIT_INDEFINITELY                   (std::numeric_limits<uint32_t>::max())
#define SMT_MAX_NOMINAL_VOTES_PER_DAY           (1000)
#define SMT_MAX_VOTES_PER_REGENERATION          ((SMT_MAX_NOMINAL_VOTES_PER_DAY * SMT_VESTING_WITHDRAW_INTERVAL_SECONDS) / 86400)
#define SMT_DEFAULT_VOTES_PER_REGEN_PERIOD      (50)
#define SMT_DEFAULT_PERCENT_CURATION_REWARDS    (25 * CLOUT_1_PERCENT)
#define SMT_INITIAL_VESTING_PER_UNIT            (1000000)
#define SMT_BALLAST_SUPPLY_PERCENT              (CLOUT_1_PERCENT/10)
#define SMT_MAX_ICO_TIERS                       (10)
