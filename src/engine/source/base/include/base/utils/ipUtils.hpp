#ifndef _IP_UTILS_H
#define _IP_UTILS_H

#include <array>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string_view>
#include <unordered_map>

namespace utils::ip
{

constexpr std::array<std::string_view, 256> makeIanaByCode()
{
    std::array<std::string_view, 256> a {};
    a[0] = "hopopt";
    a[1] = "icmp";
    a[2] = "igmp";
    a[3] = "ggp";
    a[4] = "ipv4";
    a[5] = "st";
    a[6] = "tcp";
    a[7] = "cbt";
    a[8] = "egp";
    a[9] = "igp";
    a[10] = "bbn-rcc-mon";
    a[11] = "nvp-ii";
    a[12] = "pup";
    a[13] = "argus";
    a[14] = "emcon";
    a[15] = "xnet";
    a[16] = "chaos";
    a[17] = "udp";
    a[18] = "mux";
    a[19] = "dcn-meas";
    a[20] = "hmp";
    a[21] = "prm";
    a[22] = "xns-idp";
    a[23] = "trunk-1";
    a[24] = "trunk-2";
    a[25] = "leaf-1";
    a[26] = "leaf-2";
    a[27] = "rdp";
    a[28] = "irtp";
    a[29] = "iso-tp4";
    a[30] = "netblt";
    a[31] = "mfe-nsp";
    a[32] = "merit-inp";
    a[33] = "dccp";
    a[34] = "3pc";
    a[35] = "idpr";
    a[36] = "xtp";
    a[37] = "ddp";
    a[38] = "idpr-cmtp";
    a[39] = "tp++";
    a[40] = "il";
    a[41] = "ipv6";
    a[42] = "sdrp";
    a[43] = "ipv6-route";
    a[44] = "ipv6-frag";
    a[45] = "idrp";
    a[46] = "rsvp";
    a[47] = "gre";
    a[48] = "dsr";
    a[49] = "bna";
    a[50] = "esp";
    a[51] = "ah";
    a[52] = "i-nlsp";
    a[53] = "swipe";
    a[54] = "narp";
    a[55] = "min-ipv4";
    a[56] = "tlsp";
    a[57] = "skip";
    a[58] = "ipv6-icmp";
    a[59] = "ipv6-nonxt";
    a[60] = "ipv6-opts";
    a[62] = "cftp";
    a[64] = "sat-expak";
    a[65] = "kryptolan";
    a[66] = "rvd";
    a[67] = "ippc";
    a[69] = "sat-mon";
    a[70] = "visa";
    a[71] = "ipcv";
    a[72] = "cpnx";
    a[73] = "cphb";
    a[74] = "wsn";
    a[75] = "pvp";
    a[76] = "br-sat-mon";
    a[77] = "sun-nd";
    a[78] = "wb-mon";
    a[79] = "wb-expak";
    a[80] = "iso-ip";
    a[81] = "vmtp";
    a[82] = "secure-vmtp";
    a[83] = "vines";
    a[84] = "iptm";
    a[85] = "nsfnet-igp";
    a[86] = "dgp";
    a[87] = "tcf";
    a[88] = "eigrp";
    a[89] = "ospfigp";
    a[90] = "sprite-rpc";
    a[91] = "larp";
    a[92] = "mtp";
    a[93] = "ax.25";
    a[94] = "ipip";
    a[95] = "micp";
    a[96] = "scc-sp";
    a[97] = "etherip";
    a[98] = "encap";
    a[100] = "gmtp";
    a[101] = "ifmp";
    a[102] = "pnni";
    a[103] = "pim";
    a[104] = "aris";
    a[105] = "scps";
    a[106] = "qnx";
    a[107] = "a/n";
    a[108] = "ipcomp";
    a[109] = "snp";
    a[110] = "compaq-peer";
    a[111] = "ipx-in-ip";
    a[112] = "vrrp";
    a[113] = "pgm";
    a[115] = "l2tp";
    a[116] = "ddx";
    a[117] = "iatp";
    a[118] = "stp";
    a[119] = "srp";
    a[120] = "uti";
    a[121] = "smp";
    a[122] = "sm";
    a[123] = "ptp";
    a[124] = "isis-over-ipv4";
    a[125] = "fire";
    a[126] = "crtp";
    a[127] = "crudp";
    a[128] = "sscopmce";
    a[129] = "iplt";
    a[130] = "sps";
    a[131] = "pipe";
    a[132] = "sctp";
    a[133] = "fc";
    a[134] = "rsvp-e2e-ignore";
    a[135] = "mobility-header";
    a[136] = "udplite";
    a[137] = "mpls-in-ip";
    a[138] = "manet";
    a[139] = "hip";
    a[140] = "shim6";
    a[141] = "wesp";
    a[142] = "rohc";
    a[143] = "ethernet";
    a[144] = "aggfrag";
    a[145] = "nsh";
    a[146] = "homa";
    a[147] = "bit-emu";
    return a;
}

inline constexpr auto IANA_NUMBER_TO_PROTOCOL_NAME_TABLE = makeIanaByCode();

const std::unordered_map<std::string_view, uint8_t>& IANA_PROTOCOL_NAME_TO_NUMBER();

/**
 * @brief Convert a ipv4 string to a uint32_t
 *
 * @param ip String to be converted (format x.x.x.x)
 * @return uint32_t ipv4
 * @throws std::invalid_argument if the ip is not valid
 */
uint32_t IPv4ToUInt(const std::string& ip);

/**
 * @brief convert a mask IPv4 string to a uint32_t
 *
 * @param mask network mask format x.x.x.x or x (i.e. 255.0.0.0 its equivalent to 8)
 * @return uint32_t mask
 * @throws std::invalid_argument if the mask is not valid
 */
uint32_t IPv4MaskUInt(const std::string& mask);

// TODO: implement
/**
 * @brief Convert a ipv6 string to a uint128_t
 * @param ip String to be converted
 * @return uint128_t ipv6
 */
// uint128_t IPv6ToUInt(const std::string ip);

/**
 * @brief Check if a string is a valid IPv4 address
 *
 * @param ip String to be checked
 * @return true if the string is a valid IPv4 address
 * @return false if the string is not a valid IPv4 address
 */
bool checkStrIsIPv4(const std::string& ip, std::array<uint8_t, 4>* outBytes = nullptr);

/**
 * @brief Check if a string is a valid IPv6 address
 *
 * @param ip String to be checked
 * @return true if the string is a valid IPv6 address
 * @return false if the string is not a valid IPv6 address
 */
bool checkStrIsIPv6(const std::string& ip, std::array<uint8_t, 16>* outBytes = nullptr);

/**
 * @brief Check if a IPv4 is a special address
 *
 * A special IPv4 address can be a loopback address or a private address
 * @param ip
 * @return true if the ip is a special address
 * @throw std::invalid_argument if the ip is not valid
 */
bool isSpecialIPv4Address(const std::string& ip);

/**
 * @brief Checks if the given IPv6 address is a special address.
 *
 * A special IPv6 address can be:
 * - loopback address (::1/128)
 * - link-local address (fe80::/10),
 * - Unique Local Address (ULA) (fc00::/7).
 *
 * @param ip The IPv6 address to check.
 * @return True if the address is a special IPv6 address, false otherwise.
 * @throws std::invalid_argument If the given IP address is not a valid IPv6 address.
 */
bool isSpecialIPv6Address(const std::string& ip);

/**
 * @brief Normalize a candidate IANA protocol name to canonical lookup form:
 * - lower-case
 * - spaces/underscores replaced with '-'
 * - common aliases: "icmpv6"->"ipv6-icmp", "udp-lite"/"udp_lite" → "udplite", "ip-in-ip" → "ipip"
 */
std::string normalizeIanaProtocolName(std::string_view in);

/**
 * @brief Returns the IANA number for a given protocol name (strict: names only).
 * If the name is unknown (e.g., application-layer like "smtp"), returns std::nullopt.
 */
std::optional<uint8_t> ianaProtocolNameToNumber(std::string_view name);

/**
 * @brief Lookup the canonical IANA protocol keyword for a given code.
 * Returns std::nullopt if the code is unassigned/experimental/reserved or unknown.
 *
 * @param code IANA protocol number (0..255)
 * @return std::optional<std::string_view> Canonical keyword if found, std::nullopt otherwise.
 */
std::optional<std::string_view> ianaProtocolNumberToName(uint8_t code);

} // namespace utils::ip

#endif // _IP_UTILS_H
